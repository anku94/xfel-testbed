#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdexcept>

#include "DgramServer.h"

DgramServer::DgramServer(const char *port) {
  int rv;

  struct addrinfo hints;
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;

  rv = getaddrinfo(NULL, port, &hints, &servinfo);
  if (rv) {
    fprintf(stderr, "DgramServer - getattrinfo failed\n");
    throw std::runtime_error("server getaddrinfo failed");
  }

  this->createSocket();
}

DgramServer::~DgramServer() {
  close(sockfd);
  freeaddrinfo(servinfo);
}

void DgramServer::createSocket() {
  struct addrinfo *p;
  for (p = servinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
      perror("server: socket");
    }

    if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      perror("listener: bind");
    }

    break;
  }
}

/* Max UDP datagram = 65507 approx
 * Recommended max_bytes = 2**16
 */
int DgramServer::listen(void *buf, size_t max_bytes) {
  char ip_str[INET6_ADDRSTRLEN];

  struct sockaddr_storage their_addr;
  socklen_t addr_len = sizeof their_addr;

  int bytes_read = 0;

  bytes_read = recvfrom(sockfd, buf, max_bytes, 0,
                        (struct sockaddr *)&their_addr, &addr_len);

  if (bytes_read == -1) {
    perror("server: recvfrom");
    return bytes_read;
  }

  // printf("listener: got packet from %s\n",
         // inet_ntop(their_addr.ss_family,
                   // get_in_addr((struct sockaddr *)&their_addr), ip_str,
                   // sizeof ip_str));

  return bytes_read;
}

void *DgramServer::get_in_addr(struct sockaddr *sa) {
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in *)sa)->sin_addr);
  }

  return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}
