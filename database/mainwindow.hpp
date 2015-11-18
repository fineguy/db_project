#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "session.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_depBox_currentIndexChanged(const QString &arg1);

    void on_showButton_clicked();

    void on_editButton_clicked();

    void on_chrBox_currentIndexChanged(const QString &arg1);

    void on_depBoxEditor_currentIndexChanged(const QString &arg1);

    void on_chrBoxEditor_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Session session;
    QString all = "";
};

#endif // MAINWINDOW_HPP
