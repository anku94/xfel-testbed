#include <stdio.h>
#include "xtcdata/xtc/TypeId.hh"

using namespace XtcData;

int main() {
  TypeId tid(TypeId::Parent, 0);
  printf("hello world: %d\n", tid.version());
}
