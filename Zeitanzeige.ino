
#include <LiquidCrystal.h>
#include "dht.h"
#define DHT11 47
LiquidCrystal lcd(52, 53, 32, 33, 34, 35);
dht DHT;
int J;
String Str[] = {"Temperaturen", "Zeit", "Lueftersteuerung", "LED Beleuchtung", "TEST", "Display"};
String Luefter[] = {"L1","L2","L3","L4"};
int StrArrlength = 6;
boolean inMenu = true;
int MenuePunkt = 0;
String first;
String second;
String Zeit;
String Zeit2;
int ZweierInt=0;
int Luefteranzahl=4;
void setup() {
  attachInterrupt(2, erhoehen,RISING);
  attachInterrupt(3, enter,RISING);
  attachInterrupt(4,zuruecklen,RISING);
  pinMode(24, INPUT);
  pinMode(25, INPUT);
  pinMode(2, OUTPUT);
  pinMode(7, OUTPUT);
  analogWrite(2, 15);
  analogWrite(7, 200);
  lcd.setCursor(0, 1);
  lcd.begin(16, 2);
  lcd.print("Initialisierung");
  delay(1000);
  lcd.clear();
}

void loop() {
  if (inMenu) {
    anzeigen(Str[MenuePunkt], Str[MenuePunkt + 1]);
  }
  else
  {

    if (MenuePunkt == 0)
    {
      String Temp = String(DHT.temperature);
      anzeigen("TempCPU: ", Temp);
      delay(1000);
    }
    if (MenuePunkt == 1)
    {
      long days = 0;
      long hours = 0;
      long mins = 0;
      long secs = 0;
      secs = millis() / 1000; 
      mins = secs / 60; 
      hours = mins / 60; 
      days = hours / 24; 
      secs = secs - (mins * 60); 
      mins = mins - (hours * 60); 
      hours = hours - (days * 24);
      String A = String(days);
      String B = String(hours);
      String C = String(mins);
      String D = String(secs);
      String Zeit = String(A + "d" + B + "h");
      String Zeit2 = String(C + "m" + D + "s");
      //Menü für Zeit
      anzeigen("Uptime:" + Zeit,Zeit2);
    }
    if (MenuePunkt == 2)
    {
         //Lueftersteuerung
      if(ZweierInt==Luefteranzahl-1){
          anzeigen(Luefter[ZweierInt], "");
        }
   
      else{
        anzeigen(Luefter[ZweierInt], Luefter[ZweierInt+1]);
        }
    }
    if (MenuePunkt == 3)
    {
      //LED Beleuchtung
      String Temp = String(DHT.temperature);
      anzeigen("TempCPU: ", Temp);

    }
    if (MenuePunkt == 4)
    {
      //TEST
      String Temp = String(DHT.temperature);
      anzeigen("TempCPU: ", Temp);
      delay(1000);
      zuruecklen();
    }
    if(MenuePunkt ==5){
      anzeigen("Kontrast    ****","Helligkeit  ****");
      
      
      }
  }
  delay(100);
}

void erhoehen() {
  if(inMenu){
    if (MenuePunkt + 1 < StrArrlength) {
          MenuePunkt++;
      }
  else {
            MenuePunkt = 0;
        }
  }
  if(!inMenu && MenuePunkt == 2){
    if(ZweierInt+1< Luefteranzahl){
      ZweierInt++;
      
    
    }
    else{
      ZweierInt=0;
      }

}
}

void anzeigen(String erste, String zweite) {

  if (first == erste && second == zweite) {
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(erste);
    lcd.setCursor(0, 1);
    lcd.print(zweite);
  }
  first = erste;
  second  = zweite;
}


void enter() {
  inMenu = false;
}

void zuruecklen() {
  inMenu = true;
}
void reset(){
  asm volatile ("  jmp 0");  
  lcd.clear();
  
  }
