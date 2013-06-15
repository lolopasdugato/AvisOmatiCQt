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

void MainWindow::on_NewBorrower_Clicked(){
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_ListBorrower_Clicked(){
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_NewVehicle_Clicked(){
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_ListVehicle_Clicked(){
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_NewRent_Clicked(){
    ui->stackedWidget->setCurrentIndex(5);
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

    renderBorrowerList();

    ui->line_new_borro_firstname->clear();
    ui->line_new_borro_surname->clear();
    ui->line_new_borro_number->clear();
    ui->line_new_borro_street->clear();
    ui->line_new_borro_postal->clear();
    ui->line_new_borro_city->clear();
    ui->line_new_borro_phone->clear();
}

void MainWindow::renderBorrowerList(){
    int i=_borrowerContainer.size()-1;
    ui->tableWidget->insertRow(i);
    QTableWidgetItem *firstname = new QTableWidgetItem(QString::fromStdString(_borrowerContainer.display(i)[0]));
    ui->tableWidget->setItem(i, 0, firstname);
    QTableWidgetItem *lastname = new QTableWidgetItem(QString::fromStdString(_borrowerContainer.display(i)[1]));
    ui->tableWidget->setItem(i, 1, lastname);
    QTableWidgetItem *address = new QTableWidgetItem(QString::fromStdString(_borrowerContainer.display(i)[2]));
    ui->tableWidget->setItem(i, 2, address);
    QTableWidgetItem *phone = new QTableWidgetItem(QString::fromStdString(_borrowerContainer.display(i)[3]));
    ui->tableWidget->setItem(i, 3, phone);
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

    _vehicleContainer.add(ui->line_new_vehicle_brand->text().toStdString(),ui->line_new_vehicle_misc->text().toStdString(),type);

    renderVehicleList();

    ui->line_new_vehicle_brand->clear();
    ui->line_new_vehicle_misc->clear();
}

void MainWindow::renderVehicleList(){
    int i=_vehicleContainer.size()-1;
    ui->table_vehicle->insertRow(i);
    QTableWidgetItem *brand = new QTableWidgetItem(QString::fromStdString(_vehicleContainer.display(i)[1]));
    ui->table_vehicle->setItem(i, 0, brand);
    QTableWidgetItem *type = new QTableWidgetItem(QString::fromStdString(_vehicleContainer.display(i)[0]));
    ui->table_vehicle->setItem(i, 1, type);
    QTableWidgetItem *misc = new QTableWidgetItem(QString::fromStdString(_vehicleContainer.display(i)[2]));
    ui->table_vehicle->setItem(i, 2, misc);
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
    ui->label_vehicle_brand_2->setText(returnValue->at(0)->getBrand().c_str());
    ui->label_vehicle_name->setText(returnValue->at(0)->getName().c_str());
    ui->label_vehicle_name_2->setText(returnValue->at(0)->getName().c_str());

    switch(returnValue->at(0)->getType()){
    case Vehicle::car:
        ui->label_vehicle_type->setText("Car");
        ui->label_vehicle_type_2->setText("Car");
        selectedVehicle = new Car(returnValue->at(0));  //Set the selected vehicle
        break;
    case Vehicle::moto:
        ui->label_vehicle_type->setText("Motorcycle");
        ui->label_vehicle_type_2->setText("Motorcycle");
        selectedVehicle = new Motorcycle(returnValue->at(0));   //Set the selected Vehicle
        break;
    }

    ui->label_vehicle_copy->setValue(_copyContainer.getNumberOf(returnValue->at(0)));
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->label_vehicle_copy->value()>_copyContainer.getNumberOf(selectedVehicle)){
        _copyContainer.add(ui->label_vehicle_copy->value(),selectedVehicle);
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
