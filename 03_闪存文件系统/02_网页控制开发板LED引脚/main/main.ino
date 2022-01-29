#include <ESP8266WiFi.h>      //引入连接WiFi库
#include <ESP8266WebServer.h> //引入网络服务器库
#include <FS.h>               //引入闪存文件操作系统库

ESP8266WebServer esp8266_server(80); //建立网络ESP8266WebServer对象，端口号默认为80
char *WiFi_name = "TP-LINK_1CD4";    //被连接WiFi名称
char *WiFi_password = "15150757563"; //被连接WiFi密码

/********配置函数********/
void setup()
{
  //启动串口并配置波特率为9600
  Serial.begin(9600);
  //启动闪存文件操作系统
  SPIFFS.begin();
  //设置引脚LED_BUILTIN为输出模式
  pinMode(LED_BUILTIN,OUTPUT);
  //连接WiFi
  WiFi.begin(WiFi_name,WiFi_password);
  while(WiFi.status() != WL_CONNECTED)//等待连接完成
  {
    delay(100);
  }
  Serial.println(WiFi.localIP());     //串口输出esp8266本地IP地址
  //启动esp8266网络服务
  esp8266_server.begin();
  esp8266_server.on("/LED-Control",handle_LED_control);//处理网页/LED请求                        
  esp8266_server.onNotFound(handle_user_request);      //处理其他请求
}

/********主循环函数********/
void loop()
{
  esp8266_server.handleClient();//时刻处理用户请求
}
/********处理LED控制函数********/
void handle_LED_control()
{
  digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));//控制LED_BUILTIN引脚电平取反
  esp8266_server.sendHeader("Location","/LED.html");  //跳转位置，位置为/LED.html(即刷新当前页)
  esp8266_server.send(303);                           //发送完成跳转
}

/********处理用户HTTP请求函数********/
void handle_user_request()
{
  //获取用户请求网址
  String web_address = esp8266_server.uri();
  //调用handle_file_read对文件进行处理
  bool file_read_ok = handle_file_read(web_address);
  //逻辑判断是否由该文件，若无网页展示 404: Not Found
  if(!file_read_ok)
  {
    esp8266_server.send(404,"text/plain","404: Not Found");
  }
}

/********处理文件函数********/
bool handle_file_read(String file_path)
{
  //若网址为/(即首页)，则修改网址为/index.html
  if(file_path.endsWith("/")) //endsWith函数即判断改字符串是否以 / 结尾
  {
    file_path = "/index.html";
  }
  //调用get_file_type函数获取文件格式
  String file_type = get_file_type(file_path);
  //将文件发送给网页
  if(SPIFFS.exists(file_path)) //逻辑判断是否存在该文件路径
  {
    File file = SPIFFS.open(file_path,"r");   //以读方式打开改路径文件
    esp8266_server.streamFile(file,file_type);//发送文件以及文件类型给网页
    file.close();                             //关闭文件
    return true;                              //返回true
  }
  return false;                               //返回false
}

/********获取文件类型函数********/
String get_file_type(String file_name)
{
  if (file_name.endsWith(".html")) return "text/html";
  else if(file_name.endsWith(".css")) return "text/css";
  else if(file_name.endsWith(".js")) return "application/javascript";
  else if(file_name.endsWith(".jpg")) return "image/jpeg";
  else if(file_name.endsWith(".png")) return "image/png";
  else if(file_name.endsWith(".gif")) return "image/gif";
  else if(file_name.endsWith(".ico")) return "image/x-icon";
  else return "text/plain";
}
