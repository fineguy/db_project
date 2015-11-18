
#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QtSql>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statusLabel->setText("Connected...");
    ui->statusLabelEditor->setText("Connected...");

    update_deps_editor();
    update_profs_editor();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_depBox_currentIndexChanged(const QString &arg1)
{
    update_chrs();
    update_profs();
}

void MainWindow::on_chrBox_currentIndexChanged(const QString &arg1)
{
    update_profs();
}

void MainWindow::on_depEditorBox_currentIndexChanged(const QString &arg1)
{
    QString department = ui->depEditorBox->currentText();
    QSqlQuery *dep_query = session.department_info(department);
    update_chrs_editor();

    if (dep_query) {
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
    QSqlQuery *chr_query = session.chair_info(chair);
    update_profs_editor();

    if (chr_query) {
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
        qDebug() << professor;
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
    QString dep = ui->depEditorBox->currentText();
    QString depKey = ui->depKeyEdit->text();
    QString depName = ui->depNameEdit->text();
    QString depFName = ui->depFNameEdit->text();
    QString depLName = ui->depLNameEdit->text();

    QString chr = ui->chrEditorBox->currentText();
    QString chrCode = ui->chrCodeEdit->text();
    QString chrName = ui->chrNameEdit->text();

    QString prof = ui->profEditorBox->currentText();
    QString profFName = ui->profFNameEdit->text();
    QString profLName = ui->profLNameEdit->text();
    QString profRec = ui->profRecEdit->text();
    QString profSex = ui->profSexEdit->text();

    if (dep == "") {
        if (depKey == "" || depName == "" || depFName == "" || depLName == "" ) {
            ui->statusLabelEditor->setText("Make sure you fill all info for new department");
        } else {
            if (session.insert_department(depKey.toInt(), depName, depFName, depLName)) {
                QMessageBox::critical(this, "Saved", "New department entry created");
                update_deps();
                update_deps_editor();
            } else {
                QMessageBox::critical(this, "Error", "Something went wrong");
            }
        }
    } else if (chr == "") {
        if (chrCode == "" || chrName == "") {
            ui->statusLabelEditor->setText("Make sure you fill all info for new chair");
        } else {
            if (session.insert_chair(depKey.toInt(), chrCode.toInt(), chrName)) {
                QMessageBox::critical(this, "Saved", "New chair entry created");
                update_chrs();
                update_chrs_editor();
            } else {
                QMessageBox::critical(this, "Error", "Something went wrong");
            }
        }
    } else if (prof == "") {
        if (profFName == "" || profLName == "" || profRec == "" || profSex == "") {
            ui->statusLabelEditor->setText("Make sure you fill all info for new professor");
        } else {
            if (session.insert_professor(chrCode.toInt(), profFName, profLName, profRec, profSex)) {
                QMessageBox::critical(this, "Saved", "New professor entry created");
                update_profs();
                update_profs_editor();
            } else {
                QMessageBox::critical(this, "Error", "Something went wrong");
            }
        }
    } else {
        ui->statusLabelEditor->setText("Not ready yet");
    }
}

void MainWindow::update_deps() {
    QSqlQueryModel *dep_model = session.departments();

    if (dep_model) {
        ui->depBox->setModel(dep_model);
    } else {
        ui->statusLabel->setText("Lost connection");
        ui->statusLabelEditor->setText("Lost connection");
    }
}

void MainWindow::update_chrs() {
    QString department = ui->depBox->currentText();
    QSqlQueryModel *chr_model = session.chairs(department);

    if (chr_model) {
        ui->chrBox->setModel(chr_model);
    } else {
        ui->statusLabel->setText("Lost connection");
        ui->statusLabelEditor->setText("Lost connection");
    }
}

void MainWindow::update_profs() {
    QString department = ui->depBox->currentText();
    QString chair = ui->chrBox->currentText();
    QSqlQueryModel *table_model = session.table(department, chair);

    if (table_model) {
        ui->tableView->setModel(table_model);
    } else {
        ui->statusLabel->setText("Lost connection");
    }
}

void MainWindow::update_deps_editor() {
    QSqlQueryModel *dep_model = session.departments();

    if (dep_model) {
        ui->depBox->setModel(dep_model);
        ui->depEditorBox->setModel(dep_model);
    } else {
        ui->statusLabel->setText("Lost connection");
        ui->statusLabelEditor->setText("Lost connection");
    }
}

void MainWindow::update_chrs_editor() {
    QString department = ui->depEditorBox->currentText();
    QSqlQueryModel *chr_model = session.chairs(department);

    if (chr_model) {
        ui->chrBox->setModel(chr_model);
        ui->chrEditorBox->setModel(chr_model);
    } else {
        ui->statusLabel->setText("Lost connection");
        ui->statusLabelEditor->setText("Lost connection");
    }
}

void MainWindow::update_profs_editor() {
    QString chair = ui->chrEditorBox->currentText();
    QSqlQueryModel *prof_model = session.professors(chair);

    if (prof_model) {
        ui->profEditorBox->setModel(prof_model);
    } else {
        ui->statusLabel->setText("Lost connection");
    }
}
