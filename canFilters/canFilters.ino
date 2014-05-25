// demo: CAN-BUS Shield, receive data
// Receive and print the received message
// receiving just ID 123 and 111
#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];


void setup()
{
  Serial.begin(9600);

  CAN.begin(CAN_100KBPS);                       // init can bus : baudrate = 100k 
  pinMode(2, INPUT);                            // Setting pin 2 for /INT input

  //Configure the CAN controller
  //configure mask and filters for the messages
  //we receive only std id with id 123 or 111
  CAN.init_Mask(0, 0, 0x0123);
  CAN.init_Filt(0, 0, 0x0123);
  CAN.init_Filt(1, 0, 0x0123);
  
  //Buffer 1
  CAN.init_Mask(1, 0, 0x0123);
  CAN.init_Filt(2, 0, 0x0123);
  CAN.init_Filt(3, 0, 0x0123);
  CAN.init_Filt(4, 0, 0x0123);
  CAN.init_Filt(5, 0, 0x0123);
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
    }
}

