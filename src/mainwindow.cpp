#include "../include/mainwindow.h"
#include "ui_mainwindow.h"

std::string toString(const int& i){
    std::ostringstream oss;
    oss << i;
    return oss.str();
}

std::vector<std::string> split(QString string){
    std::vector<std::string> returnValue;
    QStringList fields = string.split(QRegExp(",| "));

    for(int i = 0; i<fields.size(); ++i){
        returnValue.push_back(fields[i].toStdString());
    }

    return returnValue;
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Load JeanLapin
    XmlBorrower xmlBorrower;
    XmlCopy xmlCopy;
    XmlRent xmlRent;

    xmlBorrower.read(&_borrowerContainer);
    xmlCopy.read(&_vehicleContainer,&_copyContainer);
    xmlRent.read(&_rentContainer,&_copyContainer,&_borrowerContainer);

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
    if(selectedBorrower&&selectedCopy)
        ui->stackedWidget->setCurrentIndex(5);
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

    ui->label_vehicle_copy->setEnabled(true);
    ui->pushButton->setEnabled(true);
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

    ui->pushButton_5->setEnabled(true);
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

    ui->pushButton_6->setEnabled(true);
}

//-----------------------------------------------------------------------//

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

    for(int i=0; i<_rentContainer.size();i++){
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

void MainWindow::on_refresh_clicked(){
    renderCopyContainer();
    renderRentContainer();
    renderBorrowerContainer();
    renderVehicleContainer();
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
        QTableWidgetItem *item = new QTableWidgetItem((*it).c_str());
        table->setItem(row, it-list.begin(), item);
    }
}



void MainWindow::on_date_rent_return_userDateChanged(const QDate &date)
{
    if(selectedBorrower||selectedCopy){
        QDate start = ui->date_rent_start->date();
        int NbOfDay = start.daysTo(date);
        ui->label_rent_totalCost->setText(QString::number(calculatePrice(selectedCopy->getVehicle()->getDailyCost(),ui->radio_insu->isChecked(),NbOfDay,selectedCopy->getKilometers())));
    }
}

void MainWindow::on_date_rent_start_userDateChanged(const QDate &date)
{
    if(selectedBorrower||selectedCopy){
        QDate end = ui->date_rent_return->date();
        int NbOfDay = date.daysTo(end);

        ui->label_rent_totalCost->setText(QString::number(calculatePrice(selectedCopy->getVehicle()->getDailyCost(),ui->radio_insu->isChecked(),NbOfDay,selectedCopy->getKilometers())));
    }
}

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
    selectedCopy=NULL;
    ui->label_vehicle_brand_2->clear();
    ui->label_vehicle_name_2->clear();
    ui->label_vehicle_id_2->clear();
    ui->label_vehicle_type_2->clear();
    ui->label_rent_dailyCost->clear();
    ui->pushButton_2->setEnabled(false);
}

void MainWindow::on_save_clicked(){
    XmlBorrower xmlBorrower;
    XmlCopy xmlCopy;
    XmlRent xmlRent;

    xmlBorrower.write(&_borrowerContainer);
    xmlCopy.write(&_copyContainer);
    xmlRent.write(_rentContainer);
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

void MainWindow::on_radio_insu_clicked()
{
    if(selectedBorrower||selectedCopy){
        QDate end = ui->date_rent_return->date();
        int NbOfDay = ui->date_rent_start->date().daysTo(end);
        ui->label_rent_totalCost->setText(QString::number(calculatePrice(selectedCopy->getVehicle()->getDailyCost(),true,NbOfDay,selectedCopy->getKilometers())));
    }
}

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

void MainWindow::on_combo_fuel_currentIndexChanged(int index)
{
    int NbOfDays = QDate(selectedRent->getBegin().getYear(),selectedRent->getBegin().getMonth(),selectedRent->getBegin().getDay()).daysTo(QDate(selectedRent->getEnd().getYear(),selectedRent->getEnd().getMonth(),selectedRent->getEnd().getDay()));
    ui->label_return_realPrice->setText(QString::number(calculatePrice(selectedRent->getCopy()->getVehicle()->getDailyCost(),selectedRent->getInsurance(),NbOfDays,selectedRent->getCopy()->getKilometers(),ui->combo_fuel->currentIndex()*50,ui->comboBox->currentIndex(),QDate(selectedRent->getEnd().getYear(),selectedRent->getEnd().getMonth(),selectedRent->getEnd().getDay()).daysTo(QDate::currentDate()))));
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    int NbOfDays = QDate(selectedRent->getBegin().getYear(),selectedRent->getBegin().getMonth(),selectedRent->getBegin().getDay()).daysTo(QDate(selectedRent->getEnd().getYear(),selectedRent->getEnd().getMonth(),selectedRent->getEnd().getDay()));
    ui->label_return_realPrice->setText(QString::number(calculatePrice(selectedRent->getCopy()->getVehicle()->getDailyCost(),selectedRent->getInsurance(),NbOfDays,selectedRent->getCopy()->getKilometers(),ui->combo_fuel->currentIndex()*50,ui->comboBox->currentIndex(),QDate(selectedRent->getEnd().getYear(),selectedRent->getEnd().getMonth(),selectedRent->getEnd().getDay()).daysTo(QDate::currentDate()))));
}

void MainWindow::on_pushButton_5_clicked()
{
    _borrowerContainer.erase(selectedBorrower);
    selectedBorrower=NULL;
    renderBorrowerContainer();
    ui->pushButton_5->setEnabled(false);
}

void MainWindow::on_pushButton_6_clicked()
{
    _copyContainer.erase(selectedCopy);
    renderCopyContainer();
    selectedCopy=NULL;
    ui->pushButton_6->setEnabled(false);
}

void MainWindow::on_radioButton_4_clicked()
{
    renderCopyContainer();
}

void MainWindow::on_radioButton_5_clicked()
{
    removeAllRows(ui->tableWidget_2);

    std::vector<std::string>buffer;
    int minorV=0;

    for(int i=0; i<_copyContainer.size();i++){
        buffer.clear();
        buffer=_copyContainer.display(i+1,Vehicle::car);
        if(buffer.size()>0)
            renderRowInTable(ui->tableWidget_2,i-minorV,buffer);
        else
            minorV++;
    }
}

void MainWindow::on_radioButton_6_clicked()
{
    removeAllRows(ui->tableWidget_2);

    std::vector<std::string>buffer;
    int minorV=0;

    for(int i=0; i<_copyContainer.size();i++){
        buffer.clear();
        buffer=_copyContainer.display(i+1,Vehicle::moto);
        if(buffer.size()>0)
            renderRowInTable(ui->tableWidget_2,i-minorV,buffer);
        else
            minorV++;
    }
}

void MainWindow::on_search_Clicked(){
    int currentId = ui->stackedWidget->currentIndex();
    int i=0;
    bool ok=false;
    QString searchValue;

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
                renderRowInTable(ui->tableWidget,i,returnValue[i]->display());
            }
        }
        break;
    }
}
