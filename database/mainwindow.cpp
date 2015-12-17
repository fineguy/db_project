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

    load_deps_editor();
    load_profs_editor();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_depBox_currentIndexChanged(const QString &arg1)
{
    load_chrs();
    load_profs();
}

void MainWindow::on_chrBox_currentIndexChanged(const QString &arg1)
{
    load_profs();
}

void MainWindow::on_depEditorBox_currentIndexChanged(const QString &arg1)
{
    QString department = ui->depEditorBox->currentText();
    QSqlQuery *dep_query = session.department_info(department);
    load_chrs_editor();

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
    load_profs_editor();

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
    int depKey = ui->depKeyEdit->text().toInt();
    QString depName = ui->depNameEdit->text();
    QString depFName = ui->depFNameEdit->text();
    QString depLName = ui->depLNameEdit->text();

    QString chr = ui->chrEditorBox->currentText();
    int chrCode = ui->chrCodeEdit->text().toInt();
    QString chrName = ui->chrNameEdit->text();

    QString prof = ui->profEditorBox->currentText();
    QString profFName = ui->profFNameEdit->text();
    QString profLName = ui->profLNameEdit->text();
    int profRec = ui->profRecEdit->text().toInt();
    QString profSex = ui->profSexEdit->text();

    if (dep != "") {
        if (session.update_department(dep, depKey, depName, depFName, depLName)) {
            QMessageBox::critical(this, "Updated", "The "+dep+" department entry was updated");
            load_deps();
            load_deps_editor();
        } else {
            QMessageBox::critical(this, "Error", "Oops! Something went wrong");
        }
    }

    if (chr != "") {
        if (session.update_chair(chrCode, chrName, chr)) {
            QMessageBox::critical(this, "Updated", "The "+chr+" department entry was updated");
            load_chrs();
            load_chrs_editor();
        } else {
            QMessageBox::critical(this, "Error", "Oops! Something went wrong");
        }
    }

    if (prof != "") {
        if (session.update_professor(prof, profFName, profLName, profRec, profSex)) {
            QMessageBox::critical(this, "Updated", "The "+prof+" professor entry was updated");
            load_profs();
            load_profs_editor();
        } else {
            QMessageBox::critical(this, "Error", "Oops! Something went wrong");
        }
    }
}

void MainWindow::on_addButton_clicked()
{
    QString dep = ui->depEditorBox->currentText();
    int depKey = ui->depKeyEdit->text().toInt();
    QString depName = ui->depNameEdit->text();
    QString depFName = ui->depFNameEdit->text();
    QString depLName = ui->depLNameEdit->text();

    QString chr = ui->chrEditorBox->currentText();
    int chrCode = ui->chrCodeEdit->text().toInt();
    QString chrName = ui->chrNameEdit->text();

    QString prof = ui->profEditorBox->currentText();
    QString profFName = ui->profFNameEdit->text();
    QString profLName = ui->profLNameEdit->text();
    int profRec = ui->profRecEdit->text().toInt();
    QString profSex = ui->profSexEdit->text();

    if (dep == "") {
        if (depKey == 0 || depName == "" || depFName == "" || depLName == "") {
            ui->statusLabelEditor->setText("Make sure you filled all info for new department");
        } else {
            if (session.insert_department(depKey, depName, depFName, depLName)) {
                QMessageBox::critical(this, "Created", "New department entry was created");
                load_deps();
                load_deps_editor();
            } else {
                QMessageBox::critical(this, "Error", "Oops! Something went wrong");
            }
        }
    } else if (chr == "") {
        if (chrCode == 0 || chrName == "") {
            ui->statusLabelEditor->setText("Make sure you filled all info for new chair");
        } else {
            if (session.insert_chair(depKey, chrCode, chrName)) {
                QMessageBox::critical(this, "Created", "New chair entry was created");
                load_chrs();
                load_chrs_editor();
            } else {
                QMessageBox::critical(this, "Error", "Oops! Something went wrong");
            }
        }
    } else if (prof == "") {
        if (profFName == "" || profLName == "" || profRec == 0 || profSex == "") {
            ui->statusLabelEditor->setText("Make sure you filled all info for new department");
        } else {
            if (session.insert_professor(chrCode, profFName, profLName, profRec, profSex)) {
                QMessageBox::critical(this, "Created", "New professor entry was created");
                load_profs();
                load_profs_editor();
            } else {
                QMessageBox::critical(this, "Error", "Oops! Something went wrong");
            }
        }
    } else {
        ui->statusLabelEditor->setText("Maybe you want to update the data instead?");
    }
}

void MainWindow::on_delButton_clicked()
{
    QString dep = ui->depEditorBox->currentText();
    QString chr = ui->chrEditorBox->currentText();
    QString prof = ui->profEditorBox->currentText();

    if (dep == "") {
        ui->statusLabelEditor->setText("Pick something before deleting");
    } else if (chr == "") {
        if (session.delete_department(dep)) {
            QMessageBox::critical(this, "Removed", "The "+dep+" department entry was deleted");
            load_deps();
            load_deps_editor();
        } else {
            QMessageBox::critical(this, "Error", "Oops! Something went wrong");
        }
    } else if (prof == "") {
        if (session.delete_chair(chr)) {
            QMessageBox::critical(this, "Removed", "The "+chr+" chair entry was deleted");
            load_chrs();
            load_chrs_editor();
        } else {
            QMessageBox::critical(this, "Error", "Oops! Something went wrong");
        }
    } else {
        if (session.delete_professor(prof)) {
            QMessageBox::critical(this, "Removed", "The "+prof+" professor entry was deleted");
            load_profs();
            load_profs_editor();
        } else {
            QMessageBox::critical(this, "Error", "Oops! Something went wrong");
        }
    }
}

void MainWindow::load_deps() {
    QSqlQueryModel *dep_model = session.departments();

    if (dep_model) {
        ui->depBox->setModel(dep_model);
    } else {
        ui->statusLabel->setText("Lost connection");
        ui->statusLabelEditor->setText("Lost connection");
    }
}

void MainWindow::load_chrs() {
    QString department = ui->depBox->currentText();
    QSqlQueryModel *chr_model = session.chairs(department);

    if (chr_model) {
        ui->chrBox->setModel(chr_model);
    } else {
        ui->statusLabel->setText("Lost connection");
        ui->statusLabelEditor->setText("Lost connection");
    }
}

void MainWindow::load_profs() {
    QString department = ui->depBox->currentText();
    QString chair = ui->chrBox->currentText();
    QSqlQueryModel *table_model = session.table(department, chair);

    if (table_model) {
        ui->tableView->setModel(table_model);
    } else {
        ui->statusLabel->setText("Lost connection");
    }
}

void MainWindow::load_deps_editor() {
    QSqlQueryModel *dep_model = session.departments();

    if (dep_model) {
        ui->depBox->setModel(dep_model);
        ui->depEditorBox->setModel(dep_model);
    } else {
        ui->statusLabel->setText("Lost connection");
        ui->statusLabelEditor->setText("Lost connection");
    }
}

void MainWindow::load_chrs_editor() {
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

void MainWindow::load_profs_editor() {
    QString chair = ui->chrEditorBox->currentText();
    QSqlQueryModel *prof_model = session.professors(chair);

    if (prof_model) {
        ui->profEditorBox->setModel(prof_model);
    } else {
        ui->statusLabel->setText("Lost connection");
    }
}
