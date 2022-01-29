#include <ESP8266WiFi.h> //引入ESP8266WiFi库
#include <ArduinoJson.h> //引入ArduinoJson库
//所连接wifi名称与密码
String wifi_ssid = "TP-LINK_1CD4";
String wifi_password = "15150757563";
//心知天气qpi接口与端口
String host = "api.seniverse.com";
int port = 80;
//获取生活指数必备信息
String user_key = "S-9a3-Z4sX_eWvo7H";
String location = "Suqian";
String language = "en";
/********配置函数********/
void setup()
{
  Serial.begin(9600);         //串口初始化波特率为9600
  pinMode(LED_BUILTIN,OUTPUT);//设置LED引脚为输出模式
  wifi_connect();             //连接wifi
}
/********主循环函数********/
void loop()
{
  wifi_connect_ok();//检测WiFi是否连接成功，若连接成功打开蓝色LED
  get_life_index(); //获取实时生活指数
  delay(3000);      //延时3s，心知天气免费用户请求频率限制：20次/分
}
/********连接WiFi********/
void wifi_connect()
{
  WiFi.begin(wifi_ssid,wifi_password);//连接wifi
  while(WiFi.status() != WL_CONNECTED)//等待连接完成
  {
    delay(10);
  }
}
/********检验wifi是否连接成功********/
void wifi_connect_ok()
{
  //若连接成功。打开LED指示灯
  if(WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(LED_BUILTIN,LOW);
  }
}
/********获取实时生活指数********/
void get_life_index()
{
  //获取生活指数网址：https://api.seniverse.com/v3/life/suggestion.json?key=S-9a3-Z4sX_eWvo7H&location=shanghai&language=zh-Hans
  String temp = "/v3/life/suggestion.json?key=" + user_key + "&location=" + location + "&language=" + language;
  String http_request = "GET " + temp + " HTTP/1.1\r\n" + //http请求
                        "host: " + host + "\r\n" + 
                        "Connection: close\r\n" + 
                        "\r\n";
  WiFiClient http_client; //建立WiFiClient对象
  if(http_client.connect(host,port)) //连接服务器，若成功连接返回真，否则返回假
  {
    http_client.print(http_request); //发送http请求
//    此部分用于接受所有相应内容，用于查看响应体中json，便于在线网站生成解析json代码
//    String data = http_client.readString();
//    Serial.println(data);
    if(http_client.find("\r\n\r\n")) //寻找响应体部分
    {
      String json = http_client.readString(); //读取响应体json
      parse_json(json);                       //调用json解析函数
    }
    http_client.stop(); //断开与服务器连接
  }
}
/********解析json********/
void parse_json(String json)
{
  /*----------以下为Arduinoson库作者的网站生成的自动解析JSON代码，版本V5----------*/
  //https://arduinojson.org/v5/assistant/
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 6*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 2*JSON_OBJECT_SIZE(6) + 400;
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
  JsonObject& results_0_suggestion = results_0["suggestion"];
  const char* results_0_suggestion_car_washing_brief = results_0_suggestion["car_washing"]["brief"]; // "Good"
  const char* results_0_suggestion_dressing_brief = results_0_suggestion["dressing"]["brief"]; // "Cold"
  const char* results_0_suggestion_flu_brief = results_0_suggestion["flu"]["brief"]; // "Probably"
  const char* results_0_suggestion_sport_brief = results_0_suggestion["sport"]["brief"]; // "Not Good"
  const char* results_0_suggestion_travel_brief = results_0_suggestion["travel"]["brief"]; // "Good"
  const char* results_0_suggestion_uv_brief = results_0_suggestion["uv"]["brief"]; // "Very Low"
  const char* results_0_last_update = results_0["last_update"]; // "2022-01-29T08:23:04+08:00"
  /*----------以上为Arduinoson库作者的网站生成的自动解析JSON代码，版本V5----------*/
  //串口输出实时生活指数
  Serial.println(results_0_location_name);   //位置：Suqian
  Serial.println(results_0_location_country);//国家：CN
  Serial.println(results_0_location_path);   //路径：Suqian,Suqian,Jiangsu,China
  Serial.println("--------------------");
  Serial.println(results_0_suggestion_car_washing_brief);//洗车概要：Good
  Serial.println(results_0_suggestion_dressing_brief);   //穿衣概要：Cold
  Serial.println(results_0_suggestion_flu_brief);        //流感概要：Probably
  Serial.println(results_0_suggestion_sport_brief);      //运动概要：Not Good
  Serial.println(results_0_suggestion_travel_brief);     //旅游概要：Good
  Serial.println(results_0_suggestion_uv_brief);         //紫外线概要：Very Low
  Serial.println(results_0_last_update);                 //上次更新时间：2022-01-29T08:23:04+08:00
}
