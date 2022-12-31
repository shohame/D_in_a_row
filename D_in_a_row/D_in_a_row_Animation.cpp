#include "FastLED.h"

#include "Led_Stripe.h"
#include "IR_input.h"

#include "Color_Palette.h"

#include "D_in_a_row_core.h"

#include "D_in_a_row.h"
#include "D_in_a_row_Animation.h"

#define NUM_OF_ROW (65)

char DispMatrix[7][NUM_OF_ROW]={
{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},

};
extern IR_Input cIR_In;

char Anim_ScrollText ()
{
  for (char R = (NUM_OF_ROW -8); R>0; R--)
  {
    for(char Ri = 0; Ri<7; Ri++)
    {
      for (char C=0; C<7; C++)
      {
        CRGB Color = (DispMatrix[C][R+Ri] == 1) ? CP_GetColor(5) : CP_GetColor(0);
        LS_Set_XY(6-Ri, 6-C, Color);
      } 
   }
   LS_Show();
   delay(  200);
   char Key = cIR_In.Receive_safe();

   if (Key == en_HASHTAG_KEY || Key == en_STAR_KEY)
   {
	   return Key;
   }

  }
}

void Anim_ScrollText_on_Color (char a_R)
{
  if ( a_R < (NUM_OF_ROW - 8))
  {
    for(char Ri = 0; Ri<BOARD_NX; Ri++)
    {
      for (char C=0; C<7; C++)
      {
		  if (DispMatrix[C][NUM_OF_ROW -a_R-7+Ri] == 1)
		  {
			  LS_Set_XY(BOARD_NX-1-Ri, LEDS_NY-C-2, CP_GetColor(en_COLOR_WHITE_IDX));
		  }
      } 
    }
   
  }
}



// Params for width and height
const char kMatrixWidth = 7;
const char kMatrixHeight = 7;


// Demo that USES "XY" follows code below
void DrawOneFrame(char startHue8, char yHueDelta8, char xHueDelta8)
{
	char lineStartHue = startHue8;
	for (char y = 0; y < kMatrixHeight; y++) {
		lineStartHue += yHueDelta8;
		char pixelHue = lineStartHue;
		for (char x = 0; x < kMatrixWidth; x++) {
			pixelHue += xHueDelta8;
			LS_Set_XY(x, y, CHSV(pixelHue, 255, 255));
		}
	}
}

extern IR_Input cIR_In;

char Anim_ColorPlay()
{
	for (int i = 0; i < 30*NUM_OF_ROW; i++)
	{
		uint32_t ms = millis() / 1;
		int32_t yHueDelta32 = ((int32_t)cos16(ms / 4 * (27 / 1)) * (350 / kMatrixWidth));
		int32_t xHueDelta32 = ((int32_t)cos16(ms / 4 * (39 / 1)) * (310 / kMatrixHeight));
		DrawOneFrame(ms / 65536, yHueDelta32 / 32768, xHueDelta32 / 32768);
		Anim_ScrollText_on_Color((i/10) % (NUM_OF_ROW * 2));

    delay(20);
    char Key = cIR_In.Receive_safe();
    if (Key == en_HASHTAG_KEY || Key == en_STAR_KEY)
    {
      return Key;
    }

   
		LS_Show();
	
 	}
 return 0;
}





void Anim_ArduinoMove(stBoard *a_pB, char a_x)
{
	stBoard *pB = a_pB;
	char Nx = pB->m_Nx;
	char Ny = pB->m_Ny;
	char Direction = random(0,2) * 2 - 1; // Create -1 or 1
	
	char x0 = (Direction == 1) ? 0 : (Nx -1);
	char x1 = x0;
	char i;
	for (i=0; i< Nx; i++)
	{
		LS_Set_XY(x0, Ny, CP_GetColor(en_COLOR_BLACK_IDX));
		LS_Set_XY(x1, Ny, CP_GetColor(ARDUINO_COLOR_IDX));
		LS_Show();
		
		x0 = x1;
		x1 = x1 + Direction;
		delay(random(250,500));
	}
	Direction = -Direction;
	x1 = x0;

	char Steps = abs(x1 - a_x) + 1;
	
	for (i=0; i<Steps; i++)
	{
		LS_Set_XY(x0, Ny, CP_GetColor(en_COLOR_BLACK_IDX));
		LS_Set_XY(x1, Ny, CP_GetColor(ARDUINO_COLOR_IDX));
		LS_Show();
		x0 = x1;
		x1 = x1 + Direction;
		delay(random(250,400));
	}
	
	x1 = x0;

  Anim_ThrowDown(pB, x1, CP_GetColor(ARDUINO_COLOR_IDX), 150);

  
}



void Anim_ThrowDown(stBoard *a_pB, char a_x, CRGB a_Color, int a_Delay)
{
  stBoard *pB = a_pB;
  char Nx = pB->m_Nx;
  char Ny = pB->m_Ny;
  char Steps = 6 - a_pB->m_Mv[a_x]+1;
  
  char y0 = 6; 
  char y1 = 6;
  
  for (char i=0; i<Steps; i++)
  {
	if (y0==6)
		LS_Set_XY(a_x, y0, CP_GetColor(en_COLOR_BLACK_IDX));
	else
		LS_Set_XY(a_x, y0, CP_GetColor(BOARD_COLOR_IDX));

    LS_Set_XY(a_x, y1, a_Color);
    LS_Show();
    y0 = y1;
    y1 = y1 - 1;
    delay(a_Delay);
  }

}





void Anim_ColorRoll()
{
  char dx, dy;
   
  for (int i=0; i<100; i++)
  {
    char r = (char)(100.0*(0.5+sin( ((float)i)/40.0)));
    char g = (char)(100.0*(0.5+sin( ((float)i)/21.0)));
    char b = (char)(100.0*(0.5+sin( ((float)i)/12.0)));
  
    char x=-1, y=0;
  
    CRGB Color;
    CRGB Color1 = CRGB(r,g,b);

    for (char i=0; i<13; i++)
    {
    	char Steps = (14-i)>>1; 						// 7, 6, 6, 5, 5, ..... 2, 2, 1, 1\
    
    	dx = ( (i%2) == 0 ) - 2 * ( (i%4) == 2 );		//   dx =  1,  0, -1,  0,  1,  0, -1,  0
    	dy = ( (i%2) == 1 ) - 2 * ( (i%4) == 3 );       //   dy =  0,  1,  0, -1,  0,  1,  0, -1
    
    	for (char s=0; s<Steps; s++)
    	{
    		x = x + dx;
    		y = y + dy;
    		Color = LS_Get_XY(x, y);
   
   			LS_Set_XY(x, y, Color1);
    		Color1 = Color;
    	}
    }
    LS_Show();
     
    delay(20);
  }

}



