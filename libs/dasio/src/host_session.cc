#include "dasio/host_session.h"
#include "nl.h"
#include "nl_assert.h"

namespace DAS_IO {

hs_registry *hs_registry::instance;

hs_registry *hs_registry::instantiate() {
  if (instance == 0)
    instance = new hs_registry();
  return instance;
}

void hs_registry::add_host(const char *spec) {
  hs_registry *reg = instantiate();
  reg->add_spec(true, spec);
}

void hs_registry::add_session(const char *spec) {
  hs_registry *reg = instantiate();
  reg->add_spec(false, spec);
}

void hs_registry::add_spec(bool host, const char *spec) {
  std::map<std::string,std::string> *reg =
    host ? &host_reg : &socket_reg;

  split_arg(spec);
  std::string s1 = func_arg;
  std::string s2 = hs_arg;
  if (!reg->insert(std::pair<std::string,std::string>(s1,s2)).second) {
    std::map<std::string,std::string>::iterator pos;
    pos = reg->find(s1);
    nl_assert(pos != reg->end());
    reg->erase(pos);
    if (!reg->insert(std::pair<std::string,std::string>(s1,s2)).second) {
      msg(MSG_FATAL,
        "Redefinition of %s spec for function '%s' failed",
        host ? "host" : "socket", func_arg);
    }
  }
}

const char *hs_registry::query_host(const char *func) {
  hs_registry *reg = instantiate();
  return reg->query(true, func);
}

const char *hs_registry::query_session(const char *func) {
  hs_registry *reg = instantiate();
  return reg->query(false, func);
}

const char *hs_registry::query(bool host, const char *func) {
  std::map<std::string,std::string>::iterator pos;
  std::map<std::string,std::string> *reg =
    host ? &host_reg : &socket_reg;
  
  pos = reg->find(func);
  if (pos == reg->end()) {
    pos = reg->find("");
    if (pos == reg->end())
      return 0;
  }
  return pos->second.c_str();
}

bool hs_registry::split_arg(const char *arg) {
  int i, j;
  for (i=0; i < max_strlen && arg[i] && arg[i] != ':'; ++i) {
    func_arg[i] = arg[i];
  }
  if (i >= max_strlen) {
    msg(MSG_FATAL, "Invalid host/socket spec '%s': func too long",
      arg);
    return false;
  } else if (arg[i] != ':') {
    msg(MSG_FATAL, "Invalid host/socket spec '%s': missing colon",
      arg);
    return false;
  }
  func_arg[i++] = '\0';
  for (j = 0; j < max_strlen && arg[i+j]; ++j) {
    hs_arg[j] = arg[i+j];
  }
  if (j >= max_strlen) {
    msg(MSG_FATAL, "Invalid host/socket spec '%s': string too long",
      arg);
    return false;
  }
  hs_arg[j] = '\0';
  return true;
}

}
