#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <math.h>
#define LED_PIN    6
#define LED_COUNT 3
#define angleLimit 15

Adafruit_MPU6050 mpu;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  //start accelerometer
  mpu.begin();
  
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);

  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)


  pinMode(5,OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);



  double rx=atan2(a.acceleration.x,a.acceleration.z)*(180/PI);
  double ry=atan2(a.acceleration.y,a.acceleration.z)*(180/PI);
 // Serial.println(rx);
Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");



  if(rx>angleLimit||rx<-angleLimit){ 
    colorWipe(strip.Color(255,   0,   0), 10); // Red
    analogWrite(5,128);

    
  }
  else{ 
    colorWipe(strip.Color(  0, 255,   0), 10); // Green
    analogWrite(5,0);
  }
  delay (200); 
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
