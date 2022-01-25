#include <virtuabotixRTC.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27, 16, 4);
virtuabotixRTC myRTC(9, 10, 11);
Servo servo;

#define up 2
#define down 3
#define okey 4
#define back 5
#define mid 6
#define sett 7
#define reset 8

//degiskenler
int page = 0;
int tur = 0;
int secimi = 1;
int gerii=1;
int artiri=1;
int azalti =1;
int st = 1;
int rst =1;
int man = 0;
int say = 0;
int saat1 = 0;
int saat2 = 0;
int saat3 = 0;
int saat4 = 0;
int dakika = 0;
int dakika2 = 1;
int saniye = 0;
int saniye2 = 10;
int buz = 500 ;
int i =0;
int aci=101;
bool islem = false;

//EEPROM Adresleri
int adres1 = 50;
int adres2 = 51;
int adres3 = 52;
int adres4 = 53;
int adres5 = 54;


void setup()
{
  servo.attach(12);
  servo.write(aci);
  myRTC.setDS1302Time(55, 59, 13, 6, 8, 1, 2022);
  Serial.begin(9600);
	// initialize the LCD
	lcd.begin();
  
	// Turn on the blacklight and print a message.
	lcd.backlight();
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
  pinMode(13,OUTPUT);
  saat1 = EEPROM.read(adres1);
  saat2 = EEPROM.read(adres2);
  saat3 = EEPROM.read(adres3);
  saat4 = EEPROM.read(adres4);
  tur   = EEPROM.read(adres5);
  
  
}

void loop()
{
  manual();
  secim();
  geri();
  artir();
  azalt();
  
  if (page==0)
  {
    //giris ekranı
    lcd.clear();
    myRTC.updateTime();
    lcd.setCursor(1,0);
    lcd.print("TARIH :");
    lcd.print(myRTC.dayofmonth);                                                                    
    lcd.print("/");                                                                                    
    lcd.print(myRTC.month);                                                                            
    lcd.print("/");                                                                                     
    lcd.print(myRTC.year);
    lcd.setCursor(1,1);
    lcd.print("SAAT  :");
    lcd.print(myRTC.hours);                                                                       
    lcd.print(":");                                                                              
    lcd.print(myRTC.minutes);                                                                      
    lcd.print(":");                                                                            
    lcd.print(myRTC.seconds); 
    
    lcd.setCursor(5,2);
    lcd.print("APPTEC MUH.");
    lcd.setCursor(2,3);
    lcd.print("BESLEME ZAMANLARI");
    lcd.setCursor(0,3);
    lcd.print(">");
    delay(500);
    }
  if(page==1)
  {
    //saat ayar ekranı
    
    
    lcd.setCursor(2,0);
    lcd.print("BESLEME1 :");
    lcd.setCursor(13,0);
    lcd.print(saat1);
    lcd.print(":");
    lcd.print("00");
    if(i==0)
    {
      st = digitalRead(sett);
      if(st==0){
        
      saat1+=1;
      if(saat1>23)
      {
        lcd.clear();
        saat1=0;
        }
      }
      rst = digitalRead(reset);
      if(rst == 0)
      {
        saat1-=1;
        if(saat1<0){
        lcd.clear();
        saat1=23;
        }
      }
      EEPROM.write(adres1,saat1);
      }
      
    
    lcd.setCursor(2,1);
    lcd.print("BESLEME2 :");
    lcd.setCursor(13,1);
    lcd.print(saat2);
    lcd.print(":");
    lcd.print("00");
       
      if(i==1)
    {
      st = digitalRead(sett);
      if(st==0){
        
      saat2+=1;
      if(saat2>23)
      {
        lcd.clear();
        saat2=0;
        }
      }
      rst = digitalRead(reset);
      if(rst == 0)
      {
        saat2-=1;
        if(saat2<0){
        lcd.clear();
        saat2=23;
        }
      }
      EEPROM.write(adres2,saat2);
      }

  
    lcd.setCursor(2,2);
    lcd.print("BESLEME3 :");
    lcd.setCursor(13,2);
    lcd.print(saat3);
    lcd.print(":");
    lcd.print("00");


        if(i==2)
    {
      st = digitalRead(sett);
      if(st==0){
        
      saat3+=1;
      if(saat3>23)
      {
        lcd.clear();
        saat3=0;
        }
      }
      rst = digitalRead(reset);
      if(rst == 0)
      {
        saat3-=1;
        if(saat3<0){
        lcd.clear();
        saat3=23;
        }
      }
      EEPROM.write(adres3,saat3);
      }
    
    lcd.setCursor(2,3);
    lcd.print("BESLEME4 :");
    lcd.setCursor(13,3);
    lcd.print(saat4);
    lcd.print(":");
    lcd.print("00");

        if(i==3)
    {
      st = digitalRead(sett);
      if(st==0){
        
      saat4+=1;
      if(saat4>23)
      {
        lcd.clear();
        saat4=0;
        }
      }
      rst = digitalRead(reset);
      if(rst == 0)
      {
        saat4-=1;
        if(saat4<0){
        lcd.clear();
        saat4=23;
        }
      }
      EEPROM.write(adres4,saat4);
      }

    
    lcd.setCursor(0,i);
    lcd.print(">");


   }


   if(page == 2)
   {
    lcd.setCursor(1,0);
    lcd.print("BESLEME MIKT. : ");
    lcd.setCursor(7,1);
    lcd.print(tur);
    st = digitalRead(sett);
      if(st==0)
      {
        tur+=tur;
        if(tur>3)
        {
          tur=0;
          }
        
      }
    rst = digitalRead(reset);

    if(rst==0)
    {
      tur-=tur;
      if(tur<0)
      {
        tur=0;
        }
      }
      EEPROM.write(adres5,tur);
    }
  
   //BESLEME ZAMANI 1
   if(myRTC.hours == saat1 && myRTC.minutes == dakika && myRTC.seconds == 0)
   {
    if(tur==1)
    {
      birtur();
      }
    else if(tur==2)
    {
      ikitur();
      }
    else if(tur==3)
    {
      uctur();
      } 
    else if(tur==4)
    {
      dorttur();
      } 
    else if(tur==5)
    {
      bestur();
      } 
   }

   


   //BESLEME ZAMANI 2
   if(myRTC.hours == saat2 && myRTC.minutes == dakika && myRTC.seconds == 0)
   {
    if(tur==1)
    {
      birtur();
      }
    else if(tur==2)
    {
      ikitur();
      }
    else if(tur==3)
    {
      uctur();
      } 
    else if(tur==4)
    {
      dorttur();
      } 
    else if(tur==5)
    {
      bestur();
      } 
   }



   //BESLEME ZAMANI 3
   if(myRTC.hours == saat3 && myRTC.minutes == dakika && myRTC.seconds == 0)
   {
    if(tur==1)
    {
      birtur();
      }
    else if(tur==2)
    {
      ikitur();
      }
    else if(tur==3)
    {
      uctur();
      } 
    else if(tur==4)
    {
      dorttur();
      } 
    else if(tur==5)
    {
      bestur();
      } 
   }


   //BESLEME ZAMANI 4
   if(myRTC.hours == saat4 && myRTC.minutes == dakika && myRTC.seconds == 0)
   {
    if(tur==1)
    {
      birtur();
      }
    else if(tur==2)
    {
      ikitur();
      }
    else if(tur==3)
    {
      uctur();
      } 
    else if(tur==4)
    {
      dorttur();
      } 
    else if(tur==5)
    {
      bestur();
      } 
   }

  
  if(digitalRead(mid)==0)
  {
    manual();
    
  }

}

void secim()
{
  secimi = digitalRead(okey);
  if (secimi==0)
  {
    Serial.println("secimmmm");
    lcd.clear();
    page+=1;
    if (page>2)
    {
      page=2;
      }
    }
  
  }

void geri()
{
  gerii = digitalRead(back);
  if (gerii==0)
  {
    Serial.println("geriiiii");
    lcd.clear();
     page-=1;
    if (page<0)
    {
      page=0;
      }
    }
  
  }

void artir()
{
  
  artiri = digitalRead(up);
  if (artiri==0)
  {
    lcd.clear();
    Serial.println("artirrr");
    i+=1;
    if (i>3)
    {
      i=0;
      }
    
    }

  delay(300);
  
  }

void azalt()
{
  azalti = digitalRead(down);
  if (azalti==0)
  {
    lcd.clear();
    i-=1;
    if (i<0)
    {
      i=0;
      }
    Serial.println("azalttt");
    }
  
  }


//////////////// SON EKLEMELER ///////////////
void manual()
{
man = digitalRead(mid);

  while (man == 0)
  {
    delay(100);
    say++; 
    man = digitalRead(man); 
    islem = true;               
  }
  if (islem == true)
  {
        if (say == 5 ) 
        {
          servo.write(0);
          delay(10000);
          servo.write(101);
        }
           say=0; 
           islem = false;
  }   
   
}  

void birtur()
{
  if(tur == 1)
  {
    servo.write(0);
    delay(5000);
    servo.write(101);
    }
  
  }  
 
  void ikitur()
{
  if(tur == 2)
  {
    servo.write(0);
    delay(5000);
    servo.write(101);
    delay(5000);
    servo.write(0);
    delay(5000);
    servo.write(101);
    }
  
  }


  void uctur()
{
  if(tur == 3)
  {
    servo.write(0);
    delay(5000);
    servo.write(101);
    delay(5000);
    servo.write(0);
    delay(5000);
    servo.write(101);
    delay(5000);
    servo.write(0);
    delay(5000);
    servo.write(101);
    }
  
  }

    void dorttur()
{
  if(tur == 4)
  {
    servo.write(0);
    delay(5000);
    servo.write(101);
    delay(5000);
    servo.write(0);
    delay(5000);
    servo.write(101);
    delay(5000);
    servo.write(0);
    delay(5000);
    servo.write(101);
    delay(5000);
    servo.write(0);
    delay(5000);
    servo.write(101);
    }
  
  }



  void bestur()
{
  if(tur == 5)
  {
    servo.write(0);
    delay(5000);
    servo.write(101);
    delay(5000);
    servo.write(0);
    delay(5000);
    servo.write(101);
    delay(5000);
    servo.write(0);
    delay(5000);
    servo.write(101);
    delay(5000);
    servo.write(0);
    delay(5000);
    servo.write(101);
    delay(5000);
    servo.write(0);
    delay(5000);
    servo.write(101);
    }
  
  }
