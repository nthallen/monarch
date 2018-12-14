/** @file unix_name.cc */
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/un.h>
#include <sys/file.h>
#include <sys/types.h>
#include <signal.h>
#include <ctype.h>
#include "dasio/socket.h"
#include "dasio/appid.h"
#include "nl.h"

#ifndef UNIX_PATH_MAX
#define UNIX_PATH_MAX sizeof(((struct sockaddr_un *)0)->sun_path)
#endif

namespace DAS_IO {

Socket::unix_name_t::unix_name_t() {
  lock_fd = -1;
  lock_name = exp_name = svc_name = pid_name = 0;
  locked = false;
  server_claimed = false;
}

Socket::unix_name_t::~unix_name_t() {
  if (lock_fd >= 0) {
    ::close(lock_fd);
    lock_fd = -1;
  }
  if (lock_name) {
    free_memory((void*)lock_name);
    lock_name = 0;
  }
  if (exp_name) {
    free_memory((void*)exp_name);
    exp_name = 0;
  }
  if (svc_name) {
    free_memory((void*)svc_name);
    svc_name = 0;
  }
  if (pid_name) {
    free_memory((void*)pid_name);
    pid_name = 0;
  }
}

bool Socket::unix_name_t::is_word(const char *w, const char *context) {
  if (w == 0 || *w == '\0') {
    nl_error(2, "%s is empty", context);
    return false; // empty string
  }
  for (;*w != '\0'; ++w) {
    if (!std::isalnum(*w) && *w != '-' && *w != '_' && *w != '.') {
      nl_error(2, "%s contains invalid character(s)", context);
      return false;
    }
  }
  return true;
}

bool Socket::unix_name_t::set_service(const char *service) {
  if (exp_name) {
    nl_error(2, "Cannot call set_service() again after previous success");
    return false;
  }
  // Verify that company, Experiment and service are all valid words
  const char *Exp = AppID.Experiment;
  if (Exp == 0) {
    Exp = "none";
  }
  if (!is_word(company, "company") || !is_word(Exp, "Experiment")
      || !is_word(service, "service"))
    return false;
  int exp_len = snprintf(0, 0, "/var/run/%s/%s", company, Exp)+1;
  char *new_exp_name = (char *)new_memory(exp_len);
  snprintf(new_exp_name, exp_len, "/var/run/%s/%s", company, Exp);
  exp_name = new_exp_name;
  
  int svc_len = snprintf(0, 0, "%s/%s", exp_name, service)+1;
  char *new_svc_name = (char *)new_memory(svc_len);
  snprintf(new_svc_name, svc_len, "%s/%s", exp_name, service);
  svc_name = new_svc_name;

  if (svc_len > UNIX_PATH_MAX) {
    nl_error(2, "Service path exceeds UNIX_PATH_MAX");
    return false;
  }  
  return true;
}

const char *Socket::unix_name_t::get_svc_name() { return svc_name; }

bool Socket::unix_name_t::lock() {
  if (locked) return true;
  if (svc_name == 0 || exp_name == 0) {
    nl_error(2, "unix_name_t: Must call set_service() before lock()");
    return false;
  }
  int lock_len = ::snprintf(0, 0, "%s.lock", exp_name)+1;
  char *new_lock_name = (char *)new_memory(lock_len);
  snprintf(new_lock_name, lock_len, "%s.lock", exp_name);
  lock_name = new_lock_name;
  
  lock_fd = ::open(lock_name, O_CREAT|O_EXCL|O_WRONLY, 0660);
  if (lock_fd >= 0) {
    ::close(lock_fd);
  }
  lock_fd = ::open(lock_name, O_RDONLY);
  if (lock_fd < 0) {
    nl_error(2, "Unable to open lock file %s: %s", lock_name, strerror(errno));
    return false;
  }
  int rv = ::flock(lock_fd, LOCK_EX|LOCK_NB);
  if (rv == 0) {
    locked = true;
  } else if (errno != EWOULDBLOCK) {
    nl_error(2, "flock error: %s", strerror(errno));
  }
  return locked;
}

void Socket::unix_name_t::unlock() {
  if (!locked) return;
  int rv = ::flock(lock_fd, LOCK_UN|LOCK_NB);
  if (rv == 0) {
    locked = false;
  } else {
    nl_error(2, "flock returned error on unlock: %s", strerror(errno));
  }
  ::close(lock_fd);
  lock_fd = -1;
}

bool Socket::unix_name_t::is_locked() { return locked; }

bool Socket::unix_name_t::claim_server() {
  if (!locked) {
    nl_error(2, "Must lock() before claim_server()");
    return false;
  }
  if (mkdir(exp_name, 0660) && errno != EEXIST) {
    nl_error(2, "Unable to create %s dir: %s", exp_name, strerror(errno));
    return false;
    // if (errno == EEXIST) ==> not really an error
    // if (errno == EACCES) ==> don't have write permission
    // if (errno == ENOENT) ==> missing parent directory
    // if (errno == ENOTDIR) ==> parent directory not directory
  }
  
  int pid_len = snprintf(0, 0, "%s.pid", svc_name)+1;
  char *new_pid_name = (char *)new_memory(pid_len);
  snprintf(new_pid_name, pid_len, "%s.pid", svc_name);
  pid_name = new_pid_name;
  
  char pid_buf[80];
  
  int pid_fd = ::open(pid_name, O_RDONLY);
  if (pid_fd >= 0) {
    int nc = read(pid_fd, pid_buf, 80);
    ::close(pid_fd);
    pid_t pid = atoi(pid_buf);
    if (pid > 0) {
      int rv = kill(pid, 0);
      if (rv == 0) {
        nl_error(2, "Service %s in use by PID %d", svc_name, pid);
        unlock();
        return false;
      } else if (errno != ESRCH) {
        nl_error(2, "kill(pid,0) returned %s", strerror(errno));
        unlock();
        return false;
      }
    }
    unlink(pid_name);
  }
  
  FILE *pidf = fopen(pid_name, "w");
  if (pidf == 0) {
    nl_error(2, "Unable to write to %s", pid_name);
    return false;
  }
  fprintf(pidf, "%d\n", getpid());
  fclose(pidf);
  server_claimed = true;
  unlock();
  return true;
}

bool Socket::unix_name_t::is_server() { return server_claimed; }

void Socket::unix_name_t::release_server() {
  if (server_claimed) {
    if (unlink(svc_name)) {
      nl_error(1, "Error deleting socket %s: %s", svc_name, strerror(errno));
    }
    if (unlink(pid_name)) {
      nl_error(1, "Error deleting pid file %s: %s", pid_name, strerror(errno));
    }
    if (rmdir(exp_name) == 0) {
      unlink(lock_name);
    }
    server_claimed = false;
  }
}

} // end of namespace
