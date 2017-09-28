#include <Adafruit_LIS3DH.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#include <Adafruit_MAX31865.h>

//Declarations for imported hardware firmware classes

//Temp Sensor
#define MAX31865_CS 7 // CS pin
#define RREF 430.0 // The value of the Rref resistor. Use 430.0!
Adafruit_MAX31865 max = Adafruit_MAX31865(MAX31865_CS); // Use hardware SPI, just pass in the CS pin

//Pressure Sensor
#define BMP_CS 6
Adafruit_BMP280 bme(BMP_CS); // hardware SPI


// Accelerometer


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
    float vibX;
    float vibY;
    float vibZ;
    DataBlock();
};

//constructor for the DataBlock object
DataBlock::DataBlock(void)
{
  extTemp = 0.0;
  pressure = 0.0;
  intTemp = 0.0;
  vibX = 0.0;
  vibY = 0.0;
  vibZ = 0.0;
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
  
  float currVibX = readVibX();
  currDataBlock.vibX = currVibX;
  
  float currVibY = readVibY();
  currDataBlock.vibY = currVibY;
  
  float currVibZ = readVibZ();
  currDataBlock.vibZ = currVibZ;

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

float readVibX()
{
  float currVibX = 0.0;
  return currVibX;
}

float readVibY()
{
  float currVibY = 0.0;
  return currVibY;
}

float readVibZ()
{
  float currVibZ = 0.0;
  return currVibZ;
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

  Serial.print("Vibration X: ");
  Serial.print(dataToWrite.vibX);
  Serial.print(" ");

  Serial.print("Vibration Y: ");
  Serial.print(dataToWrite.vibY);
  Serial.print(" ");

  Serial.print("Vibration Z: ");
  Serial.print(dataToWrite.vibZ);
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
  
  //TODO: initialize the sensors on the serial bus
  //Temp Sensor
  max.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary


  //Pressure and int temp sensor
  if (!bme.begin()) {  
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }


  //Accelerometer
  
}

void finish()
{
  //TODO: close the CSV file
  //TODO: sever connections to sensors nicely if needed
  //TODO: power down, or wait for signal to start recording again (don't know what wer are supposed to do here)
}



void loop() 
{ 

}
