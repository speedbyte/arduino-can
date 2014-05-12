//modified program based on the CJFowler Library
//library includes send and receive examples


// demo: CAN-BUS Shield, send data
#include <mcp_can.h>
#include <SPI.h>

int flag = 0;

void setup()
{
  Serial.begin(9600);
  // init can bus, baudrate: 100k
  if(CAN.begin(CAN_100KBPS) == CAN_OK){
    Serial.print("can init ok!!\r\n");
    flag = 1;
  }
  else{ 
    Serial.print("Can init fail!!\r\n");
    flag = 0;
  }
}

unsigned char stmp[8] = {0, 1, 2, 3, 4, 5, 6, 7};
void loop()
{
  if(flag == 1){
    // send data:  id = 0x00, standrad frame, data len = 8, stmp: data buf
    CAN.sendMsgBuf(0x00, 0, 8, stmp);  
    Serial.println("message sent");
  }
  if(flag == 0){
    Serial.println("CAN not initialized");
    if(CAN.begin(CAN_100KBPS)){
      Serial.print("can init ok!!\r\n");
      flag = 1;
    }
  }
  delay(1000);                       // send data per 1000ms
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
