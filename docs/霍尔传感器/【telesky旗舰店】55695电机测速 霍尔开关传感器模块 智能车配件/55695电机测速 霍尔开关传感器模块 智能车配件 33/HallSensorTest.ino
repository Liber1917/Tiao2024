����������ģ��� GND��VCC��DO�ֱ����� Arduino UNO��GND��VCC(+5V)��D5���š�
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

�������н�����ų�ǿ�ȱ�ǿ���д���������ʱ������LED������ʱ��Ϩ��LED����ʾ��ģ�����LED - �����HIGHʱ��Ϩ�����LOWʱ��������