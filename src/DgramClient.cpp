#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdexcept>

#include "DgramClient.h"

DgramClient::DgramClient(const char *host, const char *port) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;

  int rv;
  rv = getaddrinfo(host, port, &hints, &servinfo_list);
  if (rv) {
    fprintf(stderr, "client getaddrinfo: %s\n", gai_strerror(rv));
    throw std::runtime_error("client getaddrinfo failed");
  }

  this->_createSocket();
}

void DgramClient::_createSocket() {
  for (servinfo = servinfo_list; servinfo != NULL;
       servinfo = servinfo_list->ai_next) {
    if ((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype,
                         servinfo->ai_protocol)) == -1) {
      perror("talker: socket");
      continue;
    }

    break;
  }

  if (servinfo == NULL) {
    throw std::runtime_error("socket creation failed");
  }
}

DgramClient::~DgramClient() {
  close(sockfd);
  freeaddrinfo(servinfo_list);
}

int DgramClient::send(void *buf, size_t bytes) {
  int bytes_sent =
      sendto(sockfd, buf, bytes, 0, servinfo->ai_addr, servinfo->ai_addrlen);

  if (bytes_sent == -1) {
    std::runtime_error("unable to sendto");
  }

  return bytes_sent;
}
