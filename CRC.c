//***********************************************************
//контрольная сумма 
//***********************************************************
int16 crc = 0; 
int16 getChecksum()
	{
		int16 chSum = 0; 
		int8 temp[2] = {0, 0}; 
		int32 adr = (getenv("Program_memory")-2 ); 
		//sendRS(0x33);
		read_program_memory(adr, temp, 2);
		//sendRS(temp[1]);
		//sendRS(temp[0]); 
		chSum = make16(temp[1], temp[0]);
		return chSum; 
	}
//***********************************************************