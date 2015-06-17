#ifndef BeachBuddyCommunication_h
#define BeachBuddyCommunication_h

#include "Arduino.h"

#define SERIAL_TXRX_BUFFER_LEN 255
#define SERIAL_FRAME_START_DELIMITER    0x7C
#define SERIAL_NUM_BYTES_HIGH   (UINT16) 1
#define SERIAL_NUM_BYTES_LOW    (UINT16) 2
#define SERIAL_COMMAND1 		(UINT16) 3
#define SERIAL_COMMAND2 		(UINT16) 4
#define SERIAL_DATA_START		(UINT16) 5

#define BAUD_RATE 57600

class PiComm {
public:
PiComm(PiComm *comm);
private:
void PiSerialProcessIncomingByte(UINT8 ByteR, PiComm *comm);		
void PiProcessRxCommand(PiComm *comm);
void PiSerialClearRxSerialFrame(PiComm *Piserclear);
UINT8 Index;
UINT16 Numbytes;
UINT16 Command;
UINT8 Data[SERIAL_TXRX_BUFFER_LEN];
UINT8 checksum;
UINT8 RxReady;
};

typedef enum SerialCommands {
	SERIAL_CMD_DIR_FORWARD 		= 0x0000,
	SERIAL_CMD_DIR_RIGHT 		= 0x0001,
	SERIAL_CMD_DIR_LEFT 		= 0x0002,
	SERIAL_CMD_DIR_BACKWAARD	= 0x0003
}_SerialCommands;

#endif