#include "../include/mainwindow.h"
#include "ui_mainwindow.h"

template<typename Type> bool in(std::vector<Type> firstOp, Type secondOp)
{
    for(typename std::vector<Type>::iterator it=firstOp.begin(); it!= firstOp.end();it++){
        if((*it)==secondOp)
            return true;
    }
    return false;
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Load Xml
    XmlBorrower xmlBorrower;
    XmlCopy xmlCopy;
    XmlRent xmlRent;

    xmlBorrower.read(&_borrowerContainer);
    xmlCopy.read(&_vehicleContainer,&_copyContainer);
    xmlRent.read(&_rentContainer,&_copyContainer,&_borrowerContainer);

    //Render
    renderBorrowerContainer();
    renderVehicleContainer();
    renderCopyContainer();
    renderRentContainer();

    selectedBorrower=NULL;
    selectedVehicle=NULL;
    selectedCopy=NULL;
    selectedRent=NULL;

    ui->date_rent_start->setMinimumDate(QDate::currentDate());
    ui->date_rent_return->setMinimumDate(QDate::currentDate());
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Add New Borrower
void MainWindow::on_button_newBorrower_clicked()
{
    _borrowerContainer.add(ui->line_new_borro_firstname->text().toStdString(),
                           ui->line_new_borro_surname->text().toStdString(),
                           Address(ui->line_new_borro_number->value(),
                                   ui->line_new_borro_street->text().toStdString(),
                                   ui->line_new_borro_postal->text().toStdString(),
                                   ui->line_new_borro_city->text().toStdString()),
                           ui->line_new_borro_phone->text().toStdString());

    renderBorrowerContainer();

    ui->line_new_borro_firstname->clear();
    ui->line_new_borro_surname->clear();
    ui->line_new_borro_number->clear();
    ui->line_new_borro_street->clear();
    ui->line_new_borro_postal->clear();
    ui->line_new_borro_city->clear();
    ui->line_new_borro_phone->clear();
}

//Add new Vehicle
void MainWindow::on_button_newvehicle_clicked()
{
    Vehicle::Type type;

    switch(ui->line_new_vehicle_type->currentIndex()){
    case 0:
        type=Vehicle::car;
        break;
    case 1:
        type=Vehicle::moto;
        break;
    }

    _vehicleContainer.add(ui->line_new_vehicle_brand->text().toStdString(),ui->line_new_vehicle_misc->text().toStdString(),type,ui->spin_vehicle_cost->value());

    renderVehicleContainer();

    ui->line_new_vehicle_brand->clear();
    ui->line_new_vehicle_misc->clear();
    ui->spin_vehicle_cost->clear();
}

//Click on Vehicle table
void MainWindow::on_table_vehicle_clicked(const QModelIndex &index)
{
    std::vector<std::string> v;
    std::vector<Vehicle*> *returnValue;

    //Get the search value in the cells
    v.push_back(ui->table_vehicle->item(index.row(),1)->text().toStdString());
    v.push_back(ui->table_vehicle->item(index.row(),2)->text().toStdString());

    //Make the search
    returnValue = new std::vector<Vehicle*>(_vehicleContainer.search(v));

    //Display
    ui->label_vehicle_brand->setText(returnValue->at(0)->getBrand().c_str());
    ui->label_vehicle_name->setText(returnValue->at(0)->getName().c_str());

    switch(returnValue->at(0)->getType()){
    case Vehicle::car:
        ui->label_vehicle_type->setText("Car");
        selectedVehicle = new Car(returnValue->at(0));  //Set the selected vehicle
        break;
    case Vehicle::moto:
        ui->label_vehicle_type->setText("Motorcycle");
        selectedVehicle = new Motorcycle(returnValue->at(0));   //Set the selected Vehicle
        break;
    }

    ui->label_vehicle_copy->setValue(_copyContainer.getNumberOf(returnValue->at(0)));

    ui->label_vehicle_copy->setEnabled(true);
    ui->pushButton->setEnabled(true);
}

//Add new copy
void MainWindow::on_pushButton_clicked()
{
   if(ui->label_vehicle_copy->value()>_copyContainer.getNumberOf(selectedVehicle)){
        _copyContainer.add(ui->label_vehicle_copy->value()-_copyContainer.getNumberOf(selectedVehicle),selectedVehicle);
        renderCopyContainer();
    }
}

//Click on Borrower table
void MainWindow::on_tableWidget_clicked(const QModelIndex &index)
{
    std::vector<std::string> v;
    std::vector<Borrower*> *returnValue;

    //Get the search value in the cells
    v.push_back(ui->tableWidget->item(index.row(),0)->text().toStdString());
    v.push_back(ui->tableWidget->item(index.row(),1)->text().toStdString());
    v.push_back(ui->tableWidget->item(index.row(),2)->text().toStdString());

    //Make the search
    returnValue = new std::vector<Borrower*>(_borrowerContainer.search(v));

    //Display
    std::string bufferName = returnValue->at(0)->getFirstName() + " " + returnValue->at(0)->getLastName();
    ui->label_borro_name->setText(bufferName.c_str());
    ui->label_borro_address->setText(returnValue->at(0)->getAddress().display().c_str());
    ui->label_borro_phone->setText(returnValue->at(0)->getPhoneNumber().c_str());

    //Set selected
    selectedBorrower = new Borrower(*returnValue->at(0));

    ui->pushButton_5->setEnabled(true);
}

//Change in Copy table
void MainWindow::on_tableWidget_2_cellChanged(int row, int column)
{
    //The user change and we save
    //The user can only edit the last two columns
    if(column>3){
        _copyContainer.getCopyContainer()[ui->tableWidget_2->item(row,0)->text().toInt()]->setKilometers(ui->tableWidget_2->item(row,column)->text().toInt());
    }
}

//Click on Copy table
void MainWindow::on_tableWidget_2_clicked(const QModelIndex &index)
{
    int id = ui->tableWidget_2->item(index.row(),0)->text().toInt();

    //set selected
    selectedCopy = _copyContainer.getCopyContainer()[id];

    switch(selectedCopy->getVehicle()->getType()){
    case Vehicle::car:
        ui->label_vehicle_type_2->setText("Car");
        break;
    case Vehicle::moto:
        ui->label_vehicle_type_2->setText("Motorcycle");
        break;
    }

    ui->label_vehicle_brand_2->setText(selectedCopy->getVehicle()->getBrand().c_str());
    ui->label_vehicle_name_2->setText(selectedCopy->getVehicle()->getName().c_str());
    ui->label_vehicle_id_2->setText(QString::number(selectedCopy->getId()));
    ui->label_rent_dailyCost->setText(QString::number(selectedCopy->getVehicle()->getDailyCost()));

    QDate end = ui->date_rent_return->date();
    QDate start = ui->date_rent_start->date();
    int NbOfDay = start.daysTo(end);

    ui->label_rent_totalCost->setText(QString::number(selectedCopy->getVehicle()->getDailyCost()*NbOfDay));

    ui->pushButton_6->setEnabled(true);
}

//Start date changed
void MainWindow::on_date_rent_return_userDateChanged(const QDate &date)
{
    if(selectedBorrower||selectedCopy){
        QDate start = ui->date_rent_start->date();
        int NbOfDay = start.daysTo(date);
        ui->label_rent_totalCost->setText(QString::number(calculatePrice(selectedCopy->getVehicle()->getDailyCost(),ui->radio_insu->isChecked(),NbOfDay,selectedCopy->getKilometers())));
    }
}

//End date changed
void MainWindow::on_date_rent_start_userDateChanged(const QDate &date)
{
    if(selectedBorrower||selectedCopy){
        QDate end = ui->date_rent_return->date();
        int NbOfDay = date.daysTo(end);

        ui->label_rent_totalCost->setText(QString::number(calculatePrice(selectedCopy->getVehicle()->getDailyCost(),ui->radio_insu->isChecked(),NbOfDay,selectedCopy->getKilometers())));
    }
}

//Add new rent
void MainWindow::on_pushButton_2_clicked()
{
    if(selectedCopy->isDispo()){
        Rent* rent = new Rent(selectedCopy, selectedBorrower, Date(ui->date_rent_start->date().day(),ui->date_rent_start->date().month(),ui->date_rent_start->date().year()), Date(ui->date_rent_return->date().day(),ui->date_rent_return->date().month(),ui->date_rent_return->date().year()));
        _rentContainer.push_back(rent);

        bool b=true;
        if(ui->radio_noinsu->isChecked())
            b=false;

        _rentContainer[_rentContainer.size()-1]->setInsurance(b);

        selectedCopy->setDispo(false);
        renderRentContainer();
        renderCopyContainer();

        ui->label_borro_name->clear();
        ui->label_borro_address->clear();
        ui->label_borro_phone->clear();

        selectedBorrower=NULL;
    }
    else
        QMessageBox::critical(this, "AvisOmatiC", "This copy is already in rent.");
    selectedCopy=NULL;
    ui->label_vehicle_brand_2->clear();
    ui->label_vehicle_name_2->clear();
    ui->label_vehicle_id_2->clear();
    ui->label_vehicle_type_2->clear();
    ui->label_rent_dailyCost->clear();
    ui->pushButton_2->setEnabled(false);
}

//Vehicle sort : ALL
void MainWindow::on_radioButton_2_clicked()
{
    renderVehicleContainer();
}

//Vehicle sort : CAR
void MainWindow::on_radioButton_3_clicked()
{
    removeAllRows(ui->table_vehicle);

    std::vector<std::string>buffer;
    int minorV=0;

    for(int i=0; i<_vehicleContainer.size();i++){
        buffer.clear();
        buffer=_vehicleContainer.display(i,Vehicle::car);
        if(buffer.size()>0)
            renderRowInTable(ui->table_vehicle,i-minorV,buffer);
        else
            minorV--;
    }
}

//Vehicle sort : MOTO
void MainWindow::on_radioButton_clicked()
{
    removeAllRows(ui->table_vehicle);

    std::vector<std::string>buffer;
    int minorV=0;

    for(int i=0; i<_vehicleContainer.size();i++){
        buffer.clear();
        buffer=_vehicleContainer.display(i,Vehicle::moto);
        if(buffer.size()>0)
            renderRowInTable(ui->table_vehicle,i-minorV,buffer);
        else
            minorV++;
    }
}

//Click rent table
void MainWindow::on_tableWidget_3_clicked(const QModelIndex &index)
{
    int id = ui->tableWidget_2->item(index.row(),0)->text().toInt();

    //set selected
    selectedRent = _rentContainer[id-1];

    //diplay
    std::string buffer1 = selectedRent->getBorrower()->getFirstName()+" "+selectedRent->getBorrower()->getLastName();
    std::string buffer2 = selectedRent->getCopy()->getVehicle()->getBrand()+" "+selectedRent->getCopy()->getVehicle()->getName();

    ui->label_return_name->setText(buffer1.c_str());
    ui->label_return_vehicle->setText(buffer2.c_str());
    ui->label_return_inod->setText(QString::number(QDate(selectedRent->getBegin().getYear(),selectedRent->getBegin().getMonth(),selectedRent->getBegin().getDay()).daysTo(QDate(selectedRent->getEnd().getYear(),selectedRent->getEnd().getMonth(),selectedRent->getEnd().getDay()))));
    ui->label_return_rnod->setText(QString::number(QDate(selectedRent->getBegin().getYear(),selectedRent->getBegin().getMonth(),selectedRent->getBegin().getDay()).daysTo(QDate::currentDate())));

    int NbOfDays = QDate(selectedRent->getBegin().getYear(),selectedRent->getBegin().getMonth(),selectedRent->getBegin().getDay()).daysTo(QDate(selectedRent->getEnd().getYear(),selectedRent->getEnd().getMonth(),selectedRent->getEnd().getDay()));

    ui->label_retur_firstPrice->setText(QString::number(calculatePrice(selectedRent->getCopy()->getVehicle()->getDailyCost(),selectedRent->getInsurance(),NbOfDays,selectedRent->getCopy()->getKilometers())));
    ui->label_return_realPrice->setText(QString::number(calculatePrice(selectedRent->getCopy()->getVehicle()->getDailyCost(),selectedRent->getInsurance(),NbOfDays,selectedRent->getCopy()->getKilometers(),ui->combo_fuel->currentIndex()*50,ui->comboBox->currentIndex(),QDate(selectedRent->getEnd().getYear(),selectedRent->getEnd().getMonth(),selectedRent->getEnd().getDay()).daysTo(QDate::currentDate()))));

    ui->pushButton_4->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
}

//Rent return
void MainWindow::on_pushButton_4_clicked()
{
    selectedRent->setStatus(false);
    selectedRent->getCopy()->setDispo(true);

    renderRentContainer();
    renderCopyContainer();

    selectedRent->setFuelMalus(ui->combo_fuel->currentIndex()*50);
    selectedRent->getCopy()->setStatus(Copy::Status(ui->comboBox->currentIndex()));

    renderCopyContainer();
}

//Insurance
void MainWindow::on_radio_insu_clicked()
{
    if(selectedBorrower||selectedCopy){
        QDate end = ui->date_rent_return->date();
        int NbOfDay = ui->date_rent_start->date().daysTo(end);
        ui->label_rent_totalCost->setText(QString::number(calculatePrice(selectedCopy->getVehicle()->getDailyCost(),true,NbOfDay,selectedCopy->getKilometers())));
    }
}

//No Insurance
void MainWindow::on_radio_noinsu_clicked()
{
    if(selectedBorrower||selectedCopy){
        QDate end = ui->date_rent_return->date();
        int NbOfDay = ui->date_rent_start->date().daysTo(end);
        ui->label_rent_totalCost->setText(QString::number(calculatePrice(selectedCopy->getVehicle()->getDailyCost(),false,NbOfDay,selectedCopy->getKilometers())));
    }
}

int MainWindow::calculatePrice(int price, bool insu, int NbOfDay, int nbKm, int fuelMalus, int damageMalus, int daysOver){
    int price2 = price*NbOfDay*1.0;
    int insuVal =0;
    int km=0;
    int damage=0;

    if(insu)
        insuVal += (price2*10.0)/100.0;
    km -= (floor(nbKm/50000.0)*price2)/10;

    if(daysOver>0){
        price2 += daysOver*50;
    }

    if(!insu){
        switch(damageMalus){
        case 0:
            damage=0;
            break;
        case 1:
            damage=1000;
            break;
        case 2:
            damage=5000;
            break;
        }
    }

    return price2+fuelMalus+insuVal+km+damage;
}

//Edit bill
void MainWindow::on_pushButton_3_clicked()
{
    //Generate the bill and change the page

    //Borrower info
    ui->label_bill_fname->setText(selectedRent->getBorrower()->getFirstName().c_str());
    ui->label_bill_lname->setText(selectedRent->getBorrower()->getLastName().c_str());
    ui->label_bill_add->setText(selectedRent->getBorrower()->getAddress().display().c_str());
    ui->label_bill_phone->setText(selectedRent->getBorrower()->getPhoneNumber().c_str());

    //Vehicule info
    ui->label_bill_brand->setText(selectedRent->getCopy()->getVehicle()->getBrand().c_str());
    ui->label_bill_model->setText(selectedRent->getCopy()->getVehicle()->getName().c_str());
    switch(selectedRent->getCopy()->getVehicle()->getType()){
    case Vehicle::car:
        ui->label_bill_type->setText("Car");
        break;
    case Vehicle::moto:
        ui->label_bill_type->setText("Motorcycle");
        break;
    }
    ui->label_bill_km->setText(QString::number(selectedRent->getCopy()->getKilometers()));

    //Bill info
    ui->label_bill_dc->setText(QString::number(selectedRent->getCopy()->getVehicle()->getDailyCost()));
    int NbOfDays = QDate(selectedRent->getBegin().getYear(),selectedRent->getBegin().getMonth(),selectedRent->getBegin().getDay()).daysTo(QDate(selectedRent->getEnd().getYear(),selectedRent->getEnd().getMonth(),selectedRent->getEnd().getDay()));
    ui->label_bill_nbod->setText(QString::number(NbOfDays));
    int price = selectedRent->getCopy()->getVehicle()->getDailyCost()*NbOfDays*1.0;
    if(selectedRent->getInsurance()){
        float insuranceCost = (price*10.0)/100.0;
        ui->label_bill_insu->setText(QString::number(insuranceCost));
    }
    else
        ui->label_bill_insu->setText(QString::number(0));

    ui->label_bill_kilo->setText(QString::number((floor(selectedRent->getCopy()->getKilometers()/50000.0)*price)/10*-1));

    int daysOver = QDate(selectedRent->getEnd().getYear(),selectedRent->getEnd().getMonth(),selectedRent->getEnd().getDay()).daysTo(QDate::currentDate());
    if(daysOver>0)
        ui->label_bill_ot->setText(QString::number(daysOver*50));
    else
        ui->label_bill_ot->setText(QString::number(0));

    ui->label_bill_fuel->setText(QString::number(selectedRent->getFuelMalus()));

    if(!selectedRent->getInsurance()){
        switch(selectedRent->getCopy()->getStatus()){
        case Copy::NEW:
            ui->label_bill_dam->setText(QString::number(0));
            break;
        case Copy::DAMAGED:
            ui->label_bill_dam->setText(QString::number(1000));
            break;
        case Copy::UNUSABLE:
            ui->label_bill_dam->setText(QString::number(5000));
            break;
        }
    }

    //Display total
    ui->label_bill_tot->setText(QString::number(calculatePrice(selectedRent->getCopy()->getVehicle()->getDailyCost(),selectedRent->getInsurance(),NbOfDays,selectedRent->getCopy()->getKilometers(),ui->combo_fuel->currentIndex()*50,ui->comboBox->currentIndex(),QDate(selectedRent->getEnd().getYear(),selectedRent->getEnd().getMonth(),selectedRent->getEnd().getDay()).daysTo(QDate::currentDate()))));

    ui->stackedWidget->setCurrentIndex(1);
}

//Fuel level changed
void MainWindow::on_combo_fuel_currentIndexChanged(int index)
{
    //Mute warnings
    int i = index;
    i++;

    int NbOfDays = QDate(selectedRent->getBegin().getYear(),selectedRent->getBegin().getMonth(),selectedRent->getBegin().getDay()).daysTo(QDate(selectedRent->getEnd().getYear(),selectedRent->getEnd().getMonth(),selectedRent->getEnd().getDay()));
    ui->label_return_realPrice->setText(QString::number(calculatePrice(selectedRent->getCopy()->getVehicle()->getDailyCost(),selectedRent->getInsurance(),NbOfDays,selectedRent->getCopy()->getKilometers(),i*50,ui->comboBox->currentIndex(),QDate(selectedRent->getEnd().getYear(),selectedRent->getEnd().getMonth(),selectedRent->getEnd().getDay()).daysTo(QDate::currentDate()))));
}

//Damage level changed
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    //Mute warnings
    int i = index;
    i++;

    int NbOfDays = QDate(selectedRent->getBegin().getYear(),selectedRent->getBegin().getMonth(),selectedRent->getBegin().getDay()).daysTo(QDate(selectedRent->getEnd().getYear(),selectedRent->getEnd().getMonth(),selectedRent->getEnd().getDay()));
    ui->label_return_realPrice->setText(QString::number(calculatePrice(selectedRent->getCopy()->getVehicle()->getDailyCost(),selectedRent->getInsurance(),NbOfDays,selectedRent->getCopy()->getKilometers(),ui->combo_fuel->currentIndex()*50,ui->comboBox->currentIndex(),QDate(selectedRent->getEnd().getYear(),selectedRent->getEnd().getMonth(),selectedRent->getEnd().getDay()).daysTo(QDate::currentDate()))));
}

//Erase borrower
void MainWindow::on_pushButton_5_clicked()
{
    _borrowerContainer.erase(selectedBorrower);
    selectedBorrower=NULL;
    renderBorrowerContainer();
    ui->pushButton_5->setEnabled(false);
}

//Erase copy
void MainWindow::on_pushButton_6_clicked()
{
    _copyContainer.erase(selectedCopy);
    renderCopyContainer();
    selectedCopy=NULL;
    ui->pushButton_6->setEnabled(false);
}

//Copy sort : ALL
void MainWindow::on_radioButton_4_clicked()
{
    renderCopyContainer();
}

//Copy sort : CAR
void MainWindow::on_radioButton_5_clicked()
{
    removeAllRows(ui->tableWidget_2);

    std::vector<std::string>buffer;
    int minorV=0;

    for(int i=0; i<_copyContainer.size();i++){
        buffer.clear();
        if(_copyContainer.getCopyContainer()[i+1]->isActive()){
            buffer=_copyContainer.display(i+1,Vehicle::car);
            if(buffer.size()>0)
                renderRowInTable(ui->tableWidget_2,i-minorV,buffer);
            else
                minorV++;
        }
        else
            minorV++;
    }
}

//Copy sort : MOTO
void MainWindow::on_radioButton_6_clicked()
{
    removeAllRows(ui->tableWidget_2);

    std::vector<std::string>buffer;
    int minorV=0;

    for(int i=0; i<_copyContainer.size();i++){
        if(_copyContainer.getCopyContainer()[i+1]->isActive()){
            buffer.clear();
            buffer=_copyContainer.display(i+1,Vehicle::moto);
            if(buffer.size()>0)
                renderRowInTable(ui->tableWidget_2,i-minorV,buffer);
            else
                minorV++;
        }
        else
            minorV++;
    }
}

std::vector<Vehicle*> MainWindow::stats(Vehicle::Type c){
    int nb=0;
    std::multimap<int,Vehicle*> sorted;
    std::vector<Vehicle*> returnValue;
    std::vector<Vehicle*> already;

    //Slow iterator
    for(std::vector<Rent*>::iterator it = _rentContainer.begin(); it != _rentContainer.end(); it++){
        if(!in(already,(*it)->getCopy()->getVehicle())){
            if((*it)->getCopy()->getVehicle()->getType()==c){
                already.push_back((*it)->getCopy()->getVehicle());
                //Fast iterator
                for(std::vector<Rent*>::iterator it2 = _rentContainer.begin(); it2 != _rentContainer.end(); it2++){
                    if((*it)->getCopy()->getVehicle()==(*it2)->getCopy()->getVehicle())
                        nb++;
                }
            }
            if(nb>0)
                sorted.insert(std::make_pair(nb,(*it)->getCopy()->getVehicle()));
            nb=0;
        }
    }

    for(std::multimap<int,Vehicle*>::reverse_iterator it3 = sorted.rbegin(); it3 != sorted.rend(); it3++){
        returnValue.push_back((*it3).second);
    }

    return returnValue;
}
