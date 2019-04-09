#pragma once

#include "xtcdata/xtc/DescData.hh"
#include "xtcdata/xtc/Dgram.hh"
#include "xtcdata/xtc/NamesLookup.hh"
#include "xtcdata/xtc/ShapesData.hh"
#include "xtcdata/xtc/TypeId.hh"
#include "xtcdata/xtc/VarDef.hh"
#include "xtcdata/xtc/XtcIterator.hh"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/time.h>
#include <unistd.h>
#include <cstring>
#include <type_traits>
#include <vector>

#define BUFSIZE 0x4000000

class FexDef : public XtcData::VarDef {
 public:
  enum index {
    floatFex,
    arrayFex,
    intFex,
    charStrFex,
    enumFex1,
    enumFex1_HighGain,
    enumFex1_LowGain,
    enumFex2,
    enumFex3,
    enumFex3_On,
    enumFex3_Off,
  };

  FexDef();
};

class PgpDef : public XtcData::VarDef {
 public:
  enum index { floatPgp, array0Pgp, intPgp, array1Pgp };

  PgpDef();
};

class PadDef : public XtcData::VarDef {
 public:
  enum index { arrayRaw };

  PadDef();
};

class DebugIter : public XtcData::XtcIterator {
 public:
  enum { Stop, Continue };
  DebugIter(XtcData::Xtc* xtc, XtcData::NamesLookup& namesLookup)
      : XtcIterator(xtc), _namesLookup(namesLookup) {}

  void get_value(int i, XtcData::Name& name, XtcData::DescData& descdata);

  int process(XtcData::Xtc* xtc);

  XtcData::NamesLookup& _namesLookup;

  void printOffset(const char* str, void* base, void* ptr);
};

#pragma pack(push, 1)
class PgpData {
 public:
  void* operator new(size_t size, void* p) { return p; }

  PgpData(float f, int i1);

  double _fdata;
  float array[3][3];
  int64_t _idata;
  float array2[3][3];
};
#pragma pack(pop)

class PadData {
 public:
  void* operator new(size_t size, void* p) { return p; }
  PadData();
  uint16_t array[18];
};

class HsdConfigDef : public XtcData::VarDef {
 public:
  enum index { enable, raw_prescale };

  HsdConfigDef();
};

class EventGenerator {
 private:
  XtcData::NamesLookup m_namesLookup1;

  XtcData::Dgram& createTransition(void* buf,
                                   XtcData::TransitionId::Value transId);

  void pgpExample(XtcData::Xtc& parent, XtcData::NamesLookup& namesLookup,
                  XtcData::NamesId& namesId);

  void fexExample(XtcData::Xtc& parent, XtcData::NamesLookup& namesLookup,
                  XtcData::NamesId& namesId);

  void padExample(XtcData::Xtc& parent, XtcData::NamesLookup& namesLookup,
                  XtcData::NamesId& namesId);

  void addNames(XtcData::Xtc& xtc, XtcData::NamesLookup& namesLookup,
                unsigned& nodeId, unsigned segment);

  void addData(XtcData::Xtc& xtc, XtcData::NamesLookup& namesLookup,
               unsigned nodeId, unsigned segment);

 public:
  EventGenerator();

  void genConfig(void* buf);

  int genEvent(void* buf);

  int saveXtc(void* buf, FILE* xtcFile);
};
