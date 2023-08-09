

/*MOTOR MODULE CONFIGURATIONS

LEFT MOTOR ini1 and ini2
Forward:
  ini1=LOW
  ini2=HIGH

RIGHT MOTOR ini3 and ini4
Forward:
  ini3=LOW
  ini4=HIGH


NOTE: The initial problem of motor having disoriented direction speed, still persists as the delay function performs abnormally.
*/

// Sensor Pins
int trigPin=12;
int echoPin=11;
int duration;
int distance;

//Motor 1
int enA = 10;
int in1 = 9;
int in2 = 8;

// Motor 2
int enB = 5;
int in3 = 7;
int in4 = 6;

//Changing Directions Alternatively
int rev_delay_factor=2000;
int turning_delay_factor=1500;
int flag=0;

//Distance TO Avoid
int distance_2_avoid=30;

  void setup(){
    Serial.begin(9600);
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(trigPin, OUTPUT);         
    pinMode(echoPin, INPUT);
  }


  void forward(){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH); 
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

  }
  void reverse(){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
 
    }
  void stop(){
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
      }


  void reverse_right(){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    }

  void reverse_left(){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    }

void loop()
{
  //Calculate Distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);   
  digitalWrite(trigPin, HIGH);// send waves for 10 us
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH);// receive reflected waves
  distance = duration / 58.2; // convert to distance to cm

  //Enable Motor Module Pins to move
  analogWrite(enB, 200);
  analogWrite(enA, 200);

  //Distance Avoidance
  
  if(distance<distance_2_avoid){  
    Serial.println("Obstacle Ahead !!! ");
    stop();
 
    if (flag==0){
        Serial.println("Reverse");
        reverse();
        delay(rev_delay_factor);
        Serial.println("Turning Left");
        reverse_right();
  
        delay(turning_delay_factor);
        flag=1;
      }
    else if(flag==1){
        Serial.println("Reverse");
        reverse();
        delay(rev_delay_factor);
        Serial.println("Turning Right");
        reverse_left();    
        delay(turning_delay_factor);
        flag=0;
      }
    forward();
  }
  else{
    // Keep Moving Forward
    Serial.println("Forward");
    forward();
    }//ENDIF
}//END LOOP
