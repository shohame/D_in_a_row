#ifndef _IR_INPUT_H_
#define _IR_INPUT_H_


#define IR_VCC  8

#define IR_RECEIVER_PIN   11  

#define NUM_OF_KEY_CODE 17

#define en_NO_KEY              -1
#define en_HASHTAG_KEY      100
#define en_STAR_KEY       101 
#define en_LEFT_KEY            102
#define en_RIGHT_KEY           103 
#define en_UP_KEY               104
#define en_DOWN_KEY             105 
#define en_OK_KEY               106 



class IR_Input
{
public:
	IR_Input();
  char Receive();
  char Receive_safe();
	void Setup();
};




#endif // #ifndef _IR_INPUT_H_



