// demo: CAN-BUS Shield, receive data
// and send it back, just for desired ID
#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

//MCP_CAN CAN0(10);                               // Set CS to pin 10


void setup()
{
  Serial.begin(9600);

  CAN.begin(CAN_100KBPS);                       // init can bus : baudrate = 500k 
  pinMode(2, INPUT);                            // Setting pin 2 for /INT input

  //Configure the CAN controller
  //configure mask and filters for the messages
  //we receive only std id with id 123 or 111
  CAN.init_Mask(0, 0, 0x0123);

  //Buffer 0
  CAN.init_Filt(0, 0, 0x0123);
  CAN.init_Filt(1, 0, 0x0111);
  
  //Buffer 1
  CAN.init_Mask(1, 0, 0x0EFF);
  CAN.init_Filt(2, 0, 0x0000);
  CAN.init_Filt(3, 0, 0x0000);
  CAN.init_Filt(4, 0, 0x0000);
  CAN.init_Filt(5, 0, 0x0000);


  Serial.println("MCP2515 Library Receive Example...");
  
   
}

void loop()
{
    if(CAN.checkReceive()==3){
     CAN.readMsgBuf(&len, rxBuf);              // Read data: len = data length, buf = data byte(s)
      rxId = CAN.getCanId();                    // Get message ID
      Serial.print("ID: ");
      Serial.print(rxId, HEX);
      Serial.print("  Data: ");
      for(int i = 0; i<len; i++)                // Print each byte of the data
      {
        if(rxBuf[i] < 0x10)                     // If data byte is less than 0x10, add a leading zero
        {
          Serial.print("0");
        }
        Serial.print(rxBuf[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
      CAN.sendMsgBuf(rxId, 0, 8, rxBuf);   // send data:  id = 0x00, standrad frame, data len = 8, stmp: data buf
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
