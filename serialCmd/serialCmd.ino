//Send control command over RS232

unsigned char start_cmd[10]= {0x0D, 0x01, 0x53, 0x31, 0x6E, 0x0D, 0x01, 0x53, 0x31, 0x6E};

unsigned char stop_cmd[10] = {0x0D, 0x01, 0x43, 0x31, 0x7E, 0x0D, 0x01, 0x43, 0x31, 0x7E};


void setup()
{
  //baudrate configuration for Serial communication
  Serial.begin(2400);
}

void loop()
{
  //sending the fist command
  for(int i = 0; i<10; i++){
    Serial.write(start_cmd[i]);
  }
  delay(3000);
  
  //after a 3s delay, send second command
  for(int i = 0; i<10; i++){
    Serial.write(stop_cmd[i]);
  }
  delay(3000);
}

