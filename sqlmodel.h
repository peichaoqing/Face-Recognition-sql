#ifndef SQLMODEL_H
#define SQLMODEL_H

#include <QDialog>

namespace Ui {
class SqlModel;
}

class SqlModel : public QDialog
{
    Q_OBJECT

public:
    explicit SqlModel(QWidget *parent = 0);
    ~SqlModel();

private:
    Ui::SqlModel *ui;
};

#endif // SQLMODEL_H
