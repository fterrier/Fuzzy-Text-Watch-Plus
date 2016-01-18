#include "num2words.h"
#include "string.h"
#include <stdio.h>

#include "lang-swedish.h"
#include "lang-english.h"
#include "lang-norwegian.h"
#include "lang-dutch.h"

static uint8_t language = LANG_EN;

void set_language(uint8_t lang) {
  language = lang;
}

const char* getHourWord(int hour) {
  int pos = (hour + 11) % 12; // + 11 instead of - 1 to avoid negative result

  switch (language) {
    case LANG_SE:
      return HOURS_SE[pos];

    case LANG_EN:
      return HOURS_EN[pos];

    case LANG_NO:
      return HOURS_NO[pos];

    case LANG_NL:
      return HOURS_NL[pos];
  }

  return HOURS_EN[pos];
}

const char* getFiveMinutePhrase(int fiveMinutePeriod) {
  switch (language) {
    case LANG_SE:
      return PHRASES_SE[fiveMinutePeriod];

    case LANG_EN:
      return PHRASES_EN[fiveMinutePeriod];

    case LANG_NO:
      return PHRASES_NO[fiveMinutePeriod];

    case LANG_NL:
      return PHRASES_NL[fiveMinutePeriod];
  }

  return PHRASES_EN[fiveMinutePeriod];

}

void time_to_words(int hours, int minutes, char* words, size_t length) {

  memset(words, 0, length);

  // Fuzzy time
  int fiveMinutePeriod = (minutes / 5) % 12;
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
    // Substitute '$x' with '%s'
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

    case LANG_NL:
      strcpy(greeting, GREETINGS_NL[pos]);
      break;

    default:
      strcpy(greeting, GREETINGS_SE[pos]);
  }
}
