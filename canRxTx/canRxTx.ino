// demo: CAN-BUS Shield, receive data
// and send it back, just for desired ID
#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId;
long unsigned int txId = 0x7FF;
unsigned char len = 0;
unsigned char rxBuf[8];
unsigned char txBuf[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x0F};


void setup()
{
  Serial.begin(9600);
  CAN.begin(CAN_500KBPS);                       // init can bus : baudrate = 500k 
 
  //Configure the CAN controller
  //configure mask and filters for the messages
  //we receive only std id with id 123 or 111
  CAN.init_Mask(0, 0, 0x07FF);

  //Buffer 0
  CAN.init_Filt(0, 0, 0x0123);
  CAN.init_Filt(1, 0, 0x0111);
  
  //Buffer 1
  CAN.init_Mask(1, 0, 0x07FF);
  CAN.init_Filt(2, 0, 0x0000);
  CAN.init_Filt(3, 0, 0x0000);
  CAN.init_Filt(4, 0, 0x0000);
  CAN.init_Filt(5, 0, 0x0000);

}

void loop()
{
  //checkReceive fcn, return 3 when message is availalbe  
  //returns 4 when no message arrived (check library code)
  if(CAN.checkReceive()==3){
     CAN.readMsgBuf(&len, rxBuf);              // Read data: len = data length, buf = data byte(s)
      rxId = CAN.getCanId();                    // Get message ID
      Serial.println("Received ID: ");
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
     }

     Serial.println();
     int l = sizeof(txBuf);
     Serial.print("Tx:");
     Serial.print(txId, HEX);
     Serial.print("  Data: ");
     for(int i = 0; i<l; i++)                // Print each byte of the data
     {
       if(txBuf[i] < 0x10)                     // If data byte is less than 0x10, add a leading zero
       {
         Serial.print("0");
       }
       Serial.print(txBuf[i], HEX);
       Serial.print(" ");
     }
     CAN.sendMsgBuf(txId, 0, 8, txBuf);
     delay(1000);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
