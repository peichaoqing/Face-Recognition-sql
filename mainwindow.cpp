#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include<train.h>
#include "recognize.h"
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
using namespace face;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    receiver = new QUdpSocket(this);
    receiver->bind(QHostAddress::Any,
                   5555);
    // 信号和槽
    connect(receiver, SIGNAL(readyRead()),
            this, SLOT(udp_read_message())
            );
    sample = new Sample(this);
    recognize=new Recognize(this);
    sqlmodel = new SqlModel(this);
}
MainWindow::~MainWindow()
{
    delete receiver;
    delete ui;
    delete sample;
    delete  recognize;
    delete  sqlmodel;

}
void MainWindow::udp_read_message()
{
    //返回数据包大小
    qint64 number =receiver->pendingDatagramSize();
    QByteArray buffer;  //定义数组
    buffer.resize(number);
    //从socket读number字节，放到 buff.data()
    receiver->readDatagram(buffer.data(),number);
    // 创建文件保存图像
    QFile file("test1.jpg");
    file.open(QIODevice::WriteOnly);
    file.write(buffer);
    file.close();

    QImage image;   //图像
    image = QImage("test1.jpg");
    //在标签中显示 图像
    ui->label->setPixmap(QPixmap::fromImage(image.rgbSwapped()));
}



void MainWindow::on_photo_clicked()
{
    sample->show();
    sample->exec();
    qDebug() << "MainWindow:"<<sample->getPath();
}

void MainWindow::on_train_clicked()
{
    Train mytrainmodel(sample->getPath());
    mytrainmodel.create_csv_file();
    mytrainmodel.train();

}

void MainWindow::on_recognize_clicked()
{
    recognize->show();
    recognize->exec();
}


void MainWindow::on_search_clicked()
{
    sqlmodel->show();
    sqlmodel->exec();
}
