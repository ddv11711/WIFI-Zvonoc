void WIFI_init(){
     WiFi.mode (WIFI_STA);//режим подключения к WI-FI
     byte tries = 11;//Количество попыток подключения 
     Serial.print("ssid:");Serial.print(_ssid);Serial.print(" password:");Serial.println(_password);
     WiFi.begin (_ssid.c_str(), _password.c_str());//подключаемся к wifi
     while (--tries && WiFi.status() != WL_CONNECTED){
           Serial.print(".");
           delay(1000);
     }
     Serial.println("");
     if (WiFi.status()== WL_NO_SSID_AVAIL){ip="Сеть не найдена";}
     if (WiFi.status()==6){ip="Неправильный пароль";}
     if (WiFi.status()!= WL_CONNECTED){//если не удалось подключится подымаем точку доступа
        Serial.println("WiFi up AP");
        Serial.println(apIP);
        StartAPMode();
     }
     else {//если удалось подключится то выводим IP
          Serial.println("WiFi Connected");
          Serial.println(WiFi.localIP());
         ip=WiFi.localIP().toString();
          /*dnsServer.setTTL(300);
          dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
          dnsServer.start(DNS_PORT,"zvonoc.com",WiFi.localIP());*/
     }
     
}
bool StartAPMode(){ 
     WiFi.disconnect();//Отключаем wifi
     WiFi.mode(WIFI_AP);//включаем режим точки доступа
     WiFi.softAPConfig(apIP,apIP, IPAddress(255,255,255,0));
     WiFi.softAP(_ssidAP.c_str(),_passwordAP.c_str());
     dnsServer.start(DNS_PORT,"*",apIP);
     return true;
}
