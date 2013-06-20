#include "../include/mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::renderCopyContainer(){
    removeAllRows(ui->tableWidget_2);
    int minorV= 0;

    for(int i=0; i<_copyContainer.size();i++){
        if(_copyContainer.getCopyContainer()[i+1]->isActive()){
            renderRowInTable(ui->tableWidget_2,i-minorV,_copyContainer.display(i));
                    ui->tableWidget_2->item(i-minorV, 0)->setBackground(Qt::white);
            if(!_copyContainer.getCopyContainer()[i+1]->isDispo())
                ui->tableWidget_2->item(i-minorV, 0)->setBackground(Qt::red);
        }
        else
            minorV++;
    }
}

void MainWindow::renderVehicleContainer(){
    removeAllRows(ui->table_vehicle);

    for(int i=0; i<_vehicleContainer.size();i++){
        renderRowInTable(ui->table_vehicle,i,_vehicleContainer.display(i));
    }
}

void MainWindow::renderBorrowerContainer(){
    removeAllRows(ui->tableWidget);

    int minorV=0;

    for(int i=0; i<_borrowerContainer.size();i++){
        if(_borrowerContainer.getBorrowerContainer()[i]->isActive())
            renderRowInTable(ui->tableWidget,i-minorV,_borrowerContainer.display(i));
        else
            minorV++;
    }
}

void MainWindow::renderRentContainer(){
    removeAllRows(ui->tableWidget_3);

    std::vector<std::string> data;

    for(unsigned int i=0; i<_rentContainer.size();i++){
        //Preparing data vector
        data.clear();
        data.push_back(toString(_rentContainer[i]->getId()));
        data.push_back(_rentContainer[i]->getCopy()->getVehicle()->getBrand()+" "+_rentContainer[i]->getCopy()->getVehicle()->getName());
        data.push_back(_rentContainer[i]->getBorrower()->getFirstName()+" "+_rentContainer[i]->getBorrower()->getLastName());
        data.push_back(toString(QDate(_rentContainer[i]->getEnd().getYear(),_rentContainer[i]->getEnd().getMonth(),_rentContainer[i]->getEnd().getDay()).daysTo(QDate::currentDate())*-1));


        renderRowInTable(ui->tableWidget_3,i,data);
        if(_rentContainer[i]->getStatus())
            ui->tableWidget_3->item(i, 0)->setBackground(Qt::green);
        else
            ui->tableWidget_3->item(i, 0)->setBackground(Qt::red);
    }
}

void MainWindow::removeAllRows(QTableWidget* table){
    while (table->rowCount() > 0)
    {
        table->removeRow(0);
    }
}

void MainWindow::renderRowInTable(QTableWidget *table, int row, std::vector<std::string> list){
    table->insertRow(row);
    for(std::vector<std::string>::iterator it=list.begin();it<list.end();it++){
        QTableWidgetItem *item = new QTableWidgetItem((*it).c_str());
        table->setItem(row, it-list.begin(), item);
    }
}

