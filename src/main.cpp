#include <stdio.h>
#include "EventGenerator.hh"

// using namespace XtcData;

int main() {
  // TypeId tid(TypeId::Parent, 0);
  // printf("hello world: %d\n", tid.version());
  // AnotherClass a(5);
  printf("hello world: %d\n", 5);
  void *buf = malloc(0x400000);
  FILE *f  = fopen("lol.xtc", "wb+");
  EventGenerator e;

  e.genConfig(buf);
  e.saveXtc(buf, f);

  e.genEvent(buf);
  e.saveXtc(buf, f);

  e.genEvent(buf);
  e.saveXtc(buf, f);

  fclose(f);
  free(buf);
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
