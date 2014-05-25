// demo: CAN-BUS Shield, send data

#include <can_shield.h>
#include <SPI.h>

void setup()
{
    Serial.begin(9600);
  
START_INIT:

    if(CAN_OK == CAN.begin(CAN_100KBPS))                   // init can bus : baudrate = 100k
    {
        Serial.println("CAN BUS Shield init ok!");
    }
    else
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(1000);
        goto START_INIT;
    }
}

void loop()
{
    unsigned char stmp[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    
    CAN.sendMsgBuf(0x00, 0, 8, stmp);   // send data:  id = 0x00, standrad flame, data len = 8, stmp: data buf
    delay(1000);                        // delay in uS to send the message again,every 1 second.
}

