#ifndef SQL_H
#define SQL_H

#include <QDialog>
#include <QMainWindow>
#include <QSqlDatabase>
#include <qsqlquery.h>
#include <QtSql>
namespace Ui {
class Sql;
}

class Sql : public QDialog
{
    Q_OBJECT

public:
    explicit Sql(QWidget *parent = 0);
   // void insert(int id,QString name,QString path);
   void c_s(int id,QString name,QString path);
   void c_s1(int sno,int id,QString name,QString path);
   int get_id();
   QString get_name();
   QString get_path();
   QSqlDatabase get_db();

   void view_dev();

   void create_database();

   void create_table();

   void insert();

   void insearch();

    ~Sql();

private slots:
    void on_view_dev_clicked();

    void on_create_database_clicked();

    void on_create_table_clicked();

    void on_insert_clicked();

    void on_insearch_clicked();

    void on_back_clicked();

private:
    Ui::Sql *ui;
    QSqlDatabase db;
    int sno;
    int id;
    QString name;
    QString path;
};

#endif // SQL_H
