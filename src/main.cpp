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
