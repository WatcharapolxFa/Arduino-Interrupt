#define led1 8
#define led2 9

#define switch1 2
#define switch2 4


#include <Wire.h>
#include <hd44780.h> // main hd44780 header
#include <hd44780_I2Cexp.h> // i2c expander i/o class header
hd44780_I2Cexp lcd; // declare lcd object: auto locate & config exapander chip

int sec=0,minutes=0,hours=0;
int checkSec = 0, checkMin = 0, checkHr = 0, checkSwitch = 0;

byte address,data,device,x;

const int LCD_COLS = 16;
const int LCD_ROWS = 2;

unsigned long period = 20; //ระยะเวลาที่ต้องการรอ
unsigned long last_time = 0; //ประกาศตัวแปรเป็น global เพื่อเก็บค่าไว้ไม่ให้ reset จากการวนloop

void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  pinMode(switch1, INPUT_PULLUP);
  pinMode(switch2, INPUT_PULLUP);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  

  int status;
  status = lcd.begin(LCD_COLS, LCD_ROWS);
  if(status) // non zero status means it was unsuccesful
  {
    // begin() failed so blink error code using the onboard LED if possible
    hd44780::fatalError(status); // does not return
  }


  Wire.begin(); // Start I2C bus
  Serial.begin(115200); // Setup serial for debug

  for(address = 1; address < 127; address++ ) // sets the value (range from 1 to 127)
  {
    Wire.beginTransmission(address); // transmit to address
    if (Wire.endTransmission() == 0) // I2C devices found
    {
        device = address;
        Serial.print("\n I2C Device Address: "); // Print Device Address
        Serial.println(address, HEX); // print as an ASCII-encoded hexa);
    }
  }

  
  
  
  Serial.begin(115200);
  noInterrupts(); // disable all interrupts
  // Clear Timer/Counter Control Register for Interrupt 1, bytes A and B (TCCR1?)
  TCCR1A = 0; // Clear TCCR1A/B registers
  TCCR1B = 0;
  TCNT1 = 0; // Initialize counter value to 0 (16-bit counter register)
  // set compare match register for TIMER1: CLOCKFREQUENCY / frequency / prescaler - 1
  OCR1A = 62499; // 16MHz/(1Hz*256) - 1 (must be <65536)
  // Timer/Counter Control Register for Interrupt 1 on register B
  TCCR1B |= (1 << WGM12); // Mode 4, turn on CTC mode
  // Clock Select Bit, Set CS12, CS11 and CS10 bits
  TCCR1B |= (1 << CS12); // Set CS12 bit for 256 prescaler
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt , The value in OCR1A is used for compare
  interrupts(); // enable all interrupts

}
void loop()
{
  Wire.requestFrom(device, 1); // recive 1 bytes from slave device
  x = Wire.read(); // Read pin state
  x = x & 0x0f;


  // Press Button
  if(!digitalRead(switch1))
  {
    checkSwitch++;
    delay(500);
    if(checkSwitch > 1)
    {
      checkSwitch = 0;
    }
  }
  if(!digitalRead(switch2))
  {
    sec = 0;
    minutes = 0;
    hours = 0;
    lcd.setCursor(4, 0);
    lcd.print("Hr Mn Sc");
    lcd.setCursor(4, 1);
    lcd.print("00:00:00");
  }

  if(checkSwitch == 1)
  {
    //if( millis() - last_time > period) 
    //{
      //last_time = millis();
      data = 0x80 | x;
      for (int i = 1 ; i <= 4; i++) // sets the value (range from 1 to 4)
      {
          Wire.beginTransmission(device); // transmit to device
          Wire.write(data); // sends one byte
          Wire.endTransmission(); // stop transmitting
          delay(5); // wait for stepper speed
  
          Serial.print("\n Out = "); // Print pin state
          Serial.println(data, BIN); // print as an ASCII-encoded binary);
          data = data >> 1;
          data = data | x;  
      }
    //}
  }


// Display Time
    lcd.setCursor(4, 0);
    lcd.print("Hr Mn Sc");
    lcd.setCursor(6, 1);
    lcd.print(":");
    lcd.setCursor(9, 1);
    lcd.print(":");
    
      if(hours==0)
      {
        lcd.setCursor(4, 1);
        lcd.print("00");
      }
      else if(hours>=1 && hours<=9)
      {
        lcd.setCursor(4, 1);
        lcd.print("0");
        lcd.setCursor(5, 1);
        lcd.print(hours);
      }
      else if(hours>=10 && hours<=99)
      {
        lcd.setCursor(4, 1);
        lcd.print(hours);
      }
      else if(hours>=100 && hours<=999)
      {
        lcd.setCursor(3, 1);
        lcd.print(hours);
      }
    
    
      if(minutes == 0)
      {
        lcd.setCursor(7, 1);
        lcd.print("00");
      }
      else if(minutes>=1 && minutes<=9)
      {
        lcd.setCursor(7, 1);
        lcd.print("0");
        lcd.setCursor(8, 1);
        lcd.print(minutes);
        checkMin = 0;
      }
      else if(minutes>=10 && minutes<=59)
      {
        lcd.setCursor(7, 1);
        lcd.print(minutes);
        checkMin = 0;
      }
    
    
      if(sec>=0 && sec<=9)
      {
        lcd.setCursor(10, 1);
        lcd.print("00");
        lcd.setCursor(11, 1);
        lcd.print(sec);
        checkSec = 0;
      }
      else if(sec>=10 && sec<=59)
      {
        lcd.setCursor(10, 1);
        lcd.print(sec);
        checkSec = 0;
      }
      else if(sec == 60)
      {
        lcd.setCursor(10, 1);
        lcd.print("00");
      }     
    
 
} 

ISR(TIMER1_COMPA_vect)
{
  if(checkSwitch == 1)
  {
    sec++;
    if (sec >= 60)
    {
      minutes++;
      sec = 0;
    }
    if (minutes >= 60)
    { 
      hours++;
      minutes = 0;
    }
  }

  
}
