#include <stdio.h>
#include <thread>

#include "DgramClient.h"
#include "DgramServer.h"
#include "EventGenerator.hh"

// using namespace XtcData;
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

VetoEventServer::VetoEventServer(const char *ip) {
  smdSender = new DgramServer(VETO_SMD_PORT);
  vetoReceiver = new DgramClient(ip, VETO_DECSN_PORT);
}

VetoEventServer::~VetoEventServer() {
  delete smdSender;
  delete vetoReceiver;
}

class VetoEventClient {
 public:
  VetoEventClient(const char *ip);
  ~VetoEventClient();

 private:
  DgramClient *smdReceiver;
  DgramServer *vetoGenerator;
};

VetoEventClient::VetoEventClient(const char *ip) {
  smdReceiver = new DgramClient(ip, VETO_SMD_PORT);
  vetoGenerator = new DgramServer(VETO_SMD_PORT);
}

VetoEventClient::~VetoEventClient() {
  delete smdReceiver;
  delete vetoGenerator;
}

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

Application::Application() {
}
Application::~Application() {
  delete serv;
  delete recv;
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

int main() {
  Application a;
  a.run();
  // TypeId tid(TypeId::Parent, 0);
  // printf("hello world: %d\n", tid.version());
  // AnotherClass a(5);
  // ******** last working evtgen ********
  // printf("hello world: %d\n", 5);
  // void *buf = malloc(0x400000);
  // FILE *f = fopen("lol.xtc", "wb+");
  // EventGenerator e;

  // e.genConfig(buf);
  // e.saveXtc(buf, f);

  // e.genEvent(buf);
  // e.saveXtc(buf, f);

  // e.genEvent(buf);
  // e.saveXtc(buf, f);

  // fclose(f);
  // free(buf);
  // ******** last working evtgen ********
}

// int main() {
// DgramServer d("4950");
// char c[1024];
// memset(c, 0, 1024);
// d.listen(c, 1024u);
// printf("%s\n", c);
// return 0;
// }

// int main(int argc, char *argv[]) {
// DgramClient c("10.92.3.24", "4950");
// c.send(argv[1], strlen(argv[1]));
// }
