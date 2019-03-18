#include "EventGenerator.hh"

FexDef::FexDef() {
    NameVec.push_back({"floatFex", XtcData::Name::DOUBLE});
    NameVec.push_back({"arrayFex", XtcData::Name::FLOAT, 2});
    NameVec.push_back({"intFex", XtcData::Name::INT64});
    NameVec.push_back({"charStrFex", XtcData::Name::CHARSTR, 1});
    // the enum dict requires ":EnumString" at the end of the name
    NameVec.push_back({"enumFex1:MyEnumName", XtcData::Name::ENUMVAL});
    NameVec.push_back({"HighGain:MyEnumName", XtcData::Name::ENUMDICT});
    NameVec.push_back({"LowGain:MyEnumName", XtcData::Name::ENUMDICT});
    // enumFex2 reuses the same dictionary as enumFex1
    NameVec.push_back({"enumFex2:MyEnumName", XtcData::Name::ENUMVAL});
    NameVec.push_back({"enumFex3:MyEnumName2", XtcData::Name::ENUMVAL});
    NameVec.push_back({"On:MyEnumName2", XtcData::Name::ENUMDICT});
    NameVec.push_back({"Off:MyEnumName2", XtcData::Name::ENUMDICT});
}

PgpDef::PgpDef() {
    NameVec.push_back({"floatPgp", XtcData::Name::DOUBLE, 0});
    NameVec.push_back({"array0Pgp", XtcData::Name::FLOAT, 2});
    NameVec.push_back({"intPgp", XtcData::Name::INT64, 0});
    NameVec.push_back({"array1Pgp", XtcData::Name::FLOAT, 2});
}

PadDef::PadDef() {
  XtcData::Alg segmentAlg("cspadseg", 2, 3, 42);
    NameVec.push_back({"arrayRaw", XtcData::Name::UINT16, 2, segmentAlg});
}

void DebugIter::get_value(int i, XtcData::Name& name, XtcData::DescData& descdata) {
    int data_rank = name.rank();
    int data_type = name.type();

    switch (name.type()) {
      case (0): {
        if (data_rank > 0) {
          XtcData::Array<uint8_t> arrT = descdata.get_array<uint8_t>(i);
          // printf("%s: %d, %d, %d\n",name.name(),arrT(0),arrT(1), arrT(2));
        } else {
          // printf("%s: %d\n",name.name(),descdata.get_value<uint8_t>(i));
        }
        break;
      }

      case (1): {
        if (data_rank > 0) {
          XtcData::Array<uint16_t> arrT = descdata.get_array<uint16_t>(i);
          // printf("%s: %d, %d, %d\n",name.name(),arrT(0),arrT(1), arrT(2));
        } else {
          // printf("%s: %d\n",name.name(),descdata.get_value<uint16_t>(i));
        }
        break;
      }

      case (2): {
        if (data_rank > 0) {
          XtcData::Array<uint32_t> arrT = descdata.get_array<uint32_t>(i);
          // printf("%s: %d, %d, %d\n",name.name(),arrT(0),arrT(1), arrT(2));
        } else {
          // printf("%s: %d\n",name.name(),descdata.get_value<uint32_t>(i));
        }
        break;
      }

      case (3): {
        if (data_rank > 0) {
          XtcData::Array<uint64_t> arrT = descdata.get_array<uint64_t>(i);
          // printf("%s: %d, %d, %d\n",name.name(),arrT(0),arrT(1), arrT(2));
        } else {
          // printf("%s: %d\n",name.name(),descdata.get_value<uint64_t>(i));
        }
        break;
      }

      case (4): {
        if (data_rank > 0) {
          XtcData::Array<int8_t> arrT = descdata.get_array<int8_t>(i);
          // printf("%s: %d, %d, %d\n",name.name(),arrT(0),arrT(1), arrT(2));
        } else {
          // printf("%s: %d\n",name.name(),descdata.get_value<int8_t>(i));
        }
        break;
      }

      case (5): {
        if (data_rank > 0) {
          XtcData::Array<int16_t> arrT = descdata.get_array<int16_t>(i);
          // printf("%s: %d, %d, %d\n",name.name(),arrT(0),arrT(1), arrT(2));
        } else {
          // printf("%s: %d\n",name.name(),descdata.get_value<int16_t>(i));
        }
        break;
      }

      case (6): {
        if (data_rank > 0) {
          XtcData::Array<int32_t> arrT = descdata.get_array<int32_t>(i);
          // printf("%s: %d, %d, %d\n",name.name(),arrT(0),arrT(1), arrT(2));
        } else {
          // printf("%s: %d\n",name.name(),descdata.get_value<int32_t>(i));
        }
        break;
      }

      case (7): {
        if (data_rank > 0) {
          XtcData::Array<int64_t> arrT = descdata.get_array<int64_t>(i);
          // printf("%s: %d, %d, %d\n",name.name(),arrT(0),arrT(1), arrT(2));
        } else {
          // printf("%s: %d\n",name.name(),descdata.get_value<int64_t>(i));
        }
        break;
      }

      case (8): {
        if (data_rank > 0) {
          XtcData::Array<float> arrT = descdata.get_array<float>(i);
          // printf("%s: %f, %f\n",name.name(),arrT(0),arrT(1));
        } else {
          // printf("%s: %f\n",name.name(),descdata.get_value<float>(i));
        }
        break;
      }

      case (9): {
        if (data_rank > 0) {
          XtcData::Array<double> arrT = descdata.get_array<double>(i);
          // printf("%s: %f, %f, %f\n",name.name(),arrT(0),arrT(1), arrT(2));
        } else {
          // printf("%s: %f\n",name.name(),descdata.get_value<double>(i));
        }
        break;
      }
    }
}

int DebugIter::process(XtcData::Xtc* xtc) {
    // printf("found typeid %s\n",XtcData::TypeId::name(xtc->contains.id()));
    switch (xtc->contains.id()) {
      case (XtcData::TypeId::Names): {
        // printf("Names pointer is %p\n", xtc);
        break;
      }
      case (XtcData::TypeId::Parent): {
        iterate(xtc);
        break;
      }
      case (XtcData::TypeId::ShapesData): {
                                            XtcData::ShapesData& shapesdata = *(XtcData::ShapesData*)xtc;
        // lookup the index of the names we are supposed to use
                                            XtcData::NamesId& namesId = shapesdata.namesId();
                                            XtcData::DescData descdata(shapesdata, _namesLookup[namesId]);
                                            XtcData::Names& names = descdata.nameindex().names();
        //   printf("Found %d names\n",names.num());
        // printf("data shapes extents %d %d %d\n", shapesdata.data().extent,
        // shapesdata.shapes().extent, sizeof(double));
        for (unsigned i = 0; i < names.num(); i++) {
          XtcData::Name& name = names.get(i);
          get_value(i, name, descdata);
        }
        break;
      }
      default:
        break;
    }
    return Continue;
}

void DebugIter::printOffset(const char* str, void* base, void* ptr) {
    printf("***%s at offset %li addr %p\n", str, (char*)ptr - (char*)base, ptr);
}

PgpData::PgpData(float f, int i1) {
    _fdata = f;
    _idata = i1;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        array[i][j] = i * j;
        array2[i][j] = i * j + 2;
      }
    }
}

PadData::PadData() {
    uint8_t counter = 0;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
          array[counter] = counter;
          counter++;
        }
      }
    }
}

HsdConfigDef::HsdConfigDef() {
    NameVec.push_back({"enable", XtcData::Name::UINT64, 1});
    NameVec.push_back({"raw_prescale", XtcData::Name::UINT64, 1});
}

void saveXtc(XtcData::Dgram& dg, FILE* xtcFile) {
  if (fwrite(&dg, sizeof(dg) + dg.xtc.sizeofPayload(), 1, xtcFile) != 1) {
    printf("Error writing to output xtc file.\n");
  }
}

XtcData::Dgram& EventGenerator::createTransition(XtcData::TransitionId::Value transId) {
  XtcData::TypeId tid(XtcData::TypeId::Parent, 0);
  uint64_t pulseId = 0;
  uint32_t env = 0;
  struct timeval tv;
  void* buf = malloc(BUFSIZE);
  gettimeofday(&tv, NULL);
  XtcData::Sequence seq(XtcData::Sequence::Event, transId, XtcData::TimeStamp(tv.tv_sec, tv.tv_usec),
               XtcData::PulseId(pulseId, 0));
  return *new (buf) XtcData::Dgram(XtcData::Transition(seq, env), XtcData::Xtc(tid));
}

void EventGenerator::pgpExample(XtcData::Xtc& parent, XtcData::NamesLookup& namesLookup,
                                XtcData::NamesId& namesId) {
  XtcData::DescribedData frontEnd(parent, namesLookup, namesId);

  // simulates PGP data arriving, and shows the address that should be given
  // to PGP driver we should perhaps worry about DMA alignment issues if in
  // the future we avoid the pgp driver copy into user-space.
  new (frontEnd.data()) PgpData(1, 2);

  // now that data has arrived update with the number of bytes received
  // it is required to call this before set_array_shape
  // printf("sizeof pgpdata %d\n",sizeof(PgpData));
  frontEnd.set_data_length(sizeof(PgpData));

  unsigned shape[] = {3, 3};
  frontEnd.set_array_shape(PgpDef::array0Pgp, shape);
  frontEnd.set_array_shape(PgpDef::array1Pgp, shape);
}

void EventGenerator::fexExample(XtcData::Xtc& parent, XtcData::NamesLookup& namesLookup,
                                XtcData::NamesId& namesId) {
  XtcData::CreateData fex(parent, namesLookup, namesId);
  fex.set_value(FexDef::floatFex, (double)41.0);

  unsigned shape[XtcData::MaxRank] = {2, 3};
  XtcData::Array<float> arrayT = fex.allocate<float>(FexDef::arrayFex, shape);
  for (unsigned i = 0; i < shape[0]; i++) {
    for (unsigned j = 0; j < shape[1]; j++) {
      arrayT(i, j) = 142.0 + i * shape[1] + j;
    }
  };

  fex.set_value(FexDef::intFex, (int64_t)42);

  fex.set_string(FexDef::charStrFex, "Test String");

  fex.set_value(FexDef::enumFex1, (int32_t)-2);
  fex.set_value(FexDef::enumFex1_HighGain, (int32_t)-2);
  fex.set_value(FexDef::enumFex1_LowGain, (int32_t)5);
  fex.set_value(FexDef::enumFex2, (int32_t)5);
  fex.set_value(FexDef::enumFex3, (int32_t)12);
  fex.set_value(FexDef::enumFex3_On, (int32_t)-7);
  fex.set_value(FexDef::enumFex3_Off, (int32_t)12);
}

void EventGenerator::padExample(XtcData::Xtc& parent, XtcData::NamesLookup& namesLookup,
                                XtcData::NamesId& namesId) {
  XtcData::DescribedData pad(parent, namesLookup, namesId);

  // simulates PGP data arriving, and shows the address that should be given
  // to PGP driver we should perhaps worry about DMA alignment issues if in
  // the future we avoid the pgp driver copy into user-space.
  new (pad.data()) PadData();

  // now that data has arrived update with the number of bytes received
  // it is required to call this before set_array_shape
  pad.set_data_length(sizeof(PadData));

  unsigned shape[XtcData::MaxRank] = {3, 6};
  pad.set_array_shape(PadDef::arrayRaw, shape);
}

void EventGenerator::addNames(XtcData::Xtc& xtc, XtcData::NamesLookup& namesLookup, unsigned& nodeId, unsigned segment) {
  XtcData::Alg hsdRawAlg("raw", 0, 0, 0);
  XtcData::NamesId namesId0(nodeId, 0 + 10 * segment);
  XtcData::Names& frontEndNames = *new (xtc) XtcData::Names("xpphsd", hsdRawAlg, "hsd",
                                          "detnum1234", namesId0, segment);
  frontEndNames.add(xtc, PgpDef);
  namesLookup[namesId0] = XtcData::NameIndex(frontEndNames);

  XtcData::Alg hsdFexAlg("fex", 4, 5, 6);
  XtcData::NamesId namesId1(nodeId, 1 + 10 * segment);
  XtcData::Names& fexNames = *new (xtc) XtcData::Names("xpphsd", hsdFexAlg, "hsd", "detnum1234",
                                     namesId1, segment);
  fexNames.add(xtc, FexDef);
  namesLookup[namesId1] = XtcData::NameIndex(fexNames);

  XtcData::Alg cspadRawAlg("raw", 2, 3, 42);
  XtcData::NamesId namesId2(nodeId, 2 + 10 * segment);
  XtcData::Names& padNames = *new (xtc) XtcData::Names("xppcspad", cspadRawAlg, "cspad",
                                     "detnum1234", namesId2, segment);
  XtcData::Alg segmentAlg("cspadseg", 2, 3, 42);
  padNames.add(xtc, PadDef);
  namesLookup[namesId2] = XtcData::NameIndex(padNames);
}

void EventGenerator::addData(XtcData::Xtc& xtc, XtcData::NamesLookup& namesLookup,
                             unsigned nodeId, unsigned segment) {
  XtcData::NamesId namesId0(nodeId, 0 + 10 * segment);
  pgpExample(xtc, namesLookup, namesId0);
  XtcData::NamesId namesId1(nodeId, 1 + 10 * segment);
  fexExample(xtc, namesLookup, namesId1);
  XtcData::NamesId namesId2(nodeId, 2 + 10 * segment);
  padExample(xtc, namesLookup, namesId2);
}

EventGenerator::EventGenerator() {}

void EventGenerator::genConfig() {
  XtcData::Dgram& config = createTransition(XtcData::TransitionId::Configure);

  unsigned nodeid1 = 1;
  unsigned nSegments = 2;

  for (unsigned iseg = 0; iseg < nSegments; iseg++) {
    addNames(config.xtc, m_namesLookup1, nodeid1, iseg);
    addData(config.xtc, m_namesLookup1, nodeid1, iseg);
  }

  // save configXtc
}
// TODO buf - receive from user
// TODO config - decide how to emit
// TODO partition - decide how to join multiple
void EventGenerator::genEvent(void* buf) {
  struct timeval tv;
  XtcData::TypeId tid(XtcData::TypeId::Parent, 0);
  uint32_t env = 0;
  uint64_t pulseId = 0;

  unsigned nodeid1 = 1;
  unsigned nSegments = 2;

  gettimeofday(&tv, NULL);
  XtcData::Sequence seq(XtcData::Sequence::Event, XtcData::TransitionId::L1Accept,
               XtcData::TimeStamp(tv.tv_sec, tv.tv_usec), XtcData::PulseId(pulseId, 0));
  XtcData::Dgram& dgram = *new (buf) XtcData::Dgram(XtcData::Transition(seq, env), XtcData::Xtc(tid));

  for (unsigned iseg = 0; iseg < nSegments; iseg++) {
    addData(dgram.xtc, m_namesLookup1, nodeid1, iseg);
  }
};
