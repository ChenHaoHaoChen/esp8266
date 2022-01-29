#include <ESP8266WiFi.h> //引入esp8266WiFi库
char *WiFi_name = "Test_chenhao"; //设置WiFi名为Test_chenhao
char *WiFi_password = "12345678"; //设置WiFi密码为12345678，若不设置密码""内不填任何信息即可
void setup()
{
  WiFi.softAP(WiFi_name, WiFi_password); //启动无线接入点模式
  Serial.begin(9600);             //配置串口波特率为9600
  Serial.println(WiFi.softAPIP());//打印esp8266所建立WiFi局域网的默认网关IP地址
                                  //程序下载完成后按下板子上RST复位按键即可在串口监视器中收到IP地址
}

void loop()
{
  
}
  
