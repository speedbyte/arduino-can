// Final sketch

// including configuration for the CAN communication
// and the corresponding action regarding the ID
// of the incomming message in order to control
// a relee in an external board.

#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId;
long unsigned int txId = 0x7FF;
unsigned char len = 0;
unsigned char rxBuf[8];
unsigned char txBuf[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x0F};
unsigned char start_cmd[10]= {0x0D, 0x01, 0x53, 0x31, 0x6E, 0x0D, 0x01, 0x53, 0x31, 0x6E};
unsigned char stop_cmd[10] = {0x0D, 0x01, 0x43, 0x31, 0x7E, 0x0D, 0x01, 0x43, 0x31, 0x7E};


void setup()
{
  //Serial configuration for relee control
  Serial.begin(2400);
  
  //Serial configuration for computer communication (debugging)
  //Serial.begin(9600);
  
  //init an bus : baudrate = 500k
  CAN.begin(CAN_500KBPS); 
 
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

void printCANmsg_serial(){
  Serial.println("Received ID: ");
  Serial.print(rxId, HEX);
  Serial.print("  Data: ");
  //print each byte of data
  for(int i = 0; i<len; i++){
    //add a 0 for 0x00 representation when data is less than 0x10
    if(rxBuf[i] < 0x10){
      Serial.print("0");
    }
    Serial.print(rxBuf[i], HEX);
    Serial.print(" ");
  }
}

void sendSerialCmd(unsigned char cmd[]){
  for(int i = 0; i<10; i++){
    Serial.write(cmd[i]);
  }
}


//Main execution program
void loop()
{
  //checkReceive fcn, return 3 when message is availalbe  
  //returns 4 when no message arrived (check library code)
  if(CAN.checkReceive()==3){
    //Read data: len = data length, buf = data byte(s) 
    CAN.readMsgBuf(&len, rxBuf);              
    //Get message ID
    rxId = CAN.getCanId(); 
    //Serial print to computer for debugging
    //printCANmsg_serial();
  
    
    /*
    //Control with ID check
    if(rxId == 0x123){
      sendSerialCmd(start_cmd);
    }
    else if (rxId = 111){
      sendSerialCmd(stop_cmd);
    }
    */
    
    //Control with first bit of Data field check
    if(rxBuf[0] == 0x01){
      sendSerialCmd(start_cmd);
    }
    else if(rxBuf[0] == 0x00){
      sendSerialCmd(stop_cmd);
    }
    
    //echo the received message to the BT device
    // send data:  id = rxID, standrad frame, data len = 8, stmp: data buffer (received data)
    CAN.sendMsgBuf(rxId, 0, 8, rxBuf);   
  }

}

