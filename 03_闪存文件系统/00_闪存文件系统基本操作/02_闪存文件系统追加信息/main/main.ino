#include <FS.h> //导入文件操作系统依赖的库

String file_name = "/Test/note_1.txt"; //被操作文件名字符串
/********配置函数********/
void setup()
{
  SPIFFS.begin();    //启动文件操作系统
 
  if(SPIFFS.exists(file_name)) //逻辑判断是否存在被操作文件
  {
    File date_file = SPIFFS.open(file_name,"a");        //创建文件操作对象，并以追加(append)方式打开文件
    date_file.println("This is a appended information");//追加(println为换行)
    date_file.close();                                  //关闭操作文件对象
  }
}
/********主循环函数********/
void loop()
{
  
}
