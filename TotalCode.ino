//---------------------------------NFC
#define INCLUDE_NFC_SHIELD
//------------------------------------MUSIC PLAYER
#define INCLUDE_MUSIC_PLAYER_SHIELD
//---------------------------------LIGHT SENSOR
#define INCLUDE_LIGHT_SENSOR_SHIELD
#define INCLUDE_LED_SHIELD

//--------------------------------GamePad
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_SHIELD
#define motorright 13 
#define motorleft 12
#define motorforward 10
#define motorbackward 11
#define pwmout 6
#define pwmright 5
#define ledright 3
#define ledleft 4 

int vSpeed = 255;
int enterloop=0;
//---------------------------------GPS
#define INCLUDE_GPS_SHIELD
#define INCLUDE_SMS_SHIELD
#define INCLUDE_PHONE_SHIELD
char callingNumber[]="01067961816";
boolean isMessageSent = false;        
float lat ;                           
float lon ;
char charlat [10];
char charlon [10];
char readings [80];
boolean flag=false;
//--------------------------------------------Mic
#define INCLUDE_MIC_SHIELD
//---------------------------------------------MusicPLayer
#define INCLUDE_MUSIC_PLAYER_SHIELD
//---------------------------------------------Color Detection
#define INCLUDE_COLOR_DETECTOR_SHIELD
#define INCLUDE_TERMINAL_SHIELD
#define INCLUDE_TEXT_TO_SPEECH_SHIELD
#define INCLUDE_VOICE_RECOGNIZER_SHIELD
#define INCLUDE_BUZZER_SHIELD
#define INCLUDE_PUSH_BUTTON_SHIELD


/* Include 1Sheeld library. */
#include <OneSheeld.h>
/* A command which will be compared. */
const char firstCommand[]="go";

/* A command which will be compared. */
const char secondCommand[]="back";

/* A command which will be compared. */
const char thirdCommand[]="right";
const char fourthCommand[]="left";
const char fifthCommand[]="good morning";
const char sixthCommand[]="stop";

//---------------temp sensor
int sensorout= A0; //intialise the output pin of the sensor
int sensorvalue;
float temp;
//-----------------------LIGHT SENSOR
int ledPin = 2;
const int trig = 7;
const int echo = 8;
const int dangerthresh = 20;
void setup() 
{
  /* Start communication. */
  OneSheeld.begin();
//-------------------------------GamePad
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  

//------------------------------GPS
            //________
//-------------------------------Color Detection
 ColorDetector.setPalette(_12_BIT_RGB_PALETTE);
 ColorDetector.enableNormalOperation();
 ColorDetector.setCalculationMode(MOST_DOMINANT_COLOR);

  //------------HEMA
pinMode (trig,OUTPUT);
pinMode(echo,INPUT);
  // put your setup code here, to run once:
  OneSheeld.begin();
PushButton.setOnButtonStatusChange(&onButtonStatusChanged);

}
//--------------------------ADEL'S SMS SENSOR3
  
  
void loop() 
{
  
 
  //--------------------------------------------------------GAMEPAD
  /* Always check the status of gamepad buttons. */
    if(NFC.isNewTagScanned())
{
  
  Terminal.println("Nfc scanned :)");
  
  
  if( GamePad.isOrangePressed())
  {
    vSpeed=255;
  }
  
 if( GamePad.isRedPressed())
{
   movement (0, LOW, LOW,0,LOW,LOW);
   ledoff();
} 
if ( GamePad.isGreenPressed())
{
  vSpeed=255;
}
  if (GamePad.isUpPressed())
  {
    movement (vSpeed, HIGH, LOW,0,LOW,LOW);
    ledoff();
  }
 if(GamePad.isDownPressed())
  {
movement (vSpeed, LOW, HIGH,0,LOW,LOW);
ledoff();
  }
 if (GamePad.isRightPressed())
  {
    movement (vSpeed, HIGH, LOW,255,HIGH,LOW);
    ledrighton();
  }
 if (GamePad.isLeftPressed())
  {
     movement (vSpeed, HIGH, LOW,255,LOW,HIGH);
     ledlefton();

  }
  
  
  
  //----------------------------------------------------------------------GPS
  
  //delay(500);  
 
 if(Phone.isRinging())
 {
   
    if(strcmp(Phone.getNumber(),callingNumber) == 0) 
   {
    if( flag==false)
    {
    // Terminal.println("owner is calling ");
             SMS.send(" 01067961816","the Coordinates are" );
     flag=true;
    }
     if(!isMessageSent)  
       {
         lat = GPS.getLatitude(); 
         lon = GPS.getLongitude(); 
         
         dtostrf(lat, 7, 3, charlat);
         dtostrf(lon, 7, 3, charlon); 
         
        // strcat(readings,"GPS Coordinates : \n");               
        // strcat(readings,"latitude is : ");
         strcat (readings,charlat);  
         strcat(readings," , ");
         strcat (readings,charlon);
         
        SMS.send("01067961816",readings);
        // Terminal.println(readings);     
         isMessageSent = true;
       }                                        
   } 
//  else {isMessageSent = false;}
 }
 //else  {isMessageSent = false;}
 if( GamePad.isBluePressed())//&& enterloop==0) enterloop=1;
{
 /*if( enterloop==1)
  {
    // Set the volume. 
       MusicPlayer.setVolume(7);
        //Turn on the music. 
       MusicPlayer.play();
       */
       //------------------------------------------------------------------ColorDetection
     
         Color readColor = ColorDetector.getLastColor();
  byte redValue = readColor.getRed();
    byte greenValue = readColor.getGreen();
        byte blueValue = readColor.getBlue();
    
        if(redValue >greenValue && redValue >blueValue )
 { 
   Terminal.println("Red"); 
   movement (0, LOW, LOW,0,LOW,LOW);
 
  }
  
    else 
    {
      Terminal.println("Else");
    movement (vSpeed, HIGH, LOW,0,LOW,LOW);
      }
  }
  //}
     
    //  if( GamePad.isBluePressed() && enterloop==1 )enterloop=0;
 
  
  
  
  
  //-----------------------speech
  
  /* Always check if a new voice command received. */ 
   if(VoiceRecognition.isNewCommandReceived())
   {
     /* Check if the voice command is the desired one. */
     if(!strcmp(firstCommand,VoiceRecognition.getLastCommand()))
     {
       Terminal.println("go");
       vSpeed=255;
       movement (vSpeed, HIGH, LOW,0,LOW,LOW);
       /* 1Sheeld responds using text-to-speech. */
       /*digitalWrite(led1,HIGH);
       digitalWrite(led2,LOW);
       digitalWrite(led3,LOW);
       digitalWrite(led4,LOW);*/
       }
     /* Check if the voice command is the desired one. */
     else if(!strcmp(secondCommand,VoiceRecognition.getLastCommand()))
     {
       Terminal.println("back");
       vSpeed=255;
       movement (vSpeed, LOW, HIGH,0,LOW,LOW);       /* 1Sheeld responds using text-to-speech. */
       /*digitalWrite(led2,HIGH);
       digitalWrite(led1,LOW);
       digitalWrite(led3,LOW);
       digitalWrite(led4,LOW);*/
       
     }
     /* Check if the voice command is the desired one. */
     else if(!strcmp(thirdCommand,VoiceRecognition.getLastCommand()))
     {
       Terminal.println("right");
      movement (vSpeed, HIGH, LOW,255,HIGH,LOW); //turn right
       /*digitalWrite(led3,HIGH);
       digitalWrite(led1,LOW);
       digitalWrite(led2,LOW);
       digitalWrite(led4,LOW);*/
     }
      else if(!strcmp(fourthCommand,VoiceRecognition.getLastCommand()))
     {
       Terminal.println("left");
       movement (vSpeed, HIGH, LOW,255,LOW,HIGH);
       /*digitalWrite(led4,HIGH);
       digitalWrite(led1,LOW);
       digitalWrite(led3,LOW);
       digitalWrite(led2,LOW);*/
     }
      else if(!strcmp(fifthCommand,VoiceRecognition.getLastCommand()))
     {
              TextToSpeech.say("Good Morning digital");

     }
     else if ( !strcmp(sixthCommand,VoiceRecognition.getLastCommand()))
     { 
       Terminal.println ( "stop" ) ;
      movement (0, LOW, LOW,0,LOW,LOW);
   }
   }
   ///////////////flame 
 
  int sensorValue = analogRead(A1);
// Terminal.println(sensorValue);
delay(1); 

  if ( sensorValue < 70 )
  {
    
  movement (vSpeed, LOW, HIGH,0,LOW,LOW);
  delay(2000);
 
 
  movement (0, LOW, LOW,0,LOW,LOW);
  
  }
  
  
////-------------------------------------------------------------------------------------------------------------------TEAM JAZZ
//--------------LIGHT SENSOR
if(LightSensor.getValue() < 100 && LightSensor.getValue() > 0)
  {
    /* Turn on the LED. */
    digitalWrite(ledPin,HIGH);
  }
  else
  {
    /* Turn off the LED. */
    digitalWrite(ledPin,LOW);
  }
//  if( LightSensor.getValue() <20)
//  {
//     
//    /* Turn on the LED. */
//    digitalWrite(ledPin,HIGH);
//     LED.setHigh();
//  }
//  else {
//      digitalWrite(ledPin,LOW);
//  }
       

  //---------------------------------ADEL'S SMS sensor
//    if (PushButton.isPressed())
//  {
//    Terminal.println("buttonPressed");
//    }

   //-------------------------temp sensor
  
  sensorvalue=analogRead(sensorout);
temp= float (sensorvalue)/1023;//we either use this numerical method or we use the map
temp= temp*500;
//temp= map(temp,0, 1024, -55.0, 150.0);
if (temp>40)
{
Terminal.print("warning, motor temperature is very high"); 
}

//Terminal. println( "Temp is: ");
//Terminal. println(temp);
//Terminal. println("C");



 // -----------------------------------------------------------------------------------------------------------------------------HEMA 
 
if(Distance()<=dangerthresh) {
 // Serial.print("DANGER");
      Buzzer.buzzOn();

  }
  else{
        Buzzer.buzzOff();
  }

}

}
//------------------------------------------------------------------- functions

void onButtonStatusChanged(bool isPressed)
{
  /* Check the buttons status. */
  if(isPressed)
  {
    /* Send an email. */
    SMS.send("01204495517", "my car isn't working, please call me.");
  }
}

long Distance()
{
  digitalWrite (trig , LOW);
delayMicroseconds (10);
digitalWrite (trig , HIGH);
delayMicroseconds (10);
digitalWrite (trig , LOW);
float distance = pulseIn (echo,HIGH);
distance =distance/58.2 ;
return(distance);
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
  void ledrighton()
  {
    digitalWrite(ledright,HIGH);
    digitalWrite(ledleft,LOW);
 
  }
  void ledlefton()
  {    digitalWrite(ledleft,HIGH);
    digitalWrite(ledright,LOW);
  }
    void ledoff()
    {
      digitalWrite(ledleft,LOW);
    digitalWrite(ledright,LOW);
  }
  // forward ==movement (vSpeed, HIGH, LOW,0,LOW,LOW)
  //backward==movement (vSpeed, LOW, HIGH,0,LOW,LOW)
  //right==movement (vSpeed, HIGH, LOW,255,HIGH,LOW)
    //left==movement (vSpeed, HIGH, LOW,255,LOW,HIGH)
    //stop==movement (0, LOW, LOW,0,LOW,LOW)
    
    
    




