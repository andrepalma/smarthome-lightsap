#define lightsap
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
const int PIN_REL3 = gv_PIN_REL3;
const int PIN_REL4 = gv_PIN_REL4;

boolean relVal1 = LOW;    // state of LED 1
boolean relVal2 = LOW;    // state of LED 2
boolean relVal3 = LOW;    // state of LED 2
boolean relVal4 = LOW;    // state of LED 2


enum LightStatus {
  ON,
  OFF
};

LightStatus light1Status = OFF;
LightStatus light2Status = OFF;
LightStatus light3Status = OFF;
LightStatus light4Status = OFF;




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

// void sendTimeForUp(){
//   String temp_str2;
//   char temp2[5];
//   temp_str2 = "TimeForUp=" + String(timeForUp);
//   temp_str2.toCharArray(temp2, temp_str2.length() + 1);
//   // client.publish(gv_shuttersTopicStatPower,convertIntToChar(shutCurrLevel));
//   // String messagePublish = "TimeForUp=" + temp2
//   Serial.printf("Msg to be send: %s",temp2);
//   client.publish(gv_shuttersTopicStatSettings,temp2);
// }

#ifdef lightsap1
  void light1ON(){
    digitalWrite(PIN_REL1, !relVal1);
    light1Status = ON;
    client.publish(gv_lights1TopicStatPower, "ON");
    Serial.println("Light1 ON.");
  }

  void light1OFF(){
    digitalWrite(PIN_REL1, relVal1);
    light1Status = OFF;
    client.publish(gv_lights1TopicStatPower, "OFF");
    Serial.println("Light1 OFF.");
  }

  void cmdLight1ON(){
    switch (light1Status) {
      case ON:
        Serial.println("Already on, so nothing.");
        break;
      case OFF:
        light1ON();
        break;
    }
  }

  void cmdLight1OFF(){
    switch (light1Status) {
      case ON:
        light1OFF();
        break;
      case OFF:
        Serial.println("Already off, so nothing.");
        break;
    }
  }

  void cmdLight1TOGGLE(){
    switch (light1Status) {
      case ON:
        light1OFF();
        break;
      case OFF:
        light1ON();
        break;
    }
  }
#endif //lightsap1

#ifdef lightsap2
  void light2ON(){
    digitalWrite(PIN_REL2, !relVal2);
    light2Status = ON;
    client.publish(gv_lights2TopicStatPower, "ON");
    Serial.println("Light2 ON.");
  }

  void light2OFF(){
    digitalWrite(PIN_REL2, relVal2);
    light2Status = OFF;
    client.publish(gv_lights2TopicStatPower, "OFF");
    Serial.println("Light2 OFF.");
  }

  void cmdLight2ON(){
    switch (light2Status) {
      case ON:
        // Serial.println("Already on, so nothing.");
        break;
      case OFF:
        light2ON();
        break;
    }
  }

  void cmdLight2OFF(){
    switch (light2Status) {
      case ON:
        light2OFF();
        break;
      case OFF:
        // Serial.println("Already off, so nothing.");
        break;
    }
  }

  void cmdLight2TOGGLE(){

    switch (light2Status) {
      case ON:
        light2OFF();
        break;
      case OFF:
        light2ON();
        break;
    }
  }
#endif  //lightsap2

#ifdef lightsap3
  void light3ON(){
    digitalWrite(PIN_REL3, !relVal3);
    light3Status = ON;
    client.publish(gv_lights3TopicStatPower, "ON");
    Serial.println("Light3 ON.");
  }

  void light3OFF(){
    digitalWrite(PIN_REL3, relVal3);
    light3Status = OFF;
    client.publish(gv_lights3TopicStatPower, "OFF");
    Serial.println("Light3 OFF.");
  }
  void cmdLight3ON(){
    switch (light3Status) {
      case ON:
        Serial.println("Already on, so nothing.");
        break;
      case OFF:
        light3ON();
        break;
    }
  }

  void cmdLight3OFF(){
    switch (light3Status) {
      case ON:
        light3OFF();
        break;
      case OFF:
        Serial.println("Already off, so nothing.");
        break;
    }
  }

  void cmdLight3TOGGLE(){
    switch (light3Status) {
      case ON:
        light3OFF();
        break;
      case OFF:
        light3ON();
        break;
    }
  }
#endif  //lightsap3

#ifdef lightsap4
  void light4ON(){
    digitalWrite(PIN_REL4, !relVal4);
    light4Status = ON;
    client.publish(gv_lights4TopicStatPower, "ON");
    Serial.println("Light4 ON.");
  }

  void light4OFF(){
    digitalWrite(PIN_REL4, relVal4);
    light4Status = OFF;
    client.publish(gv_lights4TopicStatPower, "OFF");
    Serial.println("Light4 OFF.");
  }
  void cmdLight4ON(){
    switch (light4Status) {
      case ON:
        Serial.println("Already on, so nothing.");
        break;
      case OFF:
        light4ON();
        break;
    }
  }

  void cmdLight4OFF(){
    switch (light4Status) {
      case ON:
        light4OFF();
        break;
      case OFF:
        Serial.println("Already off, so nothing.");
        break;
    }
  }

  void cmdLight4TOGGLE(){
    switch (light4Status) {
      case ON:
        light4OFF();
        break;
      case OFF:
        light4ON();
        break;
    }
  }
#endif  //lightsap4


void lightCheckState(){

}

void lightsSetup(){

  // timeForUp = EEPROMReadlong(EEP_OFFSET_UP);
  // timeForDown = EEPROMReadlong(EEP_OFFSET_DOWN);
  // levelOnEEP = EEPROMReadInt(EEP_OFFSET_LEVEL);

#ifdef lightsap1
  pinMode(PIN_REL1, OUTPUT);
  digitalWrite(PIN_REL1, relVal1);
#endif

#ifdef lightsap2
  pinMode(PIN_REL2, OUTPUT);
  digitalWrite(PIN_REL2, relVal2);
#endif

#ifdef lightsap3
  pinMode(PIN_REL3, OUTPUT);
  digitalWrite(PIN_REL3, relVal3);
  #endif

#ifdef lightsap4
  pinMode(PIN_REL4, OUTPUT);
  digitalWrite(PIN_REL4, relVal4);
#endif
}

void lightsLoop(){
  lightCheckState();

}
