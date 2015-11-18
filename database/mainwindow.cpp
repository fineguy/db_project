#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QtSql>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statusLabel->setText("Connected...");
    ui->statusLabelEditor->setText("Connected...");

    QSqlQueryModel *dep_model = session.departments();
    QSqlQueryModel *table_model = session.table(all, all);

    if (dep_model) {
        ui->depBox->setModel(dep_model);
        ui->depBoxEditor->setModel(dep_model);
        ui->tableView->setModel(table_model);
    } else {
        ui->statusLabel->setText("Lost connection");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_depBox_currentIndexChanged(const QString &arg1)
{
    QString department = ui->depBox->currentText();

    QSqlQueryModel *chr_model = session.chairs(department);
    QSqlQueryModel *table_model = session.table(department, all);

    if (chr_model) {
        ui->chrBox->setModel(chr_model);
        ui->tableView->setModel(table_model);
    } else {
        ui->statusLabel->setText("Lost connection");
    }
}

void MainWindow::on_showButton_clicked()
{
    ui->statusLabel->setText("Pressed Button");
}

void MainWindow::on_editButton_clicked()
{
    ui->statusLabel->setText("Pressed Button");
}

void MainWindow::on_chrBox_currentIndexChanged(const QString &arg1)
{
    QString department = ui->depBox->currentText();
    QString chair = ui->chrBox->currentText();
    QSqlQueryModel *table_model = session.table(department, chair);

    if (table_model) {
        ui->tableView->setModel(table_model);
    } else {
        ui->statusLabel->setText("Lost connection");
    }
}

void MainWindow::on_depBoxEditor_currentIndexChanged(const QString &arg1)
{
    QString department = ui->depBoxEditor->currentText();

    QSqlQueryModel *chr_model = session.chairs(department);

    if (chr_model) {
        ui->chrBoxEditor->setModel(chr_model);
    } else {
        ui->statusLabelEditor->setText("Lost connection");
    }
}

void MainWindow::on_chrBoxEditor_currentIndexChanged(const QString &arg1)
{
    QString department = ui->depBoxEditor->currentText();
    QString chair = ui->chrBoxEditor->currentText();
    QSqlQueryModel *prof_model = session.professors(department, chair);

    if (prof_model) {
        ui->profBoxEditor->setModel(prof_model);
    } else {
        ui->statusLabel->setText("Lost connection");
    }
}
