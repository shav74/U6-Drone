#include <ESP8266WiFi.h>
#include <Servo.h>

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPLLPtjrgyO"
#define BLYNK_TEMPLATE_NAME "ground"
#define BLYNK_AUTH_TOKEN "Lg0KGnD-HSw80M-X8Dk8u54heRrA3wwo"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "shavinda";
char pass[] = "shavinda@2001";


#define IN_1 5  // L298N in1 motors Right           GPIO5(D1)
#define IN_2 4  // L298N in2 motors Right           GPIO4(D2)
#define IN_3 0   // L298N in3 motors Left            GPIO0(r3)
#define IN_4 2  // L298N in4 motors Left            GPIO2(D4)

int ground_mode = 0;
int lr,fb;

BLYNK_WRITE(V15) {
  ground_mode = param.asInt();
}

BLYNK_WRITE(V11) {
  if (ground_mode == 1) {
    
    lr = param[0].asInt();  //left and right
    fb = param[1].asInt();  // foward and back
    Serial.printf("lr - %d \t fb - %d\n", param[0].asInt(), fb);

    if (lr < 25) {
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
    } else if (lr > 230) {
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
    } else {
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
    }

    if (fb < 25) {
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
    } else if (fb > 230) {
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
    }
  }
}
void setup() {
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
   Blynk.run();
}
