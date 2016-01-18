#pragma once
#include <pebble.h>
#include "string.h"

#define LANG_SE 1
#define LANG_EN 2
#define LANG_NO 3

void time_to_words(int hours, int minutes, char* words, size_t length);

void time_to_greeting(int hour, char* greeting);

void set_language(uint8_t language);

void get_connection_lost_message(char* message);
