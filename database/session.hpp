#ifndef SESSION
#define SESSION

#include <QtSql>
#include <QDebug>
#include <QFileInfo>

class Session {
    QSqlDatabase db;

public:
    int login(QString username, QString password);

    bool open_connection();
    void close_connection();

    QSqlQueryModel *departments();
    QSqlQueryModel *chairs(QString &department);
    QSqlQueryModel *table(QString &department, QString &chair);
    QSqlQueryModel *professors(QString &chair);

    QSqlQuery *department_info(QString &department);
    QSqlQuery *chair_info(QString &chair);
    QSqlQuery *prof_info(QString &professor);

    bool insert_department(int depKey, QString depName, QString depFName, QString depLName);
    bool insert_chair(int depKey, int chrCode, QString chrName);
    bool insert_professor(int chrCode, QString profFName, QString profLName, QString profRec, QString profSex);
};

#endif // SESSION

