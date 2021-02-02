#include <IRremote.h>      //must copy IRremote library to arduino libraries
#include <Servo.h>
#define plus 0xFF5AA5   //button Vol+ clockwise rotation button
#define minus 0xFF10EF  //button Vol- counter clockwise rotation button
#define Servo1 0xFFA25D //button 1 1st motor selection
#define Servo2 0xFF629D //button 2 2nd motor selection
#define Servo3 0xFFE21D //button 3 3d motor selection
#define Servo4 0xFF22DD //button 4 4th motor selection
#define SaveButton 0xFF6897 //button play/pause Save button
#define StartButton 0xFF38C7 //button red on Start button

int RECV_PIN = 11;       //IR receiver pin
int led_start = 12;
int led_save = 13;
int servo_1_led = A1;
int servo_2_led = A2;
int servo_3_led = A3;
int servo_4_led = A4;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
int val1 = 0; //rotation angle
int val2 = 90;
int val3 = 0;
int val4 = 90;
int counter1 = 0;
int counter2 = 0;
int counter3 = 0;
int counter4 = 0;
bool cwRotation_servo1, ccwRotation_servo1;  //the states of rotation
bool cwRotation_servo2, ccwRotation_servo2;
bool cwRotation_servo3, ccwRotation_servo3;
bool cwRotation_servo4, ccwRotation_servo4;

int servo1_Position[] = {1,1,1,1,1,1,1,1,1,1}; //position saves
int servo2_Position[] = {1,1,1,1,1,1,1,1,1,1};
int servo3_Position[] = {1,1,1,1,1,1,1,1,1,1};
int servo4_Position[] = {1,1,1,1,1,1,1,1,1,1};

int buttonpresses = 0;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  servo1.attach(3);     //servo pin
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);
  servo1.write(val1);
  servo2.write(val2);
  servo3.write(val3);
  servo4.write(val4);
  pinMode(led_start, OUTPUT);
  pinMode(led_save, OUTPUT);
  digitalWrite(led_start,LOW);
}

void loop() 
{
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    //irrecv.resume(); // Receive the next value
  
    if (results.value == Servo1)
    {
      counter1 = 1;
      counter2 = 0;
      counter3 = 0;
      counter4 = 0;
      analogWrite(servo_1_led,1024);
      analogWrite(servo_2_led,0);
      analogWrite(servo_3_led,0);
      analogWrite(servo_4_led,0);
      Serial.println("Epilexthike o prwtos kinhthras");
    }
    if (results.value == Servo2)
    {
      counter1 = 0;
      counter2 = 1;
      counter3 = 0;
      counter4 = 0;
      analogWrite(servo_1_led,0);
      analogWrite(servo_2_led,1024);
      analogWrite(servo_3_led,0);
      analogWrite(servo_4_led,0);
      Serial.println("Epilexthike o deyteros kinhthras");
    }
    if (results.value == Servo3)
    {
      counter1 = 0;
      counter2 = 0;
      counter3 = 1;
      counter4 = 0;
      analogWrite(servo_1_led,0);
      analogWrite(servo_2_led,0);
      analogWrite(servo_3_led,1024);
      analogWrite(servo_4_led,0);
      Serial.println("Epilexthike o tritos kinhthras");
    }
    if (results.value == Servo4)
    {
      counter1 = 0;
      counter2 = 0;
      counter3 = 0;
      counter4 = 1;
      analogWrite(servo_1_led,0);
      analogWrite(servo_2_led,0);
      analogWrite(servo_3_led,0);
      analogWrite(servo_4_led,1024);
      Serial.println("Epilexthike o tetartos kinhthras");
    }   
    if (counter1 == 1)
    {
      if (results.value == plus)
      {
        cwRotation_servo1 = !cwRotation_servo1;      //toggle the rotation value
        ccwRotation_servo1 = false;         //no rotation in this direction
      }
      if (results.value == minus)
      {
        ccwRotation_servo1 = !ccwRotation_servo1;   //toggle the rotation value
        cwRotation_servo1 = false;            //no rotation in this direction
      }
    }
    if (counter2 == 1)
    {
      if (results.value == plus)
      {
        cwRotation_servo2 = !cwRotation_servo2;      //toggle the rotation value
        ccwRotation_servo2 = false;         //no rotation in this direction
      }
      if (results.value == minus)
      {
        ccwRotation_servo2 = !ccwRotation_servo2;   //toggle the rotation value
        cwRotation_servo2 = false;            //no rotation in this direction
      }
    }
    if (counter3 == 1)
    {
      if (results.value == plus)
      {
        cwRotation_servo3 = !cwRotation_servo3;      //toggle the rotation value
        ccwRotation_servo3 = false;         //no rotation in this direction
      }
      if (results.value == minus)
      {
        ccwRotation_servo3 = !ccwRotation_servo3;   //toggle the rotation value
        cwRotation_servo3 = false;            //no rotation in this direction
      }
    }
    if (counter4 == 1)
    {
      if (results.value == plus)
      {
        cwRotation_servo4 = !cwRotation_servo4;      //toggle the rotation value
        ccwRotation_servo4 = false;         //no rotation in this direction
      }
      if (results.value == minus)
      {
        ccwRotation_servo4 = !ccwRotation_servo4;   //toggle the rotation value
        cwRotation_servo4 = false;            //no rotation in this direction
      }
    }
    if (results.value == SaveButton)
    {
      buttonpresses++;
      switch (buttonpresses){
        case 1:
        servo1_Position[0] = val1;
        servo2_Position[0] = val2;
        servo3_Position[0] = val3;
        servo4_Position[0] = val4;
        save(led_save);
        Serial.println("Position 1 Saved");
        break;
        case 2:
        servo1_Position[1] = val1;
        servo2_Position[1] = val2;
        servo3_Position[1] = val3;
        servo4_Position[1] = val4;
        save(led_save);
        Serial.println("Position 2 Saved");
        break;
        case 3:
        servo1_Position[2] = val1;
        servo2_Position[2] = val2;
        servo3_Position[2] = val3;
        servo4_Position[2] = val4;
        save(led_save);
        Serial.println("Position 3 Saved");
        break;
        case 4:
        servo1_Position[3] = val1;
        servo2_Position[3] = val2;
        servo3_Position[3] = val3;
        servo4_Position[3] = val4;
        save(led_save);
        Serial.println("Position 4 Saved");
        break;
        case 5:
        servo1_Position[4] = val1;
        servo2_Position[4] = val2;
        servo3_Position[4] = val3;
        servo4_Position[4] = val4;
        save(led_save);
        Serial.println("Position 5 Saved");
        break;
        case 6:
        servo1_Position[5] = val1;
        servo2_Position[5] = val2;
        servo3_Position[5] = val3;
        servo4_Position[5] = val4;
        save(led_save);
        Serial.println("Position 6 Saved");
        break;
        case 7:
        servo1_Position[6] = val1;
        servo2_Position[6] = val2;
        servo3_Position[6] = val3;
        servo4_Position[6] = val4;
        save(led_save);
        Serial.println("Position 7 Saved");
        break;
        case 8:
        servo1_Position[7] = val1;
        servo2_Position[7] = val2;
        servo3_Position[7] = val3;
        servo4_Position[7] = val4;
        save(led_save);
        Serial.println("Position 8 Saved");
        break;
        case 9:
        servo1_Position[8] = val1;
        servo2_Position[8] = val2;
        servo3_Position[8] = val3;
        servo4_Position[8] = val4;
        save(led_save);
        Serial.println("Position 9 Saved");
        break;
        case 10:
        servo1_Position[9] = val1;
        servo2_Position[9] = val2;
        servo3_Position[9] = val3;
        servo4_Position[9] = val4;
        save(led_save);
        Serial.println("Position 10 Saved");
        break;
      }
    }
     while (results.value == StartButton)
    {
      Serial.println("Ekinhsh Vraxiwna");
      delay(300);
      for (int i = 0; i < buttonpresses; i++){
        digitalWrite(led_start,HIGH);
        analogWrite(servo_1_led,0);
        analogWrite(servo_2_led,0);
        analogWrite(servo_3_led,0);
        analogWrite(servo_4_led,0);
        servo1.write(servo1_Position[i]);
        delay(100);
        servo2.write(servo2_Position[i]);
        delay(100);
        servo3.write(servo3_Position[i]);
        delay(100);
        servo4.write(servo4_Position[i]);
        Serial.print(" servomotors Angles ");
        Serial.print(i + 1);
        Serial.println("hs theshs: ");
        Serial.println(servo1_Position[i]);
        Serial.println(servo2_Position[i]);
        Serial.println(servo3_Position[i]);
        Serial.println(servo4_Position[i]);
        delay(1050);
      }
    }
    irrecv.resume(); // Receive the next value
  }
  if (cwRotation_servo1 && (val1 != 175))  {
    val1++;                         //for colockwise button
  }
  if (ccwRotation_servo1 && (val1 != 0))  {
    val1--;                         //for counter colockwise button
  }
  if (cwRotation_servo2 && (val2 != 175))  {
    val2++;                         //for colockwise button
  }
  if (ccwRotation_servo2 && (val2 != 0))  {
    val2--;                         //for counter colockwise button
  }
  if (cwRotation_servo3 && (val3 != 175))  {
    val3++;                         //for colockwise button
  }
  if (ccwRotation_servo3 && (val3 != 0))  {
    val3--;                         //for counter colockwise button
  }
  if (cwRotation_servo4 && (val4 != 175))  {
    val4++;                         //for colockwise button
  }
  if (ccwRotation_servo4 && (val4 != 0))  {
    val4--;                         //for counter colockwise button
  }
  if (counter1 == 1)
  {
    servo1.write(val1);
  }
  if (counter2 == 1)
  {
    servo2.write(val2);
  }
  if (counter3 == 1)
  {
    servo3.write(val3);
  }
  if (counter4 == 1)
  {
    servo4.write(val4);
  }
  delay(20);          //General speed
}
int save(int led_save){
  digitalWrite(led_save,HIGH);
  delay(400);
  digitalWrite(led_save,LOW);
}
