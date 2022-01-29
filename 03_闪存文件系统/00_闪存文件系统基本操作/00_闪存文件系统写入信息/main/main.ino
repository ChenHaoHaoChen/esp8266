#include <FS.h> //引入闪存文件操作依赖的库

String file_name = "/Test/note_1.txt"; //定义文件名字符串
/********配置函数********/
void setup()
{
  Serial.begin(9600);//以波特率为9600启动串口
  
  SPIFFS.format();   //格式化闪存文件系统
                     //Serial Peripheral Interface Flash File System（SPIFFS）
                     //串行外设接口Flash文件系统即闪存文件系统

  if(SPIFFS.begin()) //启动闪存文件系统
  {
    Serial.println("SPIFFS stated");
  }
  else
  {
    Serial.println("SPIFFS fail to start");
  }

  File date_file = SPIFFS.open(file_name,"w");//建立文件对象date_file,闪存文件系统以写方式打开文件。
                                              //如果文件系统没有/taichi-maker/notes.txt文件，此操作将会在文件系统中建立该文件；
                                              //如果文件系统有该文件，则程序将会重新建立该文件，即原有文件信息将会被覆盖。
                                              
  date_file.println("Hello World 2022-1-24");//文件对象写入Hello World 2022-1-24
  date_file.close();                         //关闭文件对象，结束文件操作后应执行此操作
}
/********主循环函数********/
void loop()
{
  
}
