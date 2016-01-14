#include "num2words-en.h"
#include "string.h"
#include <stdio.h>

#include "lang-swedish.h"
#include "lang-english.h"
#include "lang-norwegian.h"

static short language = LANG_NO;

const char* getHourWord(int hour) {
  int pos = (hour - 1) % 12;

  switch (language) {
    case LANG_SE:
      return HOURS_SE[pos];

    case LANG_EN:
      return HOURS_EN[pos];

    case LANG_NO:
      return HOURS_NO[pos];
  }

  return HOURS_SE[pos];
}

const char* getFiveMinutePhrase(int fiveMinutePeriod) {
  switch (language) {
    case LANG_SE:
      return PHRASES_SE[fiveMinutePeriod];

    case LANG_EN:
      return PHRASES_EN[fiveMinutePeriod];

    case LANG_NO:
      return PHRASES_NO[fiveMinutePeriod];
  }

  return PHRASES_SE[fiveMinutePeriod];

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
  int pos;

  if (hour < 5 || hour >= 22) {
    pos = 3; // night greeting
  } else if (hour < 11) {
    pos = 0; // morning greeting
  } else if (hour < 17) {
    pos = 1; // day greeting
  } else {
    pos = 2; // evening greeting
  }

  pos = 0;

  switch (language) {
    case LANG_SE:
      strcpy(greeting, GREETINGS_SE[pos]);
      break;

    case LANG_EN:
      strcpy(greeting, GREETINGS_EN[pos]);
      break;
    
    case LANG_NO:
      strcpy(greeting, GREETINGS_NO[pos]);
      break;

    default:
      strcpy(greeting, GREETINGS_SE[pos]);
  }
}
