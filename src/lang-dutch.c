#include "num2words.h"

// Language strings for Dutch
const Language LANG_DUTCH = {
	.hours = {
		"een",
		"twee",
		"drie",
		"vier",
		"vijf",
		"zes",
		"zeven",
		"acht",
		"negen",
		"tien",
		"elf",
		"twaalf"
	},

	.phrases = {
		"*$1 uur ",
		"vijf over *$1 ",
		"tien over *$1 ",
		"kwart over *$1 ",
		"tien voor half *$2 ",
		"vijf voor half *$2 ",
		"half *$2 ",
		"vijf over half *$2 ",
		"tien over half *$2 ",
		"kwart voor *$2 ",
		"tien voor *$2 ",
		"vijf voor *$2 "
	},

	.greetings = {
		"Goede- morgen ",
		"Goede- dag ",
		"Goede- avond ",
		"Goede- nacht "
	},

	.connection_lost = "Waar is je tele- foon "
};
