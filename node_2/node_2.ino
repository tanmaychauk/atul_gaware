
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include<LiquidCrystal.h>

LiquidCrystal lcd(A5, A4, A3, A2, A1, A0);
int mode1=3;
int mode2=4;
int mode3=5;

unsigned char mode;

RF24 radio(7,8);                // nRF24L01(+) radio attached using Getting Started board 

RF24Network network(radio);      // Network uses that radio

const uint16_t this_node = 02;        // NODE 2
const uint16_t other_node = 00;       // NODE 1
const uint16_t other_node2=01;        // Base station
char received[50];

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
 
  lcd.clear();

   Serial.println("NODE 2");
          
   lcd.setCursor(0,0);
   lcd.print("NODE 2");
  
           
   while(1)
   {
      network.update();                  // Check the network regularly

      while ( network.available() )
       {     // Is there anything ready for us?
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("NODE 2");
                Serial.println("NODE 2 ");    
                RF24NetworkHeader header;        // If so, grab it and print it out
                network.read(header,&received,sizeof(received));
                Serial.print("Received data : ");
                Serial.println(received);
                Serial.print('\n');
                
                lcd.setCursor(0,1);
                lcd.print(received);
                
       }
   }
   
}
  
