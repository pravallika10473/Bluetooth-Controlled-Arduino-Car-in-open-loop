//TESLA PROTO
//variable declaration
int enA=6;//enable for right side of motors
int in1=7;//input for right side of motors 
int in2=8;//input for right side of motors 
int enB=9;//enable for left side of motors
int in3=10;//input for left side of motors 
int in4=11;//input for left side of motors
int horn=12;//horn input
int led=6;//light input
int wv=100;//value between 0-255 for writing in analogwrite of setspeed and here we are initializing it 
float left;//value between 0-255 for setting left wheel speed
float right;//value between 0-255 for setting right wheel speed
char cmd;//Bluetooth command
int sv;//speed value
void setup() {
  //  setup code which runs only once:
 pinMode(enA,OUTPUT);
 pinMode(enB,OUTPUT);
 pinMode(in1,OUTPUT);
 pinMode(in2,OUTPUT);
 pinMode(in3,OUTPUT);
 pinMode(in4,OUTPUT); 
 pinMode(horn,OUTPUT);
 pinMode(led,OUTPUT);
 Serial.begin(9600);
 
 }

void loop() {
  //  main code which run's repeatedly:
 left=wv;   //leftwheel speed
 right=wv;  //rightwheelspeed
 setspeed(right,left);//calling the setspeed function
 
  while(Serial.available()==0){
    //waiting untill comand is available via bluetooth
  }
  cmd=Serial.read();
  if(cmd =='0'||cmd =='1'||cmd =='2'||cmd =='3'||cmd =='4'||cmd =='5'||cmd =='6'||cmd =='7'||cmd =='8'||cmd =='9'||cmd =='q'){
    //setting speed
    if(cmd=='q'){
      wv=255;//q means 10 which is the max value
    }
    else{
      sv=cmd-'0';//converting char into int data type
      wv=(15*sv)+100;//mapping 100-255(min-max) wv values to 0-9 speed values
    }
    left=wv;//setting left wheel speed
    right=wv;//setting right wheel speed
    setspeed(left,right);//calling setspeed function
    
  }
  if(cmd=='F'){
    forward(1,wv);//if forward  , move 1 meter forward with specified speed
  }
  if(cmd=='B'){
    backward(1,wv);//if backward  , move 1 meter backward with specified speed
  }
  if(cmd=='R'){
    turnright(90,wv);//if turnright , rotate 90degrees right with specified speed
  }
  if(cmd=='L'){
    turnleft(90,wv);//if turnleft , rotate 90degrees left with specified speed
  }
  
  if(cmd=='V'){
    beephorn();
  }
  if(cmd=='W'){
    turnlighton();
  }
  if(cmd=='w'){
    turnlightoff();
  }
  
  
  
}
//SET SPEED
void setspeed(float rightspeed,float leftspeed){
  analogWrite(enA,rightspeed);
  analogWrite(enB,leftspeed);
}
//BEEP HORN
void beephorn(){
  digitalWrite(horn,HIGH);
  delay(500);
  digitalWrite(horn,LOW);
}
//LIGHT ON
void turnlighton(){
  digitalWrite(led,HIGH);
}
//LIGHT OFF
void turnlightoff(){
  digitalWrite(led,LOW);
}
//FORWARD FUNCTION DEFINITION
void forward(float d,float speedvalue){
  float v;//Velocity
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  // linear equation of velocity in m/s and analog input to the setspeed wv
  v=(0.006)*speedvalue;
  delay((d/v)*1000);//delay time required to move the car forward to desired distance with specified v
  stopcar();
  
  
}
//BACKWARD FUNCTION DEFINITION
void backward(float d,float speedvalue){
  float v;
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  // linear equation of velocity in m/s and analog input to the setspeed wv
  v=(0.006)*speedvalue;
  delay((d/v)*1000);//delay time required to move the car back to desired distance with specified v
  stopcar();
  
}
//RIGHT FUNCTION DEFINITION
void turnright(float theta,float angularvelocity){
  float w;
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  // linear equation of angularvelocity in degrees/s and analog input to the setspeed wv
  w=(2.7*(angularvelocity)-90);
  delay(1.4*(theta/w)*1000);//delay time required to rotate the car right to desired angle with specified v
  stopcar();
  
}
//LEFT FUNCTION DEFINITION
void turnleft(float theta,float angularvelocity){
  float w;
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  // linear equation of angularvelocity in degrees/s and analog input to the setspeed wv
  w=(2.7*(angularvelocity)-90);
  delay(1.4*(theta/w)*1000);//delay time required to rotate the car left to desired angle with specified v
  stopcar();
  
}
//STOP FUNCTION DEFINITION
void stopcar(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}
//CALIBRATE FORWARD FUNCTION
void calf(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(1000);
  stopcar();
}
//CALIBRATE BACKWARD FUNCTION
void calb(){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(1000);
  stopcar();
}
//CALIBRATE TURNRIGHT FUNCTION
void calR(){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(1000);
  stopcar();
}
//CALIBRATE TURNLEFT FUNCTION
void calL(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(1000);
  stopcar();
}
