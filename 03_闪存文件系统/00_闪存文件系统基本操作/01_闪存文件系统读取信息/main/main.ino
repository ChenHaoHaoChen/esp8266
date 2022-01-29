#include <FS.h> //引入闪存文件操作依赖的库

String file_name = "/Test/note_1.txt"; //定义文件名字符串
/********配置函数********/
void setup()
{
  Serial.begin(9600);//配置串口波特率为9600
  SPIFFS.begin();    //启动闪存文件系统

  if(SPIFFS.exists(file_name)) //判断该文件是否存在
  {
    File date_file = SPIFFS.open(file_name,"r");//定义文件对象，并以读方式打开file_name
    for(int i=0; i < date_file.size(); i++)     //循环读取文件中信息
    {
      Serial.print((char)date_file.read()); //转换为字符并通过串口输出
                                            //如不加char否则输出字符对应ASCII码
    }
    date_file.close(); //关闭操作文件
  }
}
/********主循环函数********/
void loop()
{
  
}
