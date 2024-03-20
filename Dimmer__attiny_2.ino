// диммер с плавным включением при запуске 
// и подстроечным резисторм для установки нижнего порога

int i; 
int ledValue;
int isRezeble = false;
int lowLedLevel = 4;
int downLevel = 1; // для хранения значения нижнего порога свечения СД

#define MYPIN A3 // Пин для регулировки PB3
analog_pin_t myPin = A3; // Пин для регулировки PB3
#define MYPINDOWN A2 // Пин для регулировки PB4 нижнего порога
analog_pin_t myPinDown = A2; // Пин для регулировки PB4 нижнего порога


void setup() { 
   pinMode (PB0, OUTPUT); // инициализация вывода PB0 как "Выход" 
   pinMode (myPin, INPUT); // инициализация вывода PB3 как "Вход"
   pinMode (myPinDown, INPUT); // инициализация вывода PB4 как "Вход" 
   
   ledValue = 0;
   i = 0;
} 

void loop() { 
  
  int sensorValueDown = analogRead(myPinDown);  // для 
  int sensorValue = analogRead(myPin);  // считывание значения напряжения на входе A0 
  downLevel = map(sensorValueDown, 0, 1023, 1, 80);
  ledValue = map(sensorValue, 0, 1023, downLevel
  , 255);

//  Serial.println(sensorValue);
//  Serial.println(ledValue);  
//  delay(100);
  
  if (sensorValue < lowLedLevel){ // что СД гас не полностью
  sensorValue=lowLedLevel;
  }

  analogWrite(PB0, ledValue);
  
  if(!isRezeble) {
 for(i=0;i<=ledValue;i++)
{
  analogWrite(PB0, i);
  if (ledValue > 100){ // чем меньше значение с резистора, тем медленне загораеться лед
  delay(5); // при низкой освещенности, загораеться медленее
  }else{
  delay(100); // при высокой освещенности, загораеться быстрее
  }

isRezeble = true;
}
}
}
