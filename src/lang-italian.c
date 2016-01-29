#include "num2words.h"

const Language LANG_ITALIAN = {

  .hours = {
    "una",
    "due",
    "tre",
    "quattro",
    "cinque",
    "sei",
    "sette",
    "otto",
    "nove",
    "dieci",
    "undici",
    "dodici"
  },

  .phrases = {
    "*$1 in punto ",
    "*$1 e cinque ",
    "*$1 e dieci ",
    "*$1 e un quarto ",
    "*$1 e venti ",
    "*$1 e venti- cinque ",
    "*$1 e mezza ",
    "*$2 e trenta- cinque ",
    "*$2 meno venti ",
    "*$2 meno  un quarto ",
    "*$2 meno dieci ",
    "*$2 meno cinque "
  },

  .greetings = {
    "Buona matti- nata ",
    "Buon- giorno ",
    "Buona sera ",
    "Buona notte "
  },

  .connection_lost = "Dov'è il tuo telefono? "

};
