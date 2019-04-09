#include "Application.h"

VetoEventServer::VetoEventServer(const char *ip) {
  smdSender = new DgramServer(VETO_SMD_PORT);
  vetoReceiver = new DgramClient(ip, VETO_DECSN_PORT);
}

VetoEventServer::~VetoEventServer() {
  delete smdSender;
  delete vetoReceiver;
}

VetoEventClient::VetoEventClient(const char *ip) {
  smdReceiver = new DgramClient(ip, VETO_SMD_PORT);
  vetoGenerator = new DgramServer(VETO_SMD_PORT);
}

VetoEventClient::~VetoEventClient() {
  delete smdReceiver;
  delete vetoGenerator;
}

void Application::vetoEventServeWorker() {
  fprintf(stderr, "hey I'm trying to SERV...\n");
}

void Application::vetoEventRecvWorker() {
  fprintf(stderr, "hey I'm trying to RECV...\n");
}

void Application::run() {
  fprintf(stderr, "hey I'm trying to run...\n");
  serv = new std::thread(&Application::vetoEventServeWorker, this);
  recv = new std::thread(&Application::vetoEventRecvWorker, this);
  serv->join();
  recv->join();
}

Application::Application() {
}

Application::~Application() {
  delete serv;
  delete recv;
}

