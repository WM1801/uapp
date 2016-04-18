#include "ioPin.h"

int1 getStateOutError()
{
	int1 b = 0;  
	if(!input(STATE_OUT))
	{
		b = 1; 
	}
	return b; 
}