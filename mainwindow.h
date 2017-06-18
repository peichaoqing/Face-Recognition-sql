#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QUdpSocket>
#include <QImage>
#include <QFile>
//#include<train.h>
#include "sample.h"
#include "recognize.h"
#include "sql.h"
#include "sqlmodel.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void udp_read_message(); // 接收消息
    void on_photo_clicked();

    void on_train_clicked();

    void on_recognize_clicked();

    void on_search_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket *receiver;

    // sample ui
    Sample *sample;
    Recognize *recognize;
    SqlModel *sqlmodel;
};

#endif // MAINWINDOW_H
