#ifndef SESSION
#define SESSION

#include <QtSql>
#include <QDebug>
#include <QFileInfo>

class Session {
    QSqlDatabase db;

public:
    bool open_connection();
    void close_connection();
    int login(QString username, QString password);

    QSqlQueryModel *departments();
    QSqlQueryModel *chairs(QString &department);
    QSqlQueryModel *table(QString &department, QString &chair);
    QSqlQueryModel *professors(QString &chair);

    QSqlQuery *department_info(QString &department);
    QSqlQuery *chair_info(QString &chair);
    QSqlQuery *prof_info(QString &professor);
};

#endif // SESSION

