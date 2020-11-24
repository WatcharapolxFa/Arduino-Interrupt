#include <Wire.h>
#include <hd44780.h> // main hd44780 header
#include <hd44780_I2Cexp.h> // i2c expander i/o class header
#define BUTTON1 2
#define BUTTON2 3

int sec=0;
int minutes=0;
int hours=0;
int last_sec=0;
int last_minutes=0;

int start=0;

hd44780_I2Cexp lcd; 
const int LCD_COLS = 16;
const int LCD_ROWS = 2;
void setup()
{
 pinMode(BUTTON1, INPUT_PULLUP);
 pinMode(BUTTON2, INPUT_PULLUP);

 noInterrupts(); 
 TCCR1A = 0; 
 TCCR1B = 0;
 TCNT1 = 0; 
 OCR1A = 15624; 
TCCR1B |= (1 << WGM12);
 TCCR1B |= (1 << CS12) | (1 << CS10); 
 TIMSK1 |= (1 << OCIE1A); 
 interrupts();

 
 Serial.begin(9600);
  
int status;
status = lcd.begin(LCD_COLS, LCD_ROWS);
if(status) 
{
 
 hd44780::fatalError(status); 


    
}
    lcd.setCursor(0, 0);
    lcd.print("hours"); 
    lcd.setCursor(0, 1);
    lcd.print(hours); 
    
    lcd.setCursor(7, 0);
    lcd.print("min");
    lcd.setCursor(7, 1);
    lcd.print(minutes); 
  
    lcd.setCursor(12, 0);
    lcd.print("sec");
    lcd.setCursor(12, 1);
    lcd.print(sec);
    
 attachInterrupt(digitalPinToInterrupt(BUTTON1) ,switch_clear, RISING);
 attachInterrupt(digitalPinToInterrupt(BUTTON2) ,switch_start, RISING);
}
void loop()
{
  
  
  
  
    lcd.setCursor(0, 0);
    lcd.print("hours"); 
    lcd.setCursor(0, 1);
    lcd.print(hours); 
    
    lcd.setCursor(7, 0);
    lcd.print("min");
    lcd.setCursor(7, 1);
    lcd.print(minutes); 
  
    lcd.setCursor(12, 0);
    lcd.print("sec");
    lcd.setCursor(12, 1);
    lcd.print(sec);
  
    
  
    delay(500);
    lcd.clear();
  
  
}
ISR(TIMER1_COMPA_vect)
{
   if(start==1)
   {
    sec++;
   if (sec >= 60)
   {
   minutes++;
   sec = 0;
   last_sec = 0;
   }
   if (minutes >= 60)
   {
   hours++;
   minutes = 0;
   last_minutes = 0;
   }
 }
}

void switch_start()
    {
       if(start==1)
       {
         start=0;
         Serial.print("0");
         
       }
       else
       {
          start=1;
          Serial.print("1");
          
       }
       
           
    }
    
void switch_clear()
    {
        
        sec=0;
        minutes=0;
        hours=0;
        last_sec=0;
        last_minutes=0;
        start=0;
        
           
    }
