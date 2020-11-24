int sec = 0;
int hours =0;
int minutes =0 ;
void setup() {
  noInterrupts();
  TCCR1A = 0 ;
  TCCR1B = 0;
  TCNT1 = 0 ;
  OCR1A = 15624;
  TCCR1B|=(1<< WGM12);
  TCCR1B |=(1<<CS12) |(1<<CS10);
  TIMSK1 |=(1<<OCIE1A);
  interrupts();
  Serial.begin(9600);
}

void loop() {
         Serial.print("Hours : ");
         Serial.print(hours);

         Serial.print("   <<<  minutes : ");
         Serial.print(minutes);

         Serial.print("  <<<  sec : ");
         Serial.println(sec);
}
ISR(TIMER1_COMPA_vect)
{
  sec++;
  if(sec>=60)
  {
    minutes++;
    sec = 0;
  }
  if(minutes>=60)
  {
    hours++;
    minutes = 0 ;
  }
}
