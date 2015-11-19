#include "session.hpp"
#include "consts.hpp"

bool Session::open_connection() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(PATH_TO_DATABASE);

    if (!db.open()) {
        qDebug() << "Failed to connect";
        return false;
    } else {
        qDebug() << "Connected...";
        return true;
    }
}

void Session::close_connection() {
    db.close();
    db.removeDatabase(QSqlDatabase::defaultConnection);
    qDebug() << "Closed connection";
}

int Session::login(QString username, QString password) {
    if (open_connection()) {
        QSqlQuery loginQuery(db);
        loginQuery.prepare("SELECT COUNT(*) FROM Users WHERE username=? AND password=?");
        loginQuery.bindValue(0, username);
        loginQuery.bindValue(1, password);

        if (loginQuery.exec()) {
            int count = 0;

            if (loginQuery.next())
                count = loginQuery.value(0).toInt();

            if (count == 1)
                return 0;
            else
                return 1;

        } else {
            qDebug() << loginQuery.lastError();
            return -1;
        }
        close_connection();
    } else {
        qDebug() << "Couldn't connect to the database";
        return -1;
    }
}

QSqlQueryModel *Session::departments() {
    if (open_connection()) {
        QSqlQueryModel *departments_model = new QSqlQueryModel();
        QSqlQuery *query = new QSqlQuery(db);

        query->prepare("SELECT name FROM Departments UNION SELECT ''");
        query->exec();
        departments_model->setQuery(*query);

        qDebug() << "Loaded all departments";
        close_connection();
        return departments_model;
    } else {
        qDebug() << "Couldn't connect to the database";
        return NULL;
    }
}

QSqlQueryModel *Session::chairs(QString &department) {
    if (open_connection()) {
        QSqlQueryModel *chairs_model = new QSqlQueryModel();
        QSqlQuery *query = new QSqlQuery(db);

        query->prepare("SELECT c.name FROM Chairs AS c JOIN Departments AS d WHERE c.key == d.key AND d.name == ? UNION SELECT ''");
        query->bindValue(0, department);
        query->exec();
        chairs_model->setQuery(*query);

        qDebug() << "Loaded all chairs for " + department + " department";
        close_connection();
        return chairs_model;
    } else {
        qDebug() << "Couldn't connect to the database";
        return NULL;
    }
}

QSqlQueryModel *Session::table(QString &department, QString &chair) {
    if (open_connection()) {
        QSqlQueryModel *table_model = new QSqlQueryModel();
        QSqlQuery *query = new QSqlQuery(db);
        QString statement = "SELECT p.id, p.first_name, p.last_name, p.record, p.sex, c.name AS 'Chair', d.name AS 'Department' "
                            "FROM Professors AS p, Chairs AS c join Departments AS d, Roster AS r "
                            "WHERE p.id == r.id AND r.code == c.code AND c.key == d.key ";

        if (department == "") {
            query->prepare(statement);
        } else if (chair == "") {
            statement += "AND d.name == ?";
            query->prepare(statement);
            query->bindValue(0, department);
        } else {
            statement += "AND d.name == ? AND c.name == ?";
            query->prepare(statement);
            query->bindValue(0, department);
            query->bindValue(1, chair);
        }

        query->exec();
        table_model->setQuery(*query);

        close_connection();
        return table_model;
    } else {
        qDebug() << "Couldn't connect to the database";
        return NULL;
    }
}

QSqlQueryModel *Session::professors(QString &chair) {
    if (open_connection()) {
        QSqlQueryModel *prof_model = new QSqlQueryModel();
        QSqlQuery *query = new QSqlQuery(db);
        QString statement = "SELECT '' UNION SELECT p.id || ' ' || p.first_name || ' ' || p.last_name "
                            "FROM Professors AS p, Roster AS r, Chairs AS c  "
                            "WHERE p.id == r.id AND r.code == c.code AND c.name == ?";

        query->prepare(statement);
        query->bindValue(0, chair);

        query->exec();
        prof_model->setQuery(*query);

        close_connection();
        return prof_model;
    } else {
        qDebug() << "Couldn't connect to the database";
        return NULL;
    }
}

QSqlQuery *Session::department_info(QString &department) {
    if (open_connection()) {
        QSqlQuery *dep_query = new QSqlQuery(db);
        dep_query->prepare("SELECT * FROM Departments WHERE name == ?");
        dep_query->bindValue(0, department);
        dep_query->exec();
        dep_query->next();

        qDebug() << dep_query->lastQuery();
        close_connection();
        return dep_query;
    } else {
        qDebug() << "Couldn't connect to the database";
        return NULL;
    }
}

QSqlQuery *Session::chair_info(QString &chair) {
    if (open_connection()) {
        QSqlQuery *chr_query = new QSqlQuery(db);
        chr_query->prepare("SELECT * FROM Chairs WHERE name == ?");
        chr_query->bindValue(0, chair);
        chr_query->exec();
        chr_query->next();

        qDebug() << chr_query->lastQuery();
        close_connection();
        return chr_query;
    } else {
        qDebug() << "Couldn't connect to the database";
        return NULL;
    }
}

QSqlQuery *Session::prof_info(QString &professor) {
    if (open_connection()) {
        QSqlQuery *prof_query = new QSqlQuery(db);
        prof_query->prepare("SELECT first_name, last_name, record, sex FROM Professors WHERE id == ?");
        prof_query->bindValue(0, professor.split(" ")[0].toInt());
        prof_query->exec();
        prof_query->next();

        qDebug() << prof_query->lastQuery();
        close_connection();
        return prof_query;
    } else {
        qDebug() << "Couldn't connect to the database";
        return NULL;
    }
}

bool Session::insert_department(int depKey, QString depName, QString depFName, QString depLName) {
    if (open_connection()) {
        QSqlQuery query(db);
        query.prepare("INSERT INTO Departments (key, name, first_name, last_name) VALUES (?, ?, ?, ?)");
        query.bindValue(0, depKey);
        query.bindValue(1, depName);
        query.bindValue(2, depFName);
        query.bindValue(3, depLName);

        bool result = query.exec();
        qDebug() << query.lastQuery();
        close_connection();
        return result;
    } else {
        qDebug() << "Couldn't connect to the database";
        return false;
    }
}

bool Session::insert_chair(int depKey, int chrCode, QString chrName) {
    if (open_connection()) {
        QSqlQuery query(db);
        query.prepare("INSERT INTO Chairs (code, name, key) VALUES (?, ?, ?)");
        query.bindValue(0, chrCode);
        query.bindValue(1, chrName);
        query.bindValue(2, depKey);

        bool result = query.exec();
        qDebug() << query.lastQuery();
        close_connection();
        return result;
    } else {
        qDebug() << "Couldn't connect to the database";
        return false;
    }
}

bool Session::insert_professor(int chrCode, QString profFName, QString profLName, int profRec, QString profSex) {
    if (open_connection()) {
        QSqlQuery profQuery(db);
        QSqlQuery query(db);

        query.exec("SELECT COUNT (*) FROM Professors");
        query.next();
        int index = query.value(0).toInt();

        profQuery.prepare("INSERT INTO Professors (id, first_name, last_name, record, sex) VALUES (?, ?, ?, ?, ?)");
        profQuery.bindValue(0, index + 1);
        profQuery.bindValue(1, profFName);
        profQuery.bindValue(2, profLName);
        profQuery.bindValue(3, profRec);
        profQuery.bindValue(4, profSex);

        QSqlQuery rosterQuery(db);
        rosterQuery.prepare("INSERT INTO Roster (id, code) VALUES (?, ?)");
        rosterQuery.bindValue(0, index + 1);
        rosterQuery.bindValue(1, chrCode);

        bool result = profQuery.exec() && rosterQuery.exec();
        qDebug() << profQuery.lastQuery();
        close_connection();
        return result;
    } else {
        qDebug() << "Couldn't connect to the database";
        return false;
    }
}

bool Session::update_department(QString curDepName, int depKey, QString depName, QString depFName, QString depLName) {
    if (open_connection()) {
        QSqlQuery query(db);
        QString statement = "UPDATE Departments "
                            "SET key = ?, name = ?, first_name = ?, last_name = ? "
                            "WHERE name = ?";
        query.prepare(statement);
        query.bindValue(0, depKey);
        query.bindValue(1, depName);
        query.bindValue(2, depFName);
        query.bindValue(3, depLName);
        query.bindValue(4, curDepName);

        bool result = query.exec();
        qDebug() << query.lastQuery();
        close_connection();
        return result;
    } else {
        qDebug() << "Couldn't connect to the database";
        return false;
    }
}

bool Session::update_chair(int depKey, int chrCode, QString chrName) {
    if (open_connection()) {
        QSqlQuery query(db);
        QString statement = "UPDATE Chairs "
                            "SET code = ?, name = ? "
                            "WHERE key == ?";
        query.prepare(statement);
        query.bindValue(0, chrCode);
        query.bindValue(1, chrName);
        query.bindValue(2, depKey);

        QSqlQuery rosterQuery(db);
        rosterQuery.prepare("UPDATE Roster as r, Chairs as c SET r.code = ? WHERE r.code == c.code AND c.key == ?");
        rosterQuery.bindValue(0, chrCode);
        rosterQuery.bindValue(1, depKey);

        bool result = query.exec();
        qDebug() << query.lastQuery();
        close_connection();
        return result;
    } else {
        qDebug() << "Couldn't connect to the database";
        return false;
    }
}

bool Session::update_professor(QString prof, QString profFName, QString profLName, int profRec, QString profSex) {
    if (open_connection()) {
        QSqlQuery query(db);
        QString statement = "UPDATE Professors "
                            "SET first_name = ?, last_name = ?, record = ?, sex = ? "
                            "WHERE id = ?";
        query.prepare(statement);
        query.bindValue(0, profFName);
        query.bindValue(1, profLName);
        query.bindValue(2, profRec);
        query.bindValue(3, profSex);
        query.bindValue(4, prof.split(" ")[0].toInt());

        bool result = query.exec();
        qDebug() << query.lastQuery();
        close_connection();
        return result;
    } else {
        qDebug() << "Couldn't connect to the database";
        return false;
    }
}

bool Session::delete_department(QString dep) {
    if (open_connection()) {
        QSqlQuery query(db);
        QString statement = "DELETE FROM Departments "
                            "WHERE name == ?";
        query.prepare(statement);
        query.bindValue(0, dep);

        bool result = query.exec();
        qDebug() << query.lastQuery();
        close_connection();
        return result;
    } else {
        qDebug() << "Couldn't connect to the database";
        return false;
    }
}

bool Session::delete_chair(QString chr) {
    if (open_connection()) {
        QSqlQuery query(db);
        QString statement = "DELETE FROM Chairs "
                            "WHERE name = ?";
        query.prepare(statement);
        query.bindValue(0, chr);

        bool result = query.exec();
        qDebug() << query.lastQuery();
        close_connection();
        return result;
    } else {
        qDebug() << "Couldn't connect to the database";
        return false;
    }
}

bool Session::delete_professor(QString prof) {
    if (open_connection()) {
        QSqlQuery query(db);
        QString statement = "DELETE FROM Professors "
                            "WHERE id = ?";
        query.prepare(statement);
        query.bindValue(0, prof.split(" ")[0].toInt());

        QSqlQuery rosterQuery(db);
        rosterQuery.prepare("DELETE FROM Roster WHERE id = ?");
        rosterQuery.bindValue(0, prof.split(" ")[0].toInt());

        bool result = query.exec() & rosterQuery.exec();
        qDebug() << query.lastQuery();
        close_connection();
        return result;
    } else {
        qDebug() << "Couldn't connect to the database";
        return false;
    }
}
