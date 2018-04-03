
#define CUSTOM_SETTINGS
#define INCLUDE_CAMERA_SHIELD
#define INCLUDE_TERMINAL_SHIELD
#define INCLUDE_PHONE_SHIELD
#define INCLUDE_TEXT_TO_SPEECH_SHIELD
//------------------------------
#define motorright 13 
#define motorleft 12
#define motorforward 10
#define motorbackward 11
#define pwmout 6
#define pwmright 5
int vSpeed = 255;
//---------------------------------
#include <OneSheeld.h>
int LP=A3;
int RP=A4;
int FP=A5;
int ValL, ValR, ValF;
bool lightflag= false;

float x;
void setup() {
 OneSheeld.begin();
//Serial.begin(9600);
//----------------------
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  

}

void loop() {
  x=analogRead(A2);
if ( x> 100)
{ Camera.setFlash(ON);
    /* Take a photo using the phone's rear camera. */
    Camera.rearCapture();
    
   Terminal.println("CAPTURED");
    //Serial.println("CAPTURED");
    delay(500);
    //OneSheeld.delay(5000);
    
  }
  
if (Phone.isRinging())
{
  if(strcmp(Phone.getNumber(),"01118634766") == 0)
{  lightflag=true;}
}
  if (lightflag==true)
  {
ValL=analogRead(LP);
ValR=analogRead(RP);
ValF=analogRead(FP);
if ( ValL > ValR && ValL > ValF){ TextToSpeech.say("Turn Left");movement (vSpeed, HIGH, LOW,255,LOW,HIGH);delay(5000); }
else if ( ValR > ValL && ValR > ValF){TextToSpeech.say("Turn Right");movement (vSpeed, HIGH, LOW,255,HIGH,LOW);delay(5000);}
else if ( ValF > ValL && ValF > ValR){TextToSpeech.say("Move Forward"); movement (vSpeed, HIGH, LOW,0,LOW,LOW); delay(5000);}
  }
  


}



void movement (int a, int b, int c,int d,int e,int f)
 {
    analogWrite(pwmout,a);
    digitalWrite(motorforward,b);
    digitalWrite(motorbackward,c);
    analogWrite(pwmright,d);
    digitalWrite(motorright,e);
    digitalWrite(motorleft,f);
   
  }


  
