#ifndef _D_IN_A_ROW_CORE_
#define _D_IN_A_ROW_CORE_



#define BOARD_NX 7
#define BOARD_NY 6


typedef struct Board
{
	int m_Nx;
	int m_Ny;

	char m_M[BOARD_NY][BOARD_NX];	// The board 0 == free; 1 == user; 10 == Arduino;
	char m_Mv[BOARD_NX];				// The current level hieght on [x] row just to help put the take off...
	int  m_Eval_a[BOARD_NX];			// The Evaluated row to put in
	char m_Hist_P[2][5];				// Histogram to count how many in all rows for each player
	char m_BestIdxCount;
	char m_BestIdx_a[BOARD_NX];
	
	char m_WinLoction[4][2];
 
} stBoard;

void ClearBoard(stBoard *a_pB);
void InitBoard(stBoard *a_pB, char a_Nx, char a_Ny);

char GetNextIndex(stBoard* a_pB);
char PutIn(stBoard* a_pB, char a_x, char a_Val);
char Calc_All_Dir(stBoard* a_pB);
void BoardSwitchSides(stBoard *a_pB);




#endif // #ifndef _D_IN_A_ROW_CORE_ 
