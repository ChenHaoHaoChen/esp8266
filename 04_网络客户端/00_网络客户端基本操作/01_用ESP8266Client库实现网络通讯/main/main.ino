#include <ESP8266WiFi.h>
String web = "www.example.com";      //定义发送请求信息的网站的字符指针
String wifi_name = "TP-LINK_1CD4";   //定义被连接wifi名字符指针
String wifi_password = "15150757563";//定义被连接wifi密码字符指针

/********配置函数********/
void setup()
{
  Serial.begin(9600); //以波特率9600启动串口
  
  WiFi.mode(WIFI_STA);//设置esp8266为无线终端模式
  
  WiFi.begin(wifi_name,wifi_password);//连接WiFi
  while(WiFi.status() != WL_CONNECTED)//等待连接完成
  {
    delay(100);
  }

  sendClientRequest(); //向目标网站发送客户端请求
}
/********主循环函数********/
void loop()
{
  
}
/********发送客户端请求函数********/
void sendClientRequest()
{
  WiFiClient http_client;//建立客户端操作对象
  
  String http_request = String("GET /") + " HTTP/1.1\r\n" + //建立http请求字符串
                        "Host:" + web + "\r\n" + 
                        "Connection: close\r\n" + 
                        "\r\n";
                        
  if(http_client.connect(web,80))  //连接目标网站，host为被连接网站，80为默认http端口
  {
    http_client.println(http_request);//向目标网站发送http请求
    
    while(http_client.connected() || http_client.available())
    {
      if(http_client.available())
      {
        String payload = http_client.readStringUntil('\n'); //读取服务器发来的信息直到遇到\n停止
        Serial.println(payload);                            //串口打印接收到的信息
      }
    }
    
    http_client.stop();
  }
}
