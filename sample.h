#ifndef SAMPLE_H
#define SAMPLE_H

#include <QDialog>
#include <QDir>

#include<opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include "sql.h"
using namespace std;
using namespace cv;
namespace Ui {
class Sample;
}

class Sample : public QDialog
{
    Q_OBJECT

public:
    explicit Sample(QWidget *parent = 0);
    ~Sample();
    QString getPath();
    void roi(Mat &img,string  &path,int index);

private slots:
    void on_pushButton_clicked();


    void on_picture_clicked();

    void on_back_clicked();

private:
    Ui::Sample *ui;
    QDir *dir;
    QString photopath;
    QString photoallpath;
    int idex;
    Sql *sql;

};

#endif // SAMPLE_H
