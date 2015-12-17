#include "loginwindow.hpp"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    center();
    ui->pwdEdit->setEchoMode(QLineEdit::Password);

    if (session.open_connection()) {
        ui->statusLabel->setText("Connected...");
        session.close_connection();
    } else {
        ui->statusLabel->setText("Failed to open the database");
    }
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::center() {
    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());
}

void LoginWindow::on_LoginButton_clicked()
{
    QString username, password;
    username = ui->usrEdit->text();
    password = ui->pwdEdit->text();

    int status = session.login(username, password);

    if (status == NO_CONNECTION) {
        this->hide();
        MainWindow *mainwindow = new MainWindow();
        mainwindow->show();
    } else if (status == FAILURE){
        ui->statusLabel->setText("Wrong username and/or password");
    } else {
        ui->statusLabel->setText("Lost connection");
    }
}
