#include <SD.h>
#include <SPI.h>

File myFile;

int pinCS = 10;
int value = 0;
float voltage;
unsigned long time;

void setup(){
  Serial.begin(9600);
  pinMode(pinCS, OUTPUT);
  //analogReference(INTERNAL);
  
  // SD Card Initialization
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
}

void loop(){
  value = analogRead(A0);
  //voltage = value * 1.1/1023 * 1000;
  voltage = value * 5.0/1023 * 1000;
  //voltage = value;
  //voltage = value * 5.0/1023;
  Serial.print("Time: ");
  time = (millis()/1000);
  Serial.println(time);
  Serial.print("Voltage= ");
  Serial.println(voltage);

  myFile = SD.open("volt-10.txt", FILE_WRITE);
  if (myFile) {
    myFile.print(time);
    myFile.print(",");
    myFile.println(voltage);
    myFile.close(); // close the file
  }

  // if the file didn't open, print an error:
  else {
    Serial.println("error opening voltage2.txt");
  }
  
  delay(5000);
}


// GENERAL NOTES ABOUT THE ARDUINO CODE:
// 1) The file name CANNOT exceed 8 characters (including special characters)
// 2) You must name a new file after each upload (the files are NEVER overwritten or appended to)
// 3) If the Arduino accidentally powers off, you will need to re-upload the code. Use a new file name, or the new data will be lost