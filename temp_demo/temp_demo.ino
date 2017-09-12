#include <Adafruit_MAX31865.h>

//Declarations for imported hardware firmware classes

//Temp Sensor
#define MAX31865_CS 7 // CS pin
Adafruit_MAX31865 max = Adafruit_MAX31865(MAX31865_CS); // Use hardware SPI, just pass in the CS pin
#define RREF 430.0 // The value of the Rref resistor. Use 430.0!

//Pressure Sensor


// Vibration Sensor


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
  while (waitingToStart())
  {
    Serial.println("waiting for go singal to start recording");
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
  //Print Temperature data
  Serial.print("Temp: ");
  Serial.print(dataToWrite.temp);
  Serial.print(" ");

  Serial.print("Pressure: ");
  Serial.print(dataToWrite.pressure);
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
}

void finish()
{
  //TODO: close the CSV file
  //TODO: sever connections to sensors nicely if needed
  //TODO: power down, or wait for signal to start recording again (don't know what wer are supposed to do here)
}

/**
 * Function done for now, checks to see if wheels are up, if so, will inform the program that it is time to start recording
 */
bool waitingToStart()
{
  if (getGoSignal())
  {
    isRecording = true;
    return false;
  }
  else
  {
    return true;
  }
}

bool getGoSignal()
{
  if (1) //fill in once we know how to get the plane's wheels up signal
  {
    return true;
  }
  else
  {
    return false;
  }
}

void loop() 
{ 

}
