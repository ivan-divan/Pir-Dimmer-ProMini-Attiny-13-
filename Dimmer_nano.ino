
int i;
int ledValue =0;
int isRezeble = false;
int lowLedLevel = 1; //(что при прокрутке резистора СД гас не полностью.  Самое низкое свечение СД  шкала 0-1024)
int sensorValue = 0;

void setup() { 
   pinMode (3, OUTPUT); // ШИМ 
   pinMode (A1, OUTPUT); // Реле для мимималки 
   pinMode (A2, INPUT); // ПИР датчик
   pinMode (A3, INPUT); // Резистор

   ledValue = 0;
   i = 0;
   
//     Serial.begin(9600);
} 

void loop() { 


  Serial.println(analogRead(A2));
  Serial.println(sensorValue);
  Serial.println(ledValue); 
  delay(100);
  
  if (analogRead(A2) >= 1){ // перевіряємо чи сигнал від пір датчику, тоді вмикаємо сістєму
  
  sensorValue = analogRead (A3);  // считывание значения напряжения на входе A3 
  ledValue = map(sensorValue, 0, 1023, 1, 255);


  if (ledValue == 1) {
    digitalWrite(A1, HIGH);
  }else{
    digitalWrite(A1, LOW);
  }
  
 
  if (sensorValue < lowLedLevel){ // что СД гас не полностью
  sensorValue=lowLedLevel;
  } 
  analogWrite(3, ledValue);
  

  if(!isRezeble) {
 for(i=0;i<=ledValue;i++)
{
  analogWrite(3, i);
  if (ledValue > 100){ // чем меньше значение с резистора, тем медленне загораеться лед
  delay(20); // при низкой освещенности, загораеться медленее
  }else{
  delay(100); // при высокой освещенности, загораеться быстрее
  }

isRezeble = true;
}
}
}
else{
  analogWrite(3, LOW);
  analogWrite(A1, LOW);
  isRezeble = false;
  sensorValue = 0;
  lowLedLevel = 0;
  ledValue = 0;
}
}
