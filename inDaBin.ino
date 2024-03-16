#include <Servo.h>

Servo servo; // Class, creates servo object to control servo

// pin 5

int trigPin = 5;    
int echoPin = 6;   
int servoPin = 7;
int led= 10;
long duration, dist, average;   
long aver[3];   //  3 Second wait for 

// setup() -> runs once at start
// loop() -> main loop of program

void setup() {  // runs once at start 
  Serial.begin(9600);
  servo.attach(servoPin);  // attaches servo on specified pin to servo object
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);  
  servo.write(0); //sets servo position to 0    
  delay(100); //for servo to get to position
  servo.detach(); 
}

void measure() {  
  digitalWrite(10,HIGH);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  dist = (duration/2) / 29.1; // objects distance
}

void loop() {  
  for (int i=0;i<=2;i++) {   
    measure();               
    aver[i]=dist;            
    delay(10);              
  }
  dist=(aver[0]+aver[1]+aver[2])/3;    

  if ( dist<50 ) {
    servo.attach(servoPin);
    delay(1);
    servo.write(0);  
    delay(3000);       
    servo.write(150);    
    delay(1000);
    servo.detach();      
  }
  Serial.print(dist);
}
