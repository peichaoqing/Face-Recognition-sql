#ifndef TRAIN_H
#define TRAIN_H
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
using namespace cv;
using namespace std;
using namespace face;

class Train
{
public:
    Train();
    Train(QString path);
    void create_csv_file();
    int train();

private:
    QString path;
     //static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';');
};

#endif // TRAIN_H
