#pragma once

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

class DgramServer {
 public:
  DgramServer(const char *port);

  ~DgramServer();

  void createSocket();

  /* Max UDP datagram = 65507 approx
   * Recommended max_bytes = 2**16
   */
  int listen(void *buf, size_t max_bytes);

 private:
  struct addrinfo *servinfo;

  int sockfd;

  void *get_in_addr(struct sockaddr *sa);
};
