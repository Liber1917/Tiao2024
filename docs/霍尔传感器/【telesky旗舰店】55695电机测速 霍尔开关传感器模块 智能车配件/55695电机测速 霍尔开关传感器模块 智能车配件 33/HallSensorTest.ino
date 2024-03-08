霍尔传感器模块的 GND、VCC、DO分别连接 Arduino UNO的GND、VCC(+5V)、D5引脚。
//hall sensor test

#define ledPin 13       
#define hallPin 5        

void setup() { 
  pinMode(ledPin,OUTPUT); 
}

void loop() 
{ 
  if(digitalRead(hallPin) == LOW) {
    digitalWrite(ledPin,HIGH); 
  }
  else { 
    digitalWrite(ledPin,LOW); 
  }
}

程序运行结果：磁场强度变强（有磁铁靠近）时，点亮LED；变弱时，熄灭LED（提示：模块板载LED - 当输出HIGH时，熄灭；输出LOW时，点亮）