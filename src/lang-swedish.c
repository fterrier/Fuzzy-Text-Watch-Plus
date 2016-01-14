#include "lang-swedish.h"

const char* const HOURS_SE[] = {
  "ett",
  "två",
  "tre",
  "fyra",
  "fem",
  "sex",
  "sju",
  "åtta",
  "nio",
  "tio",
  "elva",
  "tolv"
};

const char* const PHRASES_SE[] = {
  "klockan är *$1 ",
  "fem över *$1 ",
  "tio över *$1 ",
  "kvart över *$1 ",
  "tjugo över *$1 ",
  "fem i halv *$2 ",
  "halv *$2 ",
  "fem över halv *$2 ",
  "tjugo i *$2 ",
  "kvart i *$2 ",
  "tio i *$2 ",
  "fem i *$2 "
};

#ifdef PBL_PLATFORM_CHALK
  const char* const GREETINGS_SE[] = {
    "God morgon ",
    "God dag ",
    "God afton ",
    "God natt "
  };
#else
  const char* const GREETINGS_SE[] = {
    "God mor- gon ",
    "God  dag ",
    "God afton ",
    "God natt "
  };
#endif
