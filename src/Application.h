#pragma once

#include <thread>

#include "DgramClient.h"
#include "DgramServer.h"
#include "EventGenerator.hh"

#define VETO_SMD_PORT "5002"
#define VETO_DECSN_PORT "5003"

#define UDP_MAX 65536
#define BILLION 1000000000L


class VetoEventServer {
 public:
  VetoEventServer(const char *ip);
  ~VetoEventServer();

  DgramClient *smdSender;
  DgramServer *vetoReceiver;
};

class VetoEventClient {
 public:
  VetoEventClient(const char *ip);
  ~VetoEventClient();

  DgramServer *smdReceiver;
  DgramClient *vetoGenerator;
};

class Application {
 public:
  Application(const char *ip);
  ~Application();
  void run();

 private:
  EventGenerator *eventGenerator;

  void vetoEventServeWorker();
  void vetoEventRecvWorker();

  std::thread *serv, *recv;

  VetoEventServer *server;
  VetoEventClient *client;

  // char perm_buf[UDP_MAX];
  char perm_buf[4194304];
};
