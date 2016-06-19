#include "num2words.h"

// Translation by David Ortmann

const Language LANG_GERMAN_E = {
  .hours = {
    "eins",
    "zwei",
    "drei",
    "vier",
    "fünf",
    "sechs",
    "sieben",
    "acht",
    "neun",
    "zehn",
    "elf",
    "zwölf"
  },

#ifdef PBL_PLATFORM_CHALK
  .phrases = {
    "*$1 uhr ",
    "fünf nach *$1 ",
    "zehn  nach *$1 ",
    "viertel *$2 ",
    "zwanzig nach *$1 ",
    "fünf vor halb *$2 ",
    "halb *$2 ",
    "fünf  nach halb *$2 ",
    "zwanzig vor *$2 ",
    "drei- viertel *$2 ",
    "zehn vor *$2 ",
    "fünf vor *$2 "
  },

  .greetings = {
    "Guten Morgen ",
    "Guten  Tag ",
    "Guten Abend ",
    "Gute Nacht "
  },
#else
  .phrases = {
    "*$1 uhr ",
    "fünf  nach *$1 ",
    "zehn  nach *$1 ",
    "viertel *$2 ",
    "zwan-  zig  nach *$1 ",
    "fünf vor halb *$2 ",
    "halb *$2 ",
    "fünf  nach  halb *$2 ",
    "zwan-  zig vor *$2 ",
    "drei- viertel *$2 ",
    "zehn  vor *$2 ",
    "fünf  vor *$2 "
  },

  .greetings = {
    "Guten Morgen ",
    "Guten  Tag ",
    "Guten Abend ",
    "Gute Nacht "
  },
#endif

  .connection_lost = "Wo ist dein Handy? "
};