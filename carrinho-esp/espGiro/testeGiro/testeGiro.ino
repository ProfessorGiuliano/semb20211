#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

float Gx = 0, Gy = 0, Gz = 0,Ax = 0,Ay = 0,Az = 0;
float Gx2 = 0, Gy2 = 0, Gz2 = 0, Ax2 = 0, Ay2 = 0, Az2 = 0;
String req = " ";


void setup() {
  Serial.begin(115200);
  if (!mpu.begin()) {
    hold(100);
    Serial.println("Failed to find MPU6050 chip");
    while (10) {
      hold(100);
    }
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  
  hold(100);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  Gx = g.gyro.x;
  Gy = g.gyro.y;
  Gz = g.gyro.z;

  Ax = a.acceleration.x;
  Ay = a.acceleration.y;
  Az = a.acceleration.z;
  /*
  if (x != x2) {
    Serial.print("x: ");
    Serial.print(x);
    x2 = x;
  }*/


  Serial.print(Ax);
  Serial.print(" ");
  Serial.print(Ay);
  Serial.print(" ");
  Serial.print(Az);
  Serial.println(" ");
  hold(150);
}

void hold(const unsigned int &ms) {
  // Non blocking hold
  unsigned long m = millis();
  while (millis() - m < ms) {
    yield();
  }
}
