
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include<LiquidCrystal.h>

LiquidCrystal lcd(A5, A4, A3, A2, A1, A0);
int mode1=3;
int mode2=4;
int mode3=5;

RF24 radio(7,8);                // nRF24L01(+) radio attached using Getting Started board 

RF24Network network(radio);      // Network uses that radio

const uint16_t this_node = 00;        // NODE 1
const uint16_t other_node = 01;       // BASE STATION
const uint16_t other_node2=02;        //NODE 2

const uint16_t other_node1 = 02; 

char receive_data[50];
unsigned char mode;

char a[18]="NO PARKING";
char b[18]="NO HORN";
char c[18]="TURN RIGHT";
char d[18]="NO ENTRY";
char e[18]="KEEP LEFT";
unsigned int i;

void setup(void)
{
  Serial.begin(9600);
  lcd.begin(16,2);
   
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ this_node);
  
  pinMode(mode1,INPUT);
  pinMode(mode2,INPUT);
  pinMode(mode3,INPUT);
}

void loop(void)
{
   if(digitalRead(mode1))
  {
    mode=1;
  }
  else if(digitalRead(mode2))
  {
    mode=2;
   }
  else if(digitalRead(mode3))
  {
    mode=3;
  }
  else
  mode=0;


switch(mode)
{
  lcd.clear();

  case 1:

          Serial.println("NODE 1 MODE 1");
          
          lcd.setCursor(0,0);
          lcd.print("NODE 1  MODE 1");
          delay(1000);
          
         while(1)
         { 
          network.update();                  // Check the network regularly
          lcd.clear();
          lcd.setCursor(0,0);
          
          if ( network.available() )
               {     // Is there anything ready for us?
                    Serial.println("NODE 1");
                    RF24NetworkHeader header;        // If so, grab it and print it out
                    network.read(header,&receive_data,sizeof(receive_data));
                    Serial.print("BASE STATION : ");
                    Serial.println(receive_data);
                    lcd.print(receive_data);
                    
                    RF24NetworkHeader header1(other_node2);        // If so, grab it and print it out

                    if(strcmp(receive_data,"PARKING IS FULL")==0)
                        {
                            char data_send[18]="PARKING AVAILABLE";
       
                            network.write(header1,data_send,sizeof(data_send));
                            Serial.print("DATA SENT : ");
                            Serial.println(data_send);
                            lcd.setCursor(0,1);
                            lcd.print(data_send);
    
                        }
                }
  
           }

  case 2:

          Serial.println("NODE 1 MODE 2");
          
          lcd.setCursor(0,0);
          lcd.print("NODE 1 MODE 2");
          delay(1000);
          i=0;
         while(1)
         { 
          network.update();                  // Check the network regularly
          lcd.clear();
          lcd.setCursor(0,0);
          
          if ( network.available() )
               {     // Is there anything ready for us?

                    RF24NetworkHeader header;        // If so, grab it and print it out
                    network.read(header,&receive_data,sizeof(receive_data));
                    Serial.print("BASE STATION : ");
                    Serial.println(receive_data);
                    lcd.print(receive_data);
                    
                    RF24NetworkHeader header1(other_node2);        // If so, grab it and print it out
                    
                    char data_send[18];

                     if(i>4)
                     i=0;
                     
                      if(i==0)
                      strcpy(data_send,a);
                      else if(i==1)
                      strcpy(data_send,b);
                      else if(i==2)
                      strcpy(data_send,c);
                      else if(i==3)
                      strcpy(data_send,d);
                      else if(i==4)
                      strcpy(data_send,e);  

                      i++;
                            network.write(header1,data_send,sizeof(data_send));
                            Serial.print("DATA SENT : ");
                            Serial.println(data_send);
                            lcd.setCursor(0,1);
                            lcd.print(data_send);
                }
  
           }
  case 3:

          Serial.println("NODE 1 MODE 3");
          
          lcd.setCursor(0,0);
          lcd.print("NODE 1 MODE 3");
          delay(1000);
          bool flag=0;
         while(1)
         { 
          network.update();                  // Check the network regularly
          lcd.clear();
          lcd.setCursor(0,0);
          
          if ( network.available() )
               {     // Is there anything ready for us?

                    RF24NetworkHeader header;        // If so, grab it and print it out
                    network.read(header,&receive_data,sizeof(receive_data));
                    Serial.print("BASE STATION : ");
                    Serial.println(receive_data);
                    lcd.print(receive_data);
                    
                    RF24NetworkHeader header1(other_node2);        // If so, grab it and print it out
                    
                    if(flag==0)
                    {
                      lcd.setCursor(0,1);
                      lcd.print("Delayed         ");
                      delay(5000);
                    }
                    flag=~flag;
                    
                            network.write(header1,receive_data,sizeof(receive_data));
                            Serial.print("DATA SENT : ");
                            Serial.println(receive_data);
                            lcd.setCursor(0,1);
                            lcd.print(receive_data);
                }
  
           }




}
}
