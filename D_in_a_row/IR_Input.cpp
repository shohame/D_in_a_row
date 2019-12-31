#include <IRremote.h>
#include <IRremoteInt.h>

#include "IR_input.h"


typedef struct IR_CodeTanslet_tbl_st
{
	unsigned long     Code;
	char              KeyVal;
}IR_CodeTanslet_tbl;


/*
IR_CodeTanslet_tbl    CodeTanslet_sa[NUM_OF_KEY_CODE] = {
            {0xE0E020DF, 0}, {0xE0E0A05F, 1}, {0xE0E0609F, 2}, {0xE0E010EF, 3},{0xE0E0906F, 4},
            {0xE0E050AF, 5}, {0xE0E030CF, 6}, {0xE0E0B04F, 7}, {0xE0E0708F, 8},
            {0xE0E0E01F, en_USER_FISRT_KEY}, {0xE0E048B7, en_USER_FISRT_KEY},
            {0xE0E0D02F, en_ARDO_FISRT_KEY}, {0xE0E008F7, en_ARDO_FISRT_KEY} };
            */
IR_CodeTanslet_tbl    CodeTanslet_sa[NUM_OF_KEY_CODE] = {
            {0xFF9867, 0}, {0xFFA25D, 1}, {0xFF629D, 2}, {0xFFE21D, 3},{0xFF22DD, 4},
            {0xFF02FD, 5}, {0xFFC23D, 6}, {0xFFE01F, 7}, {0xFFA857, 8}, {0xFF906F, 9},
            {0xFFB04F, en_HASHTAG_KEY}, {0xFF6897, en_STAR_KEY},
            {0xFF5AA5, en_RIGHT_KEY}, {0xFF10EF, en_LEFT_KEY},{0xFF18E7, en_UP_KEY}, {0xFF4AB5, en_DOWN_KEY}, {0xFF38C7, en_OK_KEY},};

IR_Input::IR_Input(/*int a_ReceiverPinID*/)
{
	//  pIR_Recv = &IR_Recv;
	//  pIR_Recv->enableIRIn(); // Start the receiver
}

IRrecv irrecv(IR_RECEIVER_PIN);

decode_results results;

void IR_Input::Setup()
{
  pinMode(IR_VCC, OUTPUT);
  digitalWrite(IR_VCC, HIGH);

	irrecv.enableIRIn();
}


char IR_Input::Receive_safe()
{
  char Ret = en_NO_KEY;
  while (!irrecv.isIdle());  // if not idle, wait till complete

  if (irrecv.decode(&results)) 
  {  
    for (int i = 0; i < NUM_OF_KEY_CODE; i++)
    {
      if (results.value == CodeTanslet_sa[i].Code)
      {
        Ret = CodeTanslet_sa[i].KeyVal;
        Serial.println("Got a key!!!");
      }

    }
    Serial.println(results.value, HEX);
    irrecv.resume();
  }
  return Ret;
}




char IR_Input::Receive()
{
	char Ret = en_NO_KEY;
	if (irrecv.decode(&results)) // have we received an IR signal?
	{
		for (int i = 0; i < NUM_OF_KEY_CODE; i++)
		{
			if (results.value == CodeTanslet_sa[i].Code)
			{
				Ret = CodeTanslet_sa[i].KeyVal;
				Serial.println("Got a key!!!");
			}

		}
		Serial.println(results.value, HEX);
		irrecv.resume();
		//  delay(200);    
	}
	return Ret;
}
