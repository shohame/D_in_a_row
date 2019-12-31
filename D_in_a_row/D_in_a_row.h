#ifndef _D_IN_A_ROW_
#define _D_IN_A_ROW_

#define ARDUINO_START	10
#define HUMAN_STAST		1

typedef struct sGame
{

	char	m_isGameOver;
	stBoard m_Board_s;
	char	m_HowStart;
	char	m_DoRestart;


} stGame;



void Matrix_2_Leds(stBoard *a_pB);




#endif //_D_IN_A_ROW_
