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
  char buffer[65536];

  struct timespec start, now;
  clock_gettime(CLOCK_MONOTONIC, &start);

  int counter = 0;

  while (1) {
    int buf_size = eventGenerator->genEvent(buffer);
    // int buf_size = 880;
    int res = server->smdSender->send(buffer, buf_size);
    counter++;

    if (counter == 10000) {
      clock_gettime(CLOCK_MONOTONIC, &now);
      uint64_t diff =
          BILLION * (now.tv_sec - start.tv_sec) + (now.tv_nsec - start.tv_nsec);
      double timedelta = diff * 1.0 / BILLION;
      double eventRate = counter / 1000 / timedelta; // kHz
      fprintf(stdout, "Time taken: %lf, evtrate: %lf kHz\n", timedelta,
              eventRate);
      fprintf(stderr, "BufSize: %d\n", buf_size);
      fprintf(stdout, "Throughput: %d MB/s\n", (int) (eventRate * buf_size / 1024.0));
      start = now;
      counter = 0;
    }
  }
}

void Application::vetoEventRecvWorker() {
  fprintf(stderr, "hey I'm trying to RECV...\n");
  char buf[65536];

  while (1) {
    int bytes_read = client->smdReceiver->listen(buf, 65536u);
  }
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

  eventGenerator = new EventGenerator();

  eventGenerator->genConfig(perm_buf);
}

Application::~Application() {
  delete serv;
  delete recv;
}

