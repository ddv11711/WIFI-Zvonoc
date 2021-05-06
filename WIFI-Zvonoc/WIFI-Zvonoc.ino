#include <ESP8266WiFi.h>//обычная библтотека для есп
#include <ESP8266WebServer.h> //библиотека для вебсервера 
#include <ESP8266SSDP.h>//библиботека для опознования устройства
#include <DNSServer.h>//библиотека для DNS-server
#include <FS.h> //библиотека для работы с файловой системы
#include <ArduinoJson.h>//библиотека для работы с json файлами
#include <time.h>
#include <DS3231.h>//библиотека для работы ds3231
#include <Wire.h>//тоже для ds3231
#include <ArduinoOTA.h> // Библиотека для OTA-прошивки
#include <ESP8266mDNS.h> //тоже для OTA
#include <WiFiUdp.h> //для отправки переменных
#define DS3231_SCL 5 // GPO для часов реального времяни
#define DS3231_SDA 4 // GPO для часов реального времяни
DNSServer dnsServer; //объявление тела dnsServer
File fsUploadFile;//подключение файловой системы
WiFiUDP Udp;//объявление тела Udp
DS3231 Clock;//объявление часов
const byte DNS_PORT = 53; //порт для DNS-server
const byte HTTP_PORT = 80; //порт для HTTP-server
IPAddress apIP (192,168,4,1); //ip для точки доступа
IPAddress ip_get(192,168,4,255);
ESP8266WebServer HTTP(HTTP_PORT);//порт для работы Web-server
String _ssid="RT-GPON-E25F";//пароль для подключения к wi-fi
String _password="pvkp25BT"; //пароль для подключения
String _ssidAP="WIFI-Zvonoc";// логин для поднимаемой точки лоступа
String _passwordAP="";//пароль для поднятой точки доступа
String SSDP_Name="WIFI-Zvonoc"; //имя устройство
String _domen="wifi-zvonoc";
String HTTP_ssid="123"; //логин для Web-server
String HTTP_password="123";//пароль для Web-server
String ip="Не знаю";
byte flag_password=0;
String jsonConfig="{}";
String text="";
String bufer="";
String exshon[101];
byte timezone=3,val=0;
byte lessons=7;
byte lessonsSaturday=7;
byte saturday=0;
byte colvo=2;
byte last_clok=61,error_day=1;
bool error_clok=false;
byte i=1,l;
String temph,tempm,ttt,error="";
byte _hour=0,_minute=0,_second=0,_day=1,_mon=1,_monlast=1,dayofwek=1;
int _year=1;
String mont="",dayofwekt="";
bool year1970=false,clockwifi=false;
bool cycle500mils = false;
bool cycle3s = false;
bool cycle5s = false;
bool cycle10s = false;
bool cycleOn = false;
bool cycleOff1 = false;
bool cycleOff = false;
bool cycleOnpauza = false;
bool cycleOff1pauza = true;
bool cycleOffpauza =true;
/*bool cycle30s = false;
bool cycle1m = false;
bool cycle3m = false;
bool cycle24h = false;*/
unsigned long timer500mils;
 unsigned long timer3s;
  unsigned long timer5s;
  unsigned long timer10s;
  unsigned long timerOn;
  unsigned long timerOff1;
  unsigned long timerOff;
/*unsigned long timer30s;
  unsigned long timer1m;
  unsigned long timer3m;
  unsigned long timer24h;*/
  bool flag1=false;
  byte flag2=0;
  String hortemp,minuttemp;
bool h12,PM;
bool Century = false;
String i1="00:00",i2;
byte predupredit_ring=0;
byte flag_ring=0;
byte flag_time=3;
byte flag_time1=3;
byte flag_pauza=3;
byte ring_saturday=0;
byte rili_i;
byte flag3=0;
int color=0;
//дробление пакетов
int dl,nomer_pak;
bool flag_get=false;
void setup(){
     Serial.begin(115200);//частота порта
     pinMode(14, OUTPUT);
     digitalWrite(14, LOW);
     pinMode(0, OUTPUT);  
     Serial.println("");
     Serial.println("Start 1-FS");
     FS_init();//запуск файловой системы
     Serial.println("Start 2-Fileconfig");
     loadConfig();//считывает данные из файла
     Serial.println("Start 3-WIFI");
     WIFI_init();//запускаем подключение к вайфаю
     Serial.println("Start 4-Time");
     Time_init();//получаем время
     Serial.println("Start 5-SSDP");
     SSDP_init();//Настройка и запуск SSDP интерфейс
     Serial.println("Start 6-Webserver");
     HTTP_init();//запуск и настройка HTTP интерфейс
     Serial.println("Start 7-Clock");
     Wire.begin();//запуск часов
     Clock_init();//синхронизация часов
     timersInit();
     Serial.println("Start 8-WIFI Update");
     Udp.begin(8888);//udp порт
     ArduinoOTA.setPort(8266);//порт подключения
     ArduinoOTA.setHostname("WIFI-Zvonoc"); // Задаем имя сетевого порта
     ArduinoOTA.setPassword((const char *)"1975"); // Задаем пароль доступа для удаленной прошивки
     ArduinoOTA.begin(); // Инициализируем OTA
     digitalWrite (0,LOW);
    if (WiFi.status()== WL_CONNECTED){  MDNS.begin(_domen);
        MDNS.addService("http", "tcp", HTTP_PORT);}
}
void loop(){
     timersWorks();
     HTTP.handleClient();
      if (WiFi.status()!= WL_CONNECTED) dnsServer.processNextRequest();
      else { 
           MDNS.update();
           ArduinoOTA.handle(); // Всегда готовы к прошивке
      }
     if(flag_get&&cycle500mils) get_udp("");
     if (Serial.available() > 0) {
        val = Serial.read();
        if (val=='1') { 
        Serial.println("I received:");
        Serial.println(exshon[0]+" ");
        for (i = 1; i<=lessons*2;i++ ) {
            if (i%2 !=0) Serial.print(exshon[i]+" "); 
            else Serial.println(exshon[i]+" ");}
            if (saturday==1)for (i =lessons*2+1; i<=lessons*2+lessonsSaturday*2;i++ ) {
            if (i%2 !=0) Serial.print(exshon[i]+" "); 
            else Serial.println(exshon[i]+" ");
            }
     }
     else if (val=='2') { 
        Serial.println("========================================================="); 
        Serial.print("Часы "); Serial.print(Clock.getHour(h12, PM), DEC);Serial.print(" минуты ");Serial.print(Clock.getMinute());Serial.print("секунды");Serial.println(Clock.getSecond());
        Serial.print(" День недели ");Serial.println(Clock.getDoW());
        Serial.print(Clock.getDate(),DEC);Serial.println(" День");
        Serial.print(Clock.getMonth(Century),DEC); Serial.println(" Месяц");
        Serial.print(Clock.getYear(), DEC); Serial.println(" Год");
        Serial.println("*********************************************************"); 
        }
        else if (val=='3') {
            if(WiFi.status() == WL_CONNECTED)Serial.println(ip);
            else Serial.println("192.168.4.1");
        }
        else if(val=='4'){Serial.print(HTTP_ssid);Serial.print(" ");Serial.println(HTTP_password);}
        else if(val=='5')Serial.println(exshon[(lessons*2+lessonsSaturday*2+1)]);
        else if(val=='6'){Serial.print(flag_time);Serial.print(" ");Serial.print(flag_pauza);Serial.print(" ");Serial.print(flag_time1);Serial.print(" ");Serial.println(colvo/2);}
        else if(val=='7'){Serial.println(flag_ring);}
        else if(val=='8'){Serial.println(_monlast);}
        val=0;
     }
     if(cycle5s){
        if(last_clok==Clock.getSecond()&&!error_clok){Serial.println("Error clok");error="Часы вышли из строя работа без интернета не представляется возможной ";}
        if(last_clok==Clock.getSecond())error_clok=true;
        else{last_clok=Clock.getSecond();error_clok=false;}
        if (error_clok && WiFi.status() == WL_CONNECTED){
            time_t now=time(nullptr);//получаем время спомощью библиотеки Time.h
            String  Time="";//cтрока для результатов времяни
            Time+=ctime(&now);//преобразуем время в строку формата Thu Jan 19 01:55:35 2019
            byte i=Time.indexOf(":");//ищем позицию перввого сивола :
            hortemp=Time.substring(i-2,i);
            minuttemp=Time.substring(i+1,i+3);
            dayofwekt=Time.substring(0,3);
     if (dayofwekt=="Sun") dayofwek=7;
     else if (dayofwekt=="Mon") dayofwek=1;
          else if (dayofwekt=="Tue") dayofwek=2;
               else if (dayofwekt=="Wed") dayofwek=3;
                    else if (dayofwekt=="Thu") dayofwek=4;
                         else if (dayofwekt=="Fri") dayofwek=5;
                              else if (dayofwekt=="Sat") dayofwek=6;
            }
            else{
              hortemp=Clock.getHour(h12, PM), DEC; minuttemp=Clock.getMinute(), DEC;
              dayofwek= Clock.getDoW();
              }
        if(year1970)Clock_init();
        else if((_monlast!=Clock.getMonth(Century),DEC) && hortemp.toInt()==0 && minuttemp.toInt()==0){ESP.restart();}
        if (dayofwek!= 6 and dayofwek != 7 and lessons!=0){
           if(predupredit_ring==1)i=0;
           else i=1;
           for (i; i<=lessons*2; i++ ){
                l =  exshon[i].indexOf(":"); //Ишем позицию первого символа :
                temph = exshon[i].substring(l - 2, l);
                tempm = exshon[i].substring(l+1, l+3);
                if (temph.toInt()==hortemp.toInt() and tempm.toInt()==minuttemp.toInt() and ((temph!="00" and tempm!="00")||(i==0))){
                  flag1=true;
                  i2=exshon[i];
                  rili_i=i;
                  break;
                }
                else flag1=false;
           }
        }
        else if (dayofwek !=7 and lessonsSaturday>=1  and saturday==1){
             if(predupredit_ring==1)ring_saturday=lessons*2+lessonsSaturday*2+1;
             else ring_saturday=lessons*2+lessonsSaturday*2;
             for (i = lessons*2+1; i<=ring_saturday; i++ ){
                 l =  exshon[i].indexOf(":"); //Ишем позицию первого символа :
                temph = exshon[i].substring(l - 2, l);
                tempm = exshon[i].substring(l+1, l+3);
                if (temph.toInt()==hortemp.toInt() and tempm.toInt()==minuttemp.toInt() and ((temph!="00" and tempm!="00")||(i==lessons*2+lessonsSaturday*2+1))){
                  i2=exshon[i];
                  rili_i=i;
                  flag1=true;
                  break;
                }
                else flag1=false;
             }             
     }
     if (!flag1) Serial.print("OFF ");
     else  Serial.print("ON ");
     if(!error_clok){
            Serial.print(Clock.getHour(h12, PM), DEC);
            Serial.print(':');
            Serial.print(Clock.getMinute(), DEC); 
            Serial.print(':');
            Serial.println(Clock.getSecond());
        }
        else if(WiFi.status() == WL_CONNECTED){
             Serial.print(hortemp);
             Serial.print(':');
             Serial.println(minuttemp);
        } 
     }
     if (flag_ring==0){
        if(i1!=i2 && flag1 && flag2==colvo)flag2=0;
        if(flag1 && flag2==0) {cycleOn=true; timerOn= millis() / 1000;}
        if (flag1) { 
           if (flag2<colvo){         
              if (cycleOn) {
                  Serial.println("on");//Serial.println(Clock.getSecond());
                  digitalWrite(14,HIGH); 
                  flag2++; 
                  i1=i2;
                  cycleOnpauza=true;
                  cycleOffpauza=false;
                  timerOff= millis() / 1000;   
              }
              if (cycleOff){
                  Serial.println("off");//Serial.println(Clock.getSecond());
                  digitalWrite(14,LOW); 
                  flag2++;
                  cycleOffpauza=true;
                  cycleOnpauza=false;
                  timerOn= millis() / 1000;
              }
           }
        }
   else {digitalWrite (14,LOW);}
   }
   else if (flag_ring==1){
        if(i1!=i2 && flag1 && flag2==colvo)flag2=0;
        if(flag1 && flag2==0) {cycleOn=true; timerOn= millis() / 1000;}
        if (flag1) { 
           if (flag2<colvo){         
              if (cycleOn && (rili_i%2!=0 || rili_i==lessons*2+lessonsSaturday*2+1 || rili_i==0)) {
                  Serial.println("1on");//Serial.println(Clock.getSecond());
                  digitalWrite(14,HIGH); 
                  flag2++; 
                  i1=i2;
                  cycleOnpauza=true;
                  cycleOffpauza=false;
                  timerOff= millis() / 1000;   
              }
               if (cycleOff && (rili_i%2!=0 || rili_i==lessons*2+lessonsSaturday*2+1 || rili_i==0)) {
                  Serial.println("1off");//Serial.println(Clock.getSecond());
                  digitalWrite(14,LOW); 
                  flag2++;
                  cycleOffpauza=true;
                  cycleOnpauza=false;
                  timerOn= millis() / 1000;
              }
              if (cycleOn && (rili_i%2==0 && rili_i!=lessons*2+lessonsSaturday*2+1 && rili_i!=0)) {
                  Serial.println("on1");//Serial.println(Clock.getSecond());
                  digitalWrite(14,HIGH); 
                  flag2++; 
                  i1=i2;
                  cycleOnpauza=true;
                  cycleOff1pauza=false;
                  timerOff1= millis() / 1000;
              }
              if (cycleOff1 && (rili_i%2==0 && rili_i!=lessons*2+lessonsSaturday*2+1 && rili_i!=0)) {
                  Serial.println("off1");//Serial.println(Clock.getSecond());
                  digitalWrite(14,LOW); 
                  flag2++;
                  cycleOff1pauza=true;
                  cycleOnpauza=false;
                  timerOn= millis() / 1000;
              }
           }
        }   
        else {digitalWrite (14,LOW);}
     }
     if(WiFi.status()!=WL_CONNECTED && cycle3s)digitalWrite(0,!digitalRead(0)); 
     eraseCyclos();
}
