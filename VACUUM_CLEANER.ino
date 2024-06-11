int leftMotorPinA = 3;
int leftMotorPinB = 5;
int rightMotorPinA = 6;
int rightMotorPinB = 9;
int trigPin = 11;
int echoPin = 12;

int motorSpeed = 150;
int totalArea = 100; 
const int leftUltrasonicTrigPin = 13; 
const int leftUltrasonicEchoPin = 14; 
const int rightUltrasonicTrigPin = 15; 
const int rightUltrasonicEchoPin = 16; 

void setup() {
  pinMode(leftMotorPinA, OUTPUT);
  pinMode(leftMotorPinB, OUTPUT);
  pinMode(rightMotorPinA, OUTPUT);
  pinMode(rightMotorPinB, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(leftUltrasonicTrigPin, OUTPUT);
  pinMode(leftUltrasonicEchoPin, INPUT);
  pinMode(rightUltrasonicTrigPin, OUTPUT);
  pinMode(rightUltrasonicEchoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  performFloodFill();
  findExitRoute();  
}

void performFloodFill() {
  int cleanCount = 0;  
  while (cleanCount < totalArea) {
    moveForward();
    if (distanceToObstacle() <= 20) {
      turnRandom();
    } else {
      cleanCount++;
    }
  }
}

void findExitRoute() {
  int leftDist = getDistance(leftUltrasonicTrigPin, leftUltrasonicEchoPin);
  int rightDist = getDistance(rightUltrasonicTrigPin, rightUltrasonicEchoPin);

  if (leftDist <= 20 && rightDist <= 20) {

  } else if (leftDist <= 20) {
 
    turnRight();
  } else if (rightDist <= 20) {
    
    turnLeft();
  } else {
 
    moveForward();
  }
}

int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;  
  return distance;
}

int distanceToObstacle() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;  
  return distance;
}

void moveForward() {
  digitalWrite(leftMotorPinA, HIGH);
  digitalWrite(leftMotorPinB, LOW);
  digitalWrite(rightMotorPinA, HIGH);
  digitalWrite(rightMotorPinB, LOW);
  delay(1000);  
}

void turnLeft() {
  digitalWrite(leftMotorPinA, LOW);
  digitalWrite(leftMotorPinB, HIGH);
  digitalWrite(rightMotorPinA, HIGH);
  digitalWrite(rightMotorPinB, LOW);
  delay(1000);  
}

void turnRight() {
  digitalWrite(leftMotorPinA, HIGH);
  digitalWrite(leftMotorPinB, LOW);
  digitalWrite(rightMotorPinA, LOW);
  digitalWrite(rightMotorPinB, HIGH);
  delay(1000);  
}

void turnRandom() {
  int randomTurn = random(0, 2);
  if (randomTurn == 0) {
    turnLeft();
  } else {
    turnRight();
  }
}
