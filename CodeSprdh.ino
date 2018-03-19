#include "SoftwareSerial.h"
SoftwareSerial BT(10,11);//RX,TX

//SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                             // and the RX line from the esp to the Arduino's pin 3

#define DEBUG true

String connectivity ;
String st ;
int operation,pinNumberInt,pinNumber;
void setup() {
    
    BT.begin(9600);

    Serial.begin(9600);

    
    pinMode(4,OUTPUT);
    digitalWrite(4,HIGH);

    pinMode(5,OUTPUT);
    digitalWrite(5,HIGH);

    pinMode(13,OUTPUT);
    pinMode(13,LOW);

    pinMode(6,OUTPUT);
    digitalWrite(6,HIGH);
    
    pinMode(7,OUTPUT);
    digitalWrite(7,HIGH);
    
    pinMode(8,OUTPUT);
    digitalWrite(8,HIGH);
  
    pinMode(9,OUTPUT);
    digitalWrite(9,HIGH);
  
    
    connectivity = "100";
    
        
    /*reset module
    sendData("AT+RST\r\n",2000,DEBUG);            //This command will reset module to default
    sendData("AT+CWMODE=2\r\n",1000,DEBUG);       // This will configure the mode as access point
    sendData("AT+CIFSR\r\n",1000,DEBUG);          // This will get ip address and will show it
    sendData("AT+CIPMUX=1\r\n",1000,DEBUG);       // This will configure the ESP8266 for multiple connections
    sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // This will set the server on port 80*/
    
    
}

void loop() {
    //bluetooth
    //if(connectivity=="100")
    //{ 
      
      while(BT.available())
      {
        Serial.println("Bluetooth available");
        delay(10);
        char c = BT.read();
        st+=c;
      }
      if(st.length()>0 )
          Serial.println(st);
      
      Serial.println(st);
      
      //if(st=="100"||st=="200"){
        //connectivity = st ;
      //}
      
      
          
        
        pinNumberInt = atoi(st.c_str());
        operation=pinNumberInt % 10;
        pinNumber = pinNumberInt / 10 ;
  
        if(pinNumber==13)
        {
         if(operation==1 && digitalRead(pinNumber)==LOW)
         {
          digitalWrite(pinNumber, HIGH);     
          Serial.println("ON");
         }
         else if(operation==0 && digitalRead(pinNumber)==HIGH )
         {
            digitalWrite(pinNumber,LOW);
            Serial.println("OFF");
         }
        }      
        
        if(pinNumber>13)
        {
          pinNumber=pinNumber%10; 
        }
        if(operation==1 && digitalRead(pinNumber)==HIGH)
        {
          digitalWrite(pinNumber, LOW);     
          Serial.println("ON");
        }
        else if(operation==0 && digitalRead(pinNumber)==LOW )
        {
          digitalWrite(pinNumber,HIGH);
          Serial.println("OFF");
        }   
          st="";
       
    //}
    //Wifi module
    /*else if(connectivity == "200")
    {
      
      
      if(esp8266.available()) // check if the esp is sending a message 
      {
        if(esp8266.find("+IPD,"))
        {
         delay(1000); // wait for the serial buffer to fill up (read all the serial data)
         // get the connection id so that we can then disconnect
         int connectionId = esp8266.read()-48; // subtract 48 because the read() function returns 
                                               // the ASCII decimal value and 0 (the first decimal number) starts at 48
              
         esp8266.find("pin="); // advance cursor to "pin="
    
         //delay(100);
         
         int pinNumber = (esp8266.read()-48)*100; // get first number i.e. if the pin 13 then the 1st number is 1, then multiply to get 10
         pinNumber += (esp8266.read()-48)*10;
         pinNumber+= (esp8266.read()-48);
         int operation=pinNumber%10;
         pinNumber=pinNumber/10;

        if(pinNumber==13)
        {
         if(operation==1 && digitalRead(pinNumber)==LOW)
         {
          digitalWrite(pinNumber, HIGH);     
          Serial.println("ON");
         }
         else if(operation==0 && digitalRead(pinNumber)==HIGH )
         {
            digitalWrite(pinNumber,LOW);
            Serial.println("OFF");
         }
        }      
         
         if(pinNumber>13)
         {
          pinNumber=pinNumber%10; 
         }
         if(operation==1 && digitalRead(pinNumber)==HIGH)
         {
          digitalWrite(pinNumber, LOW);     
          Serial.println("ON");
         }
         else if(operation==0 && digitalRead(pinNumber)==LOW )
         {
            digitalWrite(pinNumber,HIGH);
            Serial.println("OFF");
         }
         // make close command
         String closeCommand = "AT+CIPCLOSE="; 
         closeCommand+=connectionId; // append connection id
         closeCommand+="\r\n";
         
         sendData(closeCommand,1000,DEBUG); // close connection
        }
      }
    }*/
}
/*
* Name: sendData
* Description: Function used to send data to ESP8266.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
*/
/*String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}*/
