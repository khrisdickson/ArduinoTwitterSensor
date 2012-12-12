#include <SPI.h>
#include <Ethernet.h>
#include <Twitter.h> //import twitter library

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xCE, 0x1A }; // arduinoi mac address
Twitter twitter("988831734-DZhst3nSBUIBywstWLgiFoBQazxEwBvQGJetjJm9"); //key used to access twitter account http://arduino-tweet.appspot.com/
const char msg[] = "Something is at your door."; //message to send to twitter

int val = 0;   //value of motion sensor   

void setup() 
{
  pinMode(LED, OUTPUT); // LED is as an OUTPUT
}

void loop() //constant loop
{  
  val = analogRead(0); // read the value from the sensor
  Serial.begin(9600);
  Serial.println(val); //print value from sensor
  delay(500);
  digitalWrite(LED, LOW); // turn the LED off
  checkSensor();
}

void checkSensor() //checking sensor continously
{
  if(val >= 300)
  {
    Serial.begin(9600);
    Serial.println(val);
    digitalWrite(LED, HIGH); // turn the LED on
    sendTweet(); //opens sendTweet function when sensor receives a value over 300
    delay(6000);
  }
}

void sendTweet()
{
  delay(1000);
  Ethernet.begin(mac); //connects to ethernet and twitter
  Serial.begin(9600);
  
  Serial.println("connecting to twitter...");
  if (twitter.post(msg)) {

    

    int status = twitter.wait(&Serial);
    //confirms if data has been sent or not
      if (status == 200) 
      {
        Serial.println("OK.");
      } 
      else
      {
        Serial.println("failed : code ");
        Serial.println(status); //takes status from twitter api
      }
  }
  else
  {
   Serial.println("connection failed.");
  }
  delay(3000); //delay for program to resume after message is posted
}

