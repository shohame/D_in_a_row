
#ifndef _COLOR_PALETTE_
#define _COLOR_PALETTE_


#define NUM_OF_COLOR	8
#define BRIGHTNESS		255


#define en_COLOR_BLACK_IDX		0
#define en_COLOR_RED_IDX		1
#define en_COLOR_GREEN_IDX		2
#define en_COLOR_ORENGE_IDX  	3
#define en_COLOR_WHITE_IDX  	4
#define en_COLOR_PURPLE_IDX  	5
#define en_COLOR_YELLOW_IDX    6
#define en_COLOR_BLUE_IDX    7


#define BOARD_COLOR_IDX			en_COLOR_YELLOW_IDX
#define HUMAN_COLOR_IDX			en_COLOR_BLUE_IDX
#define ARDUINO_COLOR_IDX		en_COLOR_RED_IDX


#include "FastLED.h"

CRGB CP_GetColor(char a_ColorIdx);

#endif // #ifndef _COLOR_PALETTE_ 








