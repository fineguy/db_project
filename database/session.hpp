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
    QSqlQueryModel *professors(QString &department, QString &chair);
};

#endif // SESSION

