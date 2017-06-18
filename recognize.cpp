#include "recognize.h"
#include "ui_recognize.h"
#include "sql.h"
#include <QDialog>

#include<QString>


#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/core/ocl.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgproc.hpp"
#include"opencv2/flann.hpp"
#include <opencv2/core.hpp>
#include"opencv2/ml.hpp"
#include"opencv2/opencv_modules.hpp"
#include"opencv2/objdetect.hpp"
#include <opencv2/face.hpp>
#include <opencv2/face/facerec.hpp>
#include <string>

#include "MatToQImage.h"

using namespace cv;
using namespace std;
using namespace face;

Recognize::Recognize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Recognize)
{
    ui->setupUi(this);
    sql=new Sql(this);
}

Recognize::~Recognize()
{
    delete ui;
    delete sql;
}


int Recognize::recong_video()
{
	
    int okcnt=0;
    int errcnt=0;
    int thisone;

   // VideoCapture cap(0);    //打开默认摄像头
  //  if (!cap.isOpened())
  //  {
  //      return -1;
  //  }
    Mat frame;  
    Mat edges;  
    Mat gray;  
  
    CascadeClassifier cascade;
    bool stop = false;  
    //训练好的文件名称，放置在可执行文件同目录下  
    cascade.load("/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml");
  
    Ptr<BasicFaceRecognizer> modelPCA = createEigenFaceRecognizer();
    modelPCA->load("MyFacePCAModel.xml");  

      
    while (!stop)  
    {  
        frame=imread("test1.jpg");
        //建立用于存放人脸的向量容器  
        vector<Rect> faces(0);  
  
        cvtColor(frame, gray, CV_BGR2GRAY);  
        //改变图像大小，使用双线性差值  
        //resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);  
        //变换后的图像进行直方图均值化处理  
        equalizeHist(gray, gray);  
  
        cascade.detectMultiScale(gray, faces,  
            1.1, 2, 0  
            //|CV_HAAR_FIND_BIGGEST_OBJECT  
            //|CV_HAAR_DO_ROUGH_SEARCH  
            | CV_HAAR_SCALE_IMAGE,  
            Size(30, 30));  
  
        Mat face;  
        Point text_lb;  
  
        for (size_t i = 0; i < faces.size(); i++)  
        {  
            if (faces[i].height > 0 && faces[i].width > 0)  
            {  
                face = gray(faces[i]);  
                text_lb = Point(faces[i].x, faces[i].y);  
  
                rectangle(frame, faces[i], Scalar(255, 0, 0), 1, 8, 0);  
            }  
        }  
  
        Mat face_test;  
  
        int predictPCA = 0;
        if (face.rows >= 120)  
        {  
            cv::resize(face, face_test, Size(92, 112));
              
        }  
        //Mat face_test_gray;  
        //cvtColor(face_test, face_test_gray, CV_BGR2GRAY);  
  
        if (!face_test.empty())  
        {  
            //测试图像应该是灰度图  
            predictPCA = modelPCA->predict(face_test);  
        }  
  
        cout << predictPCA << endl;  
        if(okcnt==0)
        {
              thisone = predictPCA;
              okcnt++;
        }
        else if(predictPCA == thisone)
        {
              okcnt++;
        }
        if (predictPCA !=  thisone)
        {
            errcnt++;
        }

        if(errcnt==20)
        {
            string name = "no such one";
            putText(frame, name, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));
            thisone=0;
            errcnt=0;
            okcnt=0;
        }
        else if(okcnt==20 && thisone == 41)
        {  
            string name = "CYQ";
            putText(frame, name, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));  
            thisone=0;
            errcnt=0;
            okcnt=0;
        }  
        QImage image;   //图像
        image = MatToQImage(frame);
        //在标签中显示 图像
        ui->label->setPixmap(QPixmap::fromImage(image.rgbSwapped()));
  
      //  imshow("face", frame);
        waitKey(50);
        //if (waitKey(50) >= 0)
        //    stop = true;
    }  
  
    return 0;  
}

int Recognize::recong_image(char *img)
{


    Mat frame;
    Mat edges;
    Mat gray;
    QSqlDatabase db;
    CascadeClassifier cascade;
    bool stop = false;
    //训练好的文件名称，放置在可执行文件同目录下
    cascade.load("/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml");

    Ptr<FaceRecognizer> modelPCA = createEigenFaceRecognizer();
    modelPCA->load("MyFacePCAModel.xml");

    while (!stop)
    {
        //cap >> frame;
        frame = imread(img);
        //建立用于存放人脸的向量容器
        vector<Rect> faces(0);

        cvtColor(frame, gray, CV_BGR2GRAY);
        //改变图像大小，使用双线性差值
        //resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);
        //变换后的图像进行直方图均值化处理
        equalizeHist(gray, gray);

        cascade.detectMultiScale(gray, faces,
            1.1, 2, 0
            //|CV_HAAR_FIND_BIGGEST_OBJECT
            //|CV_HAAR_DO_ROUGH_SEARCH
            | CV_HAAR_SCALE_IMAGE,
            Size(30, 30));

        Mat face;
        Point text_lb;

        for (size_t i = 0; i < faces.size(); i++)
        {
            if (faces[i].height > 0 && faces[i].width > 0)
            {
                face = gray(faces[i]);
                text_lb = Point(faces[i].x, faces[i].y);

                rectangle(frame, faces[i], Scalar(255, 0, 0), 1, 8, 0);
            }
        }

        Mat face_test;

        int predictPCA = 0;
        if (face.rows >= 120)
        {
            cv::resize(face, face_test, Size(92, 112));

        }
        //Mat face_test_gray;
        //cvtColor(face_test, face_test_gray, CV_BGR2GRAY);

        if (!face_test.empty())
        {
            //测试图像应该是灰度图
            predictPCA = modelPCA->predict(face_test);
        }

        cout << "which one : "<<predictPCA << endl;

        if (predictPCA == 41)
        {
            string name = "CYQ";
            putText(frame, name, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));
        }

        imshow("face", frame);
        if (waitKey(0) >= 0)
            stop = true;

        stop = true;  // guojige add
    }

    return 0;
}
void Recognize::on_video_clicked()
{
    recong_video();
}

void Recognize::on_picture_clicked()
{
    char img[]="test1.jpg";
    recong_image(img);
}

void Recognize::on_back_clicked()
{
    this->close();
}
