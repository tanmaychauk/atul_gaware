
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include<LiquidCrystal.h>


LiquidCrystal lcd(A5, A4, A3, A2, A1, A0);
int mode1=3;
int mode2=4;
int mode3=5;

RF24 radio(7,8);                    // nRF24L01(+) radio attached using Getting Started board 

RF24Network network(radio);          // Network uses that radio

const uint16_t this_node = 01;        // BASE STATION
const uint16_t other_node = 00;       // NODE 1
const uint16_t other_node2=02;        //NODE 2

const unsigned long interval = 2000; //ms  // How often to send 'hello world to the other unit

unsigned long last_sent;             // When did we last send?
unsigned long packets_sent;          // How many have we sent already

unsigned char mode;

char transmit_data_mode1[50]="PARKING IS FULL";
char transmit_data_mode2[50]="SILENT ZONE";
char trasnmit_data_mode3[50]="TURN LEFT";
void setup(void)
{
  Serial.begin(9600);
  lcd.begin(16,2);
   SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ this_node);

}

void loop() 
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
            while(1)
            {
              Serial.println("MODE1");
              lcd.print("MODE1");
              delay(1000);

                lcd.clear();
                lcd.setCursor(0,0);
                network.update();                          // Check the network regularly
                lcd.print("BASE STATION");
                Serial.println("BASE STATION");
                Serial.print("COMMAND SENT BY BASE STATION : ");

                RF24NetworkHeader header(/*to node*/ other_node);
  
                bool ok = network.write(header,transmit_data_mode1,sizeof(transmit_data_mode1));
                if (ok)
                {
                    lcd.setCursor(12,0);
                    lcd.print("sent");
                    lcd.setCursor(0,1);
                    lcd.print(transmit_data_mode1);
                    Serial.println(transmit_data_mode1);
                }    
                else
                {
                    lcd.setCursor(12,0);
                    lcd.print("fail");
                    Serial.println("failed.");
                }
                delay(2000);      
                Serial.print('\n'); 

            }
            break;

    case 2:
            while(1)
            {
              Serial.println("MODE2");
              lcd.print("MODE2");
              delay(1000);
                lcd.clear();
                lcd.setCursor(0,0);
                network.update();                          // Check the network regularly
                lcd.print("BASE STATION");
                Serial.println("BASE STATION");
                Serial.print("COMMAND SENT BY BASE STATION : ");

                RF24NetworkHeader header(/*to node*/ other_node);
  
                bool ok = network.write(header,transmit_data_mode2,sizeof(transmit_data_mode2));
                if (ok)
                {
                    lcd.setCursor(12,0);
                    lcd.print("sent");
                    lcd.setCursor(0,1);
                    lcd.print(transmit_data_mode2);
                    Serial.println(transmit_data_mode2);
                }    
                else
                {
                    lcd.setCursor(12,0);
                    lcd.print("failed");
                    Serial.println("failed.");
                }
                delay(2000);      
                Serial.print('\n'); 

            }
            break;

     case 3:
            while(1)
            {
              Serial.println("MODE3");
              lcd.print("MODE3");
              delay(1000);
            }
            break;

    default:
            Serial.println("default");
            lcd.print("default");
  }

  while(1);
  }


