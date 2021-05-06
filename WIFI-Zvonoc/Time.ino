void Time_init(){
     HTTP.on("/Time",handle_time);//синхранизация времяни
     HTTP.on("/TimeZone",handle_timezone);//синхранизация времяной зонв
     timeSynch();
}
void timersInit() {
  unsigned long uptimeSec = millis() / 1000;
  unsigned long uptimeMils = millis();
  timer500mils=uptimeMils;
  timer3s = uptimeSec;  
  timer5s = uptimeSec; 
  timer10s = uptimeSec;
  timerOn=uptimeSec;
  timerOff1=uptimeSec;
  timerOff=uptimeSec;
 /* timer30s = uptimeSec;
  timer1m = uptimeSec;
  timer3m = uptimeSec;
  timer24h = uptimeSec;*/
}
void timersWorks() {
  unsigned long timeSec = millis() / 1000;
  unsigned long timeMils = millis();
  if (timeMils - timer500mils > 500) {timer500mils =  timeMils; cycle500mils = true;}
  if (timeSec - timer3s > 2) {timer3s =  timeSec; cycle3s = true;}
  if (timeSec - timer5s > 4) {timer5s = timeSec; cycle5s = true;}
  if (timeSec - timer10s > 9) {timer10s = timeSec; cycle10s = true;}
  if (timeSec - timerOn > flag_pauza-1&&!cycleOnpauza) { cycleOn = true;}
  if (timeSec - timerOff1 > flag_time1-1&&!cycleOff1pauza) { cycleOff1 = true;}
  if (timeSec - timerOff > flag_time-1&&!cycleOffpauza) { cycleOff = true;}
 /* if (timeSec - timer30s > 29) {timer30s = timeSec; cycle30s = true;}
  if (timeSec - timer1m >  59) {timer1m =  timeSec; cycle1m = true;}
  if (timeSec - timer3m > 179) {timer3m =  timeSec; cycle3m = true;}
  if (timeSec - timer24h > 86399) {timer24h =  timeSec; cycle24h = true;}*/}
void eraseCyclos() {
  cycle500mils=false;
  cycle3s = false;
  cycle5s = false;
  cycle10s = false;
  cycleOn = false;
  cycleOff1 = false;
  cycleOff = false;
 /* cycle30s = false;
  cycle1m = false;
  cycle3m = false;
  cycle24h = false;*/
}
void timeSynch(){
     if (WiFi.status()==WL_CONNECTED){
        configTime(timezone*3600,0,"10.168.0.1","time.nist.gov","time.windows.com");//настройка соединения с NTP сервером
        byte i=0;
        Serial.println("Waiting for time");
        while (!time(nullptr)&&i<10){
              Serial.print(".");
              i++;
              delay(1000); 
        }
        Serial.println("");
        Serial.println("Time Ready!");
        Serial.println(GetTime());
        Serial.print(GetDate());
     }
}
void handle_timezone(){
     timezone=HTTP.arg("timezone").toInt();// Получаем значение timezone из запроса конвертируем в int сохраняем в глобальной переменной
     saveConfig();
     HTTP.send(200,"text/plain","OK");
}
void handle_time(){
  timeSynch();
  HTTP.send(200,"text/plain","OK");
}

String GetTime(){//получаем текущие время
       time_t now=time(nullptr);//получаем время спомощью библиотеки Time.h
       String  Time="";//cтрока для результатов времяни
       Time+=ctime(&now);//преобразуем время в строку формата Thu Jan 19 01:55:35 2019
       byte i=Time.indexOf(":");//ищем позицию перввого сивола :
       Time=Time.substring(i-2,i+6);//выделяем из строки 2 символа перед символом : и 6 символов после
       return Time;//возвращаем полученное время
}
String GetDate(){//получаем дату
       time_t now= time(nullptr);//полкчаем время с помощью библиотеки Time.h
       String Data="";//cтрока для резульатов даты
       Data+=ctime(&now);//преобразуем время в строку формата Thu Jan 19 01:55:35 2019
       byte i=Data.lastIndexOf(" ");//ищим позицию последнего пробела
       String Time=Data.substring(i-8,i+1);//выделяем время и пробел 
       Data.replace(Time,"");//удаляем из строки 8 символов времяни и пробел
       return Data;//возращаем полученную дату
}
void Clock_init(){
     if(WiFi.status()==WL_CONNECTED){
     time_t now=time(nullptr);//получаем время спомощью библиотеки Time.h
     String  Time="";//cтрока для результатов времяни
     Time+=ctime(&now);//преобразуем время в строку формата Thu Jan 19 01:55:35 2019
     byte i=Time.indexOf(":");//ищем позицию перввого сивола :
     if(Time.substring(i+7,i+11)!="1970"){
     _hour=Time.substring(i-2,i).toInt();
     Clock.setHour(_hour);
     _minute=Time.substring(i+1,i+3).toInt();
     Clock.setMinute(_minute);
     _second=Time.substring(i+4,i+6).toInt();
     Clock.setSecond(_second);
     _day=Time.substring(i-5,i-3).toInt();
     Clock.setDate(_day);
     dayofwekt=Time.substring(i-13,i-10);
     if (dayofwekt=="Sun") dayofwek=7;
     else if (dayofwekt=="Mon") dayofwek=1;
          else if (dayofwekt=="Tue") dayofwek=2;
               else if (dayofwekt=="Wed") dayofwek=3;
                    else if (dayofwekt=="Thu") dayofwek=4;
                         else if (dayofwekt=="Fri") dayofwek=5;
                              else if (dayofwekt=="Sat") dayofwek=6;
     Clock.setDoW(dayofwek);
     mont=Time.substring(i-9,i-6);
     if (mont=="Jan") _mon=1;
     else if (mont=="Feb") _mon=2;
             else if (mont=="Mar") _mon=3;
                     else if (mont=="Apr") _mon=4;
                          else if (mont=="May") _mon=5;
                               else if (mont=="Jun") _mon=6;
                                    else if (mont=="Jul") _mon=7;
                                         else if (mont=="Aug") _mon=8;
                                              else if (mont=="Sep") _mon=9;
                                                   else if (mont=="Oct") _mon=10;
                                                        else if (mont=="Nov") _mon=11;
                                                             else if (mont=="Dec") _mon=12;
     _monlast=_mon;
     Clock.setMonth(_mon);
     _year=Time.substring(i+9,i+11).toInt();
     Clock.setYear(_year);
     year1970=false;
     }
     else year1970=true;
     }
     else _monlast=Clock.getMonth(Century),DEC;
}
