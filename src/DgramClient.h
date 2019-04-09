#pragma once

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

class DgramClient {
 public:
  DgramClient(const char *host, const char *port);
  void _createSocket();
  ~DgramClient();
  int send(void *buf, size_t bytes);
  private:
  int sockfd;
  struct addrinfo *servinfo;
  struct addrinfo *servinfo_list;
};
