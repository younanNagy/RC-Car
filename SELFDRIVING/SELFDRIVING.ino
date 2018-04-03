 

#define CUSTOM_SETTINGS
#define INCLUDE_INTERNET_SHIELD
#define INCLUDE_GPS_SHIELD
#define INCLUDE_TERMINAL_SHIELD
#define INCLUDE_TEXT_TO_SPEECH_SHIELD 
#include <OneSheeld.h>
String YARAB[7][3];
int vSpeed = 255;
#define motorright 13 
#define motorleft 12
#define motorforward 10
#define motorbackward 11
#define pwmout 6
#define pwmright 5
#define ledright 3
#define ledleft 4 

bool flagDone = false;
#define url "https://maps.googleapis.com/maps/api/directions/json?origin=30.0706968,31.29401159999999&destination=30.073080,%2031.317828&key=AIzaSyCG68D74poWhfbdzZ1xgqr_CZidaGc8li0"
int arrLen;
HttpRequest myrequest (url);

void setup() {
 /*
  float latDouble = GPS.getLatitude();
  double lngDouble = GPS.getLongitude();
  //Terminal.print(latDouble);
  char * part1 = "https://maps.googleapis.com/maps/api/directions/json?origin=";
  char * part3 = ",";
  char * part5 = "&destination=30.0685127,31.279899&key=AIzaSyCG68D74poWhfbdzZ1xgqr_CZidaGc8li0";
  char * part2="30.07";
  char * part4="31.28";
  //sprintf(part2,"%lf", latDouble);
  //sprintf(part4,"%lf", lngDouble);
  int n = strlen(part1)+strlen(part2)+strlen(part3)+strlen(part4)+strlen(part5);
  char * url = (char *)malloc((n*sizeof(char))-1);
  int j = 0;
  for(int k=0;k<strlen(part1);k++){
    url[j]=part1[k];
    j++;
  }
  for(int k=0;k<strlen(part2);k++){
    url[j]=part2[k];
    j++;
  }
  for(int k=0;k<strlen(part3);k++){
    url[j]=part3[k];
    j++;
  }
  for(int k=0;k<strlen(part4);k++){
    url[j]=part4[k];
    j++;
  }
  for(int k=0;k<strlen(part5);k++){
    url[j]=part5[k];
    j++;
  } 
  HttpRequest myrequest (url);
  */OneSheeld.begin();
  myrequest.setOnSuccess(&onSuccess);
  Internet.performGet(myrequest);
  myrequest.getResponse().setOnJsonResponse(&onJsonReply);
  myrequest.getResponse().setOnJsonArrayLengthResponse(&lenReq);


//------------------
pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  
}
int m=0;
float lat;
float lng;
bool flagArrived = false;
float error = 0.000297321*3;
void loop ()
{
  //Terminal.println(url);
  if(flagDone){
    lat=GPS.getLatitude();
    lng=GPS.getLongitude();
    lat=(lat-30.0)*10000000;
    lng=(lng-31.2)*10000000;
    //Terminal.println(YARAB[m][1]);
    //Terminal.println(YARAB[m][2]);
    //Terminal.println(lat);
    //Terminal.println(lng);
    error=5000;
    if((YARAB[m][1].toFloat())>=(lat-error)&&YARAB[m][1].toFloat()<=(lat+error)&&(YARAB[m][2].toFloat())>=(lng-error)&&YARAB[m][2].toFloat()<=(lng+error)&&m<3){
        Terminal.println(YARAB[m][0]); TextToSpeech.say(YARAB[m][0]);
       if (YARAB[m][0]=="turn right"){movement (vSpeed, HIGH, LOW,255,HIGH,LOW); /*delay(500);*/}
       if( YARAB[m][0]=="turn left"){movement (vSpeed, HIGH, LOW,255,LOW,HIGH); /*delay(500);*/}
        
        
        
        
        m++;
      
      
      }else{
        //else{Terminal.println("no match");}
        if(m==1&&!flagArrived){
          flagArrived = true;
          delay(10000);
          Terminal.println("Arrived"); TextToSpeech.say("Arrived");
        }
      }
  }  
}

void onSuccess(HttpResponse & response)
{ 
  response ["routes"][0]["legs"][0]["steps"].queryArrayLength();
 
  for(int k=1;k<4;k++)
  //for(int k=1;k<3;k++)
  {
    response ["routes"][0]["legs"][0]["steps"][k]["maneuver"].query();
    response ["routes"][0]["legs"][0]["steps"][k]["start_location"]["lat"].query();  
    response ["routes"][0]["legs"][0]["steps"][k]["start_location"]["lng"].query();  

   }

}

void lenReq (JsonKeyChain &chain , unsigned long arrayLength )
{
  
  //Terminal.println(arrayLength);
  if (myrequest.getResponse()["routes"][0]["legs"][0]["steps"]==chain){arrLen=arrayLength-1;}
  //Terminal.println(arrLen);
}
void onJsonReply(JsonKeyChain & hell, char * output)
{
  Terminal.println(output);
  for(int j=0;j<5;j++){
    if (myrequest.getResponse ()["routes"][0]["legs"][0]["steps"][j]["maneuver"] == hell)
    {
      if(output==""){
        YARAB[j-1][0]="forward";
        }
      else{
        YARAB[j-1][0]=output;
        }
    }
    if (myrequest.getResponse ()["routes"][0]["legs"][0]["steps"][j]["start_location"]["lat"] == hell)
    {
      YARAB[j-1][1]=output;
      
    }
    if (myrequest.getResponse ()["routes"][0]["legs"][0]["steps"][j]["start_location"]["lng"] == hell)
    {
      YARAB[j-1][2]=output;
      if(j==3){
      //if(j==2){  
        delay(2000);
        rundone();
       }
    }
    
  }
 
}

void rundone(){
    for(int d=0;d<3;d++){
    //for(int d=0;d<2;d++){
    Terminal.println(arrLen);
    Terminal.println(YARAB[d][1]);
    Terminal.println(YARAB[d][2]);
    Terminal.println(YARAB[d][0]);
    YARAB[d][1]=YARAB[d][1].substring(4);
    YARAB[d][2]=YARAB[d][2].substring(4);
  }
  flagDone = true;
}




//---------------------------------------


void movement (int a, int b, int c,int d,int e,int f)
 {
    analogWrite(pwmout,a);
    digitalWrite(motorforward,b);
    digitalWrite(motorbackward,c);
    analogWrite(pwmright,d);
    digitalWrite(motorright,e);
    digitalWrite(motorleft,f);
   
  }
 
