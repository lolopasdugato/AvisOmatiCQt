#include "../include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_NewBorrower_Clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_ListBorrower_Clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_button_newBorrower_clicked()
{
    //_borrowerContainer.add(ui->line_new_borro_firstname->text(),ui->line_new_borro_surname->text(),Address(ui->line_new_borro_number->value(),ui->line_new_borro_street->text(),ui->line_new_borro_postal->value(),ui->line_new_borro_city->text()),ui->line_new_borro_phone->text());
}
