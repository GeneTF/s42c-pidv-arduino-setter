#include <SoftwareSerial.h>

const byte rxPin = 2;
const byte txPin = 3;

String fullInput = "";

// Set up a new SoftwareSerial object
SoftwareSerial S42C = SoftwareSerial(rxPin, txPin);

const byte syncBits = 0b10101000;
const byte readMode = 0b10000000;
const byte writeMode = 0b00000000;

const byte enabledAddress = 0x17;
const byte disabled = 1;
const byte enabled = 0;

const byte readStepModePIDaddress = 0x86;
const byte readUARTModePIDAddress = 0x90;

const byte setMotorModeAddress = 0x13;
const byte setUARTModeAddress = 0x20;
const byte setStepModeAddress = 0x33;

const byte setP = 0x06;
const byte setI = 0x07;
const byte setV = 0x08;
const byte setD = 0x09;

const byte saveParams = 0x18;

const bool doRead = true;

void setup() {
  // Define pin modes for TX and RX
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  
  // Start the serial communication at 9600 baud rate
  Serial.begin(115200);
  Serial.println("Serial communication started...");

  S42C.begin(115200);

  delay(100);

  //saveParameters();
  //setPvalue(50);
  //setIvalue(10);
  //setDvalue(0);
  //setVvalue(0);
  readStepModePID();
}

void writeGenericInput() {
  byte dataSize = 0b00000010; //sizeof(setStepModeAddress);
  byte byte1 = syncBits | dataSize;
  byte byte2 = writeMode | saveParams;
  byte byte3 = 0; //setStepModeAddress;
  byte byte4 = 0;

  printBinary(byte1);
  printBinary(byte2);
  printBinary(byte3);
  printBinary(byte4);

  S42C.write(byte1); 
  S42C.write(byte2);
  S42C.write(byte3);
  S42C.write(byte4);
}

void setPvalue(int Pin) {
  writeGenericPIDValue(Pin, setP);
}

void setIvalue(int Iin) {
  writeGenericPIDValue(Iin, setI);
}

void setDvalue(int Din) {
  writeGenericPIDValue(Din, setD);
}

void setVvalue(int Vin) {
  writeGenericPIDValue(Vin, setV);
}

void writeGenericPIDValue(int valueIn, byte addressIn) {
  int value = valueIn;

  byte dataSize = sizeof(value); //sizeof(setStepModeAddress);
  byte byte1 = syncBits | dataSize;
  byte byte2 = writeMode | addressIn;
  byte byte3 = value >> 8; //setStepModeAddress;
  byte byte4 = value;

  printBinary(byte1);
  printBinary(byte2);
  printBinary(byte3);
  printBinary(byte4);

  S42C.write(byte1); 
  S42C.write(byte2);
  S42C.write(byte3);
  S42C.write(byte4);
}

void saveParameters() {
  byte dataSize = 0b00000010; //sizeof(setStepModeAddress);
  byte byte1 = syncBits | dataSize;
  byte byte2 = writeMode | saveParams;
  byte byte3 = 0; //setStepModeAddress;
  byte byte4 = 0;

  printBinary(byte1);
  printBinary(byte2);
  printBinary(byte3);
  printBinary(byte4);

  S42C.write(byte1); 
  S42C.write(byte2);
  S42C.write(byte3);
  S42C.write(byte4);
}

void readStepModePID() {
  byte dataSize = 0; //sizeof(setStepModeAddress);
  byte byte1 = syncBits | dataSize;
  byte byte2 = readMode | readStepModePIDaddress;

  S42C.write(byte1); 
  S42C.write(byte2);
}

void loop() {
  if (S42C.overflow()) {
        Serial.println("S42C overflow!");
  }

  if (S42C.available() > 0 && doRead) {
    byte input1 = S42C.read();
    fullInput += (char) input1;
    
    Serial.print(input1);
    Serial.print(" : ");
    Serial.print((char) input1);
    Serial.print(" : ");
    Serial.println(fullInput);
  }

}

void printBinary(byte b) {
  for (int i = 7; i >= 0; i--) {
    byte bit = (b >> i) & 1;  // Shift bit and mask with 1 to extract each bit
    Serial.print(bit);         // Print the bit (either 0 or 1)
  }
  Serial.println();  // New line after the binary representation
}

