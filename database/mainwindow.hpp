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

private:
    Ui::MainWindow *ui;
    Session session;

    void update_table();
    void update_deps();
    void update_chrs();
    void update_profs();
    void update_deps_editor();
    void update_chrs_editor();
    void update_profs_editor();
};

#endif // MAINWINDOW_HPP
