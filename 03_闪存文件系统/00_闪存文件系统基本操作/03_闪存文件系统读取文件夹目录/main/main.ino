#include <FS.h> //引入闪存操作系统依赖的库

String folder_name = "/Test"; //定义文件夹名的字符串

void setup()
{
  Serial.begin(9600); //初始化串口并配置波特率为9600
  SPIFFS.begin();     //初始化打开闪存文件操作系统

  Dir dir = SPIFFS.openDir(folder_name);//定义文件目录对象，并打开文件目录folder_name
  while(dir.next()) //检查目录中是否由下一个文件                  
  {
    Serial.println(dir.fileName()); //通过串口输出文件名
  }
}

void loop()
{
  
}
