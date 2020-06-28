
//#include "stdafx.h"
#include <Arduino.h>
#include "D_in_a_row_core.h"



void TakeOff(stBoard* a_pB, char a_x);
void Eval_All_Index(stBoard *a_pB);

//void Display_Board(stBoard* a_pB);


int GetBestValue(int* a_pEval_a, char a_N)
{
	int BestValue = -10000;
	for (int i = 0; i < a_N; i++) // Find the best value
	{
		if (BestValue < a_pEval_a[i])
		{
			BestValue = a_pEval_a[i];
		}
	}
	return BestValue;
}



char GetNextIndex(stBoard* a_pB)
{
	stBoard* pB = a_pB;
	char* pBestIdx = a_pB->m_BestIdx_a;

	int BestValue;

	Eval_All_Index(pB);

	BestValue = GetBestValue(a_pB->m_Eval_a[0], pB->m_Nx);

	char BestIdxCount = 0;
	for (int i = 0; i < pB->m_Nx; i++) // Find the best value ( can be a_Turn or 0 )
	{
		if (BestValue == a_pB->m_Eval_a[0][i])
		{
			pBestIdx[BestIdxCount] = i;
			BestIdxCount++;
		}
	}

	char Rand_Idx_of_idx = random(0, BestIdxCount);

	char Idx = pBestIdx[Rand_Idx_of_idx];

	return Idx;
}



// 	10 represent arduino 1 represent the human
// -2000 => Can't play;  -1000 => Lost index;  1000 => Win index
void Eval_All_Index(stBoard *a_pB)
{
	stBoard* pB = a_pB;
	char legal;
	int* pEval_a = pB->m_Eval_a[0];
	int* pEval_2_a = pB->m_Eval_a[1];
	//    char* pHist_P;

	for (int x = 0; x < pB->m_Nx; x++)
	{
		pEval_a[x] = 0;
		legal = PutIn(pB, x, 10);
		
		if (!legal)
		{
			pEval_a[x] = -2000; // can't put here!
			continue;
		}

		Calc_All_Dir(pB);

		if (pB->m_Hist_P[1][4] > 0)		// If Arduino can win? ... mark it as 1000
		{
			pEval_a[x] = 1000;
			TakeOff(pB, x);
			continue;
		}

		pEval_a[x] += pB->m_Hist_P[1][3] * 3; 
		pEval_a[x] += pB->m_Hist_P[1][2]; 

		for (int x2 = 0; x2 < pB->m_Nx; x2++)
		{
			pEval_2_a[x2] = 0;
			
			legal = PutIn(pB, x2, 1);
			if (!legal)
			{
				pEval_2_a[x2] = -2000; // can't put here!
				continue;
			}


			Calc_All_Dir(pB);

			if (pB->m_Hist_P[0][4] > 0) // If HUMAN can win? ... mark it as -100
			{
				pEval_2_a[x2] = 1000;
				TakeOff(pB, x2);
				break;
			}
			pEval_2_a[x2] += pB->m_Hist_P[0][3] * 3; 
			pEval_2_a[x2] += pB->m_Hist_P[0][2]; 

			TakeOff(pB, x2);
		}
		
		int HisBestValue = GetBestValue(pEval_2_a, pB->m_Nx);		
		pEval_a[x] -= HisBestValue;
		TakeOff(pB, x);
	}

  for (int x = 2; x < 5; x++)
  {
    if (pB->m_Mv[x] == 0)
    {
      pEval_a[x] += 1;
    }
  }
}

char Calc_All_Dir(stBoard* a_pB)	// Return 10 if arduino has won or 1 if human
{
	stBoard* pB = a_pB;
	char *pHist_P0 = pB->m_Hist_P[0];
	char *pHist_P1 = pB->m_Hist_P[1];
	memset(pHist_P0, 0, 5);
	memset(pHist_P1, 0, 5);

	//   debug_All_4_Opt = zeros(B.Nx, B.Ny, 4);

	static char dV[4][4][2] = { { {0,0},{1, 0},{2, 0},{3, 0} },
									{ {0,0},{0, 1},{0, 2},{0, 3} },
									{ {0,0},{1, 1},{2, 2},{3, 3} },
									{ {0,0},{1,-1},{2,-2},{3,-3} }
	};

	for (char y = 0; y < pB->m_Ny; y++)
	{
		for (char x = 0; x < pB->m_Nx; x++)
		{
			for (char d = 0; d < 4; d++)
			{
				char Val = 0;
				for (char i = 0; i < 4; i++)
				{
					char xx = x + dV[d][i][0];
					char yy = y + dV[d][i][1];
					if (xx < 0 || yy < 0 || xx >= pB->m_Nx || yy >= pB->m_Ny)
					{
						Val = 11;	// if it's out of board ignore it
						break;
					}
					else
					{
						Val = Val + pB->m_M[yy][xx];
					}
				}

				char PVal_0 = 0;
				char PVal_1 = 0;

				if (Val < 10)
				{
					PVal_0 = Val;
				}
				if ((Val % 10) == 0)
				{
					PVal_1 = Val / 10;
				}
				
				if (PVal_0 == 4 || PVal_1 == 4)
				{
					for (char i = 0; i < 4; i++)
					{
						pB->m_WinLocation[i][0] = x + dV[d][i][0];
						pB->m_WinLocation[i][1] = y + dV[d][i][1];
					}
				}
				
				pHist_P0[PVal_0] = pHist_P0[PVal_0] + 1;
				pHist_P1[PVal_1] = pHist_P1[PVal_1] + 1;

				//             debug_All_4_Opt(x,y,d) = Val;
			}
		}
	}
	
	if (pHist_P0[4]>0) // human won
		return 1;
	
	if (pHist_P1[4]>0) // arduino won 
		return 10;
	
	return 0; // no one won
}

void TakeOff(stBoard* a_pB, char a_x)
{
	stBoard* pB = a_pB;
	char y = pB->m_Mv[a_x];
	if (y > 0)
	{
		pB->m_Mv[a_x] = y - 1;
		pB->m_M[y - 1][a_x] = 0;
	}
}

char PutIn(stBoard* a_pB, char a_x, char a_Val)
{
	stBoard* pB = a_pB;
	char legal, y = a_x;

	y = pB->m_Mv[a_x];
	if (y < pB->m_Ny)
	{
		pB->m_Mv[a_x] = y + 1;
		pB->m_M[y][a_x] = a_Val;
		legal = 1;//TRUE;
	}
	else
	{
		legal = 0;//FALSE;
	}
	return legal;
}

void BoardSwitchSides(stBoard *a_pB)
{
	for (int y = 0; y < a_pB->m_Ny; y++)
	{
		for (int x = 0; x < a_pB->m_Nx; x++)
		{
			a_pB->m_M[y][x] = (a_pB->m_M[y][x] * 10) % 99;
		}
	}
}

void ClearBoard(stBoard *a_pB)
{
	for (int y = 0; y < a_pB->m_Ny; y++)
	{
		for (int x = 0; x < a_pB->m_Nx; x++)
		{
			a_pB->m_M[y][x] = 0;
			a_pB->m_Mv[x] = 0;
		}
	}
}

void InitBoard(stBoard *a_pB, char a_Nx, char a_Ny)
{
	a_pB->m_Nx = a_Nx;
	a_pB->m_Ny = a_Ny;
}
