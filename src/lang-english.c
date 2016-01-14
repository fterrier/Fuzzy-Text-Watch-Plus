#include "lang-english.h"

const char* const HOURS_EN[] = {
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "eight",
  "nine",
  "ten",
  "eleven",
  "twelve"
};

const char* const PHRASES_EN[] = {
  "*$1 o'clock ",
  "five past *$1 ",
  "ten past *$1 ",
  "quarter past *$1 ",
  "twenty past *$1 ",
  "twenty five past *$1 ",
  "half past *$1 ",
  "twenty five to *$2 ",
  "twenty to *$2 ",
  "quarter to *$2 ",
  "ten to *$2 ",
  "five to *$2 "
};

#ifdef PBL_PLATFORM_CHALK
  const char* const GREETINGS_EN[] = {
    "Good morning ",
    "Good day ",
    "Good evening ",
    "Good night "
  };
#else
  const char* const GREETINGS_EN[] = {
    "Good mor- ning ",
    "Good day ",
    "Good even- ing ",
    "Good night "
  };
#endif
