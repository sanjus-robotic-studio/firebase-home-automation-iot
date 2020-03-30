
#include <ESP8266WiFi.h>
#include<FirebaseArduino.h>
#define FIREBASE_HOST "......."                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "......."       //Your Firebase Database Secret goes here
#define WIFI_SSID "....."             //your WiFi SSID for which yout NodeMCU connects
#define WIFI_PASSWORD "...."        //Password of your wifi network 

#define Light 4  //D2
int val3;


void setup() 
{
  Serial.begin(115200);                                                   // Select the same baud rate if you want to see the datas on Serial Monitor
 
  pinMode(Light,OUTPUT);
  digitalWrite(Light,HIGH);
    
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.setInt("S1",0);                     //Here the varialbe"S1","S2","S3" and "S4" needs to be the one which is used in our Firebase and MIT App Inventor
  
}
void firebasereconnect()
{
  Serial.println("Trying to reconnect");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }

void loop() 
{
  if (Firebase.failed())
      {
      Serial.print("setting number failed:");
      Serial.println(Firebase.error());
      firebasereconnect();
      return;
      }
      
 
   val3=Firebase.getString("S1").toInt();                                        //Reading the value of the varialble Status from the firebase
  
  if(val3==0)                                                             // If, the Status is 1, turn on the TV
     {
      digitalWrite(Light,LOW);
      Serial.println("TV ON");
    }
    else if(val3==1)                                                      // If, the Status is 0, turn Off the TV
    {                                      
      digitalWrite(Light,HIGH);
      Serial.println("TV OFF");
    }
  }
