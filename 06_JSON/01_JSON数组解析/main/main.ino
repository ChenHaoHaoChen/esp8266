#include <ArduinoJson.h> //引入ArduinoJson解析库

void setup()
{
  Serial.begin(9600);
  
  //带解析json字符
  String json = "[{\"name\":\"taichi-maker\"},{\"website\":\"www.taichi-maker.com\"}]";
  //定义带解析json字符容量 和 定义名为doc的DynamicJsonDocument对象
  const size_t capacity = JSON_ARRAY_SIZE(2) + 2*JSON_OBJECT_SIZE(1) + 60;
  DynamicJsonDocument doc(capacity);
  //利用deserialize函数（反序列化函数）解析json并将结果保存至doc对象中
  deserializeJson(doc,json);
  //将解析结果转换为字符串分别赋值给name_str 和 website_str
  String name_str = doc[0]["name"].as<String>();
  String website_str = doc[1]["website"].as<String>();

  Serial.println(name_str);
  Serial.println(website_str);
}

void loop()
{
  
}
