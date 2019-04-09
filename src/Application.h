#pragma once

#include <thread>

#include "DgramClient.h"
#include "DgramServer.h"
#include "EventGenerator.hh"

#define VETO_SMD_PORT "5000"
#define VETO_DECSN_PORT "5001"

class VetoEventServer {
 public:
  VetoEventServer(const char *ip);
  ~VetoEventServer();

 private:
  DgramServer *smdSender;
  DgramClient *vetoReceiver;
};

class VetoEventClient {
 public:
  VetoEventClient(const char *ip);
  ~VetoEventClient();

 private:
  DgramClient *smdReceiver;
  DgramServer *vetoGenerator;
};

class Application {
 public:
  Application();
  ~Application();
  void run();

 private:
  void vetoEventServeWorker();
  void vetoEventRecvWorker();
  std::thread *serv, *recv;
};
