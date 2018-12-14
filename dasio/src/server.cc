/** @file server.cc */
#include "dasio/server.h"

namespace DAS_IO {

  SubServices::SubServices() {}
  SubServices::~SubServices() {}
  
  bool SubServices::add_subservice(const char *subservice, socket_clone_t func) {
    std::pair<std::map<std::string,socket_clone_t>::iterator,bool> ret;
    ret = subs.insert( std::pair<std::string,socket_clone_t>(subservice, func));
    return ret.second;
  }
  
  socket_clone_t SubServices::find_subservice(const char *subservice) {
    std::map<std::string,socket_clone_t>::iterator pos;
    
    pos = subs.find(subservice);
    return (pos == subs.end()) ? 0 : pos->second;
  }

  //Server::Server
}
