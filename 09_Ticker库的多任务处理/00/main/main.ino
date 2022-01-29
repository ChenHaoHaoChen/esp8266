#include <Ticker.h> //引入Ticker库
Ticker ticker; //建立Ticker对象

void setup()
{
  Serial.begin(9600);         //初始化串口
  pinMode(LED_BUILTIN,OUTPUT);//设置LED为输出模式
  
  ticker.attach(1,say_hi);    //每间隔1s执行say_hi函数
  //ticker.attach(1,say_hi,10); //每间隔1s执行say_hi函数，执行10次
}
void loop()
{
  //呼吸灯
  for(int i=0;i<1024;i++)
  {
    analogWrite(LED_BUILTIN,i);
    delay(1);
  }
  for(int i=1023;i>-1;i--)
  {
    analogWrite(LED_BUILTIN,i);
    delay(1);
  }
}

void say_hi()
{
  static int count = 0;
  Serial.print(count);
  Serial.println("hi");
  count++;
}
//void say_hi(int a)
//{
//  static int count = 0;
//  Serial.print(count);
//  Serial.println("hi");
//  count++;
//  if(count == a)
//  {
//    ticker.detach(); //停止ticker对象调用say_hi函数
//  }
//}
