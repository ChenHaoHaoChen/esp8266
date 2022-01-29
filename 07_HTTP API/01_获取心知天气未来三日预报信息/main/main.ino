#include <ESP8266WiFi.h> //引入ESP8266WiFi库
#include <ArduinoJson.h> //引入ArduinoJso库
//wifi名称与密码
String wifi_ssid = "TP-LINK_1CD4";
String wifi_password = "15150757563";
//心知天气api接口网址与服务器端口
String host = "api.seniverse.com";
int port = 80;
//心知天气获取未来三天天气预报必备信息
String user_key = "S-9a3-Z4sX_eWvo7H";
String location = "Suqian";
String language = "en";
String unit = "c";
String start = "0";
String days = "3";
/********配置函数********/
void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
  connect_wifi();
}
/********主循环函数********/
void loop()
{
  wifi_connect_ok();
  get_weather_forecast();
  delay(3000);
}
/********连接wifi函数********/
void connect_wifi()
{
  WiFi.begin(wifi_ssid,wifi_password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(10);
  }
}
/********检验wifi连接是否成功********/
void wifi_connect_ok()
{
  if(WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(LED_BUILTIN,LOW);
  }
}
void get_weather_forecast()
{
  //https://api.seniverse.com/v3/weather/daily.json?key=S-9a3-Z4sX_eWvo7H&location=beijing&language=zh-Hans&unit=c&start=0&days=5
  String temp = "/v3/weather/daily.json?key=" + user_key + 
                "&location=" + location + "&language=" + language + 
                "&unit=" +  unit + "&start=" + start + "&days=" + days;
  String http_request = "GET " + temp + " HTTP/1.1\r\n" + 
                        "host: " + host + "\r\n" + 
                        "Connection: close\r\n" + 
                        "\r\n";
  WiFiClient http_client;
  if(http_client.connect(host,port))
  {
    http_client.print(http_request);
//    此部分用于接受所有相应内容，用于查看响应体中json，便于在线网站生成解析json代码
//    String data = http_client.readString();
//    Serial.println(data);
    if(http_client.find("\r\n\r\n"))
    {
      String json = http_client.readString();
      parse_json(json);
    }
    http_client.stop();
  }
}
/********解析JSON函数********/
void parse_json(String json)
{
  //ArduinoJson库作者网站自动生成代码，库版本V5
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(3) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 3*JSON_OBJECT_SIZE(14) + 860;
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
  JsonArray& results_0_daily = results_0["daily"];
  JsonObject& results_0_daily_0 = results_0_daily[0];
  const char* results_0_daily_0_date = results_0_daily_0["date"]; // "2022-01-28"
  const char* results_0_daily_0_text_day = results_0_daily_0["text_day"]; // "Overcast"
  const char* results_0_daily_0_code_day = results_0_daily_0["code_day"]; // "9"
  const char* results_0_daily_0_text_night = results_0_daily_0["text_night"]; // "Overcast"
  const char* results_0_daily_0_code_night = results_0_daily_0["code_night"]; // "9"
  const char* results_0_daily_0_high = results_0_daily_0["high"]; // "3"
  const char* results_0_daily_0_low = results_0_daily_0["low"]; // "-1"
  const char* results_0_daily_0_rainfall = results_0_daily_0["rainfall"]; // "0.00"
  const char* results_0_daily_0_precip = results_0_daily_0["precip"]; // "0.00"
  const char* results_0_daily_0_wind_direction = results_0_daily_0["wind_direction"]; // "NE"
  const char* results_0_daily_0_wind_direction_degree = results_0_daily_0["wind_direction_degree"]; // "45"
  const char* results_0_daily_0_wind_speed = results_0_daily_0["wind_speed"]; // "8.4"
  const char* results_0_daily_0_wind_scale = results_0_daily_0["wind_scale"]; // "2"
  const char* results_0_daily_0_humidity = results_0_daily_0["humidity"]; // "54"
  JsonObject& results_0_daily_1 = results_0_daily[1];
  const char* results_0_daily_1_date = results_0_daily_1["date"]; // "2022-01-29"
  const char* results_0_daily_1_text_day = results_0_daily_1["text_day"]; // "Cloudy"
  const char* results_0_daily_1_code_day = results_0_daily_1["code_day"]; // "4"
  const char* results_0_daily_1_text_night = results_0_daily_1["text_night"]; // "Cloudy"
  const char* results_0_daily_1_code_night = results_0_daily_1["code_night"]; // "4"
  const char* results_0_daily_1_high = results_0_daily_1["high"]; // "3"
  const char* results_0_daily_1_low = results_0_daily_1["low"]; // "-2"
  const char* results_0_daily_1_rainfall = results_0_daily_1["rainfall"]; // "0.00"
  const char* results_0_daily_1_precip = results_0_daily_1["precip"]; // "0.00"
  const char* results_0_daily_1_wind_direction = results_0_daily_1["wind_direction"]; // "NE"
  const char* results_0_daily_1_wind_direction_degree = results_0_daily_1["wind_direction_degree"]; // "45"
  const char* results_0_daily_1_wind_speed = results_0_daily_1["wind_speed"]; // "8.4"
  const char* results_0_daily_1_wind_scale = results_0_daily_1["wind_scale"]; // "2"
  const char* results_0_daily_1_humidity = results_0_daily_1["humidity"]; // "52"
  JsonObject& results_0_daily_2 = results_0_daily[2];
  const char* results_0_daily_2_date = results_0_daily_2["date"]; // "2022-01-30"
  const char* results_0_daily_2_text_day = results_0_daily_2["text_day"]; // "Cloudy"
  const char* results_0_daily_2_code_day = results_0_daily_2["code_day"]; // "4"
  const char* results_0_daily_2_text_night = results_0_daily_2["text_night"]; // "Cloudy"
  const char* results_0_daily_2_code_night = results_0_daily_2["code_night"]; // "4"
  const char* results_0_daily_2_high = results_0_daily_2["high"]; // "6"
  const char* results_0_daily_2_low = results_0_daily_2["low"]; // "-3"
  const char* results_0_daily_2_rainfall = results_0_daily_2["rainfall"]; // "0.00"
  const char* results_0_daily_2_precip = results_0_daily_2["precip"]; // "0.00"
  const char* results_0_daily_2_wind_direction = results_0_daily_2["wind_direction"]; // "S"
  const char* results_0_daily_2_wind_direction_degree = results_0_daily_2["wind_direction_degree"]; // "180"
  const char* results_0_daily_2_wind_speed = results_0_daily_2["wind_speed"]; // "3.0"
  const char* results_0_daily_2_wind_scale = results_0_daily_2["wind_scale"]; // "1"
  const char* results_0_daily_2_humidity = results_0_daily_2["humidity"]; // "52"
  const char* results_0_last_update = results_0["last_update"]; // "2022-01-28T08:00:00+08:00"
  /*----------串口输出今天及未来两天天气情况----------*/
  Serial.println(results_0_location_name);   //位置：Suqian
  Serial.println(results_0_location_country);//国家：CN
  Serial.println(results_0_location_path);   //路径：Suqian,Suqian,Jiangsu,China
  //2022.1.28天气情况
  Serial.println("--------------------");
  Serial.println(results_0_daily_0_date);                 //日期：2022-01-28
  Serial.println(results_0_daily_0_text_day);             //白天天气：Overcast
  Serial.println(results_0_daily_0_code_day);             //白天天气码：9
  Serial.println(results_0_daily_0_text_night);           //夜晚天气：Overcast
  Serial.println(results_0_daily_0_code_night);           //夜晚天气码：9 
  Serial.println(results_0_daily_0_high);                 //最高温度：3
  Serial.println(results_0_daily_0_low);                  //最低温度：-1
  Serial.println(results_0_daily_0_rainfall);             //降水量：0.00   （注意：单位为mm）
  Serial.println(results_0_daily_0_precip);               //降水概率：0.00 （注意：单位为%）
  Serial.println(results_0_daily_0_wind_direction);       //风向：NE
  Serial.println(results_0_daily_0_wind_direction_degree);//风向角度：45
  Serial.println(results_0_daily_0_wind_speed);           //风速：8.4   （注意：单位为km/h）
  Serial.println(results_0_daily_0_wind_scale);           //风力等级：2
  Serial.println(results_0_daily_0_humidity);             //相对湿度：54 （注意：单位为%）
  //2022.1.29天气情况
  Serial.println("--------------------");
  Serial.println(results_0_daily_1_date);
  Serial.println(results_0_daily_1_text_day);
  Serial.println(results_0_daily_1_code_day);
  Serial.println(results_0_daily_1_text_night);
  Serial.println(results_0_daily_1_code_night);
  Serial.println(results_0_daily_1_high);
  Serial.println(results_0_daily_1_low);
  Serial.println(results_0_daily_1_rainfall);
  Serial.println(results_0_daily_1_precip);
  Serial.println(results_0_daily_1_wind_direction);
  Serial.println(results_0_daily_1_wind_direction_degree);
  Serial.println(results_0_daily_1_wind_speed);
  Serial.println(results_0_daily_1_wind_scale);
  Serial.println(results_0_daily_1_humidity);
  //2022.1.30天气情况
  Serial.println("--------------------");
  Serial.println(results_0_daily_2_date);
  Serial.println(results_0_daily_2_text_day);
  Serial.println(results_0_daily_2_code_day);
  Serial.println(results_0_daily_2_text_night);
  Serial.println(results_0_daily_2_code_night);
  Serial.println(results_0_daily_2_high);
  Serial.println(results_0_daily_2_low);
  Serial.println(results_0_daily_2_rainfall);
  Serial.println(results_0_daily_2_precip);
  Serial.println(results_0_daily_2_wind_direction);
  Serial.println(results_0_daily_2_wind_direction_degree);
  Serial.println(results_0_daily_2_wind_speed);
  Serial.println(results_0_daily_2_wind_scale);
  Serial.println(results_0_daily_2_humidity);
  //数据更新时间
  Serial.println("--------------------");
  Serial.println(results_0_last_update);
}
