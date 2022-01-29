#include <ESP8266WiFi.h> //引入ESP8266WiFi库
#include <ArduinoJson.h> //引入ArduinoJson库
#include <ESP8266_Seniverse.h> //引入ESP8266_Seniverse库
//被连接WiFi名称与密码
String wifi_ssid = "TP-LINK_1CD4";
String wifi_password = "15150757563";
//获取心知天气信息必备信息
String user_key = "S-9a3-Z4sX_eWvo7H";
String location = "Suqian";
String unit = "c";
//创建WeatherNow
WeatherNow weather_now;
/********配置函数********/
void setup()
{
  Serial.begin(9600); //串口初始画波特率为9600
  WiFi.begin(wifi_ssid,wifi_password); //连接WiFi
  while(WiFi.status() != WL_CONNECTED) //等待连接成功
  {
    delay(10);
  }

  weather_now.config(user_key,location,unit); //配置心知天气
}
/********主循环函数********/
void loop()
{
  if(weather_now.update()) //如果成功连接至心知天气服务器
  {
    Serial.println(weather_now.getWeatherText()); //获取实时天气
    Serial.println(weather_now.getWeatherCode()); //获取实时天气对应代码
    Serial.println(weather_now.getDegree());      //获取实时温度
    Serial.println(weather_now.getLastUpdate());  //获取上次更新时间
  }
  delay(3000); //延时3s
}
