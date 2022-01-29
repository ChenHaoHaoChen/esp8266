#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer esp8266_server(80);//建立ESP8266WebServer对象，对象名称为esp8266_server
                                    //响应http请求端口号为80
                                    //网络服务器标准http端口号为80

char *WiFi_name = "TP-LINK_1CD4";   //被连接WiFi名称
char *WiFi_password = "15150757563";//被连接WiFi密码
/********配置函数********/
void setup()
{
      pinMode(LED_BUILTIN,OUTPUT);//配置内置LED引脚为输出模式
      Serial.begin(9600);         //配置串口波特率为9600
       
      WiFi.begin(WiFi_name, WiFi_password);//开始连接WiFi
      
      while(WiFi.status() != WL_CONNECTED) //等待连接完成
      {
        delay(100);
      }
      digitalWrite(LED_BUILTIN,LOW);
      
      Serial.println(WiFi.localIP());      //串口打印esp8266本地IP地址

      /*------启动网络服务程序------*/     
      esp8266_server.begin();                     //开始启动网络服务器
      esp8266_server.on("/", handle_root);        //首页显示，调用handle_root函数（/：为首页的意思）
      esp8266_server.onNotFound(handle_not_found);//若没有此网页，则调用handle_not_found函数
}
/********循环函数********/
void loop()
{
  esp8266_server.handleClient();//处理http服务器访问
}
/********处理首页访问函数********/
void handle_root()
{
  //成功接受请求后，以纯文本方式发送字符 Hello From ESP8266 and ChenHao
  esp8266_server.send(200, "text/plain", "Hello From ESP8266 and ChenHao");
  //200表示成功接受请求并已经完成整个处理过程
}
/********其他页访问处理函数********/
void handle_not_found()
{ 
  //客服端网络服务请求错误，并以纯文本形式发送字符 404: Not Found
  esp8266_server.send(404, "text/plain", "404: Not Found");
  //404表示客户端网页请求错误
}
