#include "num2words.h"

// Translations by Andrea Riosa

const Language LANG_ITALIAN = {

  .hours = {
    "una",
    "due",
    "tre",
#ifdef PBL_PLATFORM_CHALK
    "quattro",
#else
    "<quattro",
#endif
    "cinque",
    "sei",
    "sette",
    "otto",
    "nove",
    "dieci",
    "undici",
    "dodici"
  },

#ifdef PBL_PLATFORM_CHALK
  .phrases = {
    "*$1 in punto ",
    "*$1 e cinque ",
    "*$1 e dieci ",
    "*$1 e un quarto ",
    "*$1 e venti ",
    "*$1 e venti- cinque ",
    "*$1 e mezza ",
    "*$1 e trenta- cinque ",
    "*$2 meno venti ",
    "*$2 meno un quarto ",
    "*$2 meno dieci ",
    "*$2 meno cinque "
  },
#else
  .phrases = {
    "*$1 in  punto ",
    "*$1 e  cinque ",
    "*$1 e dieci ",
    "*$1 e un quarto ",
    "*$1 e venti ",
    "*$1 e venti- cinque ",
    "*$1 e  mezza ",
    "*$1 e  trenta- cinque ",
    "*$2 meno venti ",
    "*$2 meno  un  quarto ",
    "*$2 meno dieci ",
    "*$2 meno cinque "
  },
#endif

  .greetings = {
    "Buona matti- nata ",
    "Buon- giorno ",
    "Buona sera ",
    "Buona notte "
  },

#ifdef PBL_PLATFORM_CHALK
  .connection_lost = "Dov'è il tuo tele- fono? "
#else
  .connection_lost = "Dov'è il tuo  tele- fono? "
#endif

};
