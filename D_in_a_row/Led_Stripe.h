#ifndef _TTT_LED_H_
#define _TTT_LED_H_







#define LEDS_NX 7
#define LEDS_NY 7

#define NUM_LEDS (LEDS_NX * LEDS_NY + 1)

#define DATA_PIN 2


#define ORDER_L2R 0			// 1- Left to right;   0 - Right to left
#define ORDER_D2U 0			// 1- Done to Up;      0 - Up to Down

#define BLINK_DELAY_mSec 300

void LS_Setup();

void LS_Set_XY(char a_X, char a_Y, CRGB a_Val);
CRGB LS_Get_XY(char a_X, char a_Y);

void LS_Show();
void LS_Clear_All();
/*
void SetBoardPostion(char* a_pBoard);
char Led_Proro_Untill_StartKey(IR_Input* pIR_Input);
void BlinkAllLed(char* a_pBoard);
void BlinkLineOfLeds(char* a_pBoard, char* a_pLedIdx);
void BlinkOneLed(char* a_pBoard, char a_LedIdx);
void Led_Proro_Clear_Board();
*/
#endif // #ifndef _TTT_LED_H_



