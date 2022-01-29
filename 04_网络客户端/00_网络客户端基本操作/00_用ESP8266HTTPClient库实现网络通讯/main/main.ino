#include <ESP8266WiFi.h>       //引入ESP8266库       
#include <ESP8266HTTPClient.h> //引入esp网络客户端库
#define URL "http://www.example.com" //宏定义

char *WiFi_name = "TP-LINK_1CD4";   //被连接wifi名
char *WiFi_password = "15150757563";//被连接wifi密码
/********配置函数********/
void setup()
{
  Serial.begin(9600); //以波特率为9600启动串口
  WiFi.mode(WIFI_STA);//设置esp8266工作模式为无线终端模式

  WiFi.begin(WiFi_name,WiFi_password);//连接wifi
  while(WiFi.status() != WL_CONNECTED)//等待wifi连接完成
  {
    delay(100);
  }

  httpClientRequest();
}
/********主循环函数********/
void loop()
{
  
}
/********处理客户端请求函数********/
void httpClientRequest()
{
  HTTPClient http_client; //定义HTTPclient对象

  http_client.begin(URL); //esp8266发送请求目标网址

  int http_code = http_client.GET(); //esp8266向网络服务器发送GET请求，

  if(http_code == HTTP_CODE_OK)
  {
    String response_payload = http_client.getString(); //获取服务器响应体的信息
    Serial.println(response_payload);                  //通过串口打印响应体信息
  }
  else
  {
    Serial.println(http_code);
  }
}
//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
//
//char *wifi_name = "TP-LINK_1CD4";
//char *wifi_password = "15150757563";
//
//void setup()
//{
//  Serial.begin(9600);
//  WiFi.mode(WIFI_STA);
//  
//  WiFi.begin(wifi_name,wifi_password);
//  while(WiFi.status() != WL_CONNECTED)
//  {
//    delay(100);
//  }
//  
//  sendClientRequest();
//}
//
//void loop()
//{
//
//}
//
//void sendClientRequest()
//{
//  HTTPClient http_client;
//  
//  http_client.begin("http://www.example.com");
//  
//  if(http_client.GET() == HTTP_CODE_OK)
//  {
//    String payload = http_client.getString();
//    Serial.println(payload);
//  }
//  else
//  {
//    Serial.println(http_client.GET());
//  }
//}
