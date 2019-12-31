




#include "FastLED.h"
#include "Color_Palette.h"

CRGB Color_arr[NUM_OF_COLOR] = { {0,0,0},  {BRIGHTNESS, 0, 0},{ 0, BRIGHTNESS, 0 },{ 0, BRIGHTNESS, BRIGHTNESS },
                            { BRIGHTNESS, BRIGHTNESS, BRIGHTNESS } ,{ BRIGHTNESS, BRIGHTNESS / 3, BRIGHTNESS } ,{ BRIGHTNESS/7, BRIGHTNESS/7 , 0 },
                            { 0, 0, BRIGHTNESS }};

CRGB CP_GetColor(char a_ColorIdx)
{
	return Color_arr[a_ColorIdx];
}




