/* 
 * Wrappers to make I/O functions available with C linkage. This allows C++
 * methods to be called from C code.
 *
 * Copyright 2012 The MathWorks, Inc. */


#include <inttypes.h>
#include "Arduino.h"
#include "Servo.h"

extern "C" { 
    void __cxa_pure_virtual(void);
}

extern "C" void Serial_begin(int port, long r) 
{
#ifdef _ROTH_MEGA2560_        
    switch(port) {
    case 0:
        Serial.begin(r); 
        break;
    case 1:
        Serial1.begin(r); 
        break;
    case 2:
        Serial2.begin(r); 
        break;  
    case 3:
        Serial3.begin(r); 
        break;    
    }
#else
        Serial.begin(r); 
#endif        
}

extern "C" void Serial_read(int port, int showOutStatus, uint8_t *outData, int *outStatus) 
{ 
	int libFcnOutput;
#ifdef _ROTH_MEGA2560_  /* Could do without this conditional */       
    switch(port) {
    case 0:
		libFcnOutput = Serial.read();
        break;
    case 1:
		libFcnOutput = Serial1.read();
        break;
    case 2:
		libFcnOutput = Serial2.read();
        break;  
    case 3:
		libFcnOutput = Serial3.read();
        break;    
    }    
#else
    libFcnOutput = Serial.read();
#endif          
    *outData = (uint8_t) libFcnOutput; 
    *outStatus = (libFcnOutput != -1);
}

extern "C" void Serial_write(int port, uint8_t * c, size_t s)
{ 
#ifdef _ROTH_MEGA2560_         
    switch(port) {
    case 0:
        Serial.write(c, s); 
        break;
    case 1:
        Serial1.write(c, s); 
        break;
    case 2:
        Serial2.write(c, s); 
        break;  
    case 3:
        Serial3.write(c, s); 
        break;    
    }    
#else
        Serial.write(c, s); 
#endif          
}

#if _RTT_NUMSERVOS_ != 0 
Servo myservos[_RTT_NUMSERVOS_];

extern "C" void MW_servoAttach(uint8_t nServo, uint8_t pinNumber) 
{
 	myservos[nServo].attach(pinNumber);
}

extern "C" void MW_servoWrite(uint8_t nServo, uint8_t inValue) 
{    
    myservos[nServo].write(inValue);
}

extern "C" int MW_servoRead(uint8_t nServo) 
{    
    return myservos[nServo].read();
}
#endif