#define led8  8
#define led9  9
int i;


int sec=0;
int minutes=0;
int hours=0;
int last_sec=0;
int last_minutes=0;


void setup()
{
 pinMode(led8, OUTPUT);
 pinMode(led9, OUTPUT);

 
  noInterrupts(); 
 TCCR1A = 0; 
 TCCR1B = 0;
 TCNT1 = 0; 
 OCR1A = 15624; 
 TCCR1B |= (1 << WGM12); 
 TCCR1B |= (1 << CS12) | (1 << CS10); // Set CS10 and CS12 bits for 1024 prescaler
 TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt , The value in OCR1A is used for compare
 interrupts(); // enable all interrupts

 
 Serial.begin(9600);
}
void loop()
{
         
         if(sec>last_sec)
         {
            digitalWrite(led8, HIGH);
            delay(500);
            last_sec=sec;
         }
         if(minutes>last_minutes)
         {
          digitalWrite(led9, HIGH);
          delay(1000);
          last_minutes=minutes;
         }
         digitalWrite(led8, LOW);
         digitalWrite(led9, LOW);
         
         
}
ISR(TIMER1_COMPA_vect)
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
 Serial.print("Hours : ");
 Serial.print(hours);

 Serial.print("  >>>  minutes : ");
 Serial.print(minutes);

 Serial.print("  >>>  sec : ");
 Serial.println(sec);

}
