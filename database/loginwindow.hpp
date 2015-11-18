#ifndef LOGINWINDOW_HPP
#define LOGINWINDOW_HPP

#include <QWidget>

#include <QRect>
#include <QDesktopWidget>
#include <QString>

#include "session.hpp"
#include "mainwindow.hpp"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT
    // friend class MainWindow;

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    void center();

private slots:
    void on_LoginButton_clicked();

private:
    Ui::LoginWindow *ui;
    Session session;
};

#endif // LOGINWINDOW_HPP
