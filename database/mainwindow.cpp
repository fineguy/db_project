
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
        ui->depEditorBox->setModel(dep_model);
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

void MainWindow::on_depEditorBox_currentIndexChanged(const QString &arg1)
{
    QString department = ui->depEditorBox->currentText();
    QSqlQueryModel *chr_model = session.chairs(department);
    QSqlQuery *dep_query = session.department_info(department);

    if (chr_model) {
        ui->chrEditorBox->setModel(chr_model);
        ui->depKeyEdit->setText(dep_query->value(0).toString());
        ui->depNameEdit->setText(dep_query->value(1).toString());
        ui->depFNameEdit->setText(dep_query->value(2).toString());
        ui->depLNameEdit->setText(dep_query->value(3).toString());
    } else {
        ui->statusLabelEditor->setText("Lost connection");
    }
}

void MainWindow::on_chrEditorBox_currentIndexChanged(const QString &arg1)
{
    QString chair = ui->chrEditorBox->currentText();
    QSqlQueryModel *prof_model = session.professors(chair);
    QSqlQuery *chr_query = session.chair_info(chair);

    if (prof_model) {
        ui->profEditorBox->setModel(prof_model);
        ui->chrCodeEdit->setText(chr_query->value(0).toString());
        ui->chrNameEdit->setText(chr_query->value(1).toString());
    } else {
        ui->statusLabel->setText("Lost connection");
    }
}

void MainWindow::on_profEditorBox_currentIndexChanged(const QString &arg1)
{
    QString professor = ui->profEditorBox->currentText();
    QSqlQuery *prof_query = session.prof_info(professor);

    if (prof_query) {
        ui->profFNameEdit->setText(prof_query->value(0).toString());
        ui->profLNameEdit->setText(prof_query->value(1).toString());
        ui->profRecEdit->setText(prof_query->value(2).toString());
        ui->profSexEdit->setText(prof_query->value(3).toString());
    } else {
        ui->statusLabel->setText("Lost connection");
    }
}

void MainWindow::on_editButton_clicked()
{
    QString department = ui->depEditorBox->currentText();
    QString depKey = ui->depKeyEdit->text();
    QString depFName = ui->depFNameEdit->text();
    QString depLName = ui->depLNameEdit->text();

    QString chair = ui->chrEditorBox->currentText();
    QString chrCode = ui->chrCodeEdit->text();
    QString chrName = ui->chrNameEdit->text();

    QString professor = ui->profEditorBox->currentText();
    QString profFName = ui->profFNameEdit->text();
    QString profLName = ui->profLNameEdit->text();
    QString profRec = ui->profRecEdit->text();
    QString profSex = ui->profSexEdit->text();
}
