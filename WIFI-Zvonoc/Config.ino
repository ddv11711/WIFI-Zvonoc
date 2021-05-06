bool loadConfig(){//считывание сохроннёных данных из файла
  File configFile=SPIFFS.open("/config.json","r");//открываем файл для чтения
  if (!configFile){//если файл не найден
     Serial.println("Filed to open config file");
     saveConfig();//создаём файл записав в него значения по умолчанию
     configFile.close();
     return false;
  }
  size_t size = configFile.size();//проверяем размер файла будем использовать файл меньше 1024 байта
  if (size > 1024){//eсли файл больше то выдаём ошибку
     Serial.println("Config file size is too large");
     configFile.close();
     return false;
  }
  jsonConfig = configFile.readString();//схраняем файд в глобальную перменную
  configFile.close();
  DynamicJsonBuffer jsonBuffer;//выделяем память для json обекта
  //вызываем парсер JSON через экземпляр jsonBuffer
  //строку возьмём из глобальной памяти String jsonConfig
  JsonObject&root = jsonBuffer.parseObject(jsonConfig);
  //теперь можно получить значения из root
  _ssidAP = root["ssidAPName"].as<String>();//так получаем строку
  _passwordAP = root["ssidAPPassword"].as<String>();
  timezone = root["timezone"];//так получаем число
  SSDP_Name = root["SSDPName"].as<String>();
  _ssid = root["ssidName"].as<String>();
  _password = root["ssidPassword"].as<String>();
  ip=root["ip"].as<String>();
  text=root["text"].as<String>();
  color=root["color"];
  if(root["flag"]==0||root["flag"]==1)flag_password=root["flag"];
  else {flag_password=0;Serial.println("Error file");error+="Oшибка при поднятии переменной flag ";}
  if(root["flag1"]==0||root["flag1"]==1)predupredit_ring=root["flag1"];
  else {predupredit_ring=0;Serial.println("Error file");error+="Oшибка при поднятии переменной проверьте пожалуста настройку предупредительный звонок сейчас он выключен  ";}
  if(root["flag2"]==0||root["flag2"]==1)flag_ring=root["flag2"];
  else {flag_ring=0;Serial.println("Error file");error+="Oшибка при поднятии переменной проверьте пожалуйста настройку метод звонения ";}
  if(root["flag3"]>=1&&root["flag3"]<=30)flag_time=root["flag3"];
  else {flag_time=3;Serial.println("Error file");error+="Oшибка при поднятии переменной проверьте пожалуйста настройку длительность звонка сейчас 3 сек. ";}
  if(root["flag4"]>=1&&root["flag4"]<=59)flag_pauza=root["flag4"];
  else {flag_pauza=3;Serial.println("Error file");error+="Oшибка при поднятии переменной проверьте пожалуйста настройку длительность паузы сейчас 3 сек. ";}
  if(flag_ring==1&&root["flag5"]>=1&&root["flag5"]<=30)flag_time1=root["flag5"];
  else if(flag_ring==1){flag_time1=3;Serial.println("Error file");error+="Oшибка при поднятии переменной проверьте пожалуйста настройку длительность звонка с урока сейчвс 3 сек. ";}
  if(root["flag6"]>=1&&root["flag6"]<=126)colvo=root["flag6"];
  else {colvo=1;Serial.println("Error file");error+="Oшибка при поднятии переменной проверьте пожалуйста настройку количество звонков сечвс 1 ";}
  if(root["lessons"]>=0&&root["lessons"]<=50)lessons = root["lessons"];
  else {lessons=7;Serial.println("Error file");error+="Oшибка при поднятии переменной проверьте пожалуйста настройку количество уроков сейчвс 7 ";}
  if(root["lessonsSaturday"]>=0&&root["lessonsSaturday"]<=25)lessonsSaturday = root["lessonsSaturday"];
  else {lessonsSaturday = root["lessonsSaturday"]=7;Serial.println("Error file");error+="Oшибка при поднятии переменной проверьте пожалуйста настройку количество уроков в субботу сейчвс 7 ";}
  if(root["saturday"]==0||root["saturday"]==1)saturday = root["saturday"];
  else {saturday=7;Serial.println("Error file");error+="Oшибка при поднятии переменной проверьте пожалуйста настройку пяти/шести дневку сейчас пятидневка ";}
  byte tix=0;
     for (i=1;i<=lessons;i++){
         tix++;
         exshon[tix]=root["start"+String(i)].as<String>();
         tix++;
         exshon[tix]=root["end"+String(i)].as<String>();
     }
     if(saturday==1) for (i=lessons+1;i<=lessons+lessonsSaturday;i++){
         tix++;
         exshon[tix]=root["start"+String(i)].as<String>();
         tix++;
         exshon[tix]=root["end"+String(i)].as<String>();
     }
     loadConfig1();
  return true;
}
bool saveConfig(){//запись данных в файл config.json
     DynamicJsonBuffer jsonBuffer; //резервируем память для json обекта 
     JsonObject&json=jsonBuffer.parseObject(jsonConfig);//выводим парсер JSON через экземпляр jsonBuffer
     //заполняем поля json
     json["SSDPName"] = SSDP_Name;
     json["ssidAPName"] = _ssidAP;
     json["ssidAPPassword"] = _passwordAP;
     json["ssidName"] = _ssid;
     json["ssidPassword"] = _password;
     json["ip"] = ip;
     json["timezone"] = timezone;
     json["lessons"] = lessons;
     json["lessonsSaturday"] = lessonsSaturday;
     json["flag"]=flag_password;
     json["flag1"]=predupredit_ring;
     json["flag2"]=flag_ring;
     json["flag3"]=flag_time;
     json["flag4"]=flag_pauza;
     if(flag_ring==1) json["flag5"]=flag_time1;
     json["flag6"]=colvo;
     json["saturday"] = saturday;
     json["text"]=text;
     json["color"]=color;
     byte tix=0;
     for (i=1;i<=lessons;i++){
         tix++;
         json["start"+String(i)]=exshon[tix];
         
         tix++;
         json["end"+String(i)]=exshon[tix];
          
     }
     if(saturday==1 ) for (i=lessons+1;i<=lessons+lessonsSaturday;i++){
         tix++;
         json["start"+String(i)]=exshon[tix];
         tix++;
         json["end"+String(i)]=exshon[tix];
     }
      
      
     json.printTo(jsonConfig);//помещаем созданный json в глобальную переменную json.printTo(jsonConfig)
     File configFile= SPIFFS.open("/config.json","w");//открываем файл для записи
     if(!configFile){
      Serial.println("Failed to open config file for writing");
      error+="Ошибка при открытии файла config.json пожалуйста проверьте свои настройки ";
      configFile.close();
      return false;
     }
     json.printTo(configFile);//записываем строку json в файл
     configFile.close();
     return true;
}
String readFile(String fileName, size_t len ) {
  File configFile = SPIFFS.open("/" + fileName, "r");
  if (!configFile) {
    return "Failed";
  }
  size_t size = configFile.size();
  if (size > len) {
    configFile.close();
    return "Large";
  }
  String temp = configFile.readString();
  configFile.close();
  return temp;
}
bool loadConfig1(){//считывание сохроннёных данных из файла
  File configFile=SPIFFS.open("/37d4OzOV.json","r");//открываем файл для чтения
  if (!configFile){//если файл не найден
     Serial.println("Filed to open config password file");
     error+="Ошибка при открытии файла пожалуйста проверьте свой логин и пароль от сайта ";
     saveConfig1();//создаём файл записав в него значения по умолчанию
     flag_password=0;
     configFile.close();
     saveConfig();
     return false;
  }
  size_t size = configFile.size();//проверяем размер файла будем использовать файл меньше 1024 байта
  if (size > 1024){//eсли файл больше то выдаём ошибку
     Serial.println("Config password file size is too large");
     error+="Ошибка при открытии файла ";
     configFile.close();
     return false;
  }
  jsonConfig = configFile.readString();//схраняем файд в глобальную перменную
  configFile.close();
  DynamicJsonBuffer jsonBuffer;//выделяем память для json обекта
  //вызываем парсер JSON через экземпляр jsonBuffer
  //строку возьмём из глобальной памяти String jsonConfig
  JsonObject&root = jsonBuffer.parseObject(jsonConfig);
  //теперь можно получить значения из root
  HTTP_ssid = root["cRp1og63"].as<String>();
  HTTP_password = root["6q3vxFC6"].as<String>();
  return true;
}
bool saveConfig1(){//запись данных в файл config.json
     DynamicJsonBuffer jsonBuffer; //резервируем память для json обекта 
     JsonObject&json=jsonBuffer.parseObject(jsonConfig);//выводим парсер JSON через экземпляр jsonBuffer
     //заполняем поля json
     json["cRp1og63"] = HTTP_ssid;
     json["6q3vxFC6"] = HTTP_password;
     json.printTo(jsonConfig);//помещаем созданный json в глобальную переменную json.printTo(jsonConfig)
     File configFile= SPIFFS.open("/37d4OzOV.json","w");//открываем файл для записи
     if(!configFile){
      Serial.println("Failed to open config password file for writing");
       error+="Ошибка при открытии файла c паролем ";
      configFile.close();
      return false;
     }
     json.printTo(configFile);//записываем строку json в файл
     configFile.close();
     return true;
}
