#include <ESP8266WiFi.h>            //引入ESP8266WiFi库
char *WiFi_name = "TP-LINK_1CD4";   //设置连接WiFi名为TP-LINK_1CD4
char *WiFi_password = "15150757563";//被连接WiFi密码为15150757563
void setup()
{
  Serial.begin(9600);                  //配置串口比特率为9600
  pinMode(LED_BUILTIN,OUTPUT);         //设置LED_BUILTIN引脚为输出模式
  
  WiFi.begin(WiFi_name, WiFi_password);//开始连接WiFi
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(100);
  }
  
  Serial.println(WiFi.localIP());      //打印ESP8266本地IP地址
}
void loop()
{
  if (WiFi.status() == WL_CONNECTED)   //若连接上WiFi，点亮蓝色LED
  {
    digitalWrite(LED_BUILTIN,LOW);
  }
}
