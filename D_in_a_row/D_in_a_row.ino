#include "FastLED.h"

#include "Led_Stripe.h"
#include "IR_input.h"

#include "Color_Palette.h"

#include "D_in_a_row_core.h"
#include "D_in_a_row.h"
#include "D_in_a_row_Animation.h"

//#include "stdafx.h

//#include <string.h>
//#include <conio.h>
//#include <stdio.h>
//#include <time.h>

//#include <iostream>
IR_Input cIR_In;
//using namespace std;

stGame g_Game_s;



void Matrix_2_Leds(stBoard *a_pB);
void PlayGame(stGame* a_pGame);
char TestHowStart(stGame *a_pG_s);

/* main
int main()
{
	stBoard* pB = &B;
	D_in_a_row_core(pB);
	return 0;
}
*/
void setup()
{
	Serial.begin(9600);
  
	LS_Setup();
	cIR_In.Setup();
	InitBoard(&g_Game_s.m_Board_s, BOARD_NX, BOARD_NY);
	randomSeed(analogRead(0));
  Serial.println (random(6));
}

// the loop function runs over and over again until power down or reset
void loop()
{
	stGame *pGame_s = &g_Game_s;
    stBoard* pB = &pGame_s->m_Board_s;
  
	ResetGame(pGame_s);

//	Anim_ColorPlay();
//	Anim_ColorRoll();
//	MainMenu(pGame_s);

	while(1)
	{
   Serial.println("Anim_ColorPlay()");
		char Key = Anim_ColorPlay();
		
		if (Key == en_HASHTAG_KEY)	pGame_s->m_HowStart = HUMAN_STAST;
		if (Key == en_STAR_KEY)     pGame_s->m_HowStart = ARDUINO_START;
		
		if (TestHowStart(pGame_s))	break;
    
   Serial.println("PlayGame_demo()");

		PlayGame_demo(pGame_s);
		
		if (TestHowStart(pGame_s))	break;

	}
	

  Serial.println("PlayGame(pGame_s)");
	PlayGame(pGame_s);
}

void GetNextArduinoStep(stGame* a_pGame)
{
	stBoard* pB = &a_pGame->m_Board_s;

	char SetIndex = GetNextIndex(pB);
	Anim_ArduinoMove(pB, SetIndex);
	PutIn(pB, SetIndex, 10);
	Matrix_2_Leds(pB);
	LS_Show();

}


void GetNextArduinoStep_demo(stGame* a_pGame)
{
	stBoard* pB = &a_pGame->m_Board_s;
	char SetIndex = GetNextIndex(pB);
	Anim_ThrowDown(pB, SetIndex, CP_GetColor(ARDUINO_COLOR_IDX), 50);
	PutIn(pB, SetIndex, 10);
	Matrix_2_Leds(pB);
	LS_Show();
}

void GetNextHumanStep_demo(stGame* a_pGame)
{
	stBoard* pB = &a_pGame->m_Board_s;
	BoardSwitchSides(pB);
	char SetIndex = GetNextIndex(pB);
	BoardSwitchSides(pB);
	Anim_ThrowDown(pB, SetIndex, CP_GetColor(HUMAN_COLOR_IDX), 50);
	PutIn(pB, SetIndex, 1);
	Matrix_2_Leds(pB);
	LS_Show();
}




void GetNextHumanStep(stGame* a_pGame)
{
	stBoard* pB = &a_pGame->m_Board_s;
  char x1 = 3;
  char x0 = 0;
  cIR_In.Receive_safe();
  while(1)
  {
   char Key = cIR_In.Receive_safe();

   if (Key == en_LEFT_KEY && x1<(BOARD_NX-1))
   {
      x1 = x1 + 1;
   }
   if (Key == en_RIGHT_KEY && x1>0)
   {
      x1 = x1 - 1;
   }
    if (Key == en_OK_KEY && (pB->m_Mv[x1] < pB->m_Ny))
    {
        break;      
    }
    if (Key == 0)
    {
        a_pGame->m_DoRestart = 1;
        return;      
    }

    if (x0 != x1)
    {
      LS_Set_XY(x0, BOARD_NY , CP_GetColor(en_COLOR_BLACK_IDX));
      LS_Set_XY(x1, BOARD_NY , CP_GetColor(HUMAN_COLOR_IDX));
      LS_Show();
    }
    x0 = x1;
    delay(100);
    
  }
  
  Anim_ThrowDown(pB, x1, CP_GetColor(HUMAN_COLOR_IDX), 150);
  PutIn(pB, x1, 1);
  Matrix_2_Leds(pB);
  LS_Show();

}

char TestIfGameOver(stGame* a_pGame)
{
	stBoard* pB = &a_pGame->m_Board_s;
	
	char WhoWon = Calc_All_Dir(pB);
 
  char x = pB->m_WinLocation[0][0];
  char y = pB->m_WinLocation[0][1];
	
	CRGB WonColor = LS_Get_XY(x, y);
	
	
	if (WhoWon)
	{
		for (char j = 0; j < 20; j++)
		{
			for (char i = 0; i < 4; i++)
			{
				x = pB->m_WinLocation[i][0];
				y = pB->m_WinLocation[i][1];
				
				LS_Set_XY(x, y , CP_GetColor(en_COLOR_WHITE_IDX));
			}
			LS_Show();
			delay(50);
			for (char i = 0; i < 4; i++)
			{
				x = pB->m_WinLocation[i][0];
				y = pB->m_WinLocation[i][1];
				
				LS_Set_XY(x, y , WonColor);
			}
			LS_Show();
			delay(100);
		}
	}
	else
	{
		int Sum = 0;
		for (int i = 0; i < BOARD_NX; i++)
		{
			Sum += pB->m_Mv[i];
		}
		if (Sum == BOARD_NX * BOARD_NY)
		{
			WhoWon = 100;	
		}
		
	}

	return WhoWon;
}

void PlayGame(stGame* a_pGame)
{
	stBoard* pB = &a_pGame->m_Board_s;
	char GameOver = 0;
	ClearBoard(pB);
  LS_Clear_All();
  Matrix_2_Leds(pB);
  LS_Show();

	char Turn = 1;

	if (a_pGame->m_HowStart == ARDUINO_START)
	{
		Turn = -1;
	}
  
	
	while (!GameOver)
	{
		if (Turn == -1)		
			GetNextArduinoStep(a_pGame);
		else
			GetNextHumanStep(a_pGame);
    
		GameOver = TestIfGameOver(a_pGame);
		Turn = -Turn;

		if (a_pGame->m_DoRestart)
			break;
	}
	if (!a_pGame->m_DoRestart)
		delay (3000);
}

void PlayGame_demo(stGame* a_pGame)
{
	stBoard* pB = &a_pGame->m_Board_s;
	char GameOver = 0;
	ClearBoard(pB);
  LS_Clear_All();
	Matrix_2_Leds(pB);
	LS_Show();
	char Turn = random(0,2)*2-1;
	
	while (!GameOver)
	{
		if (TestHowStart(a_pGame))
			break;

		if (Turn == -1)	
		{			
			GetNextArduinoStep_demo(a_pGame);
		}
		else
		{
			GetNextHumanStep_demo(a_pGame);
		}
    
		GameOver = TestIfGameOver(a_pGame);
		Turn = -Turn;

		if (a_pGame->m_DoRestart)
			break;
   
	}
	if(GameOver)
		delay (1000);

}

char TestHowStart(stGame *a_pG_s)
{
	if (a_pG_s->m_HowStart == 0)
	{
		char Key = cIR_In.Receive_safe();

		if (Key == en_HASHTAG_KEY)
		{
			a_pG_s->m_HowStart = HUMAN_STAST;
		}
		if (Key == en_STAR_KEY)
		{
			a_pG_s->m_HowStart = ARDUINO_START;
		}
	}
	return (a_pG_s->m_HowStart);
}

void MainMenu(stGame *a_pG_s)
{
	stBoard *pB = &a_pG_s->m_Board_s;
	float x1, y1, x2, y2, x3, y3, x0, y0, dx, dy;

	float X_max = (float)(LEDS_NX - 1);
	float Y_max = (float)(LEDS_NY - 1);

	ClearBoard(&a_pG_s->m_Board_s);

	x0 = 3; y0 = 3;
	x1 = 3; y1 = 3;
	x2 = 3; y2 = 3;
	x3 = 3; y3 = 3;
	dx = 1.1; dy = 0.9;

	while (1)
	{
		x1 = x1 + dx;
		y1 = y1 + dy;

		if (x1 > X_max)
		{
			x1 = X_max - (x1 - X_max);
			dx = -dx;
		}
		if (y1 > Y_max)
		{
			y1 = Y_max - (y1 - Y_max);
			dy = -dy;
		}
		if (x1 < 0)
		{
			x1 = -x1;
			dx = -dx;
		}
		if (y1 < 0)
		{
			y1 = -y1;
			dy = -dy;
		}
		LS_Set_XY((char)round(x0), (char)round(y0), CP_GetColor(en_COLOR_BLACK_IDX));
		LS_Set_XY((char)round(x0+1), (char)round(y0), CP_GetColor(en_COLOR_BLACK_IDX));
		LS_Set_XY((char)round(x0), (char)round(y0+1), CP_GetColor(en_COLOR_BLACK_IDX));
		LS_Set_XY((char)round(x0), (char)round(y0-1), CP_GetColor(en_COLOR_BLACK_IDX));
		LS_Set_XY((char)round(x0-1), (char)round(y0), CP_GetColor(en_COLOR_BLACK_IDX));
		LS_Set_XY((char)round(x1), (char)round(y1), CP_GetColor(en_COLOR_RED_IDX));
		LS_Set_XY((char)round(x1+1), (char)round(y1), CP_GetColor(en_COLOR_GREEN_IDX));
		LS_Set_XY((char)round(x1), (char)round(y1+1), CP_GetColor(en_COLOR_GREEN_IDX));
		LS_Set_XY((char)round(x1), (char)round(y1-1), CP_GetColor(en_COLOR_GREEN_IDX));
		LS_Set_XY((char)round(x1-1), (char)round(y1), CP_GetColor(en_COLOR_GREEN_IDX));
		LS_Show();
		x0 = x1; y0 = y1;

		
		if (TestHowStart(a_pG_s))
			break;
		
		delay(200);
	}

	ClearBoard(&a_pG_s->m_Board_s);
	LS_Clear_All();
	LS_Show();

}

void ResetGame(stGame *a_pG_s)
{
	ClearBoard(&a_pG_s->m_Board_s);
  LS_Clear_All();
  LS_Show();
	a_pG_s->m_isGameOver = false;
	a_pG_s->m_HowStart = 0;
  a_pG_s->m_DoRestart = 0;
}

void Matrix_2_Leds(stBoard *a_pB)
{
	stBoard* pB = a_pB;
	char Nx = pB->m_Nx;
	char Ny = pB->m_Ny;

	char C_idx;
	CRGB Color;

	for (char y = pB->m_Ny - 1; y >= 0; y--)
	{
		for (char x = 0; x < pB->m_Nx; x++)
		{
			C_idx = pB->m_M[y][x];
			if (C_idx == 1)
				Color = CP_GetColor(HUMAN_COLOR_IDX);
			else if (C_idx == 10)
				Color = CP_GetColor(ARDUINO_COLOR_IDX);
			else 
				Color = CP_GetColor(BOARD_COLOR_IDX);
			LS_Set_XY(x, y, Color);
		}
	}
}





/*
void Display_Board(stBoard* a_pB)
{
	stBoard* pB = a_pB;


	char Nx = pB->m_Nx;
	char Ny = pB->m_Ny;
	// pB->m_M;
	printf("\n\n========================================================\n\n");
	for (char y = pB->m_Ny - 1; y >= 0; y--)
	{
		for (char x = 0; x < pB->m_Nx; x++)
		{
			if (pB->m_M[y][x] == 0)
				printf("-");
			else if (pB->m_M[y][x] == 1)
				printf("*");
			else if (pB->m_M[y][x] == 10)
				printf("#");
		}
		printf("\n");
	}
}

*/




