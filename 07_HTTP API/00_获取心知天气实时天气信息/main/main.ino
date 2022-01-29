#include <ESP8266WiFi.h> //引入ESP8266WiFi库
#include <ArduinoJson.h> //引入ArduinoJson库
//wifi名与wifi密码
String wifi_ssid = "TP-LINK_1CD4";
String wifi_password = "15150757563";
//心知天气api接口
String host = "api.seniverse.com";
int port = 80;
//心知天气获取天气必备
String user_key = "S-9a3-Z4sX_eWvo7H"; //私钥
String city = "Suqian"; //城市：宿迁
String language = "en"; //语言：英语
String unit = "c";      //温度单位：摄氏度
/********配置函数********/
void setup()
{
  Serial.begin(9600);         //初始化串口
  pinMode(LED_BUILTIN,OUTPUT);//设置LED引脚为输出模式
  connect_wifi();             //连接wifi
}
/********主循环函数********/
void loop()
{
  wifi_ok_LED();     //检测esp8266是否连接wifi，若连接点亮LED
  get_now_weather();//获取当前天气状况
  delay(3000);   //延时3s，免费版心知天气，访问频率：20次/分
}
/********连接wifi函数********/
void connect_wifi()
{
  WiFi.begin(wifi_ssid,wifi_password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(100);
  }
}
/********wifi连接，LED点亮函数********/
void wifi_ok_LED()
{
  if(WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(LED_BUILTIN,LOW);
  }
}
/********获取天气函数********/
void get_now_weather()
{
  String temp = "/v3/weather/now.json?key=" + user_key + "&location=" + city + "&language=" +language + "&unit=" + unit;
  String http_request = "GET " + temp + " HTTP/1.1\r\n" + //http请求
                        "Host: " + host + "\r\n" + 
                        "Connection: close\r\n" + 
                        "\r\n";
  WiFiClient http_client; //建立WiFiClient对象
  if(http_client.connect(host,port)) //连接心知天气api，成功连接返回1
  {
    http_client.print(http_request); //发送http请求
//    此部分用于接受所有相应内容，用于查看响应体中json，便于在线网站生成解析json代码
//    String data = http_client.readString();
//    Serial.println(data);
    if(http_client.find("\r\n\r\n")) //寻找"\r\n\r\n"
    {
      String json = http_client.readString(); //读取http响应中的json数据
      parse_json(json);                       //调用json解析函数，并串口输出解析结果
    }
    http_client.stop(); //断开与服务器连接
  }
}
/********json解析函数********/
void parse_json(String json)
{
  /*以下代码为ArduinoJson库作者的在线网站（https://arduinojson.org/v5/assistant/）自动生成解析json代码，注意：这里实用json库为V5版本*/
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 240;
  DynamicJsonBuffer jsonBuffer(capacity);
  JsonObject& root = jsonBuffer.parseObject(json);
  JsonObject& results_0 = root["results"][0];
  JsonObject& results_0_location = results_0["location"];
  const char* results_0_location_id = results_0_location["id"]; // "WWH1780CEFBR"
  const char* results_0_location_name = results_0_location["name"]; // "Suqian"
  const char* results_0_location_country = results_0_location["country"]; // "CN"
  const char* results_0_location_path = results_0_location["path"]; // "Suqian,Suqian,Jiangsu,China"
  const char* results_0_location_timezone = results_0_location["timezone"]; // "Asia/Shanghai"
  const char* results_0_location_timezone_offset = results_0_location["timezone_offset"]; // "+08:00"
  JsonObject& results_0_now = results_0["now"];
  const char* results_0_now_text = results_0_now["text"]; // "Haze"
  const char* results_0_now_code = results_0_now["code"]; // "31"
  const char* results_0_now_temperature = results_0_now["temperature"]; // "4"
  const char* results_0_last_update = results_0["last_update"]; // "2022-01-27T16:04:05+08:00"
  /*以上代码为ArduinoJson库作者的在线网站（https://arduinojson.org/v5/assistant/）自动生成解析json代码，注意：这里实用json库为V5版本*/

  //串口输出解析结果
  Serial.println(results_0_location_name);   //城市：Suqian
  Serial.println(results_0_location_country);//国家：CN
  Serial.println(results_0_location_path);   //路径：Suqian,Suqian,Jiangsu,China
  Serial.println(results_0_now_text);        //天气：Clundy
  Serial.println(results_0_now_code);        //对应天气码：4
  Serial.println(results_0_now_temperature); //摄氏温度：4
  Serial.println(results_0_last_update);     //上一次更新时间：2022-01-27T16:43:16+08:00

}
