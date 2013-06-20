#include "../include/mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_NewBorrower_Clicked(){
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_ListBorrower_Clicked(){
    ui->stackedWidget->setCurrentIndex(6);
    if(!selectedBorrower)
        ui->pushButton_5->setEnabled(false);
}

void MainWindow::on_ListCopy_Clicked(){
    ui->stackedWidget->setCurrentIndex(7);
    if(!selectedCopy)
        ui->pushButton_6->setEnabled(false);
}

void MainWindow::on_NewVehicle_Clicked(){
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_ListVehicle_Clicked(){
    ui->stackedWidget->setCurrentIndex(2);
    if(!selectedVehicle){
        ui->label_vehicle_copy->setEnabled(false);
        ui->pushButton->setEnabled(false);
    }
}

void MainWindow::on_NewRent_Clicked(){
    if(selectedBorrower&&selectedCopy){
        ui->stackedWidget->setCurrentIndex(5);
        ui->pushButton_2->setEnabled(true);
    }
    else{
        QMessageBox::critical(this, "AvisOmatiC", "Please, select a borrower and a copy before.");
        return;
    }

}

void MainWindow::on_RentList_Clicked(){
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_returnRent_Clicked(){
    if(selectedRent){
        ui->stackedWidget->setCurrentIndex(9);
    }
    else{
        QMessageBox::critical(this, "AvisOmatiC", "Please, select a rent before.");
        ui->stackedWidget->setCurrentIndex(8);
    }
}

void MainWindow::on_search_Clicked(){
    int currentId = ui->stackedWidget->currentIndex();
    unsigned int i=0;
    bool ok=false;
    QString searchValue;
    int minorV=0;

    switch(currentId){
    default:
        QMessageBox::critical(this, "AvisOmatiC", "You can't make a search on this page.");
        break;
    case 2:
        ok=false;
        searchValue = QInputDialog::getText(this, "AvisOmatiC", "Enter the search parameters:", QLineEdit::Normal, QString(), &ok);
        if(ok){
            removeAllRows(ui->table_vehicle);
            std::vector<std::string> search = split(searchValue);
            std::vector<Vehicle*> returnValue = _vehicleContainer.search(search);
            for(i=0; i<returnValue.size();i++){
                renderRowInTable(ui->table_vehicle,i,returnValue[i]->display());
            }
        }
        break;
    case 6:
        ok=false;
        searchValue = QInputDialog::getText(this, "AvisOmatiC", "Enter the search parameters:", QLineEdit::Normal, QString(), &ok);
        if(ok){
            removeAllRows(ui->tableWidget);
            std::vector<std::string> search = split(searchValue);
            std::vector<Borrower*> returnValue = _borrowerContainer.search(search);
            for(i=0; i<returnValue.size();i++){
                for(i=0; i<returnValue.size();i++){
                    if(returnValue[i]->isActive())
                        renderRowInTable(ui->tableWidget,i-minorV,returnValue[i]->display());
                    else
                        minorV++;
                }
            }
        }
        break;
    }
}

void MainWindow::on_stats_clicked(){
    //Let's generate the stats!
    std::vector<Vehicle*> statsCar = stats(Vehicle::car);
    std::vector<Vehicle*> statsMoto = stats(Vehicle::moto);

    //Car

    if(statsCar.size()>0)
        ui->label_stats_car_1->setText((statsCar[0]->getBrand()+" "+statsCar[0]->getName()).c_str());
    if(statsCar.size()>1)
        ui->label_stats_car_2->setText((statsCar[1]->getBrand()+" "+statsCar[1]->getName()).c_str());
    if(statsCar.size()>2)
        ui->label_stats_car_3->setText((statsCar[2]->getBrand()+" "+statsCar[2]->getName()).c_str());

    if(statsMoto.size()>0)
        ui->label_stats_moto_1->setText((statsMoto[0]->getBrand()+" "+statsMoto[0]->getName()).c_str());
    if(statsMoto.size()>1)
        ui->label_stats_moto_2->setText((statsMoto[1]->getBrand()+" "+statsMoto[1]->getName()).c_str());
    if(statsMoto.size()>2)
        ui->label_stats_moto_3->setText((statsMoto[2]->getBrand()+" "+statsMoto[2]->getName()).c_str());


    ui->stackedWidget->setCurrentIndex(10);
}

void MainWindow::on_save_clicked(){
    XmlBorrower xmlBorrower;
    XmlCopy xmlCopy;
    XmlRent xmlRent;

    xmlBorrower.write(&_borrowerContainer);
    xmlCopy.write(&_copyContainer);
    xmlRent.write(_rentContainer);
}

void MainWindow::on_refresh_clicked(){
    renderCopyContainer();
    renderRentContainer();
    renderBorrowerContainer();
    renderVehicleContainer();
}
