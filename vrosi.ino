#include <stdio.h>
#define echoPinsag 10 // Echo Pin
#define trigPinsag 8
#define echoPin 12 // Echo Pin
#define trigPin 11
extern HardwareSerial Serial;
int BIN_1 = 3;
int BIN_2 = 5;
int AIN_1 = 6;
int AIN_2 = 9;// otor bacaklarının olduğu pinler 3,5,6,9 pwm kontrolü yapılabiliyor.
int MAX_PWM_VOLTAGE = 140;// motorun,teker hızını ayarlamak
int INA=7;
int INB=4;
int pushButton = 2; // flame sensörden dijital çıkış arduino’ya 
void setup() {
  Serial.begin(9600);
   pinMode(trigPinsag, OUTPUT);
 pinMode(echoPinsag, INPUT);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
    pinMode(BIN_1, OUTPUT);
    pinMode(BIN_2, OUTPUT);
    pinMode(AIN_1, OUTPUT);
    pinMode(AIN_2, OUTPUT);
     pinMode(pushButton, INPUT);
pinMode (INA, OUTPUT);      
pinMode(INB,OUPTUT);                              

}
 

 
void loop() {
  

int atesdeger=digitalRead(pushButton);                              //flameSensor’den gelen değerianalogRead komutu ile okuyup atesdeger’in içene aktar.


Serial.println (atesdeger); 
delay(1000);

digitalWrite(trigPinsag, LOW);
delayMicroseconds(2);
digitalWrite(trigPinsag, HIGH);
delayMicroseconds(10);
digitalWrite(trigPinsag, LOW);

int durationsag = pulseIn(echoPinsag, HIGH);

int distancesag = (durationsag/2) / 29.1;

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
int duration = pulseIn(echoPin, HIGH);
int distance = (duration/2) / 29.1;

if(atesdeger==0){// fan modülünü en baştan kapatmış oluyoruz
digitalWrite(INA,HIGH);
digitalWrite(INB,HIGH);

 if(distance > 10){// ön sensörün belli bir mesafeden (10cm) fazla görmesi durumunda yoluna sadece sağ sensörün durumlarına göre hareket etmesi durumu söz konusu
    if(distancesag<3){// sola dönmesi için, labirentte ortalama bir yolda gidebilmesi için
     digitalWrite(BIN_1, LOW);
     digitalWrite(AIN_1, LOW);
     analogWrite(BIN_2, MAX_PWM_VOLTAGE);
     analogWrite(AIN_2, MAX_PWM_VOLTAGE);
     delay(50);
     digitalWrite(BIN_2, LOW);
     digitalWrite(AIN_1, LOW);
     digitalWrite(BIN_1, LOW);
     digitalWrite(AIN_2, LOW);
     
    }else if(distancesag> 20 ){// sağ tarafın boştur sağ tarafa doğru dönmeyi işaret eder. Lakin direk doksan derecelik bir dönüşten ziyade boşluğu görünce biraz daha düz ilerlemesi ve sonra 45 derecelik bir açıyla dönmesi (dereceyi de süreye göre ve deneme yanılma ile öğreniyoruz.) ve sonra tekrar düz ilerleyip sağ labirent yoluna girmesi ve o sağ labirent yolunu ortalayabilmesi içinde tekrardan bir 45 derecelik bir açı yapması komutu verilmiştir.
        digitalWrite(BIN_2, LOW);
    digitalWrite(AIN_2, LOW);
    analogWrite(BIN_1, MAX_PWM_VOLTAGE);
    analogWrite(AIN_1, MAX_PWM_VOLTAGE);
    delay(300);
               digitalWrite(BIN_2, LOW);
    digitalWrite(AIN_1, LOW);
    digitalWrite(BIN_1, LOW);
    digitalWrite(AIN_2, LOW);
    delay(100);
   
           digitalWrite(BIN_2, LOW);
    digitalWrite(AIN_1, LOW);
    analogWrite(BIN_1, MAX_PWM_VOLTAGE);
    analogWrite(AIN_2, MAX_PWM_VOLTAGE);
    delay(500);
               digitalWrite(BIN_2, LOW);
    digitalWrite(AIN_1, LOW);
    digitalWrite(BIN_1, LOW);
    digitalWrite(AIN_2, LOW);
     
    
    
    }else{// sağ sensör algıladığı mesafe ne 3 cm’den küçük ne de 20 cm’den büyük değilse  ve de en başta tanımladığımız gibi de önündeki en yakın engelle mesafesi 10 cm’den büyükse dümdüz devam etmesi komutunu verdik.
       digitalWrite(BIN_2, LOW);
    digitalWrite(AIN_1, LOW);
    analogWrite(BIN_1, MAX_PWM_VOLTAGE);
    analogWrite(AIN_2, MAX_PWM_VOLTAGE);
   delay(350);
      digitalWrite(BIN_2, LOW);
    digitalWrite(AIN_1, LOW);
    digitalWrite(BIN_1, LOW);
    digitalWrite(AIN_2, LOW);
     
    }
  } else  {// Bu “değilse” şartı da ön sensör 10 cm’den küçük algılaması durumunda bir süreliğine 45 derece dönüş olacak şekilde sola bir dönüş ve tekrar düz bir gidiş ve tekrar 45 derece bir dönüş ile tekrardan sağ sensörün algılayabileceği bir engel koymuş ve robotun sağ taraftan gitmesini sağlamış olduk.
   digitalWrite(BIN_1, LOW);
    digitalWrite(AIN_1, LOW);
    analogWrite(BIN_2, MAX_PWM_VOLTAGE);
    analogWrite(AIN_2, MAX_PWM_VOLTAGE);
    delay(300);
            digitalWrite(BIN_2, LOW);
    digitalWrite(AIN_1, LOW);
    analogWrite(BIN_1, MAX_PWM_VOLTAGE);
    analogWrite(AIN_2, MAX_PWM_VOLTAGE);
    delay(1100);
    digitalWrite(BIN_1, LOW);
    digitalWrite(AIN_1, LOW);
    analogWrite(BIN_2, MAX_PWM_VOLTAGE);
    analogWrite(AIN_2, MAX_PWM_VOLTAGE);
    delay(300);
    
    
          digitalWrite(BIN_2, LOW);
    digitalWrite(AIN_1, LOW);
    digitalWrite(BIN_1, LOW);
    digitalWrite(AIN_2, LOW);
  }
}
  else
  {
          digitalWrite(BIN_2, LOW);
    digitalWrite(AIN_1, LOW);
    digitalWrite(BIN_1, LOW);
    digitalWrite(AIN_2, LOW);
    digitalWrite(INA,HIGH);
digitalWrite(INB,LOW);// Veya INB bacağını çalıştıradabiliriz.  Bu durumda alevi söndürmek içinde her iki bacak da kullanılabilir.
  }


}
