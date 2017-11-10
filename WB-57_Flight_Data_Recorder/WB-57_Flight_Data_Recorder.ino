#include <Adafruit_LIS3DH.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <SD.h>
#include <Adafruit_MAX31865.h>

//Declarations for imported hardware firmware classes

//Temp Sensor
#define MAX31865_CS 6//7 // CS pin
#define RREF 430.0 // The value of the Rref resistor. Use 430.0!
Adafruit_MAX31865 max = Adafruit_MAX31865(MAX31865_CS); // Use hardware SPI, just pass in the CS pin

//Pressure Sensor
#define BMP_CS 7//6
Adafruit_BMP280 bme(BMP_CS); // hardware SPI

// Accelerometer
#define LIS3DH_CS 5
Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);

//SD Reader
#define SD_CS SDCARD_SS_PIN

//Internal Heater
#define HEATER_PIN 4 //pin for the PWM output for the heater
char dutyCycle;

//Software Instance variables
bool isRecording; //whether or not the recorder is running
int totalEntries; //total number of recorded entries
String dataString = ""; // holds the String of one line to be written to the CSV file
File sensorData; //pointer to the file on the SD

//Constants
const int POLLING_RATE = (int)((1/(double)400)*1000); //the polling rate, expressed in miliseconds (400Hz = 1/400ms)
const int DESIRED_TEMP = 15; //desired temperature of the box, what the pwm of the heater works toward, in celsius
const String CSV_FILENAME = "DATA.CSV"; //the file name of the CSV file on the SD


//class Defintions
/**
 * DataBlock class to represent a collection of all current readings from the sensors
 */
class DataBlock
{
  public:
    double extTemp;
    double pressure;
    double intTemp;
    double accelX;
    double accelY;
    double accelZ;
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
  Serial.println("Initializing software...");
  isRecording = false;
  totalEntries = 0;

  //Initialize the serial bus
  Serial.begin(115200);
  
  initSensors();  
  initCSV();
  initHeater();
  
  while (!isRecording)
  {
    checkForGoSignal();
    Serial.println("waiting for go signal to start recording");
  }
  
  Serial.println("Software Initialized. Beginning recording...");
  record();
}

void record()
{
  while (isRecording)
  {
    checkForStopSignal();
    DataBlock currentReadings = pollSensors();
    updateHeater(currentReadings.intTemp);
    writeToCSV(currentReadings);
    //printToConsole(currentReadings);
    totalEntries++;
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
  if(totalEntries > 100) //for testing, limit recording entries to 100
  {
    isRecording = false;
  }
  
  if (0) //fill in once we know what the wheels down singal is going to look like to our software
  {
    isRecording = false;
  }
}

DataBlock pollSensors()
{
  DataBlock currDataBlock;
  
  double currExtTemp = readExtTemp();
  currDataBlock.extTemp = currExtTemp;
  
  double currPres = readPressure();
  currDataBlock.pressure = currPres;
  
  double currIntTemp = readIntTemp();
  currDataBlock.intTemp = currIntTemp;
  
  double currAccelX = readAccelX();
  currDataBlock.accelX = currAccelX;
  
  double currAccelY = readAccelY();
  currDataBlock.accelY = currAccelY;
  
  double currAccelZ = readAccelZ();
  currDataBlock.accelZ = currAccelZ;

  return currDataBlock;
}

double readExtTemp()
{
  double currExtTemp = max.temperature(100, RREF);
  return currExtTemp;
}

double readIntTemp()
{
  double currIntTemp = bme.readTemperature();
  return currIntTemp;
}

double readPressure()
{
  double currPres = bme.readPressure();
  return currPres;
}

double readAccelX()
{
  sensors_event_t event; 
  lis.getEvent(&event);
  double currAccelX = event.acceleration.x;
  return currAccelX;
}

double readAccelY()
{
  sensors_event_t event; 
  lis.getEvent(&event);
  double currAccelY = event.acceleration.y;
  return currAccelY;
}

double readAccelZ()
{
  sensors_event_t event; 
  lis.getEvent(&event);
  double currAccelZ = event.acceleration.z;
  return currAccelZ;
}

void printToConsole(DataBlock dataToWrite)
{
  //Print Temperature data
  Serial.print("External Temp (°C): ");
  Serial.print(dataToWrite.extTemp);
  Serial.print(" ");

  Serial.print("Pressure (Pa): ");
  Serial.print(dataToWrite.pressure);
  Serial.print(" ");

  Serial.print("Internal Temp (°C): ");
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
}

void writeToCSV(DataBlock dataToWrite)
{  
  // build the data string
  dataString = "";
  dataString.concat(dataToWrite.extTemp);
  dataString.concat(", ");
  dataString.concat(dataToWrite.pressure);
  dataString.concat(", ");
  dataString.concat(dataToWrite.accelX);
  dataString.concat(",");
  dataString.concat(dataToWrite.accelY);
  dataString.concat(", ");
  dataString.concat(dataToWrite.accelZ);
  //Serial.println("Datablock " + dataString);
  
  //write the string to the csv
  sensorData = SD.open(CSV_FILENAME, FILE_WRITE);
  sensorData.println(dataString);
  sensorData.close();
  Serial.println("Datablock written to CSV");
}

void initCSV()
{
  Serial.print("Initializing SD card...");
  pinMode(SD_CS, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(SD_CS)) 
  {
    Serial.println("\nCard failed, or not present");
    loop(); //go into infinite loop if no sd card
    return;
  }  
  Serial.println("Done.");

  Serial.print("Initializing CSV...");
  if(SD.exists(CSV_FILENAME))
  {
    Serial.print("Data.csv exists, deleting old version...");
    SD.remove(CSV_FILENAME);
  }

  sensorData = SD.open(CSV_FILENAME, FILE_WRITE);
  if (sensorData)
  {
    sensorData.println("External Temperature, Barometric Pressure, Acceleration X, Acceleration Y, Acceleration Z");
    sensorData.close();
  }
  else
  {
    Serial.println("\nError writing to file!");
  }
  Serial.println("Done.");
}

void initSensors()
{
  Serial.print("Initializing Sensors...");
  
  //initialize the sensors on the serial bus
  
  //Temp Sensor
  if (!max.begin(MAX31865_3WIRE)) // set to 2WIRE or 4WIRE as necessary
  {
    Serial.println("\n could not start temperature sensor");
  }

  //Pressure and int temp sensor
  if (!bme.begin()) 
  {  
    Serial.println("\nCould not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

  //Accelerometer
  #ifndef ESP8266
    while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif
  if (! lis.begin(0x18)) // change this to 0x19 for alternative i2c address
  {   
    Serial.println("\nCouldn't start accelerometer");
  }
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!

  Serial.println("Done.");
}

void initHeater()
{
  Serial.print("Initializing heater...");
  dutyCycle = 0;
  analogWrite(HEATER_PIN, dutyCycle);
  Serial.println("Done.");
}

/**
 * manages the PWM of the heater pad. It works as follows:
 * -look at the current internal temperature of the box
 * -subtract the current temperature from the desired temperature (constant), this yields the deviance from desired, which will be a positive value if too cold, a negative value if too hot
 * -convert the deviance in steps ranging from 1 to 5 away from the desired temp (i.e. 1 unit (degree) too cold, 3 units too hot, 5 units too cold max, 5 units too hot max)
 * -scale the units to a percentage scale for the duty cycle (i.e. 1 unit too cold = 60% duty cycle, 3 units too hot = 20% duty cycle, 5 too cold = 100% DC, 5 too hot = 0% DC)
 * -scale the duty cycle from 0 to 255 based on the percentage value (i.e. 0% = 0, 100% = 255)
 */
void updateHeater(double intTemp)
{
  double desired = DESIRED_TEMP;
  double actual = intTemp;
  double tempDeviance = desired - actual; //difference between actual and desired temps, positive if temp needs to go up
  char tempSteps = (char) tempDeviance; //truncate deviance to signed integer value of degree difference, this is the number of temp steps off from desired
  if (tempSteps > 5) //make sure tempSteps is max of 5 and min of -5
  {
    tempSteps = 5;
  }
  if (tempSteps < -5)
  {
    tempSteps = -5;
  }
  int dutyCyclePercentage = 50 + (10 * tempSteps); //convert tempSteps to a percentage value
  dutyCycle = (char)(dutyCyclePercentage * 2.55); //scale percentage duty cycle to between 0 and 255
  analogWrite(HEATER_PIN, dutyCycle);
}


void finish()
{
  sensorData.close();
  //TODO: sever connections to sensors nicely if needed
  //TODO: power down, or wait for signal to start recording again (don't know what wer are supposed to do here)
}


void loop() 
{ 
  while(1);
}
