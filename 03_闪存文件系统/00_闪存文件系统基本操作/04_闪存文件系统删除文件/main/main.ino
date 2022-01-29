#include <FS.h> //引入闪存文件系统操作依赖的函数

String file_name = "/Test/note_1.txt";//定义文件名字符串
/********配置函数********/
void setup()
{
  Serial.begin(9600);//启动串口并配置波特率为9600
  SPIFFS.begin();    //启动闪存文件操作系统
  
  if(SPIFFS.remove(file_name)) //删除文件名为file_name的文件
  {                            //并逻辑判断是否成功
    Serial.println("remove sucessfully");//成功删除则输出remove sucessfully
  }
  else
  {
    Serial.println("remove fail");       //失败则输出remove fail
  }
  //注意：按下RST键会输出失败，这是由于程序已经上传后已经执行过一次，再按下RST程序会执行第二次
}
/********主循环函数********/
void loop()
{
  
}
