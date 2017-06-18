#include "train.h"
#include<QProcess>




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

using namespace cv;  
using namespace std;  
using namespace face;
Train::Train()
{

}

Train::Train(QString path)
{
    this->path=path;
}
void Train::create_csv_file()
{
    char buff[1024];
    sprintf(buff,"python create_csv.py %s > train.txt",path.toLatin1().data());
    system(buff);
#if 0
    QString cmd;
    cmd="python create_csv.py";
    cmd+=this->path;
    cmd+=" ";
    cmd+="> train.txt";
    QProcess program;
    program.start(cmd);
#endif


}
static void read_csv(const string  &filename, vector<Mat>  &images, vector<int> &labels, char separator = ';')
{
    std::ifstream file(filename.c_str(), ifstream::in);  
    if (!file) {  
        string error_message = "No valid input file was given, please check the given filename.";  
        CV_Error(CV_StsBadArg, error_message);  
    }  
    string line, path, classlabel;  
    while (getline(file, line)) {  
        stringstream liness(line);  
        getline(liness, path, separator);  
        getline(liness, classlabel);  
        if (!path.empty() && !classlabel.empty()) {  
            images.push_back(imread(path, 0));  
            labels.push_back(atoi(classlabel.c_str()));  
        }  
    }  
}  
  
  
int Train:: train()
{  
  
    //读取你的CSV文件路径.  
    //string fn_csv = string(argv[1]);  
    string fn_csv = "train.txt";
  
    // 2个容器来存放图像数据和对应的标签  
    vector<Mat> images;  
    vector<int> labels;  
    // 读取数据. 如果文件不合法就会出错  
    // 输入的文件名已经有了.  
    try  
    {  
        read_csv(fn_csv, images, labels);
    }  
    catch (cv::Exception& e)  
    {  
        cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;  
        // 文件有问题，我们啥也做不了了，退出了  
        exit(1);  
    }  
    // 如果没有读取到足够图片，也退出.  
    if (images.size() <= 1) {  
        string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";  
        CV_Error(CV_StsError, error_message);  
    }  
    std::cout << "images:"<<images.size()<<endl;
    std::cout<<"lables:"<<labels.size()<<endl;
  
    // 下面的几行代码仅仅是从你的数据集中移除最后一张图片  
    //[gm:自然这里需要根据自己的需要修改，他这里简化了很多问题]  
    Mat testSample = images[images.size() - 1];  
    int testLabel = labels[labels.size() - 1];  
    std::cout<<"testSample:"<<testSample.size()<<endl;
    std::cout<<"testLabel:"<<testLabel<<endl;
   // images.pop_back();
   // labels.pop_back();
    // 下面几行创建了一个特征脸模型用于人脸识别，  
    // 通过CSV文件读取的图像和标签训练它。  
    // T这里是一个完整的PCA变换  
    //如果你只想保留10个主成分，使用如下代码  
    //      cv::createEigenFaceRecognizer(10);  
    //  
    // 如果你还希望使用置信度阈值来初始化，使用以下语句：  
    //      cv::createEigenFaceRecognizer(10, 123.0);  
    //  
    // 如果你使用所有特征并且使用一个阈值，使用以下语句：  
    //      cv::createEigenFaceRecognizer(0, 123.0);  
      
//    Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
//    model->train(images, labels);
//    model->save("MyFacePCAModel.xml");
  
//    Ptr<FaceRecognizer> model1 = createFisherFaceRecognizer();
//    model1->train(images, labels);
//    model1->save("MyFaceFisherModel.xml");
  
//    Ptr<FaceRecognizer> model2 = createLBPHFaceRecognizer();
//    model2->train(images, labels);
//    model2->save("MyFaceLBPHModel.xml");


    Ptr<BasicFaceRecognizer> model = createEigenFaceRecognizer();
    model->train(images, labels);
    model->save("MyFacePCAModel.xml");

    Ptr<BasicFaceRecognizer> model1 = createFisherFaceRecognizer();
    model1->train(images, labels);
    model1->save("MyFaceFisherModel.xml");

    Ptr<LBPHFaceRecognizer> model2 = createLBPHFaceRecognizer();
    model2->train(images, labels);
    model2->save("MyFaceLBPHModel.xml");
  
    // 下面对测试图像进行预测，predictedLabel是预测标签结果  
    int predictedLabel = model->predict(testSample);  
    int predictedLabel1 = model1->predict(testSample);  
    int predictedLabel2 = model2->predict(testSample);  
  
    // 还有一种调用方式，可以获取结果同时得到阈值:  
    //      int predictedLabel = -1;  
    //      double confidence = 0.0;  
    //      model->predict(testSample, predictedLabel, confidence);  
      
    string result_message = format("Predicted class = %d / Actual class = %d.", predictedLabel, testLabel);  
    string result_message1 = format("Predicted class = %d / Actual class = %d.", predictedLabel1, testLabel);  
    string result_message2 = format("Predicted class = %d / Actual class = %d.", predictedLabel2, testLabel);  
    cout << result_message << endl;  
    cout << result_message1 << endl;  
    cout << result_message2 << endl;  
  
    waitKey(0);  
    return 0;  
}  
