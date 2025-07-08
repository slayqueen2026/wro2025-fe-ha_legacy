#include <Servo.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <VL53L0X.h>

Servo myservo;

const int l = 2;
const int f = 0;
const int r = 0;

long duration;
long dist_w;

const int IN1 = 8;
const int IN2 = 7;
const int ENA = 9;

char side = ' ';
bool free_round = NULL;
short corners = 0;

bool run = false;

double Fdist = 300, Ldist = 300, Rdist = 300;
double tLdist = 300, tRdist = 300;

const int keyPin = 3; //the number of the key pin 12

VL53L0X sensors[3];  // Adjust the size of the array based on the number of sensors you have

// Define XSHUT pin numbers for each sensor
const int xshutPins[] = {10, 11, 12};  // Adjust these pin numbers based on your wiring

// Define unique I2C addresses for each sensor
const uint8_t addresses[] = {0x30, 0x31, 0x32};  // Make sure these addresses do not conflict with other I2C devices

void stop ()  //stop motors
{
  digitalWrite(IN2, LOW);
  digitalWrite(IN1, LOW);
  ///coast - break - hold
}

void move (int speed)  //forward backward 255
{
  //return; //test line to avoid movement, comment this command "return"
  digitalWrite(IN2, LOW);
  digitalWrite(IN1, LOW);
  analogWrite(ENA,  abs(speed));
  if (speed >= 0)
      digitalWrite(IN1,  HIGH);
  else
      digitalWrite(IN2,  HIGH);
}

double dist (int space)
{
  return sensors[space].readRangeContinuousMillimeters();
}
 
 void turn(char opts)
{
  corners++;
  myservo.write(opts=='l'? 140: 40);
  /*if (opts == 'l')
     myservo.write(140);
  else if (opts == 'r')
     myservo.write(40);*/
  //Serial.println(corners);
  delay(700);
}

void upsy()
{
  long tDist = 0;
  while (true)
    {
      tDist = dist(side == 'l'? l: r);
      //tRdist = dist(r);
      if (tDist < 1000);//((side == 'l'? tLdist : tRdist) < 1000)
      {
        break;
      }
    }
}

void fix_d ()
{
     myservo.write(90);
}

void setup() {
  Serial.begin (9600);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (ENA, OUTPUT);

  myservo.attach(13);//attachs the servo on pin 7 to servo object

  myservo.write(90);//back to 0 degrees

  pinMode(keyPin,INPUT);//initialize the key pin as inp


  Wire.begin();

  // Initialize each sensor
  for (int i = 0; i < sizeof(sensors) / sizeof(sensors[0]); i++) {
    pinMode(xshutPins[i], OUTPUT);
    digitalWrite(xshutPins[i], LOW);  // Keep the sensor in reset state
  }

  // Set up each sensor with a unique I2C address
  for (int i = 0; i < sizeof(sensors) / sizeof(sensors[0]); i++) {
    digitalWrite(xshutPins[i], HIGH);  // Bring the sensor out of reset
    delay(10);  // Allow time for the sensor to initialize

    sensors[i].init();
    sensors[i].setTimeout(500);
    sensors[i].setAddress(addresses[i]);
  }

  // Start continuous measurement for each sensor
  for (int i = 0; i < sizeof(sensors) / sizeof(sensors[0]); i++) {
    sensors[i].startContinuous();
  }
}
 
void loop() {



 
  while (!run)    // starting button
  {
   // run = DigitalRead(bpin    
   
    if(digitalRead(keyPin) ==HIGH )
      {
        stop();
        run = true; //validate the starting button
      }
      Serial.write("\nWaiting button...");
  }

  fix_d();

run = false;
while(0)
{
  Ldist = dist(l);
  Rdist = dist(r);
  Fdist = dist(f);
  Serial.println("L");
  Serial.println(Ldist);
  Serial.println(Rdist);
  Serial.println(Fdist);
  delay(500);
}

  if ((Ldist < 500) || (Rdist < 500))
    {
      free_round = true;
    }
  else
    free_round = false;

  if (free_round)
    Serial.write("\n - Free Round");
  else
    Serial.write("\n - Not sure...");

  move(100);
  while (true)
    {
      tLdist = dist(l);
      Fdist = dist(f);
      tRdist = dist(r);
      Serial.print("tL ");
      Serial.println(tLdist);
      Serial.print("tR ");
      Serial.println(tRdist);
      Serial.print("tF ");
      Serial.println(Fdist);
      if (Fdist < 1250)
      {
        stop();
        delay(500);
        if ((tLdist > 1300) || (tRdist > 1300))
        {
          side = (tLdist > 1300? 'l': 'r');
          break;
        }

      }
    }
//Serial.write("\n"+side);
  turn(side);
  delay(side == 'r'? 400: 50);
  delay(150);
  fix_d();
  delay(350);
  //upsy();
  stop();
  delay(300);
  move(100);
  int base_delay = 125;//controls turns, cambia si es nesesario
  while (corners <= 11)
  {
    dist_w = dist('f');
    if (dist_w < 600)
    {
      turn(side);
      delay(side=='r'? 500: 50);
      fix_d();
      upsy();
      stop();
      delay(350);
      move(100);
      delay(base_delay);
      //base_delay*=(2/5);
      //fix_d();
    }
   
  }
  //if (corners > 12)
    stop();

}