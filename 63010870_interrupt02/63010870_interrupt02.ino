//กำหนดขา LED 
int led8 = 8;
int led9 = 9;
int led10 = 10;
int led11 = 11;
int led12 = 12;
//กำหนดไว้ใช้ในคำสั่งในการวนลูป
int i;
void setup() {
 //กำหนดขา LED เป็นขาเพื่อสั่งงานออก
pinMode(led8, OUTPUT);
pinMode(led9, OUTPUT);
pinMode(led10, OUTPUT);
pinMode(led11, OUTPUT);
pinMode(led12, OUTPUT);
}

void loop() {
 for (i=50; i>0; i--)
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
}

}
