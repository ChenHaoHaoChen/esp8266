#include <ESP8266WiFi.h> //引入esp8266wifi库

String web = "www.example.com";      //连接的网站
String wifi_name = "TP-LINK_1CD4";   //被连接wifi名
String wifi_password = "15150757563";//被连接wifi密码
/********配置函数********/
void setup()
{
  Serial.begin(9600); //启动串口并配置波特率为9600

  WiFi.mode(WIFI_STA);//设置wifi工作模式为无线终端模式
  WiFi.begin(wifi_name,wifi_password);//连接wifi
  while(WiFi.status() != WL_CONNECTED)//等待连接完成
  {
    delay(100);
  }

  sendClientRequest(); //发送客户端请求
}
/********主循环函数********/
void loop()
{
  
}
/********向目标网站发送客户端请求函数********/
void sendClientRequest()
{
  WiFiClient http_client; //定义WiFiClient对象

  String http_request = String("GET /") + " HTTP/1.1\r\n" + //建立http请求字符串
                        "Host:" + web + "\r\n" + 
                        "Connection: close\r\n" + 
                        "\r\n";

  if(http_client.connect(web,80))   //连接目标网站，若成功则返回1否则返回0
  {
    http_client.print(http_request);//向目标网站发送http请求
    //循环接受服务器发来的数据信息
    while(http_client.connected() || http_client.available()) 
    {
      if(http_client.available())
      {
        String payload = http_client.readStringUntil('\n'); //接受目标网站发来的数据信息，知道遇到‘\n’
        Serial.println(payload);                            //串口输出接收到的数据
      }
    }
  }
  
  http_client.stop(); //停止esp8266连接服务器，即断开esp8266与服务器的连接
}
