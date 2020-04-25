#include "widget.h"
#include "ui_widget.h"
#include<QFile>
#include<QFileDialog>
#include<QFileInfo> //文件信息
#include<QDebug>
#include<QDateTime> //必须要这个头文件。输出时见
#include<QDataStream> //以二进制操作文件
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                  "open","../","TXT(*.txt)");

    if(path.isEmpty() == false)
    {
        QFile file(path);
        bool isOk = file.open(QIODevice::ReadOnly);

        if(isOk == true)
        {
            QString arr;
            while(!file.atEnd())
            {
               arr +=  QString(file.readLine());

            }

            ui->textEdit->setText(arr);

        }

        file.close();

            QFileInfo info(path);
            qDebug() <<"文件名"<<info.fileName();
             qDebug() <<"文件后缀"<<info.suffix();
              qDebug() <<"文件大小"<<info.fileName();
               qDebug() <<"创建文件时间"<<
                    info.created().toString("yyyy-MM-dd hh:mm:ss");
    }



}

void Widget::on_pushButton_2_clicked()
{
    //!获取文件名
   QString filename =  QFileDialog::getOpenFileName(this,"save","../","TXT(*txt)");
    //! 判断文件名是否为空
    if(filename.isEmpty() == false)
    {
        //!不为空则创建对象
        QFile file;
        //!指定文件名
        file.setFileName(filename);
        //! 打开文件
        bool isOk = file.open(QIODevice::WriteOnly);
        if(isOk==true)
        {
            //! 获取编辑框内容
            QString str = ui->textEdit->toPlainText();
            //! 写文件
            //! QString -> QByteArray  @1
            file.write(str.toUtf8());
            //! @2 QString->c++ string ->char*
            //! 通过c++进行中转，在用data()
//            file.write(str.toStdString().data());

//            file.write(str.toLocal8Bit());//转回window本地编码


            //!QString->QByteAray
//            QString buf = "123";
//            QByteArray a = buf.toUtf8(); //中国文
//            a = buf.toLocal8Bit();//转回本地编码

            //!QByteArray->char*
//            char* b = a.data();


        }

        file.close();
    }
}
