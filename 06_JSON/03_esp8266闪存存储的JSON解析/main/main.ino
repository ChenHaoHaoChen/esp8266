#include <ArduinoJson.h> //引入ArduinoJson解析库
#include <ESP8266WiFi.h> //引入ESP8266WiFi库
#include <FS.h>          //引入闪存文件操作库

void setup()
{
  //从闪存文件系统中config.json的文件读出wifi的ssid与password
  SPIFFS.begin();
  File config_file = SPIFFS.open("config.json","r");
  String json = config_file.readString();
  config_file.close();
  //解析读出的json
  const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + 50;
  DynamicJsonBuffer jsonBuffer(capacity);
  JsonObject& root = jsonBuffer.parseObject(json);
  const char* wifi_ssid = root["wifi"]["ssid"];         // "TP-LINK_1CD4"
  const char* wifi_password = root["wifi"]["password"]; // "15150757563"
  //连接WiFi
  WiFi.begin(wifi_ssid,wifi_password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(10);
  }
  //设置LED引脚为输出模式
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop()
{
  //若esp8266已连接wifi则打开LED
  if(WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(LED_BUILTIN,LOW);
  }
}
