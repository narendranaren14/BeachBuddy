#include "BeachBuddyCommunication.h"

PiComm::PiComm()
{
	PiSerialClearRxSerialFrame();
	Serial.begin(BAUD_RATE);
}

void PiComm::PiSerialProcessIncomingByte(unsigned char ByteR)//, PiComm *comm )
{	
	while(RxReady == false)
	{
		//unsigned char ByteR = Serial.read();	
		if(ByteR == SERIAL_FRAME_START_DELIMITER)
		{
			PiSerialClearRxSerialFrame();
			Index = SERIAL_NUM_BYTES_HIGH;
			//Serial.println("B1");
			//Serial.println(ByteR, HEX);
			break;
		}
		else if (Index == SERIAL_NUM_BYTES_HIGH)
		{
			Numbytes  = (UINT16)ByteR;
			Numbytes *= 256;
			checksum += ByteR;
			Index 	= SERIAL_NUM_BYTES_LOW;
			//Serial.println("B2");
			//Serial.println(ByteR, HEX);
			break;
		}
		else if(Index == SERIAL_NUM_BYTES_LOW){
			Numbytes |= ByteR;
			checksum += ByteR;
			Index 	= SERIAL_COMMAND1;
			if(Numbytes >= SERIAL_TXRX_BUFFER_LEN)
        	{
            	Numbytes = SERIAL_TXRX_BUFFER_LEN;
        	}
        	//Serial.println("B3");
        	//Serial.println(ByteR, HEX);
        	break;
		}
		else if(Index == SERIAL_COMMAND1)
		{
			Command   = (UINT16)ByteR;
			Command  *= 256;
			checksum += ByteR;			  
			Numbytes--;
			Index 	= SERIAL_COMMAND2;
			//Serial.println("B4");
			//Serial.println(ByteR, HEX);			
			break;
		}
		else if(Index == SERIAL_COMMAND2)
		{
			Command  |= (UINT16)ByteR;			
			checksum += ByteR;			  
			Numbytes--;
			Index 	= SERIAL_DATA_START;
			//Serial.println("B5");
			//Serial.println(Numbytes, HEX);			
			break;
		}
		else if (((Index - SERIAL_DATA_START) < Numbytes) && (Numbytes != 0))
		{
			Data[Index - SERIAL_DATA_START] = ByteR;
			checksum +=  ByteR;
			Index 	= Index + 1;
			//Serial.println("B6");
			//Serial.println(ByteR, HEX);			
			break;
		}
		else if ((Index - SERIAL_DATA_START) == Numbytes)
		{
			//Serial.println("B0");
			//Serial.println(checksum, HEX);
			checksum = (~checksum);
			checksum &= 0xFF;
			//Serial.println("B0");
			//Serial.println(checksum, HEX);
			if(checksum == ByteR)
			{
				RxReady = true;
				//Serial.println("B7");
				//break;
			}
			
			break;
		}
		else
		{
			PiSerialClearRxSerialFrame();
			break;
		}
	}
}

void PiComm::PiProcessRxData()
{
	
}

void PiComm::PiSerialClearRxSerialFrame()
{
	memset(Data,0x00,SERIAL_TXRX_BUFFER_LEN);
	Index    = 0;
	Numbytes = 0;
	Command  = 0;
	checksum = 0;
	RxReady  = 0;		
}