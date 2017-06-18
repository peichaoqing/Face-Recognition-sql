#include "sample.h"
#include "ui_sample.h"

#include <QDebug>
#include <QFileInfoList>

#include<opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <string>

#include "sql.h"
#include "ui_sql.h"

using namespace std;
using namespace cv;

/** Function Headers */
//void detectAndDisplay(Mat frame);

/** Global variables */
String face_cascade_name = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "/usr/local/share/OpenCV/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;   //¶¨ÒåÈËÁ³·ÖÀàÆ÷
CascadeClassifier eyes_cascade;   //¶¨ÒåÈËÑÛ·ÖÀàÆ÷
String window_name = "Capture - Face detection";

#if 0
void paizhao(int idir)
{
    VideoCapture cap(0);
    int i=1;
    Mat frame;
    char quit;
    while (quit != 'q')
    {
          char key = waitKey(100);
           //cap >> frame;
          cap.read(frame);
           imshow("frame", frame);
           string filename = format("pic/s%d/%d.pgm", idir, i); //which dir index
            //cout << filename << endl;
             //imwrite(filename, frame);
                switch (key)
                {
                case 's':
                    roi(frame, filename, i++);
                    break;
                case'p':
                    imwrite(filename, frame);
                    imshow("photo", frame);
                    waitKey(500);
                    destroyWindow("photo");
                    i++;
                    break;
                case 'q':
                    quit = key;
                    break;
                default:
                    break;
                }
            }
    cap.release();

}

#endif

void Sample::roi(Mat &img, string &path,int index)
{
            //static int i=1;

            std::vector<Rect> faces;
            Mat img_gray;

            cvtColor(img, img_gray, COLOR_BGR2GRAY);
            equalizeHist(img_gray, img_gray);

            //-- Detect faces
            String face_cascade_name = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";

             if (!face_cascade.load(face_cascade_name)){ printf("--(!)Error loading face cascade\n"); return ; };
            //face_cascade.detectMultiScale(img_gray, faces, 1.1, 3, CV_HAAR_DO_ROUGH_SEARCH, Size(50, 50));
            face_cascade.detectMultiScale(img_gray, faces, 1.1, 3, CV_HAAR_DO_ROUGH_SEARCH);

            for (size_t j = 0; j < faces.size(); j++)
            {
                Mat faceROI = img(faces[j]);
                Mat MyFace;
                if (faceROI.cols > 100)
                {
                    cv::resize(faceROI, MyFace, Size(92, 112));
                    //string  str = format("%s/%d.jpg", path.c_str(),index);
                    imwrite(path, MyFace);
                    imshow("ii", MyFace);
                }
                waitKey(10);
                index++;
            }
}

Sample::Sample(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sample)
{
    ui->setupUi(this);
    sql=new Sql(this);

}

Sample::~Sample()
{
    delete ui;
    delete sql;
}

void Sample::on_pushButton_clicked()
{
    dir = new QDir("./photo");
    QString name =ui->lineEdit->text();
    qDebug() << ui->lineEdit->text();//name

    QFileInfoList filelist = dir->entryInfoList();
    idex = filelist.size()-2+1;//id

    char buff[32];
    sprintf(buff, "s%d", idex);
    dir->mkdir(buff);

   //QString photopath = dir->absolutePath()+"/"+buff;
    photoallpath = dir->absolutePath();  //lujing
    photopath = dir->absolutePath()+"/"+buff;
     this->ui->lineEdit->clear();
    qDebug()<< photopath;
     sql->c_s((filelist.size()-2+1),name,getPath());
     qDebug() <<name;
     qDebug()<<sql->get_id();
      qDebug()<<sql->get_name();
       qDebug()<<sql->get_path();
     sql->show();

     sql->exec();
   // sql->insert((filelist.size()-2+1),ui->lineEdit->text(),getPath());

   // delete dir;
   // this->close();

}

QString Sample::getPath()
{
    return photoallpath;
}


void Sample::on_picture_clicked()
{
    Mat frame;
    int static i=1;
    frame=imread("test1.jpg");
    string filename = format("photo/s%d/%d.jpg",idex,i); //which dir index

     roi(frame, filename, i++);

}

void Sample::on_back_clicked()
{
    delete dir;
    this->close();
}
