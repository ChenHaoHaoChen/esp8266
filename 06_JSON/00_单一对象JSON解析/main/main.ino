#include <ArduinoJson.h>  //引入ArduinoJson解析库

void setup()
{
   Serial.begin(9600);
   
   //定义带解析json字符
   String json = "{\"name\":\"chenhao\",\"age\":21}";
   //定义带解析的json字符的容量 和 建立对象名为doc的DynamicJsonDocument对象
   const size_t capacity = JSON_OBJECT_SIZE(2) + 30; //带解析json有两个名值对，且需要预留30空间裕量（裕量由...确定）
   DynamicJsonDocument doc(capacity);
   //实用deserializeJson函数对json进行解析，解析结果保存至doc对象中
   deserializeJson(doc,json);
   //分别定义字符型与整型接受解析过的数据
   String name_str = doc["name"].as<String>();//将json中名为name中的值转换为字符串型并赋值给name_str
   int age_int = doc["age"].as<int>();        //将json中名为age中的值转换为整并赋值给age_int

   Serial.print(name_str);
   Serial.print(age_int);
}

void loop()
{
  
}
