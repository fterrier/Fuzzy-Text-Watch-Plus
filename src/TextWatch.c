#include <pebble.h>
#ifdef PBL_COLOR
  #include "gcolor_definitions.h" // Allows the use of color
#endif
#include "num2words-en.h"

// Make watch switch time every 5 seconds
#define DEBUG 1

// Data keys
#define KEY_INVERSE 0

#define NUM_LINES 4
#define LINE_LENGTH 7
#define BUFFER_SIZE (LINE_LENGTH + 2)
#define ROW_HEIGHT 37
#define TOP_MARGIN 10

#ifdef PBL_PLATFORM_CHALK
  #define XRES 180
  #define YRES 180
#else
  #define XRES 144
  #define YRES 168
#endif

// Text alignment. Can be GTextAlignmentLeft, GTextAlignmentCenter or GTextAlignmentRight
#define TEXT_ALIGN GTextAlignmentCenter

// The time it takes for a layer to slide in or out.
#define ANIMATION_DURATION 400
// Delay between the layers animations, from top to bottom
#define ANIMATION_STAGGER_TIME 150
// Delay from the start of the current layer going out until the next layer slides in
#define ANIMATION_OUT_IN_DELAY 100

#define LINE_APPEND_MARGIN 0
// We can add a new word to a line if there are at least this many characters free after
#define LINE_APPEND_LIMIT (LINE_LENGTH - LINE_APPEND_MARGIN)

// How long to show messages, in seconds
#define MESSAGE_DISPLAY_TIME 3

Window *window;

typedef struct {
	TextLayer *currentLayer;
	TextLayer *nextLayer;
	char lineStr1[BUFFER_SIZE];
	char lineStr2[BUFFER_SIZE];
	PropertyAnimation *animation1;
	PropertyAnimation *animation2;
} Line;

Line lines[NUM_LINES];

int currentMinutes;
int currentNLines;

// Corrent color of normal text
GColor8 normalTextColor;
// Corrent color of bold text
GColor8 boldTextColor;

// Time in seconds since epoch when a displayed message should be removed.
// Only set to non zero when a message is displaying.
time_t resetMessageTime = 0;

// Animation handler
void animationStoppedHandler(struct Animation *animation, bool finished, void *context)
{
	TextLayer *current = (TextLayer *)context;
	GRect rect = layer_get_frame((Layer *)current);
	rect.origin.x = XRES;
	layer_set_frame((Layer *)current, rect);
}

// Animate line
void makeAnimationsForLayer(Line *line, int delay)
{
	TextLayer *current = line->currentLayer;
	TextLayer *next = line->nextLayer;

	// Destroy old animations 
	if (line->animation1 != NULL)
	{
		 property_animation_destroy(line->animation1);
	}
	if (line->animation2 != NULL)
	{
		 property_animation_destroy(line->animation2);
	}

	// Configure animation for current layer to move out
	GRect rect = layer_get_frame((Layer *)current);
	rect.origin.x =  -XRES;
	line->animation1 = property_animation_create_layer_frame((Layer *)current, NULL, &rect);
	Animation *animation = property_animation_get_animation(line->animation1);
	animation_set_duration(animation, ANIMATION_DURATION);
	animation_set_delay(animation, delay);
	animation_set_curve(animation, AnimationCurveEaseIn); // Accelerate

	// Configure animation for current layer to move in
	GRect rect2 = layer_get_frame((Layer *)next);
	rect2.origin.x = 0;
	line->animation2 = property_animation_create_layer_frame((Layer *)next, NULL, &rect2);
	animation = property_animation_get_animation(line->animation2);	
	animation_set_duration(animation, ANIMATION_DURATION);
	animation_set_delay(animation, delay + ANIMATION_OUT_IN_DELAY);
	animation_set_curve(animation, AnimationCurveEaseOut); // Deaccelerate

	// Set a handler to rearrange layers after animation is finished
	animation_set_handlers(animation, (AnimationHandlers) {
		.stopped = (AnimationStoppedHandler)animationStoppedHandler
	}, current);

	// Start the animations
	animation_schedule(property_animation_get_animation(line->animation1));
	animation_schedule(property_animation_get_animation(line->animation2));	
}

void updateLayerText(TextLayer* layer, char* text)
{
	const char* layerText = text_layer_get_text(layer);
	strcpy((char*)layerText, text);
	// To mark layer dirty
	text_layer_set_text(layer, layerText);
    //layer_mark_dirty(&layer->layer);
}

// Update line
void updateLineTo(Line *line, char *value, int delay)
{
	updateLayerText(line->nextLayer, value);
	makeAnimationsForLayer(line, delay);

	// Swap current/next layers
	TextLayer *tmp = line->nextLayer;
	line->nextLayer = line->currentLayer;
	line->currentLayer = tmp;
}

// Check to see if the current line needs to be updated
bool needToUpdateLine(Line *line, char *nextValue)
{
	const char *currentStr = text_layer_get_text(line->currentLayer);

	if (strcmp(currentStr, nextValue) != 0) {
		return true;
	}
	return false;
}

// Configure bold line of text
void configureBoldLayer(TextLayer *textlayer)
{
	text_layer_set_font(textlayer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
	text_layer_set_text_color(textlayer, boldTextColor);
	text_layer_set_background_color(textlayer, GColorClear);
	text_layer_set_text_alignment(textlayer, TEXT_ALIGN);
}

// Configure light line of text
void configureLightLayer(TextLayer *textlayer)
{
	text_layer_set_font(textlayer, fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT));
	text_layer_set_text_color(textlayer, normalTextColor);
	text_layer_set_background_color(textlayer, GColorClear);
	text_layer_set_text_alignment(textlayer, TEXT_ALIGN);
}

// Configure the layers for the given text
int configureLayersForText(char text[NUM_LINES][BUFFER_SIZE], char format[])
{
	int numLines = 0;

	// Set bold layer.
	int i;
	for (i = 0; i < NUM_LINES; i++) {
		if (strlen(text[i]) == 0) {
			break;
		}

		if (format[i] == 'b')
		{
			configureBoldLayer(lines[i].nextLayer);
		}
		else
		{
			configureLightLayer(lines[i].nextLayer);
		}
	}
	numLines = i;

	// Calculate y position of top Line
	int ypos = (YRES - numLines * ROW_HEIGHT) / 2 - TOP_MARGIN;

	// Set y positions for the lines
	for (int i = 0; i < numLines; i++)
	{
		layer_set_frame((Layer *)lines[i].nextLayer, GRect(XRES, ypos, XRES, 50));
		ypos += ROW_HEIGHT;
	}

	return numLines;
}

void string_to_lines(char *str, char lines[NUM_LINES][BUFFER_SIZE], char format[])
{
	char *start = str;
	char *end = strstr(start, " ");
	int l = 0;

	// Empty all lines
	for (int i = 0; i < NUM_LINES; i++)
	{
		lines[i][0] = '\0';
	}

	while (end != NULL && l < NUM_LINES) {
		// Check word for bold prefix
		if (*start == '*' && end - start > 1)
		{
			// Mark line bold and move start to the first character of the word
			format[l] = 'b';
			start++;
		}
		else
		{
			// Mark line normal
			format[l] = ' ';
		}

		// Can we add another word to the line?
		if (format[l] == ' ' && *(end + 1) != '*'    // are both lines formatted normal?
			&& end - start < LINE_APPEND_LIMIT - 1)  // is the first word short enough?
		{
			// See if next word fits
			char *try = strstr(end + 1, " ");
			if (try != NULL && try - start <= LINE_APPEND_LIMIT)
			{
				end = try;
			}
		}

		// copy to line
		*end = '\0';
		strcpy(lines[l++], start);

		// Look for next word
		start = end + 1;
		end = strstr(start, " ");
	}
}

void time_to_lines(int hours, int minutes, char lines[NUM_LINES][BUFFER_SIZE], char format[])
{
	int length = NUM_LINES * BUFFER_SIZE + 1;
	char timeStr[length];
	time_to_words(hours, minutes, timeStr, length);
	
	string_to_lines(timeStr, lines, format);
}

// Update screen based on new time
void display_message(char *message, int displayTime)
{
	// The current time text will be stored in the following strings
	char textLine[NUM_LINES][BUFFER_SIZE];
	char format[NUM_LINES];

	string_to_lines(message, textLine, format);
	
	int nextNLines = configureLayersForText(textLine, format);

	int delay = 0;
	for (int i = 0; i < NUM_LINES; i++) {
	    updateLineTo(&lines[i], textLine[i], delay);
	    delay += ANIMATION_STAGGER_TIME;
	}
	
	currentNLines = nextNLines;

	time(&resetMessageTime);
	resetMessageTime += displayTime;
}

// Update screen based on new time
void display_time(struct tm *t, bool force)
{
	if (resetMessageTime != 0) // Don't update time if a message is showing
	{
		return;
	}

	// The current time text will be stored in the following strings
	char textLine[NUM_LINES][BUFFER_SIZE];
	char format[NUM_LINES];

#if DEBUG == 1
	time_to_lines(t->tm_hour, t->tm_sec, textLine, format);
#else
	time_to_lines(t->tm_hour, t->tm_min, textLine, format);
#endif
	
	int nextNLines = configureLayersForText(textLine, format);

	int delay = 0;
	for (int i = 0; i < NUM_LINES; i++) {
		if (force || nextNLines != currentNLines || needToUpdateLine(&lines[i], textLine[i])) {
			updateLineTo(&lines[i], textLine[i], delay);
			delay += ANIMATION_STAGGER_TIME;
		}
	}
	
	currentNLines = nextNLines;
}

// Time handler called every minute by the system
void handle_tick(struct tm *tick_time, TimeUnits units_changed)
{
  bool resetMessage = false;
  if (resetMessageTime != 0)
  {
  	time_t now;
  	time(&now);
  	if (now >= resetMessageTime)
  	{
  		resetMessage = true;
  		resetMessageTime = 0;
  	}
  }

  if (resetMessage || 
  	  (units_changed & MINUTE_UNIT) != 0 ||
  	  DEBUG)
  {
	display_time(tick_time, false);
  }
}

void init_line(Line* line)
{
	// Create layers with dummy position to the right of the screen
	line->currentLayer = text_layer_create(GRect(XRES, 0, XRES, 50));
	line->nextLayer = text_layer_create(GRect(XRES, 0, XRES, 50));

	// Configure a style
	configureLightLayer(line->currentLayer);
	configureLightLayer(line->nextLayer);

	// Set the text buffers
	line->lineStr1[0] = '\0';
	line->lineStr2[0] = '\0';
	text_layer_set_text(line->currentLayer, line->lineStr1);
	text_layer_set_text(line->nextLayer, line->lineStr2);

	// Initially there are no animations
	line->animation1 = NULL;
	line->animation2 = NULL;
}

struct tm *get_localtime()
{
	time_t raw_time;
	time(&raw_time);
	return localtime(&raw_time);
}

void refresh_time() {
	display_time(get_localtime(), true);
}

void inbox_received_handler(DictionaryIterator *iter, void *context) {
  // High contrast selected?
  Tuple *color_inverse_t = dict_find(iter, KEY_INVERSE);
  if(color_inverse_t) {
  	if (color_inverse_t->value->int8 > 0) {  // Read boolean as an integer
	    // Set inverse colors
	    window_set_background_color(window, GColorWhite);
	    normalTextColor.argb = GColorBlack.argb;
	    boldTextColor.argb = GColorBlack.argb;
	    // Persist value
	    persist_write_bool(KEY_INVERSE, true);
	} else {
	    // Set normal colors
	    window_set_background_color(window, GColorBlack);
	    normalTextColor.argb = GColorWhite.argb;
	    boldTextColor.argb = GColorWhite.argb;
	    // Persist value
	    persist_write_bool(KEY_INVERSE, false);
	}
    refresh_time();
  }
}

void bt_handler(bool connected) {
	if (!connected) {
		vibes_long_pulse();
		light_enable_interaction();
		display_message("Var är din telefon ", MESSAGE_DISPLAY_TIME * 2);
	}
}

void handle_init() {
	window = window_create();
	window_stack_push(window, true);

	if (persist_read_bool(KEY_INVERSE)) {
		window_set_background_color(window, GColorWhite);	
		normalTextColor.argb=GColorBlack.argb;
		boldTextColor.argb=GColorBlack.argb;
	} else {
		window_set_background_color(window, GColorBlack);	
		normalTextColor.argb=GColorWhite.argb;
		boldTextColor.argb=GColorWhite.argb;
	}

	app_message_register_inbox_received(inbox_received_handler);
  	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());

	// Init and load lines
	for (int i = 0; i < NUM_LINES; i++)
	{
		init_line(&lines[i]);
	  	layer_add_child(window_get_root_layer(window), (Layer *)lines[i].currentLayer);
		layer_add_child(window_get_root_layer(window), (Layer *)lines[i].nextLayer);
	}

	// Configure time on init
	char greeting[32];
	time_to_greeting(get_localtime()->tm_hour, greeting);
#if DEBUG == 1
	strcat(greeting, " Debug ");
#endif
	display_message(greeting, MESSAGE_DISPLAY_TIME);
	//refresh_time();

	// Subscribe to minute ticks
	tick_timer_service_subscribe(SECOND_UNIT, handle_tick);

	// Subscribe to bluetooth events
	connection_service_subscribe((ConnectionHandlers) {
	  .pebble_app_connection_handler = bt_handler
	});

}

void destroy_line(Line* line)
{
	// Free layers
	text_layer_destroy(line->currentLayer);
	text_layer_destroy(line->nextLayer);
}

void handle_deinit()
{
	// Free lines
	for (int i = 0; i < NUM_LINES; i++)
	{
		destroy_line(&lines[i]);
	}

	// Free window
	window_destroy(window);
}

int main(void)
{
	handle_init();
	app_event_loop();
	handle_deinit();
}

