#ifndef RECOGNIZE_H
#define RECOGNIZE_H

#include <QDialog>

#include<QString>
#include "sql.h"

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

namespace Ui {
class Recognize;
}

class Recognize : public QDialog
{
    Q_OBJECT

public:
    explicit Recognize(QWidget *parent = 0);
    ~Recognize();
	int recong_video();
    int recong_image(char *img);


private slots:
    void on_video_clicked();

    void on_picture_clicked();

    void on_back_clicked();

private:
    Ui::Recognize *ui;
    Sql *sql;
};

#endif // RECOGNIZE_H
