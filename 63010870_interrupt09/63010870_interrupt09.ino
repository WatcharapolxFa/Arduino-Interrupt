#define led8  8
#define led9  9
#define led10  10
#define led11  11
#define led12  12
#define BUTTON 2

void setup()
{
 pinMode(led8, OUTPUT);
 pinMode(led9, OUTPUT);
 pinMode(led10, OUTPUT);
 pinMode(led11, OUTPUT);
 pinMode(led12, OUTPUT); 
 pinMode(BUTTON, INPUT_PULLUP);

 attachInterrupt(digitalPinToInterrupt(BUTTON) ,switch1, CHANGE);  
 Serial.begin(115200);
}
void switch1()
    {
       if(digitalRead(BUTTON) == LOW)
       {
          digitalWrite(13,HIGH);
         
       }
         
       else
       {
        
       }
         
    }

void loop()
{
for (int i=50; i>0; i--)
{
 for(;51-i;)
 {
   
         digitalWrite(led8, HIGH);
         delay(i);
         digitalWrite(led8, LOW);
         digitalWrite(led9, HIGH);
         delay(i);
         digitalWrite(led9, LOW);
         digitalWrite(led10, HIGH);
         delay(i);
         digitalWrite(led10, LOW);
         digitalWrite(led11, HIGH);
         delay(i);
         digitalWrite(led11, LOW);
         digitalWrite(led12, HIGH);
         delay(i);
         digitalWrite(led12, LOW);
         digitalWrite(13, LOW);
     
  }

}
}
