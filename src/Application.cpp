#include "Application.h"

VetoEventServer::VetoEventServer(const char *ip) {
  vetoReceiver = new DgramServer(VETO_DECSN_PORT);
  smdSender = new DgramClient(ip, VETO_SMD_PORT);
}

VetoEventServer::~VetoEventServer() {
  delete smdSender;
  delete vetoReceiver;
}

VetoEventClient::VetoEventClient(const char *ip) {
  vetoGenerator = new DgramClient(ip, VETO_DECSN_PORT);
  smdReceiver = new DgramServer(VETO_SMD_PORT);
}

VetoEventClient::~VetoEventClient() {
  delete smdReceiver;
  delete vetoGenerator;
}

void Application::vetoEventServeWorker() {
  fprintf(stderr, "hey I'm trying to SERV...\n");
  char buffer[10];
  strcpy(buffer, "hello");
  server->smdSender->send(buffer, 5);
}

void Application::vetoEventRecvWorker() {
  fprintf(stderr, "hey I'm trying to RECV...\n");
  char buf[1024];
  int bytes = client->smdReceiver->listen(buf, 1024);
  buf[bytes] = '\0';

  fprintf(stdout, "hey I'm received: %s\n", buf);
}

void Application::run() {
  fprintf(stderr, "hey I'm trying to run...\n");
  serv = new std::thread(&Application::vetoEventServeWorker, this);
  recv = new std::thread(&Application::vetoEventRecvWorker, this);
  serv->join();
  recv->join();
}

Application::Application(const char *ip) {
  server = new VetoEventServer(ip);
  client = new VetoEventClient(ip);
}

Application::~Application() {
  delete serv;
  delete recv;
}

