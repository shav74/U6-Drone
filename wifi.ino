#include <ESP8266WiFi.h>
#include <Servo.h>

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPLhki80VaJ"
#define BLYNK_DEVICE_NAME "remote"
#define BLYNK_AUTH_TOKEN "C_YHRc-NIi-xdAcOAQHFB3P31W73jqFP"

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int start = 0;
int stop = 0;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "shavinda";
char pass[] = "shavinda@2001";

int yaw, roll, pitch, gas, speed;
int roll_trim, pitch_trim;

BLYNK_WRITE(V1) {
  start = param.asInt();
}

BLYNK_WRITE(V2) {
  stop = param.asInt();
}

BLYNK_WRITE(V3) {
  roll_trim = param.asInt();
}

BLYNK_WRITE(V4) {
  pitch_trim = param.asInt();
}

BLYNK_WRITE(V13) {
  speed = param.asInt();
}

BLYNK_WRITE(V0) {
  gas = param.asInt();
  if (stop == 1) {
    gas = 0;
  }
  servo1.write(gas);
}


BLYNK_WRITE(V9) {
  int yaw_value = param[0].asInt();
  yaw_value = map(yaw_value, 0, 255, 0, 180);
  if (stop == 1) {
    yaw = 180;
  } else if (start == 1) {
    yaw = 0;
  } else {
    if (yaw_value >= 90) {
      yaw = 90 + (yaw_value - 90) / 20 * speed;
    } else {
      yaw = 90 - (90 - yaw_value) / 20 * speed;
    }
  }
  servo2.write(yaw);
}

BLYNK_WRITE(V10) {
  int roll_value = param[0].asInt();
  roll_value = map(roll_value, 0, 255, 0, 180);
  if (roll_value >= 90) {
    roll = 90 + (roll_value - 90) / 20 * speed + roll_trim;
  } else {
    roll = 90 - (90 - roll_value) / 20 * speed + roll_trim;
  }
  servo3.write(roll);

  int pitch_value = param[1].asInt();
  pitch_value = map(pitch_value, 0, 255, 0, 180);
  if (pitch_value >= 90) {
    pitch = 90 + (pitch_value - 90) / 20 * speed + pitch_trim;
  } else {
    pitch = 90 - (90 - pitch_value) / 20 * speed + pitch_trim;
  }
  servo4.write(pitch);
}


void setup() {
  // Serial.begin(9600);

  servo1.attach(D0, 1000, 2000);
  servo2.attach(D1, 1000, 2000);
  servo3.attach(D2, 1000, 2000);
  servo4.attach(D3, 1000, 2000);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  delay(1000);
}

void loop() {
  Blynk.run();

  // Serial.printf("ground mode - %d lr - %d fb - %d", ground_mode, lr, fb);
  // Serial.printf("\t roll_trim - %d \t pitch_trim - %d \t\n", roll_trim, pitch_trim);
  // Serial.printf("gas - %d \t yaw - %d \t roll - %d \t pitch - %d ",gas, yaw, roll, pitch);
  // delay(100);

  // Blynk.config()
}
