#include "num2words-en.h"
#include "string.h"
#include <stdio.h>

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


const char* getHourWord(int hour) {
  return HOURS_SE[(hour - 1) % 12];
}

const char* getFiveMinutePhrase(int fiveMinutePeriod) {
  return PHRASES_SE[fiveMinutePeriod % 12];
}

void time_to_words(int hours, int minutes, char* words, size_t length) {

  memset(words, 0, length);

  // Fuzzy time
  int fiveMinutePeriod = ((minutes + 3) / 5) % 12;
  char phrase[length]; 
  strcpy(phrase, getFiveMinutePhrase(fiveMinutePeriod));
 
  char *variable = NULL;
  const char *hour;

  if ((variable = strstr(phrase, "$1")) != NULL) {
    hour = getHourWord(hours);
  }
  else if ((variable = strstr(phrase, "$2")) != NULL) {
    hour = getHourWord(hours + 1);
  }

  if (variable != NULL) {
    *variable = '%';
    *(variable + 1) = 's';
    snprintf(words, length, phrase, hour);
  } else {
    strncpy(words, phrase, length);
  }

}

void time_to_greeting(int hour, char* greeting)
{
  if (hour < 5 || hour >= 22) {
    strcpy(greeting, "God natt ");
  } else if (hour < 11) {
#ifdef PBL_PLATFORM_CHALK
    strcpy(greeting, "God morgon ");
#else
    strcpy(greeting, "God mor- gon ");
#endif
  } else if (hour < 17) {
#ifdef PBL_PLATFORM_CHALK
    strcpy(greeting, "God dag ");
#else
    strcpy(greeting, "God  dag ");
#endif
  } else {
    strcpy(greeting, "God afton ");
  }
}
