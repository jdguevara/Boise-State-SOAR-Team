#include <Adafruit_LIS3DH.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
<<<<<<< HEAD
=======
<<<<<<< HEAD
#include "SD.h"
#include "SPI.h"
 
=======
>>>>>>> 8ed2c668645b02884abc6a16a624019ae8fca875
#include <Adafruit_MAX31865.h>
#include "SD.h"
#include "SPI.h"
>>>>>>> 8a208e4ccd6c89a297125b86b0ea423a221a8405

#include <Adafruit_MAX31865.h>

// CSV string variables
String dataString =""; // holds the data to be written to the SD card
File sensorData;

//Declarations for imported hardware firmware classes

//Temp Sensor
#define MAX31865_CS 7 // CS pin
#define RREF 430.0 // The value of the Rref resistor. Use 430.0!
Adafruit_MAX31865 max = Adafruit_MAX31865(MAX31865_CS); // Use hardware SPI, just pass in the CS pin

//Pressure Sensor
#define BMP_CS 6
Adafruit_BMP280 bme(BMP_CS); // hardware SPI


// Accelerometer
#define LIS3DH_CS 5
Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);

//Software Instance variables
bool isRecording;

//Constants
const int POLLING_RATE = (int)((1/(double)400)*1000); //the polling rate, expressed in miliseconds (400Hz = 1/400ms)

//class Defintions
/**
 * DataBlock class to represent a collection of all current readings from the sensors
 */
class DataBlock
{
  public:
    float extTemp;
    float pressure;
    float intTemp;
    float accelX;
    float accelY;
    float accelZ;
    DataBlock();
};

//constructor for the DataBlock object
DataBlock::DataBlock(void)
{
  extTemp = 0.0;
  pressure = 0.0;
  intTemp = 0.0;
  accelX = 0.0;
  accelY = 0.0;
  accelZ = 0.0;
}

void setup() 
{
  initialization();  
  
}

void initialization()
{
  isRecording = false;
  
  initCSV();
  initSensors();
  while (!isRecording)
  {
    checkForGoSignal();
    Serial.println("waiting for go signal to start recording");
  }
  record();
}

void record()
{
  checkForStopSignal();
  while (isRecording)
  {
    DataBlock currentReadings = pollSensors();
    writeToCSV(currentReadings);
    delay(POLLING_RATE); //enforce the polling rate with a hardware no-op for the duration of gap time
  }
  finish();
}

void checkForGoSignal()
{
  if (1) //fill in once we know how to get the plane's wheels up signal
  {
    isRecording = true;
  }
}

void checkForStopSignal()
{
  if (0) //fill in once we know what the wheels down singal is going to look like to our software
  {
    isRecording = false;
  }
}

DataBlock pollSensors()
{
  DataBlock currDataBlock;
  
  float currExtTemp = readExtTemp();
  currDataBlock.extTemp = currExtTemp;
  
  float currPres = readPressure();
  currDataBlock.pressure = currPres;
  
  float currIntTemp = readIntTemp();
  currDataBlock.intTemp = currIntTemp;
  
  float currAccelX = readAccelX();
  currDataBlock.accelX = currAccelX;
  
  float currAccelY = readAccelY();
  currDataBlock.accelY = currAccelY;
  
  float currAccelZ = readAccelZ();
  currDataBlock.accelZ = currAccelZ;

  return currDataBlock;
}

float readExtTemp()
{
  float currExtTemp = max.temperature(100, RREF);
  return currExtTemp;
}

float readIntTemp()
{
  float currIntTemp = bme.readTemperature();
  return currIntTemp;
}

float readPressure()
{
  float currPres = bme.readPressure();
  return currPres;
}

float readAccelX()
{
  sensors_event_t event; 
  lis.getEvent(&event);
  float currAccelX = event.acceleration.x;
  return currAccelX;
}

float readAccelY()
{
  sensors_event_t event; 
  lis.getEvent(&event);
  float currAccelY = event.acceleration.y;
  return currAccelY;
}

float readAccelZ()
{
  sensors_event_t event; 
  lis.getEvent(&event);
  float currAccelZ = event.acceleration.z;
  return currAccelZ;
}

void writeToCSV(DataBlock dataToWrite)
{  
  //Print Temperature data
  Serial.print("External Temp: ");
  Serial.print(dataToWrite.extTemp);
  Serial.print(" ");

  Serial.print("Pressure: ");
  Serial.print(dataToWrite.pressure);
  Serial.print(" ");

  Serial.print("Internal Temp: ");
  Serial.print(dataToWrite.intTemp);
  Serial.print(" ");

  Serial.print("Acceleration X: ");
  Serial.print(dataToWrite.accelX);
  Serial.print(" ");

  Serial.print("Acceleration Y: ");
  Serial.print(dataToWrite.accelY);
  Serial.print(" ");

  Serial.print("Acceleration Z: ");
  Serial.print(dataToWrite.accelZ);
  Serial.print(" ");

  Serial.println();
  //TODO write each member of the class to the csv file according to proper format
}

void initCSV()
{
  //TODO open intitialize, and set up the CSV file
}

void initSensors()
{
  //Initialize the serial bus the sensors will be using
  Serial.begin(115200);
  
  //initialize the sensors on the serial bus
  
  //Temp Sensor
  max.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======

>>>>>>> d277c921bc4abfa7f156440d8e529f7f6bba9771
>>>>>>> 8a208e4ccd6c89a297125b86b0ea423a221a8405

  //Pressure and int temp sensor
  if (!bme.begin()) {  
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

  //Accelerometer
<<<<<<< HEAD
  #ifndef ESP8266
    while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!

=======
  
>>>>>>> 8ed2c668645b02884abc6a16a624019ae8fca875
>>>>>>> 8a208e4ccd6c89a297125b86b0ea423a221a8405
}

void finish()
{
  //TODO: close the CSV file
  //TODO: sever connections to sensors nicely if needed
  //TODO: power down, or wait for signal to start recording again (don't know what wer are supposed to do here)
}

void checkForGoSignal()
{
  if (1) //fill in once we know how to get the plane's wheels up signal
  {
    isRecording = true;
  }
}

void loop() 
{ 

}