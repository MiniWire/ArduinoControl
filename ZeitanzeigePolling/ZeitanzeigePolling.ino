
#include <LiquidCrystal.h>
#include "dht11.h"
#define DHT11PIN 47
#define Buttonrein 25
#define Buttonrunter 24
#define Buttonraus 26
LiquidCrystal lcd(52, 53, 32, 33, 34, 35);
dht11 DHT11;
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
String TEMPERATUR;
String GradCelsius ="C";
String FEUCHTIGKEIT;
long days = 0;
long hours = 0;
long mins = 0;
long secs = 0;
unsigned long lastpress1 = 0;
unsigned long lastpress2 = 0;
unsigned long lastpress3 = 0;
void setup() {
  
  pinMode(24, INPUT);
  pinMode(25, INPUT);
  pinMode(26,INPUT);
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
  
  if(digitalRead(Buttonrunter)==HIGH){
    if(lastpress1 ==0){
      erhoehen();
      lastpress1 = millis();
      }
    if((millis()-lastpress1)>500){
      erhoehen();
      lastpress1 = millis();
      }
  }
  
   if(digitalRead(Buttonrein)==HIGH){
    if(lastpress2 ==0){
      inMenu=false;
      lastpress2 = millis();
      }
    if((millis()-lastpress2)>500){
      inMenu=false;
      lastpress2 = millis();
      }
  }
   if(digitalRead(Buttonraus)==HIGH){
    if(lastpress3 ==0){
      inMenu=true;
      lastpress2 = millis();
      }
    if((millis()-lastpress3)>500){
      inMenu=true;
      lastpress2 = millis();
      }
  }
  if (inMenu) {
    if(MenuePunkt==StrArrlength){
      anzeigen(Str[MenuePunkt],"");
      }
    anzeigen(Str[MenuePunkt], Str[MenuePunkt + 1]);
  }
  else
  {
    if(DHT11.temperature<50){
      //Lüfter schneller
      }
    if (MenuePunkt == 0)
    {
      int chk=DHT11.read(DHT11PIN);
      switch(chk){
         case DHTLIB_OK: 
		 TEMPERATUR = String(DHT11.temperature);
                 FEUCHTIGKEIT= String(DHT11.humidity);
                 anzeigen("TempCPU: "+ TEMPERATUR+GradCelsius,"Feucht."+FEUCHTIGKEIT);
		break;
          case DHTLIB_ERROR_CHECKSUM: 
		anzeigen("Checksum Fehler","");
		break;
          case DHTLIB_ERROR_TIMEOUT: 
		anzeigen("Timeout Fehler","");
		break;
            default: 
		anzeigen("Unbekannter Fehler","Nicht verbunden?"); 
		break;
      }
      delay(1000);
    }
    if (MenuePunkt == 1)
    {
      
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
          if(ZweierInt==Luefteranzahl-1)
              {
                anzeigen(Luefter[ZweierInt], "");
          }
   
                  else
              {
                anzeigen(Luefter[ZweierInt], Luefter[ZweierInt+1]);
              }
    }
    
    
    if (MenuePunkt == 3)
    {
      //LED Beleuchtung
      anzeigen("´LED Beleuchtung","");

    }
    if (MenuePunkt == 4)
    {
      //TEST
      anzeigen("TestMenue","TestMenue");
    }

    if(MenuePunkt ==5){
      //Display
      
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
    delay(50);
  }
  first = erste;
  second  = zweite;
}

void reset(){
  asm volatile ("  jmp 0");  
  lcd.clear();
  
  }
