

////////  #includes  //////////
#include <Servo.h>

/////// global veribal //////////////
const int standBayH=20;
const int  X1 = A0, Y1 = A1, X2 = A2, Y2 = A3;
int Xmeas[3] = {0};
int Ymeas[3] = {0};
int refposX =0,refposY =0;
double y_cord=0,old_y_cord=0,old_old_y_cord=0, x_cord=0,old_x_cord=0,old_old_x_cord=0;
double divX[2]={0},divY[2]={0};
unsigned long t,old_t=0;
int maxVal = 85;
int minVal = -85;

int touchFlag = 0;
Servo servo1,servo2,servo3;
////////////////////////////////////////







/////// Functions /////////////
    boolean touch();
    void ReadData();
    void hight(int h);
    double sat( double input);
    void mixer(float x,float y);
    void hight(int h);
    //void ibit();
//////////////////////////




void setup() {
 Serial.begin(9600); 



    ////////////////////// Servo init  /////////////////////////
    servo1.attach(9);  
    servo2.attach(10);
    servo3.attach(11);
    servo1.write(standBayH);
    servo2.write(standBayH);
    servo3.write(standBayH);
    delay(500);
    ///////////////////////////////////////////////////////////


  ///////////////////////// TIM2 init ////////////////////////  
  TCCR2A=(1<<WGM01);    //Set the CTC mode   
  OCR2A=108; //Value for ORC0A for 1ms 
  
  TIMSK2|=(1<<OCIE0A);   //Set the interrupt request
  sei(); //Enable interrupt
  
  TCCR2B|=(1<<CS01);    //Set the prescale 1/64 clock
  TCCR2B|=(1<<CS00);
///////////////////////////////////////////////////////////////
 
    
}

void loop() {
  //in this way you can count 1 second because the nterrupt request is each 1ms
  
  
 
  
}

ISR(TIMER2_COMPA_vect){    // Interrupt request every ~ 150Hz 
  old_t=t;

if (touch())
  { 
    touchFlag = 0;
  
  
  ReadData(); 
 /*
Serial.print(y_cord);  
Serial.print(" | ");
Serial.println(x_cord);
*/

  mixer(sat(+0.38*(y_cord+refposY)+6.2*(y_cord-Ymeas[2])),sat(0.38*(x_cord+refposX)+6.2*(x_cord-Xmeas[2])));
 
}
t = micros();
 Serial.println(t-old_t); 
 touchFlag++;
 if(touchFlag>10)   hight(standBayH);
}






























void hight(int h){
    servo1.write(h);
    servo2.write(h);
    servo3.write(h);
   
  
}

void mixer(float x,float y)
{  
    servo1.write(90+int(y));
    servo2.write(90+int(-x*sqrt(3)/2-y*0.5));
    servo3.write(90+int(x*sqrt(3)/2-y*0.5));
   
    /*
    Serial.print(int(y));
    Serial.print("  ");
    Serial.print(int(-x*sqrt(3)/2-y*0.5));
    Serial.print("  ");
    Serial.println(int(x*sqrt(3)/2-y*0.5));
    
    */
    
}







boolean touch()
{
  
 pinMode(Y1, OUTPUT);
 pinMode(Y2, OUTPUT);
 pinMode(X1, OUTPUT);
 pinMode(X2, OUTPUT);
 digitalWrite(X1, HIGH);
 digitalWrite(X2, LOW);
 digitalWrite(Y1, LOW);
 digitalWrite(Y2, LOW);
 pinMode(Y1, INPUT);
 pinMode(Y2, INPUT);

 

  if( analogRead(Y1)>100)return 1;
  else return 0;
}

  void ReadData()
  {
 pinMode(Y1, OUTPUT);
 pinMode(Y2, OUTPUT);
 pinMode(X1, OUTPUT);
 pinMode(X2, OUTPUT);
 digitalWrite(X1, HIGH);
 digitalWrite(X2, LOW);
 digitalWrite(Y1, LOW);
 digitalWrite(Y2, LOW);
 pinMode(Y1, INPUT);
 pinMode(Y2, INPUT);

 //y_cord =(analogRead(Y2)+analogRead(Y1))/2;
  //
Ymeas[2] = Ymeas[1];
Ymeas[1] = y_cord;

for(int i=0;i<3;i++) Ymeas[0]  = analogRead(Y2);

y_cord  = 0.996*Ymeas[0]+0.0015*Ymeas[1]+0.0025*Ymeas[2];
y_cord =(y_cord -480)*70/400;
 
 pinMode(Y1, OUTPUT);
 pinMode(Y2, OUTPUT);
 pinMode(X1, OUTPUT);
 pinMode(X2, OUTPUT);
 digitalWrite(Y1, HIGH );
 digitalWrite(Y2, LOW);
 digitalWrite(X1, LOW);
 digitalWrite(X2, LOW);
 pinMode(X1, INPUT);
 pinMode(X2, INPUT);
 //x_cord = (analogRead(X2)+analogRead(X1))/2;
 
 Xmeas[2] = Xmeas[1];
 Xmeas[1] = x_cord;
 for(int i=0;i<3;i++) Xmeas[0]  = analogRead(X2);

x_cord = 0.996*Xmeas[0]+0.0015*Xmeas[1]+0.0025*Xmeas[2];
x_cord = (x_cord-480)*50/400;
  
  }

double sat( double input)
{
  if(input>maxVal)return maxVal;
  else if (input<minVal)return minVal;
  else return input;

}
   
