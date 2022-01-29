#include <ArduinoJson.h>

void setup()
{
  Serial.begin(9600);
  /**********************************************************/
  //网站自动解析生成的代码（https://arduinojson.org/v5/assistant/）
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(3) + 130;
  DynamicJsonBuffer jsonBuffer(capacity);
  const char* json = "{\"results\":[{\"location\":{\"name\":\"Beijing\",\"country\":\"CN\"},\"now\":{\"text\":\"Clear\",\"code\":\"1\",\"temperature\":\"3\"},\"last_update\":\"2020-03-01T20:10:00+08:00\"}]}";
  JsonObject& root = jsonBuffer.parseObject(json);
  JsonObject& results_0 = root["results"][0];
  const char* results_0_location_name = results_0["location"]["name"]; // "Beijing"
  const char* results_0_location_country = results_0["location"]["country"]; // "CN"
  JsonObject& results_0_now = results_0["now"];
  const char* results_0_now_text = results_0_now["text"]; // "Clear"
  const char* results_0_now_code = results_0_now["code"]; // "1"
  const char* results_0_now_temperature = results_0_now["temperature"]; // "3"
  const char* results_0_last_update = results_0["last_update"]; // "2020-03-01T20:10:00+08:00"
  /**********************************************************/
  //输出json解析结果
  Serial.println(results_0_location_name);
  Serial.println(results_0_location_country);
  Serial.println(results_0_now_text);
  Serial.println(results_0_now_code);
  Serial.println(results_0_now_temperature);
  Serial.println(results_0_last_update);
}

void loop()
{
  
}
