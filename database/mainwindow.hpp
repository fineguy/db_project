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

    void on_chrBox_currentIndexChanged(const QString &arg1);

    void on_depEditorBox_currentIndexChanged(const QString &arg1);

    void on_chrEditorBox_currentIndexChanged(const QString &arg1);

    void on_profEditorBox_currentIndexChanged(const QString &arg1);

    void on_editButton_clicked();

    void on_addButton_clicked();

    void on_delButton_clicked();

private:
    Ui::MainWindow *ui;
    Session session;

    void load_deps();
    void load_chrs();
    void load_profs();
    void load_deps_editor();
    void load_chrs_editor();
    void load_profs_editor();
};

#endif // MAINWINDOW_HPP
