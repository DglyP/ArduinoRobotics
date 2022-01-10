#include <SoftwareSerial.h>

//Initializations
SoftwareSerial HM10(2, 3); // RX, TX of bluetooth module
String command = "";
String left = "";
String right = "";
String forward = "";
String backward = "";

int dampy = 700;

int motor1pin1 = 5;
int motor1pin2 = 6;
int motor2pin1 = 9;
int motor2pin2 = 10;

void setup() {
  HM10.begin(9600); // HC-06's usual default baud-rate
  Serial.begin(9600);
  
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  analogWrite(motor1pin1, 0);
  analogWrite(motor1pin2, 0);
  analogWrite(motor2pin1, 0);
  analogWrite(motor2pin2, 0);
}

void loop()
{
if(HM10.available()) {
  //Reads output from the bluetooth module.
  //Each command is in the format example L130R000F073B000. 
  //Number amount is between 0-255
  String command = HM10.readStringUntil('L');

  left = command.substring(0,3);
  right = command.substring(4,7);
  forward = command.substring(8,11);
  backward = command.substring(12,15);
  
  move(forward.toInt(),left.toInt(),right.toInt(),backward.toInt());
  
  left = "";
  right = "";
  forward = "";
  backward = "";
 }
  delay(10);
}


void move(double f, double l, double r, double b){

  //dampy variable was determined through testing the turning of the robot
  analogWrite(motor1pin1, f*(1 - l/dampy));
  analogWrite(motor1pin2, b*(1 - l/dampy));
  analogWrite(motor2pin1, b*(1 - r/dampy));
  analogWrite(motor2pin2, f*(1 - r/dampy));
  
}
