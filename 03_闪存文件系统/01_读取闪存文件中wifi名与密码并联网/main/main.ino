#include <ESP8266WiFi.h>
#include <FS.h>

void setup()
{
  //启动闪存文件系统
  SPIFFS.begin();
  
  //读取wifi_name_file文件中wifi名并赋值给wifi_name
  File wifi_name_file = SPIFFS.open("wifi_name_file","r");
  String wifi_name = wifi_name_file.readString();
  wifi_name_file.close();
  //读取wifi_passwor_file文件中wifi密码并赋值给wifi_password
  File wifi_password_file = SPIFFS.open("wifi_password_file","r");
  String wifi_password = wifi_password_file.readString();
  wifi_password_file.close();
  
  //esp8266连接wifi，并设置工作模式为无线终端模式
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_name,wifi_password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(100);
  }
  
  //设置板上LED引脚为输出模式
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop()
{
  //检测esp8266是否联网，若联网则打开蓝色LED
  if(WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(LED_BUILTIN,LOW);
  }
}
