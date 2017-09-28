#include <Adafruit_MAX31865.h>
#include "SD.h"
#include "SPI.h"

// CSV string variables
String dataString =""; // holds the data to be written to the SD card
File sensorData;

//Declarations for imported hardware firmware classes

//Temp Sensor
#define MAX31865_CS 7 // CS pin
Adafruit_MAX31865 max = Adafruit_MAX31865(MAX31865_CS); // Use hardware SPI, 
just pass in the CS pin
#define RREF 430.0 // The value of the Rref resistor. Use 430.0!

//Pressure Sensor
<<<<<<< HEAD
=======

>>>>>>> b5e755028bb69922ec4e406b932f65675650b86a


// Accelerometer


//Software Instance variables
bool isRecording;

//Constants
const int POLLING_RATE = (int)((1/(double)400)*1000); //the polling rate, 
expressed in miliseconds (400Hz = 1/400ms)

//class Defintions
/**
 * DataBlock class to represent a collection of all current readings from the 
sensors
 */
class DataBlock
{
  public:
    float temp;
    float pressure;
    float vibX;
    float vibY;
    float vibZ;
    DataBlock();
};

//constructor for the DataBlock object
DataBlock::DataBlock(void)
{
  temp = 0.0;
  pressure = 0.0;
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
    delay(POLLING_RATE); //enforce the polling rate with a hardware no-op for 
the duration of gap time
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
  if (0) //fill in once we know what the wheels down singal is going to look 
like to our software
  {
    isRecording = false;
  }
}

DataBlock pollSensors()

{
  DataBlock currDataBlock;
  
  float currTemp = readTemp();
  currDataBlock.temp = currTemp;
  
  float currPres = readPressure();
  currDataBlock.pressure = currPres;
  
  float currVibX = readVibX();
  currDataBlock.vibX = currVibX;
  
  float currVibY = readVibY();
  currDataBlock.vibY = currVibY;
  
  float currVibZ = readVibZ();
  currDataBlock.vibZ = currVibZ;

  return currDataBlock;
}

float readTemp()
{
  float currTemp = max.temperature(100, RREF);
  return currTemp;
}

float readPressure()
{
  float currPres = 0.0;
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
 /* //Print Temperature data
  Serial.print("Temp: ");
  Serial.print(dataToWrite.temp);
  Serial.print(" ");
  
  //Print Pressure data
  Serial.print("Pressure: ");
  Serial.print(dataToWrite.pressure);
  Serial.print(" ");

  //Print Vibration on X data
  Serial.print("Vibration X: ");
  Serial.print(dataToWrite.vibX);
  Serial.print(" ");

  //Print Vibration on Y axis data
  Serial.print("Vibration Y: ");
  Serial.print(dataToWrite.vibY);
  Serial.print(" ");

  //Print Vibration on Z axis data
  Serial.print("Vibration Z: ");
  Serial.print(dataToWrite.vibZ);
  Serial.print(" ");

  Serial.println();
  */
  
  //TODO write each member of the class to the csv file according to proper 
format

  // build the data string
  dataString = String("test temp"/*dataToWrite.temp*/) + "," + String("test 
pressure"/*dataToWrite.pressure*/) + "," + String("test 
vibX"/*dataToWrite.vibX*/) + "," + String("test vibY" /*dataToWrite.vibY*/) + 
"," +String("test vibZ"/*dataToWrite.vibZ*/); // convert to CSV
  
  if(SD.exists("data.csv")){ // check the card is still there
     // now append new data file
      sensorData = SD.open("data.csv", FILE_WRITE);
      if (sensorData){
      sensorData.println(dataString);
      
      }
  else{
    Serial.println("Error writing to file !");
    }
  }
 delay(60000); // delay before next write to SD Card, adjust as required

}

void initCSV()
{
  //TODO open intitialize, and set up the CSV file

  Serial.print("Initializing SD card...");
  pinMode(CSpin, OUTPUT);

  // see if the card is present and can be initialized:
    if (!SD.begin(CSpin)) {
        Serial.println("Card failed, or not present");

    return;
  }
  Serial.println("card initialized.");

}

void initSensors()
{
  //Initialize the serial bus the sensors will be using
  Serial.begin(115200);
  
  //TODO: initialize the sensors on the serial bus
  //Temp Sensor
  max.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary
<<<<<<< HEAD
<<<<<<< HEAD

  //Pressure and int temp sensor
  if (!bme.begin()) {  
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

  //Accelerometer
  
=======
>>>>>>> b5e755028bb69922ec4e406b932f65675650b86a
=======
>>>>>>> b5e755028bb69922ec4e406b932f65675650b86a
}

void finish()
{
  //TODO: close the CSV file
   sensorData.close();
   
  //TODO: sever connections to sensors nicely if needed
  //TODO: power down, or wait for signal to start recording again (don't know 
what wer are supposed to do here)
}



void loop() 
{ 

}

