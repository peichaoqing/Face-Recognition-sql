#include "sql.h"
#include "ui_sql.h"
#include <QDebug>

Sql::Sql(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sql)
{
    ui->setupUi(this);
}
int Sql::get_id()
{
    return id;
}
QString Sql::get_name()
{
    return name;
}
QString Sql::get_path()
{
    return path;
}
void Sql::c_s(int id,QString name,QString path)
{
    this->id=id;
    this->name=name;
    this->path=path;
}
void Sql::c_s1(int sno,int id,QString name,QString path)
{
    this->sno=sno;
    this->id=id;
    this->name=name;
    this->path=path;
}
QSqlDatabase Sql::get_db()
{
    return db;
}
Sql::~Sql()
{
    delete ui;
}


void Sql::view_dev()
{
    QStringList dris= QSqlDatabase::drivers();
    foreach(QString iter,dris)
    qDebug()<<iter;
}

void Sql::create_database()
{
    db =QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("stu.db");
    db.setUserName("root");
    db.setPassword("root");
    db.open();
    db.close();
}



void Sql::create_table()
{
    db.open();
    QSqlQuery query;
    query.exec("create table tb_ate(sno int,id int,name varchar(64),status varchar(64))");
    db.close();
}

void Sql::insert()
{

    db.open();
    QSqlQuery query;
    sno=query.exec("SELECT COUNT(*) FROM student WHERE id!=0");
    sno++;
    QString nm=this->name;
    QString pth=this->path;
    query.prepare("insert into tb_ate(sno,id,name,status) values(:sno,:id,:name,:status)");
    query.bindValue(":sno",sno);
    query.bindValue(":id",id);
    query.bindValue(":name",nm);
    query.bindValue(":status",pth);
    query.exec();

    db.close();
}


void Sql::insearch()
{
     db.open();
      qDebug()<<"helloworld";
    QSqlQuery query;
#if 0
   query.exec("select * from tb_stu where id=?");
   while(query.next())
   {
       int id=query.value(0).toInt();
       QString name=query.value(1).toString();
       QString path=query.value(2).toString();

       qDebug()<<id<<":"<<name<<":"<<path;
   }

#endif

    query.exec("select * from tb_ate");
    while(query.next())
    {
#if 1
        int sno=query.value(0).toInt();
        int id=query.value(1).toInt();
        QString name=query.value(2).toString();
        QString path=query.value(3).toString();

        qDebug()<<sno<<":"<<id<<":"<<name<<":"<<path;
#endif
    }
    db.close();
}


#if 0
void Sql::insert(int id,QString name,QString path)
{
    db.open();
    QSqlQuery query;
    query.prepare("insert into tb_stu(id,name,path) values(？,？,？)");
	query.addBindValue(id);
    query.addBindValue(name);
    query.addBindValue(path);
    query.exec(sql);
    db.close();
}

#endif


void Sql::on_view_dev_clicked()
{
    QStringList dris= QSqlDatabase::drivers();
    foreach(QString iter,dris)
    qDebug()<<iter;
}

void Sql::on_create_database_clicked()
{
    db =QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("stu.db");
    db.setUserName("root");
    db.setPassword("root");
    db.open();
    db.close();
}



void Sql::on_create_table_clicked()
{
    db.open();
    QSqlQuery query;
   // query.exec("create table tb_ate(sno INTEGER primary key AUTOINCREMENT,name varchar(64),status varchar(64))");
   // query.exec("create table tb_ate(sno int,id int,name varchar(64),status varchar(64))");
  // query.exec("create table tb_stu(id INTEGER primary key AUTOINCREMENT,name varchar(64),path varchar(1024))");
    query.exec("create table tb_stu(id int,name varchar(64),path varchar(1024))");



    //  query.exec("create table tb_stu(id INTEGER PRIMARY KEY AUTOINCREMENT,name VARCHAR,age INT)");

    db.close();
}

void Sql::on_insert_clicked()
{
    #if 1
    db.open();
    QSqlQuery query;
    QString nm=this->name;
    QString pth=this->path;
    query.prepare("insert into tb_stu(id,name,path) values(:id,:name,:path)");

    query.bindValue(":id",id);
    query.bindValue(":name",nm);
    query.bindValue(":path",pth);
    query.exec();
    query.prepare("insert into tb_ate(sno,id,name,status) values(:sno,:id,:name,:status)");
    query.bindValue(":sno",id);
    query.bindValue(":id",id);
    query.bindValue(":name",nm);
    query.bindValue(":status",pth);
    query.exec();

#if 0
    query.exec("insert into tb_stu values(41,'CYQ','/home/linux/work/build-videoReceiver2-Desktop_Qt_5_7_1_GCC_64bit-Debug/photo')");
    query.exec("insert into tb_stu values(42,'guojige','/home/linux/work/build-videoReceiver2-Desktop_Qt_5_7_1_GCC_64bit-Debug/photo')");
    query.exec("insert into tb_stu values(43,'A','/home/linux/work/build-videoReceiver2-Desktop_Qt_5_7_1_GCC_64bit-Debug/photo')");
    query.exec("insert into tb_stu values(44,'B','/home/linux/work/build-videoReceiver2-Desktop_Qt_5_7_1_GCC_64bit-Debug/photo')");
    query.exec("insert into tb_stu values(45,'C','/home/linux/work/build-videoReceiver2-Desktop_Qt_5_7_1_GCC_64bit-Debug/photo')");
    query.exec("insert into tb_stu values(46,'D','/home/linux/work/build-videoReceiver2-Desktop_Qt_5_7_1_GCC_64bit-Debug/photo')");
#endif

    db.close();
	#endif
	
#if 0
	 db.open();
    QSqlQuery query;
    QString sql="insert into tb_stu values(1,'abc',20)";
    query.exec(sql);

    query.bindValue(":name","xyz");
    query.bindValue(":age",22);
    query.prepare("insert into tb_stu(name,age) VALUES(3,:name,:age)");

    query.exec();

    query.prepare("insert into tb_stu(name,age) VALUES(4,?,?)");
   // QVariantList userId;
    //userId<<name;
    query.addBindValue("fewfew");
    //QVariantList iid;
   // iid<<id;
    query.addBindValue(24);
    query.exec();
    query.exec("insert into tb_stu values(2,'abcd',20)");//效果与上一句一样
     query.exec("insert into tb_stu values(2,name,20)");
    db.close();
    qDebug()<<"helloworld";
#endif

}

void Sql::on_insearch_clicked()
{
	 db.open();
      qDebug()<<"helloworld";
    QSqlQuery query;
    query.exec("select * from tb_stu");
    while(query.next())
    {
#if 1
        int id=query.value(0).toInt();
        QString name=query.value(1).toString();
        QString path=query.value(2).toString();

        qDebug()<<id<<":"<<name<<":"<<path;
#endif


#if 0
		QString name=query.value(1).toString();
        int age=query.value(2).toInt();
        qDebug()<<name<<":"<<age;
         qDebug()<<"helloworld";
#endif
    }
    query.exec("select * from tb_ate");
    while(query.next())
    {
#if 1
        int sno=query.value(0).toInt();
        int id=query.value(1).toInt();
        QString name=query.value(2).toString();
        QString path=query.value(3).toString();

        qDebug()<<sno<<":"<<id<<":"<<name<<":"<<path;
#endif
    }
    db.close();
}

void Sql::on_back_clicked()
{
    this->close();
}
