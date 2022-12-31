
#include "FastLED.h"
#include "D_in_a_row_core.h"
#include "Led_Stripe.h"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define IS_ODD(a) (a & 1)


CRGB Led_arr[NUM_LEDS];


void LS_Setup()
{
   FastLED.addLeds<WS2812B, DATA_PIN>(Led_arr, NUM_LEDS);
   FastLED.setBrightness(255);
}

void LS_Show()
{
	FastLED.show();
}


/*
	for (char y = BOARD_NY - 1; y >= 0; y--)
	{
		for (char x = 0; x < LEDS_NX; x++)
		{
		}
	}


*/


void LS_Clear_All()
{
	for (char i = 0; i < NUM_LEDS; i++)
	{
		Led_arr[i] = 0;
	}
}

void LS_Set_XY(char a_X, char a_Y, CRGB a_Val)
{

	char X = ORDER_L2R ? a_X : LEDS_NX - 1 - a_X;
	char Y = ORDER_D2U ? a_Y : LEDS_NY - 1 - a_Y;

	if (X < 0 || X >= LEDS_NX || Y<0 || Y>=LEDS_NY)
		return;


	if (IS_ODD(Y))
	{
		X = LEDS_NX - 1 - X;
	}


	char Led_idx = Y * LEDS_NX + X;

	Led_arr[Led_idx + START_LED] = a_Val;

}

CRGB LS_Get_XY(char a_X, char a_Y)
{

  char X = ORDER_L2R ? a_X : LEDS_NX - 1 - a_X;
  char Y = ORDER_D2U ? a_Y : LEDS_NY - 1 - a_Y;

  if (X < 0 || X >= LEDS_NX || Y<0 || Y>=LEDS_NY)
    return;


  if (IS_ODD(Y))
  {
    X = LEDS_NX - 1 - X;
  }


  char Led_idx = Y * LEDS_NX + X;

  return(Led_arr[Led_idx + START_LED]);

}


/*

// After it been set
void BlinkOneLed(char* a_pBoard, char a_LedIdx)
{
	char LedVal = a_pBoard[a_LedIdx];
	
	for (int i=0; i<5; i++)
	{	
		a_pBoard[a_LedIdx] = 0;
		SetBoardPostion(a_pBoard);
		delay(BLINK_DELAY_mSec);
		a_pBoard[a_LedIdx] = LedVal;
		SetBoardPostion(a_pBoard);
		delay(BLINK_DELAY_mSec);
	}
}

void BlinkLineOfLeds(char* a_pBoard, char* a_pLedIdx)
{
	char LedVal = a_pBoard[a_pLedIdx[0]];
	
	for (int i=0; i<5; i++)
	{	
		a_pBoard[a_pLedIdx[0]] = 0;
		a_pBoard[a_pLedIdx[1]] = 0;
		a_pBoard[a_pLedIdx[2]] = 0;
		SetBoardPostion(a_pBoard);
		delay(BLINK_DELAY_mSec);
		a_pBoard[a_pLedIdx[0]] = LedVal;
		a_pBoard[a_pLedIdx[1]] = LedVal;
		a_pBoard[a_pLedIdx[2]] = LedVal;
		SetBoardPostion(a_pBoard);
		delay(BLINK_DELAY_mSec);
	}
}

void BlinkAllLed(char* a_pBoard)
{
	Led_Proro_Clear_Board();
	
	
	for (int i=0; i<5; i++)
	{	
		SetBoardPostion(PromoBoard);
		delay(BLINK_DELAY_mSec);
		SetBoardPostion(a_pBoard);
		delay(BLINK_DELAY_mSec);
	}
	for(int i=0; i<9; i++)
	{
		a_pBoard[i] = 0;
		SetBoardPostion(a_pBoard);
		delay(BLINK_DELAY_mSec);
	}	
}

*/
