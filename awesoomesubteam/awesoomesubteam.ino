#define CUSTOM_SETTINGS
#define INCLUDE_NFC_SHIELD
#define INCLUDE_TERMINAL_SHIELD
#define INCLUDE_MUSIC_PLAYER_SHIELD
#define INCLUDE_CLOCK_SHIELD
#define INCLUDE_VOICE_RECOGNIZER_SHIELD
#define INCLUDE_TEXT_TO_SPEECH_SHIELD
#define INCLUDE_LIGHT_SENSOR_SHIELD


/* Include 1Sheeld library. */
#include <OneSheeld.h>
const char startCommand[] = "engine start";
int hour;
  int counter=0;
int ledPin = 13;

//temp sensor
int sensorout= A0; //intialise the output pin of the sensor
int sensorvalue;
float temp;
void setup()
{

  /* Start Communication. */
  OneSheeld.begin();
   // Clock.queryDateAndTime();
      VoiceRecognition.start();
       pinMode(ledPin,OUTPUT);

}

void loop()
{
 
  if( LightSensor.getValue() == 0)
  {
     
    /* Turn on the LED. */
   digitalWrite(ledPin,HIGH);
  }     

  
   hour = Clock.getHours();
    if(NFC.isNewTagScanned()&& counter==0)
    {
      TextToSpeech.say("good morning doctor");
       delay(3000);
    counter= counter+1;
    }
            //  NFCTag & myTag = NFC.getLastTag();

//if (hour<12&& counter==0)
//{
//  TextToSpeech.say("good morning doctor");
//    delay(3000);
//    counter= counter+1;
//  } 
//
//if (hour>12 && (hour<18||hour ==18) && counter==0)
//{
//  TextToSpeech.say("good evening Doctor");
//  delay(3000);
//      counter= counter+1;
//  } 
//  if (hour>18 && counter==0)
//{
//  TextToSpeech.say("good night doctor");
//  delay(3000);
//        counter= counter+1;
// } 



    if(VoiceRecognition.isNewCommandReceived())
{
  if(!strcmp(startCommand,VoiceRecognition.getLastCommand()))
    {
      Terminal.println(VoiceRecognition.getLastCommand());
      /* Play the track. */
      MusicPlayer.play();
      OneSheeld.delay(5000); 
     MusicPlayer.pause();
    }
  }
  //temp sensor
  sensorvalue=analogRead(sensorout);
//temp= sensorvalue*(5000/1023) //we either use this numerical method or we use the map
temp= map(temp,0, 1024, -55.0, 150.0);
Terminal. print( "Temp is: ");
Terminal. print(temp);
}







