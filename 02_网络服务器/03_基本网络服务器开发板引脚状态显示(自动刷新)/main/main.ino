#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#define button_pin D3 //宏定义

ESP8266WebServer esp8266_server(80);//建立ESP8266webServer对象  
                                    //响应HTTP请求端口为80
char *WiFi_name = "TP-LINK_1CD4";   //被连接WiFi名 
char *WiFi_password = "15150757563";//被连接WiFi密码  
bool button_status;                 //按键状态
/********配置函数********/
void setup()
{
  Serial.begin(9600);              //串口初始化
  pinMode(LED_BUILTIN,OUTPUT);     //蓝色LED引脚设置为输出模式
  pinMode(button_pin,INPUT_PULLUP);//设置button_pin引脚为输入模式且打开上拉电阻
  
  WiFi.begin(WiFi_name,WiFi_password);//连接WiFi
  while(WiFi.status() != WL_CONNECTED)//等待连接完成
  {
    delay(100);
  }
  digitalWrite(LED_BUILTIN,LOW); //点亮LED,表示连接成功  
  Serial.println(WiFi.localIP());//串口输出esp8266本地IP地址
 
  esp8266_server.begin();                     //启动esp8266网络服务器 
  esp8266_server.on("/",handle_root);         //设置服务器根目录"/"，并调用handle_root函数  
  esp8266_server.onNotFound(handle_not_found);//若没有此网页则调用handle_not_found函数
}
/********主循环函数********/
void loop()
{
  esp8266_server.handleClient();          //时刻处理客户端访问
  button_status = digitalRead(button_pin);//读取button_pin引脚(D3)状态 
}
/********处理网页根目录函数********/  
void handle_root()
{
  //成功接受请求，则以html形式发送函数send_html返回字符串
  esp8266_server.send(200,"text/html",send_html(button_status));
  //200表示成功接受请求并已经完成整个处理过程  
}
/********发送html代码函数********/
String send_html(bool button_status_temp)
{
  String html_code = "<!DOCTYPE html> <html>\n";
  //content中可设置网页刷新率，当前1s刷新一次
  html_code +="<head><meta http-equiv='refresh' content='1'/>\n";
  html_code +="<title>ESP8266 Butoon State</title>\n";
  html_code +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  html_code +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  html_code +="</style>\n";
  html_code +="</head>\n";
  html_code +="<body>\n";
  html_code +="<h1>ESP8266 BUTTON STATE</h1>\n";
  //逻辑判断D3引脚当前电平状态
  if(button_status_temp == HIGH)
  {
    html_code +="<p>Button Status: HIGH</p>\n";
  }
  else
  {
    html_code +="<p>Button Status: LOW</p>\n";
  }

  return html_code; //返回html代码
}
/********处理未发现网页函数********/
void handle_not_found()
{
  //客户端网页请求错误，则以纯文本形式发送字符404: Not Found  
  esp8266_server.send(404,"text/plain","404: Not Found");
  //404表示客户端网页请求错误 
}
