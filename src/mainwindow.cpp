#include "../include/mainwindow.h"
#include "ui_mainwindow.h"

std::string toString(const int& i){
    std::ostringstream oss;
    oss << i;
    return oss.str();
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Load JeanLapin
    XmlBorrower xmlBorrower;
    XmlCopy xmlCopy;

    xmlBorrower.read(&_borrowerContainer);
    xmlCopy.read(&_vehicleContainer,&_copyContainer);

    renderBorrowerContainer();
    renderVehicleContainer();
    renderCopyContainer();

    selectedBorrower=NULL;
    selectedVehicle=NULL;
    selectedCopy=NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_NewBorrower_Clicked(){
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_ListBorrower_Clicked(){
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_ListCopy_Clicked(){
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_NewVehicle_Clicked(){
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_ListVehicle_Clicked(){
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_NewRent_Clicked(){
    ui->stackedWidget->setCurrentIndex(5);
    if(!selectedBorrower||!selectedCopy){
        ui->pushButton_2->setEnabled(false);
        return;
    }
    ui->pushButton_2->setEnabled(true);
}

void MainWindow::on_RentList_Clicked(){
    ui->stackedWidget->setCurrentIndex(8);
}


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
}

void MainWindow::on_pushButton_clicked()
{
   if(ui->label_vehicle_copy->value()>_copyContainer.getNumberOf(selectedVehicle)){
        _copyContainer.add(ui->label_vehicle_copy->value()-_copyContainer.getNumberOf(selectedVehicle),selectedVehicle);
        renderCopyContainer();
    }
}

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
}

void MainWindow::on_tableWidget_2_cellChanged(int row, int column)
{
    //The user change and we save
    //The user can only edit the last two columns
    if(column>3){
        _copyContainer.getCopyContainer()[ui->tableWidget_2->item(row,0)->text().toInt()]->setKilometers(ui->tableWidget_2->item(row,column)->text().toInt());
    }
}

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
}

//-----------------------------------------------------------------------//

void MainWindow::renderCopyContainer(){
    removeAllRows(ui->tableWidget_2);

    for(int i=0; i<_copyContainer.size();i++){
        renderRowInTable(ui->tableWidget_2,i,_copyContainer.display(i));
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

    for(int i=0; i<_borrowerContainer.size();i++){
        renderRowInTable(ui->tableWidget,i,_borrowerContainer.display(i));
    }
}

void MainWindow::renderRentContainer(){
    removeAllRows(ui->tableWidget_3);

    std::vector<std::string> data;

    for(int i=0; i<_rentContainer.size();i++){
        //Preparing data vector
        data.clear();
        data.push_back(toString(_rentContainer[i]->getId()));
        data.push_back(_rentContainer[i]->getCopy()->getVehicle()->getBrand()+" "+_rentContainer[i]->getCopy()->getVehicle()->getName());
        data.push_back(_rentContainer[i]->getBorrower()->getFirstName()+" "+_rentContainer[i]->getBorrower()->getLastName());

        renderRowInTable(ui->tableWidget_3,i,data);
    }
}

//-----------------------------------------------------------------------//

void MainWindow::removeAllRows(QTableWidget* table){
    while (table->rowCount() > 0)
    {
        table->removeRow(0);
    }
}

void MainWindow::renderRowInTable(QTableWidget *table, int row, std::vector<std::string> list){
    table->insertRow(row);
    for(std::vector<std::string>::iterator it=list.begin();it<list.end();it++){
        QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString((*it)));
        table->setItem(row, it-list.begin(), item);
    }
}



void MainWindow::on_date_rent_return_userDateChanged(const QDate &date)
{
    QDate start = ui->date_rent_start->date();
    int NbOfDay = start.daysTo(date);

    ui->label_rent_totalCost->setText(QString::number(selectedCopy->getVehicle()->getDailyCost()*NbOfDay));
}

void MainWindow::on_date_rent_start_userDateChanged(const QDate &date)
{
    QDate end = ui->date_rent_return->date();
    int NbOfDay = date.daysTo(end);

    ui->label_rent_totalCost->setText(QString::number(selectedCopy->getVehicle()->getDailyCost()*NbOfDay));
}

void MainWindow::on_pushButton_2_clicked()
{
    Rent* rent = new Rent(selectedCopy, selectedBorrower, Date(ui->date_rent_start->date().day(),ui->date_rent_start->date().month(),ui->date_rent_start->date().year()), Date(ui->date_rent_return->date().day(),ui->date_rent_return->date().month(),ui->date_rent_return->date().year()));
    _rentContainer.push_back(rent);

    selectedCopy->setDispo(false);
    renderRentContainer();
}

void MainWindow::on_save_clicked(){
    XmlBorrower xmlBorrower;
    XmlCopy xmlCopy;

    xmlBorrower.write(&_borrowerContainer);
    xmlCopy.write(&_copyContainer);
}

void MainWindow::on_radioButton_2_clicked()
{
    renderVehicleContainer();
}

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
