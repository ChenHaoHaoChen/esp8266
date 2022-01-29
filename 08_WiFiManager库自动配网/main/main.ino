#include <ESP8266WiFi.h> //引入ESP8266WiFi（不引入也可以）
#include <WiFiManager.h> //引入WiFiManager
#include <ESP8266WebServer.h> //引入ESP8266WebServer库（不引入也可以）
/********配置函数********/
void setup()
{
  Serial.begin(9600); //初始化串口波特率为9600
  
  WiFiManager wifi_manager; //建立WiFiManager对象
  wifi_manager.autoConnect("chenhaohao"); //自动联网，若连接失败启动接入点模式，发出wifi为"chenhaohao"，无密码
  Serial.println(WiFi.SSID());   //串口输出连接wifi名
  Serial.println(WiFi.localIP());//串口输出连接WiFi密码
}
/********主循环函数********/
void loop()
{

}
