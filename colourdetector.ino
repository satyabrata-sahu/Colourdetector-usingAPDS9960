#include <Wire.h>
#include <SparkFun_APDS9960.h>

// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
uint16_t ambient_light = 0;
uint16_t red_light = 0;
uint16_t green_light = 0;
uint16_t blue_light = 0;

int R=9;//(common anode rgb led )red led pin 
int G=8;//green led pin
int B=7;//blue led pin

void setup() {


  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  // Initialize Serial port
  Serial.begin(9600);
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - ColorSensor"));
  Serial.println(F("--------------------------------"));
  
  
  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  
  // Start running the APDS-9960 light sensor (no interrupts)
  if ( apds.enableLightSensor(false) ) {
    Serial.println(F("Light sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during light sensor init!"));
  }
  
  // Wait for initialization and calibration to finish
  delay(500);
}

void loop() {
  
  // Read the light levels (ambient, red, green, blue)
  if (  !apds.readAmbientLight(ambient_light) ||
        !apds.readRedLight(red_light) ||
        !apds.readGreenLight(green_light) ||
        !apds.readBlueLight(blue_light) ) {
    Serial.println("Error reading light values");
  } else {
    Serial.print("Ambient: ");
    Serial.print(ambient_light);
    Serial.print(" Red: ");
    Serial.print(red_light);
    Serial.print(" Green: ");
    Serial.print(green_light);
    Serial.print(" Blue: ");
    Serial.println(blue_light);

if(red_light>green_light && red_light>blue_light)
{
  digitalWrite(R,LOW);
  digitalWrite(B,HIGH);
  digitalWrite(G,HIGH);
}
else if(green_light>red_light && green_light>blue_light)
{
  digitalWrite(G,LOW);
  digitalWrite(B,HIGH);
  digitalWrite(R,HIGH);
}
else
{
  digitalWrite(B,LOW);
  digitalWrite(G,HIGH);
  digitalWrite(R,HIGH);
} 
  }
  delay(1000);
}
