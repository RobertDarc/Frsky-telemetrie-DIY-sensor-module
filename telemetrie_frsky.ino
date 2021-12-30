//************For Frsky telemetrie diy sensor Dec 2021*********
//**                  Robert D'Arcangelo              *********
//**        Test it on the Frsky x20s tranmitter      *********
//*************************************************************



#include <SPort.h>
#include <Thermistor.h>
#include <NTC_Thermistor.h>




#define SPORT_PIN 3
#define SPORT_PHYSICAL_ID

SPortHub hub(0x12, 3); 

//SPortHub hub(SPORT_PHYSICAL_ID, SPORT_PIN);

SimpleSPortSensor IO1Sensor(0x5200);  
SimpleSPortSensor IO2Sensor(0x5201);  
SimpleSPortSensor IO3Sensor(0x5210);  
SimpleSPortSensor IO4Sensor(0x5202);  
SimpleSPortSensor IO5Sensor(0x5203);
SimpleSPortSensor IO6Sensor(0x5204); 
 
SimpleSPortSensor AN1Sensor(0x5205);  
SimpleSPortSensor AN2Sensor(0x5206);
SimpleSPortSensor AN3Sensor(0x5207);
SimpleSPortSensor AN4Sensor(0x5208);

SimpleSPortSensor ANXSensor(0x5209);
SimpleSPortSensor ANYSensor(0x5211);
SimpleSPortSensor ANZSensor(0x5212);
 
SimpleSPortSensor ANTSensor(0x5213);
 
 

const int buttonPin1 = 7;     // I/O1
const int buttonPin2 = 8;     // I/O2
const int buttonPin3 = 9;     // I/O3
const int buttonPin4 = 10;    // I/O4
const int buttonPin5 = 11;    // I/O5
const int buttonPin6 = 12;    // I/O6

const int analogInPin1 = A0;   //AN1
const int analogInPin2 = A1;   //AN2
const int analogInPin3 = A2;   //AN3
const int analogInPin4 = A3;   //AN4

const int analogInPinX = A4;   //gyro X
const int analogInPinY = A5;   //Gyro Y
const int analogInPinZ = A6;   //AN5

//const int analogInPinT = A7;   //temp sensor
 


int buttonState4 = 0;
int buttonState5 = 0;
int buttonState6 = 0;

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;

int sensorValue1 = 0;    
int sensorValue2 = 0;    
int sensorValue3 = 0;    
int sensorValue4 = 0; 

int sensorValueX = 0; 
int sensorValueY = 0; 
int sensorValueZ = 0; 

double sensorValueT = 0; 

int SensX=0;



const int ledPin = LED_BUILTIN;  


#define SENSOR_PIN             A7
#define REFERENCE_RESISTANCE   8800  //10820
#define NOMINAL_RESISTANCE     10000
#define NOMINAL_TEMPERATURE    25
#define B_VALUE                3950

Thermistor* thermistor;




void setup() {


thermistor = new NTC_Thermistor(
    SENSOR_PIN,
    REFERENCE_RESISTANCE,
    NOMINAL_RESISTANCE,
    NOMINAL_TEMPERATURE,
    B_VALUE
  );



 // Serial.begin(9600);
  
  hub.registerSensor(IO1Sensor);
  hub.registerSensor(IO2Sensor);
  hub.registerSensor(IO3Sensor); 
  hub.registerSensor(IO4Sensor);
  hub.registerSensor(IO5Sensor);
  hub.registerSensor(IO6Sensor);

  hub.registerSensor(AN1Sensor); 
  hub.registerSensor(AN2Sensor);
  hub.registerSensor(AN3Sensor);
  hub.registerSensor(AN4Sensor);

  hub.registerSensor(ANXSensor);
  hub.registerSensor(ANYSensor);
  hub.registerSensor(ANZSensor);

  hub.registerSensor(ANTSensor);

  hub.begin();


   pinMode(ledPin, OUTPUT);
     
   pinMode(buttonPin1, INPUT);
   pinMode(buttonPin2, INPUT);
   pinMode(buttonPin3, INPUT);
   pinMode(buttonPin4, INPUT);
   pinMode(buttonPin5, INPUT);
   pinMode(buttonPin6, INPUT);   

   pinMode(7, INPUT_PULLUP);
   pinMode(8, INPUT_PULLUP);
   pinMode(9, INPUT_PULLUP);

   pinMode(10, INPUT_PULLUP);
   pinMode(11, INPUT_PULLUP);
   pinMode(12, INPUT_PULLUP);
   
}


//**************************************main program*******************************************************************************

void loop() {

   buttonState1 = digitalRead(buttonPin1);  //inlezen IO channels 1....6
   buttonState2 = digitalRead(buttonPin2);
   buttonState3 = digitalRead(buttonPin3);
   buttonState4 = digitalRead(buttonPin4);
   buttonState5 = digitalRead(buttonPin5);
   buttonState6 = digitalRead(buttonPin6);

   sensorValue1 = analogRead(analogInPin1);  //inlezen AD channels 1....4
   sensorValue2 = analogRead(analogInPin2);
   sensorValue3 = analogRead(analogInPin3);
   sensorValue4 = analogRead(analogInPin4);

   sensorValueX = analogRead(analogInPinX);  //inlezen Gyro X,Y,Z
   sensorValueY = analogRead(analogInPinY);
   sensorValueZ = analogRead(analogInPinZ);

   sensorValueT = thermistor->readCelsius();  //inlezen Temp


  
  
  hub.handle();

 if (buttonState1 == LOW) {        //To filter input channels 1...6    HIGH / LOW
    IO1Sensor.value = 1;  
  } else {   
    IO1Sensor.value = 0;  
  }


if (buttonState2 == LOW) {
    IO2Sensor.value = 1;  
  } else {   
    IO2Sensor.value = 0;  
  }

if (buttonState3 == LOW) {
    IO3Sensor.value = 1;  
  } else {   
    IO3Sensor.value = 0;  
  }


if (buttonState4 == LOW) {
    IO4Sensor.value = 1;  
  } else {   
    IO4Sensor.value = 0;  
  }


if (buttonState5 == LOW) {
    IO5Sensor.value = 1;  
  } else {   
    IO5Sensor.value = 0;  
  }

if (buttonState6 == LOW) {
    IO6Sensor.value = 1;  
  } else {   
    IO6Sensor.value = 0;  
  }



    AN1Sensor.value = sensorValue1;     //0....1023
    AN2Sensor.value = sensorValue2;     //0....1023
    AN3Sensor.value = sensorValue3;    //0.....1023
  //AN4Sensor.value = sensorValue4;  //0.....1023
    AN4Sensor.value = map(sensorValue4, 0, 1023, 0, 255);     //0.....255

    ANXSensor.value = map(sensorValueX,0,675,0,1023);     //gyro X ch
    ANYSensor.value = map(sensorValueY,0,675,0,1023);     //gyro Y ch
    ANZSensor.value = map(sensorValueZ,0,675,0,1023);     //gyro Z ch
    ANTSensor.value = (sensorValueT);     //Temp ch

       
    //Serial.println(ANXSensor.value);
    //Serial.println(ANYSensor.value);
   // Serial.println(ANXZensor.value);

   
 
    delay(2);
   
  }
