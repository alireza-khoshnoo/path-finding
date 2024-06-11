#include <AFMotor.h>

const int trigPin = 9;
const int echoPin = 10;

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

const int rows = 5;
const int cols = 5;

int maze[rows][cols] = {
  {0, 0, 0, 0, 0},
  {0, 1, 0, 1, 1},
  {0, 1, 0, 0, 0},
  {0, 1, 1, 1, 0},
  {0, 0, 0, 0, 0}
};

void moveForward() {
  motor1.setSpeed(150);
  motor2.setSpeed(150);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}

void moveBackward() {
  motor1.setSpeed(150);
  motor2.setSpeed(150);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
}

void turnLeft() {
  motor1.setSpeed(150);
  motor2.setSpeed(150);
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
}

void turnRight() {
  motor1.setSpeed(150);
  motor2.setSpeed(150);
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
}

bool isValidMove(int x, int y) {
  return (x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] == 0);
}


void floodFill(int x, int y) {
  if (!isValidMove(x, y)) {
    return;
  }

  maze[x][y] = 2;

  moveForward();

  floodFill(x + 1, y); 
  floodFill(x - 1, y); 
  floodFill(x, y + 1); 
  floodFill(x, y - 1); 

  moveBackward();
}


float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
  return distance;
}


void identifyExitPath() {

  float frontDistance = getDistance();
  
  if (frontDistance > 10) {

    moveForward();
  } else {
 
    turnLeft();
    float leftDistance = getDistance();
    delay(1000); 
    turnRight();
    float rightDistance = getDistance();
    delay(1000); 
    
    if (leftDistance > rightDistance) {
      turnLeft();
    } else {
      turnRight();
    }
  }
}


void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  floodFill(0, 0);

  identifyExitPath();
}

void loop() {

}

