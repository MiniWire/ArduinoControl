#include <LiquidCrystal.h>
#include "dht11.h"
#define DHT11PIN 47
#define Buttonrein 25
#define Buttonrunter 24
#define Buttonraus 26
LiquidCrystal lcd(52, 53, 32, 33, 34, 35);
dht11 DHT11;
String Str[] = {"Temperaturen", "Zeit", "Lueftersteuerung", "LED Beleuchtung", "TEST", "Display"};
int StrArrlength = 6;
String Luefter[] = {"H100i -1","H100i -2","Gehause -1","Gehause -2"};
int Luefteranzahl=4;
boolean inMenu = true;
boolean inUntermenu =false;
int MenuePunkt = 0;
String first;
String second;
String Zeit;
String Zeit2;
String A;
String B;
String C;
String D;
int ZweierInt=0;
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
int chk;
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
  delay(500);
  lcd.clear();
  lcd.cursor();
}

void loop() {
  lcd.setCursor(0,0);
  
  if(digitalRead(Buttonrunter)==HIGH){
    if(lastpress1 ==0){
      lastpress1 = millis();
      erhoehen();
      }
    if((millis()-lastpress1)>500){
      lastpress1 = millis();
      erhoehen();
      }
  }
  
   if(digitalRead(Buttonrein)==HIGH){
    if(lastpress2 ==0){
      
      lastpress2 = millis();
      if(!inMenu){
        inUntermenu=true;
        }
        else{
      inMenu=false;
      }
      }
    if((millis()-lastpress2)>500){
      lastpress2 = millis();
      if(!inMenu){
        inUntermenu=true;
        }
        else{
      inMenu=false;
      }}
  }
   if(digitalRead(Buttonraus)==HIGH){
    if(lastpress3 ==0){
      lastpress3 = millis();
      if(inUntermenu){
        inUntermenu=false;
        }
        else{
          inMenu=true;
          }
      }
    if((millis()-lastpress3)>500){
      lastpress3 = millis();
      if(inUntermenu){
        inUntermenu=false;
        }
        else{
          inMenu=true;
          }
      }
  }
  
  if (inMenu) {
        if(MenuePunkt==StrArrlength-1){
              anzeigen(Str[MenuePunkt],"");
              }
        else
        {
          anzeigen(Str[MenuePunkt], Str[MenuePunkt + 1]);
                }
        }
  if(!inMenu)
  {
    /*if(DHT11.temperature<50){
      //Lüfter schneller
      }
      */
    if (MenuePunkt == 0)
    {
      chk=DHT11.read(DHT11PIN);
      switch(chk){
         case DHTLIB_OK: 
		 TEMPERATUR = String(DHT11.temperature);
                 FEUCHTIGKEIT= String(DHT11.humidity);
                 anzeigen("TempCPU: "+ TEMPERATUR+GradCelsius,"Feuchtigk. "+FEUCHTIGKEIT+"%");
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
      delay(300);
    }
    if (MenuePunkt == 1)
    {
      //ZEIT
      secs = millis() / 1000; 
      mins = secs / 60; 
      hours = mins / 60; 
      days = hours / 24; 
      secs = secs - (mins * 60); 
      mins = mins - (hours * 60); 
      hours = hours - (days * 24);
       A = String(days);
       B = String(hours);
       C = String(mins);
       D = String(secs);
       Zeit = String(A + "d" + B + "h");
       Zeit2 = String(C + "m" + D + "s");
      //Menü für Zeit
      anzeigen("Uptime:" + Zeit,Zeit2);
    }
    if (MenuePunkt == 2)
    {
      if(inUntermenu==true){
             anzeigen(Luefter[ZweierInt],"RPM");
             }
             else{
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
    }
    
    
    if (MenuePunkt == 3)
    {
      //LED Beleuchtung
      anzeigen("LED Beleuchtung","");

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
    if (MenuePunkt+1<StrArrlength) {
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
    else
    {
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
    lcd.setCursor(0,0);
  }
  first = erste;
  second  = zweite;
}

void reset(){
  asm volatile ("  jmp 0");  
  lcd.clear();
  
  }
