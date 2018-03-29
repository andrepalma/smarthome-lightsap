#include <EEPROM.h>
#define MEM_ALOC_SIZE 30

// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte valueFromEEP;

const int EEP_OFFSET_LEVEL = 0;
const int EEP_OFFSET_UP = 5;
const int EEP_OFFSET_DOWN = 10;


const int PIN_REL1 = gv_PIN_REL1;
const int PIN_REL2 = gv_PIN_REL2;

boolean ledValUp = false;    // state of LED 1
boolean ledValdn = false;    // state of LED 2
boolean relVal1 = 1;    // state of LED 1
boolean relVal2 = 1;    // state of LED 2



long ratioUp = 0;
long ratioDown = 0;

int shutLevelToGo = 0;
int shutCurrLevel = 0;  // 0 - 100; 0 - Open, 100 Close
char chrShutCurrLevel[10] = "";

long shutCurrMili = 0;


enum LightStatus {
  ON,
  OFF
};

LightStatus light1Status = OFF;



void convertCurrLevelToChar(){
  String temp_str2;
  temp_str2 = String(shutCurrLevel);
  temp_str2.toCharArray(chrShutCurrLevel, temp_str2.length() + 1);
}

void readeep(){
  if (address > 50) return;
  valueFromEEP = EEPROM.read(address);
  Serial.print(address);
  Serial.print("\t");
  Serial.print(valueFromEEP, DEC);
  Serial.println();
  address = address + 1;
  if (address == EEPROM.length()) {
    address = 0;
  }
}

void EEPROMWritelong(int addressOffSet, long value){
  EEPROM.begin(MEM_ALOC_SIZE);
  //Decomposition from a long to 4 bytes by using bitshift.
  //One = Most significant -> Four = Least significant byte
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);

  EEPROM.write(addressOffSet, four);
  EEPROM.write(addressOffSet + 1, three);
  EEPROM.write(addressOffSet + 2, two);
  EEPROM.write(addressOffSet + 3, one);
  // Serial.printf("Bytes Write, Four: %d\t Three: %d\t Two: %d\t One: %d\n", (int)four, (int)three, (int)two, (int)one);
  EEPROM.end();
}

void EEPROMWriteint (int addressOffSet, int value){
  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.write(addressOffSet, value);
  EEPROM.end();
}

long EEPROMReadlong(long address3){
  //Read the 4 bytes from the eeprom memory.
  long long_value;

  EEPROM.begin(MEM_ALOC_SIZE);
  byte four = EEPROM.read(address3);
  byte three = EEPROM.read(address3 + 1);
  byte two = EEPROM.read(address3 + 2);
  byte one = EEPROM.read(address3 + 3);
  EEPROM.end();

  long_value  = (long)one << 24;
  long_value += (long)two << 16;
  long_value += (long)three << 8;
  long_value += (long)four;

  return long_value;
}

int EEPROMReadInt(long addressOffSet){
  EEPROM.begin(MEM_ALOC_SIZE);
  uint8_t readvalue = EEPROM.read(addressOffSet);
  int ret = (int) readvalue;
  EEPROM.end();
  Serial.printf("IntLevel: %d\n", ret);
  return ret;
}

void writeLevelToEEPROM(){
  EEPROMWriteint(EEP_OFFSET_LEVEL, shutCurrLevel);
}

void writeTimeUpToEEPROM(long TimeGoUp){
  EEPROMWritelong(EEP_OFFSET_UP, TimeGoUp);
  timeForUp = TimeGoUp;
}

void writeTimeDnToEEPROM(long TimeGoDn){
  EEPROMWritelong(EEP_OFFSET_DOWN, TimeGoDn);
  timeForDown = TimeGoDn;
}


void sendTimeForUp(){
  String temp_str2;
  char temp2[5];
  temp_str2 = "TimeForUp=" + String(timeForUp);
  temp_str2.toCharArray(temp2, temp_str2.length() + 1);
  // client.publish(gv_shuttersTopicStatPower,convertIntToChar(shutCurrLevel));
  // String messagePublish = "TimeForUp=" + temp2
  Serial.printf("Msg to be send: %s",temp2);
  client.publish(gv_shuttersTopicStatSettings,temp2);

}

void sendTimeForDn(){
  String temp_str2;
  char temp2[5];
  temp_str2 = "TimeForDn=" + String(timeForDown);
  temp_str2.toCharArray(temp2, temp_str2.length() + 1);
  // client.publish(gv_shuttersTopicStatPower,convertIntToChar(shutCurrLevel));
  // String messagePublish = "TimeForUp=" + temp2
  Serial.printf("Msg to be send: %s",temp2);
  client.publish(gv_shuttersTopicStatSettings,temp2);
}

void light1ON(){
  digitalWrite(PIN_REL1, relVal1);
  light1Status = ON;
  Serial.println("Light ON.");
}

void light1OFF(){
  digitalWrite(PIN_REL1, !relVal1);
  light1Status = OFF;
  Serial.println("Light OFF.");
}



void cmdLightON(){

  switch (light1Status) {
    case ON:
      Serial.println("Already on, so nothing.");
      break;
    case OFF:
      light1OFF();
      break;
  }
}

void cmdLightOFF(){

  switch (light1Status) {
    case ON:
      light1ON();
      break;
    case OFF:

      Serial.println("Already off, so nothing.");
      break;
  }
}


void cmdLightTOGGLE(){

  switch (light1Status) {
    case ON:
      light1OFF();
      break;
    case OFF:
      light1ON();
      break;
  }
}


void lightCheckState(){

}

void lightsSetup(){

  // timeForUp = EEPROMReadlong(EEP_OFFSET_UP);
  // timeForDown = EEPROMReadlong(EEP_OFFSET_DOWN);
  // levelOnEEP = EEPROMReadInt(EEP_OFFSET_LEVEL);

  // shutCurrLevel = levelOnEEP;
  pinMode(PIN_REL1, OUTPUT);
  digitalWrite(PIN_REL1, !relVal1;
  // pinMode(PIN_REL2, OUTPUT);
  // digitalWrite(PIN_REL_DN, !relValDn);

}

void lightsLoop(){
  lightCheckState();

}
