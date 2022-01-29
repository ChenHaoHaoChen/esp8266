#include <ESP8266WiFi.h> //引入ESP8266WiFi库
#include <ArduinoOTA.h>  //引入ArduinoOTA库
#include <Ticker.h>      //引入Ticker库
//被连接wifi名与密码
String wifi_ssid = "TP-LINK_1CD4";
String wifi_password = "15150757563";
//建立Ticker对象
Ticker ticker;
/********配置函数********/
void setup()
{
  connect_wifi(); //连接wifi
  
  pinMode(LED_BUILTIN,OUTPUT);     //设置LED引脚为输出模式
  ticker.attach_ms(1000,LED_blink);//每1秒调用LED_blink函数
  
  ArduinoOTA.setHostname("ESP8266"); //设置端口名为ESP8266
  ArduinoOTA.setPassword("12345678");//设置连接密码为12345678
  ArduinoOTA.begin();                //启动OTA
}
/********主循环函数********/
void loop()
{
  ArduinoOTA.handle(); //处理OTA下载程序请求
}
/********连接wifi********/
void connect_wifi()
{
  WiFi.begin(wifi_ssid,wifi_password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(10);
  }
}
/********LED闪烁********/
void LED_blink()
{
  digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
}
