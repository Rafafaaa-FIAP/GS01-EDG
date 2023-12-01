#include <LiquidCrystal.h>

#define pinButton 4

#define pinLEDGreen 5
#define pinLEDYellow 6
#define pinLEDRed 7

LiquidCrystal LCD (8,9,10,11,12,13);

String names[] = {"Ampla Visao",
                  "Lab Exames",
                  "DermaTestes",
                  "Saude Mais",
                  "Pes Sem Dor"};
String contacts[] = {"(11) 11111-1111",
                     "(11) 22222-2222",
                     "(11) 33333-3333",
                     "(11) 44444-4444",
                     "(11) 55555-5555"};
int daysQtd[] = {0,
                 1,
                 -5,
                 0,
                 2};

int lengthOfArrays = sizeof(names) / sizeof(names[0]);

int currentIndex = 0;
bool buttonON = false;

void setup()
{
  Serial.begin(9600);
  
  pinMode(pinButton, INPUT);
  
  pinMode(pinLEDGreen, OUTPUT);
  pinMode(pinLEDYellow, OUTPUT);
  pinMode(pinLEDRed, OUTPUT);
  
  LCD.begin(16,2);
  
  LCD.setCursor(0,0);
  LCD.print("APERTE O BOTAO");
  LCD.setCursor(0,1);
  LCD.print("PARA INICIAR");
}

void loop()
{
  if (digitalRead(pinButton) == HIGH) {
    if (!buttonON) {
      buttonON = true;

      if (currentIndex == lengthOfArrays) {
        currentIndex = 0;
      }
      
      String name = names[currentIndex];
      String contact = contacts[currentIndex];
      int days = daysQtd[currentIndex];
      
      LCD.clear();
      
      LCD.setCursor(0,0);
      LCD.print(name);
      LCD.setCursor(0,1);
      LCD.print(contact);

      digitalWrite(pinLEDGreen, LOW);
      digitalWrite(pinLEDYellow, LOW);
      digitalWrite(pinLEDRed, LOW);

      if (days == 0) {
        digitalWrite(pinLEDGreen, HIGH);
      }
      else if (days > 0) {
        digitalWrite(pinLEDYellow, HIGH);
        
        LCD.setCursor(13,0);
        LCD.print(" " + String(days) + " ");
      }
      else {
        digitalWrite(pinLEDRed, HIGH);
      }

      currentIndex += 1;
    }
  }
  else {
    buttonON = false;
  }
}