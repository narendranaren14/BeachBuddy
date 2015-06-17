#include <BeachBuddyCommunication.h>
PiComm::PiComm(PiComm *comm)
{
	PiSerialClearRxSerialFrame(comm);
	serial.begin(BAUD_RATE);
}

void PiComm::PiSerialProcessIncomingByte(UINT8 ByteR, PiComm *comm )
{
	while(serial.available() > 0)
	{
		if(ByteR == SERIAL_FRAME_START_DELIMITER)
		{
			PiSerialClearRxSerialFrame(comm);
			comm->Index = SERIAL_NUM_BYTES_HIGH;
		}
		else if (Index == SERIAL_NUM_BYTES_HIGH)
		{
			comm->Numbytes  = (UINT16)ByteR;
			comm->Numbytes *= 256;
			comm->checksum += ByteR;
			comm->Index 	= SERIAL_NUM_BYTES_LOW;
		}
		else if(Index == SERIAL_NUM_BYTES_LOW){
			comm->Numbytes |= ByteR;
			comm->checksum += ByteR;
			comm->Index 	= SERIAL_COMMAND1;
			if(comm->NumBytes >= SERIAL_TXRX_BUFFER_LEN)
        	{
            	comm->NumBytes = SERIAL_TXRX_BUFFER_LEN;
        	}
		}
		else if(comm->Index == SERIAL_COMMAND1)
		{
			comm->Command   = (UINT16)ByteR;
			comm->Command  *= 256;
			comm->checksum += ByteR;			  
			comm->Index 	= SERIAL_COMMAND2;
		}
		else if(Index == SERIAL_COMMAND2)
		{
			comm->Command  |= (UINT16)ByteR;			
			comm->checksum += ByteR;			  
			comm->Index 	= SERIAL_DATA_START;
		}
		else if (((comm->Index - SERIAL_DATA_START) < comm->NumBytes) && (comm->NumBytes != 0))
		{
			comm->Data[comm->Index - SERIAL_DATA_START] = ByteR;
			comm->checksum +=  ByteR;
			comm->Index 	= comm->Index + 1;
		}
		else if ((comm->Index - SERIAL_DATA_START) == comm->NumBytes))
		{
			comm->checksum = (UINT8) (~comm->checksum);
			if(comm->checksum == ByteR)
			{
				comm->RxReady = TRUE;
				break;
			}
		}
		else
		{
			PiSerialClearRxSerialFrame(comm);
			break;
		}
	}
}

void PiProcessRxData(PiComm *comm)
{
	switch(comm->Command){

		case SERIAL_CMD_DIR_FORWARD:
		break;
		case SERIAL_CMD_DIR_RIGHT:
		break;
		case SERIAL_CMD_DIR_LEFT:
		break;
		case SERIAL_CMD_DIR_BACKWAARD:
		break;
		default:
		break;
	}
}

void PiSerialClearRxSerialFrame (PiComm *Piserclear)
{
	memset(Piserclear->Data,0x00,SERIAL_TXRX_BUFFER_LEN);
	Piserclear->Index    = 0;
	Piserclear->Numbytes = 0;
	Piserclear->Command  = 0;
	Piserclear->checksum = 0;
	Piserclear->RxReady  = 0;		
}