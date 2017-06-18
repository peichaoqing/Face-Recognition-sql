#include "sqlmodel.h"
#include "ui_sqlmodel.h"

SqlModel::SqlModel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SqlModel)
{
    ui->setupUi(this);
}

SqlModel::~SqlModel()
{
    delete ui;
}
