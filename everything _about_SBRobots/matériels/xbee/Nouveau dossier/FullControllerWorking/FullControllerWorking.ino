
int digitaldataMSB;
int digitaldataLSB;
int joystickrightMSB;
int joystickrightLSB;
int joystickleftMSB;
int joystickleftLSB;
int throwingpotMSB;
int throwingpotLSB;
byte bitread[28];

int qbswivelright = 2;
int qbthrowingspeed = 3;
int qbthrowingspeedvalue;
int qbswivelleft = 4;
int rightwheel = 9;
int rightwheelspeed;
int rightwheelspeedvalue;
int leftwheel = 10;
int leftwheelspeed;
int leftwheelspeedvalue;
int qbthrow = 11;

int inputPin = A0;
int scaleValue = 0;
int PWMvaluetoMotorDriver = 0;

float analogReading = 0;


void setup(){
  Serial.begin(9600);
  //for more info go here: http://forum.arduino.cc/index.php/topic,16612.0.html 
  //but i basically just took the default PWM frequency and tweeked it to get better resolution, the default is ~1kHz
  TCCR1B = TCCR1B & 0b11111000 | 0x03;//set the PWM frequency of pins 9 and 10 to 488Hz
  TCCR2B = TCCR2B & 0b11111000 | 0x04;//set the PWM frequency of pins 11 and 3 to 488Hz
}

void loop(){
  if(Serial.available()>27){
      for (int i = 0; i<28; i++){
        bitread[i] = Serial.read();
        //Serial.print(i);
        //Serial.print(": ");
        //Serial.print(bitread[i]);
        //Serial.print(",");
      }
      //Serial.println();
  }
/*
bit assignments

bitread 19- MSB Digital data
bitread 20- LSB Digital data
bitread 21- MSB Throwing Potentiometer
bitread 22- LSB Throwing Potentiometer
bitread 23- MSB Left Joystick
bitread 24- LSB Left Joystick
bitread 25- MSB Right Joystick
bitread 26- LSB Right Joystick
*/
digitaldataMSB = bitread[19];
digitaldataLSB = bitread[20];
throwingpotMSB = bitread[21];
throwingpotLSB = bitread[22];
joystickleftMSB = bitread[23];
joystickleftLSB = bitread[24];
joystickrightMSB = bitread[25];
joystickrightLSB = bitread[26];
/*
Serial.print("digitaldataMSB: ");
Serial.println(digitaldataMSB);
Serial.print("digitaldataLSB: ");
Serial.println(digitaldataLSB);
Serial.print("throwingPotMSB: ");
Serial.println(throwingPotMSB);
Serial.print("throwingPotLSB: ");
Serial.println(throwingPotLSB);
Serial.print("joystickLeftMSB: ");
Serial.println(joystickLeftMSB);
Serial.print("joystickLeftLSB: ");
Serial.println(joystickLeftLSB);
Serial.print("joystickRightMSB: ");
Serial.println(joystickRightMSB);
Serial.print("joystickRightLSB: ");
Serial.println(joystickRightLSB);
*/



//Digital data for qb swivel and fire
if (digitaldataMSB == 0){//fire pb pressed
  digitalWrite(qbswivelleft,HIGH); 
}
if (digitaldataMSB == 4){//fire pb released
  digitalWrite(qbswivelleft,LOW); 
}
  
switch (digitaldataLSB){
  case 8: //just qbswivelright pressed
    digitalWrite(qbswivelright,HIGH);
    break;
  case 32: //just qbthrow pressed
    digitalWrite(qbthrow, HIGH);
    break;
  case 40://both qbswivelright and qbthrow pressed
    digitalWrite(qbswivelright,HIGH);
    digitalWrite(qbthrow, HIGH);
    break;
  default://neither qbswivelright or qbthrow pressed
    digitalWrite(qbswivelright,LOW);
    digitalWrite(qbthrow, LOW);
}

//motor and throwing speed signals
     qbthrowingspeedvalue = throwingpotLSB +(throwingpotMSB*256);
     //Serial.println(qbthrowingspeedvalue);
     qbthrowingspeed = map(qbthrowingspeedvalue,0,1023,141.25,232.5);//scale value from 0-1023 to 141.25-232.5
     analogWrite(qbthrow,qbthrowingspeed);

     leftwheelspeedvalue = joystickleftLSB +(joystickleftMSB*256);
     //Serial.println(leftwheelspeedvalue);
     leftwheelspeed = map(leftwheelspeedvalue,0,1023,141.25,232.5);//scale value from 0-1023 to 141.25-232.5
     analogWrite(leftwheel,leftwheelspeed);
  
     rightwheelspeedvalue = joystickrightLSB +(joystickrightMSB*256);
     //Serial.println(rightwheelspeedvalue);
     rightwheelspeed = map(rightwheelspeedvalue,0,1023,141.25,232.5);//scale value from 0-1023 to 141.25-232.5
     analogWrite(rightwheel,rightwheelspeed);
      
      
}
