// Norska, bokmål
#include "lang-norwegian.h"

const char* const HOURS_NO[] = {
  "ett",
  "to",
  "tre",
  "fire",
  "fem",
  "seks",
  "sju",
  "åtte",
  "ni",
  "ti",
  "elleve",
  "tolv"
};

const char* const PHRASES_NO[] = {
  "*$1 ",
  "fem over *$1 ",
  "ti over *$1 ",
  "kvart over *$1 ",
  "ti på halv *$2 ",
  "fem på halv *$2 ",
  "halv *$2 ",
  "fem over halv *$2 ",
  "ti over halv *$2 ",
  "kvart på *$2 ",
  "ti på *$2 ",
  "fem på *$2 "
};

#ifdef PBL_PLATFORM_CHALK
  const char* const GREETINGS_NO[] = {
    "God morgen ",
    "God dag ",
    "God kveld ",
    "God natt "
  };
#else
  const char* const GREETINGS_NO[] = {
    "God mor- gen ",
    "God  dag ",
    "God kveld ",
    "God natt "
  };
#endif

const char* const CONNECTION_LOST_NO = "Hvor er tele- fonen din? ";
