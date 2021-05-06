void HTTP_init(void){
     HTTP.on("/restart",handle_Restart);//Перезагрузка модуля по запросу http://192.168.4.1/restart?device=ok
     HTTP.on("/configs.json",handle_ConfigJSON);//формирование config.json страницы для передачи данных в web интерфейс 
     HTTP.on("/ssdp", handle_set_ssdp);//получение с web-server параметр ssdp
     HTTP.on("/ssid", handle_set_ssid);//получение с web-server пароль и логин для wifi
     HTTP.on("/ip", handle_set_ip);
     HTTP.on("/ssidap", handle_set_ssidap);//получаем с web-server пароль и логин для точки доступа
     HTTP.on("/lessons", handle_set_lessons);//получаем с web-server количество уроков
     HTTP.on("/lessonsSaturday", handle_set_lessonsSaturday);//получаем с web-server количество уроков
     HTTP.on("/saturday", handle_set_saturday);//получаем с web-server наличие субботы
     HTTP.on("/flag", Get_Flag);
     HTTP.on("/error",error1);
     HTTP.on("/timer",time_set);
     HTTP.on("/flag1",hendle_set_predupredit_ring);
     HTTP.on("/flag2",hendle_set_flag_ring);
     HTTP.on("/flag3",hendle_set_flag_time);
     HTTP.on("/ring", Get_Ring);
     HTTP.on("/w3a2o4jS", Get_HTTP);
     HTTP.on("/text",handle_set_text);
     HTTP.on("/color",handle_set_color);
     HTTP.on ("/ring2.html", [](){
              login_pasvord("ring2.html","text/html");
     });
    HTTP.on ("/", [](){
             login_pasvord("index.html","text/html");
     });
     HTTP.on ("/setup.html", [](){
              login_pasvord("setup.html","text/html");    
     });
    HTTP.on ("/config.json", [](){
            login_pasvord("config.json","text/json");    
     });
      HTTP.on ("/37d4OzOV.json", [](){
             HTTP.send(404, "text/plain", "File Not Found");
           /* if(!HTTP.authenticate("aBxDd948", "pP0UKx97"))
            //if(!HTTP.authenticate("", "1"))
             return HTTP.requestAuthentication(DIGEST_AUTH, "realm", "Please Log In");
             HTTP.send(200, "text/json", readFile("37d4OzOV.json", 32000));*/
     });
     HTTP.on ("/g2Hv38YM.html", [](){
             if(!HTTP.authenticate("aBxDd948", "pP0UKx97"))
             return HTTP.requestAuthentication(DIGEST_AUTH, "realm", "Please Log In");
             HTTP.send(200, "text/html", readFile("g2Hv38YM.html", 32000));
     });
     HTTP.begin(); //запускаем HTTP сервер
}
void login_pasvord(String fail, String tip){
  if(HTTP_ssid==""&&HTTP_password=="")HTTP.send(200, tip, readFile(fail, 32000));
             if(HTTP_ssid!=""&&HTTP_password!=""){
             if (!HTTP.authenticate(HTTP_ssid.c_str(),HTTP_password.c_str()))
                return HTTP.requestAuthentication(DIGEST_AUTH, "realm", "Please Log In");
             HTTP.send(200, tip, readFile(fail, 32000));}
             if(HTTP_ssid!=""&&HTTP_password==""){
             if (!HTTP.authenticate(HTTP_ssid.c_str(),""))
                return HTTP.requestAuthentication(DIGEST_AUTH, "realm", "Please Log In");
             HTTP.send(200, tip, readFile(fail, 32000));}
  }
void time_set(){            //0123456789ABCDEFG
  String t=HTTP.arg("timer");//2020-11-24T22:16:43
  byte cod,dow;
  Clock.setYear(t.substring(2,4).toInt());
   Clock.setMonth(t.substring(5,7).toInt());
   Clock.setDate(t.substring(8,10).toInt());
  Clock.setHour(t.substring(11,13).toInt());
  Clock.setMinute(t.substring(14,16).toInt());
  Clock.setSecond(t.substring(17,19).toInt());
  if(t.substring(5,7).toInt()==2||t.substring(5,7).toInt()==3||t.substring(5,7).toInt()==11)cod=4;
   else if(t.substring(5,7).toInt()==12||t.substring(5,7).toInt()==9)cod=6;
  else if(t.substring(5,7).toInt()==1||t.substring(5,7).toInt()==10)cod=1;
   else if(t.substring(5,7).toInt()==4||t.substring(5,7).toInt()==7)cod=0;
  else if(t.substring(5,7).toInt()==5)cod=2;
  else if(t.substring(5,7).toInt()==8)cod=3;
    else if(t.substring(5,7).toInt()==6)cod=5; 
    dow=(t.substring(8,10).toInt()+cod+(6+t.substring(2,4).toInt()+t.substring(2,4).toInt()/4)%7)%7 ;
    if(dow>1)Clock.setDoW(dow-1);
    else if (dow==0)Clock.setDoW(6);
    else if (dow==1)Clock.setDoW(7);
  HTTP.send (200,"text/plain", "OK"); //ответ сервера
  }
void handle_Restart(){//что делать если нужно презагрузить устройство с сайта
     String restart = HTTP.arg("device");//записываем значение аргумента device
     if (restart == "ok"){
        HTTP.send (200,"text/plain", "OK"); //ответ сервера
        ESP.restart();//если аргумент равен "оk" то перезапускаем еsp
     }
     else HTTP.send(200,"text/plain","No Reset");
}
void handle_set_ssdp(){
     SSDP_Name = HTTP.arg("ssdp");//получаем значение ssdp
     saveConfig();//cохраняем во внутренную память
     HTTP.send(200,"text/plain","OK");//отправляем ответ о выполнении
}
void handle_set_ssid(){
     _ssid=HTTP.arg("ssid");//получаем значение ssid /ssid?ssid=ddv&password=2630826308
     _password=HTTP.arg("password");//получаем значение password
     saveConfig();//cохраняем во внутренную память
     HTTP.send(200,"text/plain","OK");//отправляем ответ о выполнении
}
void error1(){
  if(HTTP.arg("error")=="ok"){
  error="";
  saveConfig();//cохраняем во внутренную память
  HTTP.send(200,"text/plain","OK");//отправляем ответ о выполнении
}
else HTTP.send(200,"text/plain","No ok error");
  }
void handle_set_text(){
     text=HTTP.arg("text");
     HTTP.send(200, "text/plain","OK");
     flag_get=true;
     dl=text.length();
     nomer_pak=0;
     get_udp("!9!");
     timer500mils=millis();
     cycle500mils=false;
     saveConfig();
}
void get_udp(String sms){
     Udp.beginPacket(ip_get,8888);
     if(sms==""){
     if(dl>255){dl-=255;bufer=text.substring(255*nomer_pak,255*(nomer_pak+1));nomer_pak++;}
     else {bufer=text.substring(255*nomer_pak,255*nomer_pak+dl);flag_get=false;}
     }
     else bufer=sms;
     Serial.println(bufer);
     Udp.print(bufer);
     Udp.endPacket();
}
void handle_set_color (){
     color=HTTP.arg("color").toInt();
     HTTP.send(200, "text/plain","OK");
     get_udp("!"+String(color)+"!");
     timer500mils=millis();
     cycle500mils=false;
     saveConfig();
     }
void handle_set_ip(){
  if(HTTP.arg("device")=="ok"){
     HTTP.send (200,"text/plain", "OK"); //ответ сервера
  WiFi.disconnect();
  Serial.println("disconnect");
  WiFi.mode (WIFI_STA);//Переходим в режим для подключения к wifi
     byte tries = 11;//Количество попыток подключения 
     WiFi.begin (_ssid.c_str(), _password.c_str());//подключаемся к wifi
     while (--tries && WiFi.status() != WL_CONNECTED){
           Serial.print(".");
           delay(1000);
     }
     if (WiFi.status()== WL_NO_SSID_AVAIL)ip="Сеть не найдена";
     if (WiFi.status()==6){ip="Неправильный пароль";}
     if (WiFi.status()!= WL_CONNECTED){
        //Если не удалось подключиться подымаем свою точку доступа
        Serial.println("fail");
        Serial.println("WiFi up AP");
        Serial.println("192.168.4.1");
        StartAPMode();
     }
     else {
          Serial.println("");
          Serial.println("connect");
          ip=WiFi.localIP().toString();
          Serial.println(WiFi.localIP());
          Serial.println(ip);
          saveConfig();
          StartAPMode();
     }
  }
   else HTTP.send(200,"text/plain","No IP");
}
void handle_set_ssidap(){
     _ssidAP=HTTP.arg("ssidAP");//получаем значение ssidAP
     _passwordAP=HTTP.arg("passwordAP");//получае значение passwordAP
     saveConfig();//cохраняем во внутренную память
     HTTP.send(200,"text/plain","OK");//отправляем ответ о выполнении
}
void Get_Flag(){
     if(HTTP.arg("flag").toInt()==0||HTTP.arg("flag").toInt()==1)flag_password=HTTP.arg("flag").toInt();
     else {Serial.println("Error HTTP");error+="Ошибка при отправки переменной flag ";}
     saveConfig();//cохраняем во внутренную память
     HTTP.send(200,"text/plain","OK");//отправляем ответ о выполнении
}
void hendle_set_predupredit_ring(){
     if(HTTP.arg("flag1").toInt()==0||HTTP.arg("flag1").toInt()==1)predupredit_ring=HTTP.arg("flag1").toInt();
     else{Serial.println("Error HTTP");error+="Ошибка при отпраки переменной пожалуйста проверьте настройку предупредительный звонок ";}
     saveConfig();//cохраняем во внутренную память
     HTTP.send(200,"text/plain","OK");//отправляем ответ о выполнении
}
void hendle_set_flag_ring(){
     if(HTTP.arg("flag2").toInt()==0||HTTP.arg("flag2").toInt()==1)flag_ring=HTTP.arg("flag2").toInt();
     else {Serial.println("Error HTTP");error+="Ошибка при отпраки переменной пожалуйста проверьте настроку метод звонения ";}
     saveConfig();//cохраняем во внутренную память
     HTTP.send(200,"text/plain","OK");//отправляем ответ о выполнении
}
void hendle_set_flag_time(){
     if(HTTP.arg("on").toInt()>=1&&HTTP.arg("on").toInt()<=30)flag_time=HTTP.arg("on").toInt();
     else{Serial.println("Error HTTP");error+="Ошибка при отправки переменной пожалуста проверьте настройку длительность звока ";}
     if(HTTP.arg("off").toInt()>=1&&HTTP.arg("off").toInt()<=59)flag_pauza=HTTP.arg("off").toInt();
     else{Serial.println("Error HTTP");error+="Ошибка при отправки переменной пожалуста проверьте настройку длительность паузы ";}
     if(HTTP.arg("on1").toInt()>=1&&HTTP.arg("on1").toInt()<=30)flag_time1=HTTP.arg("on1").toInt();
     else if(flag_ring==1){Serial.println("Error HTTP");error+="Ошибка при отправки переменной пожалуста проверьте настройку длительность звока с урока ";}
     if(HTTP.arg("qua").toInt()>=1&&HTTP.arg("qua").toInt()<=126)colvo=HTTP.arg("qua").toInt()*2;
     else{Serial.println("Error HTTP");error+="Ошибка при отправки переменной пожалуста проверьте настройку колличество звоков ";}
     saveConfig();//cохраняем во внутренную память
     HTTP.send(200,"text/plain","OK");//отправляем ответ о выполнении
}
void Get_HTTP(){
     HTTP_ssid=HTTP.arg("kAM184BD");//получаем значение ssidAP
     HTTP_password=HTTP.arg("68tS0pMP");//получае значение passwordAP
     saveConfig1();//cохраняем во внутренную память
     HTTP.send(200,"text/plain","OK");//отправляем ответ о выполнении
}
void handle_set_lessons(){
     if(HTTP.arg("lessons").toInt()>=0&&HTTP.arg("lessons").toInt()<=50)lessons=HTTP.arg("lessons").toInt();//получаем значение 
     else{Serial.println("Error HTTP");error+="Ошибка при отправки переменной пожалуйста проверьте настройку количество уроков ";}
     saveConfig();//cохраняем во внутренную память
     HTTP.send(200,"text/plain","OK");//отправляем ответ о выполнении
}
void handle_set_lessonsSaturday(){
     if(HTTP.arg("lessonsSaturday").toInt()>=0&&HTTP.arg("lessonsSaturday").toInt()<=25)lessonsSaturday=HTTP.arg("lessonsSaturday").toInt();//получаем значение 
     else {Serial.println("Error HTTP");error+="Ошибка при отправки переменной пожалуйста проверьте настройку количество уроков в субботу ";}
     saveConfig();//cохраняем во внутренную память
     HTTP.send(200,"text/plain","OK");//отправляем ответ о выполнении
}
void handle_set_saturday(){
     if(HTTP.arg("saturday").toInt()==0||HTTP.arg("saturday").toInt()==1)saturday=HTTP.arg("saturday").toInt();//получаем значение saturday
     else {Serial.println("Error HTTP");error+="Ошибка при отправки переменной пожалуйста проверьте настройку пяти/шести дневка ";}
     saveConfig();//cохраняем во внутренную память
     HTTP.send(200,"text/plain","OK");//отправляем ответ о выполнении
}
void Get_Ring(){
  byte tix=0;
  for (i=1;i<=lessons;i++){
      tix++;
      exshon[tix]=HTTP.arg("start"+String(i));
      tix++;
      exshon[tix]=HTTP.arg("end"+String(i));  
  }
  if(predupredit_ring==1){
    l=exshon[1].indexOf(":"); //Ишем позицию первого символа :
    temph = exshon[1].substring(l - 2, l);
    tempm = exshon[1].substring(l+1, l+3);
    if(tempm.toInt()<5){
      if(temph.toInt()>0){
        temph=(temph.toInt()-1);
        tempm=(tempm.toInt()+55);
        }
        else{temph="23";tempm=(tempm.toInt()+55);}
     }
    else tempm=(tempm.toInt()-5);
    exshon[0]=temph+":"+tempm;
    }
  if(saturday==1 ){
    for (i=lessons+1;i<=lessons+lessonsSaturday;i++){
       tix++;
      exshon[tix]=HTTP.arg("start"+String(i));
      tix++;
      exshon[tix]=HTTP.arg("end"+String(i)); 
     }
     if(predupredit_ring==1){
    l=exshon[lessons*2+1].indexOf(":"); //Ишем позицию первого символа :
    temph = exshon[lessons*2+1].substring(l - 2, l);
    tempm = exshon[lessons*2+1].substring(l+1, l+3);
    if(tempm.toInt()<5){
      if(temph.toInt()>0){
        temph=(temph.toInt()-1);
        tempm=(tempm.toInt()+55);
        }
        else{temph="23";tempm=(tempm.toInt()+55);}
     }
    else tempm=(tempm.toInt()-5);
    exshon[lessons*2+lessonsSaturday*2+1]=temph+":"+tempm;
    }
  }
  saveConfig();
  HTTP.send(200,"text/plain","OK");
}
void handle_ConfigJSON(){
     String root="{}";//формирование строки для отправки в браузер json формат
     DynamicJsonBuffer jsonBuffer;// Резервируем память для json обекта
     JsonObject& json = jsonBuffer.parseObject(root);//  вызовите парсер JSON через экземпляр jsonBuffer
     //заполняем поля JSON
     json["SSDP"]=SSDP_Name;
     json["ssidAP"]=_ssidAP;
     json["passwordAP"]=_passwordAP;
     json["ssid"]=_ssid;
     json["password"]=_password;
     json["ip"]=ip;
     json["timezone"]=timezone;
     json["lessons"]=lessons;
     json["lessonsSaturday"]=lessonsSaturday;
     json["flag"]=flag_password;
     json["flag1"]=predupredit_ring;
     json["flag2"]=flag_ring;
     json["flag3"]=flag_time;
     json["flag4"]=flag_pauza;
     json["flag5"]=flag_time1;
     json["flag6"]=colvo/2;
     json["saturday"]=saturday;
     json["error"]=error;
     json["text"]=text;
     byte tix=1;
     if(lessons>0)for (i=1;i<=lessons;i++){
         json["start"+String(i)]=exshon[tix];
         tix++;
         json["end"+String(i)]=exshon[tix];
         tix++;
     }
     if(saturday==1 and lessonsSaturday>0) for (i=lessons+1;i<=lessons+lessonsSaturday;i++){
         tix++;
         json["start"+String(i)]=exshon[tix];
         tix++;
         json["end"+String(i)]=exshon[tix];
     }
     if(WiFi.status() == WL_CONNECTED && !year1970)json["time"]=GetTime();
     else {
      ttt="";
       ttt=Clock.getHour(h12, PM), DEC;ttt+=":";ttt+=Clock.getMinute(), DEC;ttt+=":";ttt+=Clock.getSecond();
      json["time"]=ttt;}
     root="";
     json.printTo(root);//помещаем созданный json в переменную root
     HTTP.send(200,"text/json",root);
}
