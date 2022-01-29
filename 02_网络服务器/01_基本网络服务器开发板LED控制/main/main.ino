#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer esp8266_server(80);//建立ESP8266WebServer对象，对象名称为esp8266_server
                                    //响应http请求端口号为80
                                    //网络服务器标准http端口号为80

char *WiFi_name = "TP-LINK_1CD4";   //被连接WiFi名
char *WiFi_password = "15150757563";//被连接WiFi密码
/********配置函数********/
void setup()
{
  Serial.begin(9600);         //配置串口波特率为9600
  pinMode(LED_BUILTIN,OUTPUT);//设置内置LED端口为输出模式

  WiFi.begin(WiFi_name,WiFi_password);//开始连接WiFi
  while(WiFi.status() != WL_CONNECTED)//等待连接完成
  {
    delay(100);
  }
  Serial.println(WiFi.localIP());     //串口打印esp8266本地IP地址

  esp8266_server.begin();                        //开始启动网页服务
  //设置服务器根目录即"/"，HTTP_GET表示其他终端HTTP协议的请求，并调用handle_root函数
  esp8266_server.on("/",HTTP_GET,handle_root);   
  //设置服务器目录LED"/LED"，HTTP_POST表示其他终端HTTP协议的发送，并调用handle_LED函数
  esp8266_server.on("/LED",HTTP_POST,handle_LED);
  esp8266_server.onNotFound(handle_not_found);   //若没有此网页，则调用handle_not_found函数
}
/********主循环函数********/
void loop()
{
  esp8266_server.handleClient();//时刻处理客户端访问
}
/********处理网页根目录函数********/
void handle_root()
{
  //以html格式发送一段代码
  esp8266_server.send(200,"text/html","<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");
  //200表示成功接受请求并已经完成整个处理过程
}
/********处理LED点亮与熄灭函数*********/
void handle_LED()
{
  digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));//读取当前引脚电平并取反输出
  esp8266_server.sendHeader("Location","/");//跳转回页面根目录
  esp8266_server.send(303);                 //发送完成请求，303表示完成请求
}
/********处理未发现网页函数********/
void handle_not_found()
{
  esp8266_server.send(404,"text/plain","404:Not Found");//以纯文本形式发送404:Not Found
  //404表示客户端端网页请求错误
}
