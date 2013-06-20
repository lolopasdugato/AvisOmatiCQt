#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QInputDialog>
#include <math.h>
#include "../include/Rent.h"
#include "../include/BorrowerContainer.h"
#include "../include/VehicleContainer.h"
#include "../include/CopyContainer.h"
#include "../include/XmlBorrower.h"
#include "../include/Borrower.h"
#include "../include/Address.h"
#include "../include/Date.h"
#include "../include/XmlCopy.h"
#include "../include/XmlRent.h"

//Tools
std::string toString(const int& i);
template<typename Type> bool in(std::vector<Type> firstOp, Type secondOp);
std::vector<std::string> split(QString string);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    //Page change
    void on_NewBorrower_Clicked();
    void on_ListBorrower_Clicked();
    void on_ListVehicle_Clicked();
    void on_NewVehicle_Clicked();
    void on_NewRent_Clicked();
    void on_ListCopy_Clicked();
    void on_RentList_Clicked();
    void on_returnRent_Clicked();
    void on_search_Clicked();
    void on_stats_clicked();
    void on_save_clicked();
    void on_refresh_clicked();

    //Others
    void on_button_newBorrower_clicked();                           //Add New Borrower
    void on_button_newvehicle_clicked();                            //Add new Vehicle
    void on_pushButton_2_clicked();                                 //Add new rent
    void on_pushButton_clicked();                                   //Add new copy

    void on_tableWidget_2_cellChanged(int row, int column);         //Change in Copy table

    void on_tableWidget_clicked(const QModelIndex &index);          //Click on Borrower table
    void on_table_vehicle_clicked(const QModelIndex &index);        //Click on Vehicle table
    void on_tableWidget_2_clicked(const QModelIndex &index);        //Click on Copy table
    void on_tableWidget_3_clicked(const QModelIndex &index);        //Click rent table

    void on_date_rent_return_userDateChanged(const QDate &date);    //Start date changed
    void on_date_rent_start_userDateChanged(const QDate &date);     //End date changed

    void on_pushButton_4_clicked();                                 //Rent return
    void on_pushButton_3_clicked();                                 //Edit bill

    void on_radio_insu_clicked();                                   //Insurance
    void on_radio_noinsu_clicked();                                 //No Insurance
    void on_combo_fuel_currentIndexChanged(int index);              //Fuel level changed
    void on_comboBox_currentIndexChanged(int index);                //Damage level changed

    void on_pushButton_5_clicked();                                 //Erase borrower
    void on_pushButton_6_clicked();                                 //Erase copy

    void on_radioButton_2_clicked();                                //Vehicle sort : ALL
    void on_radioButton_3_clicked();                                //Vehicle sort : CAR
    void on_radioButton_clicked();                                  //Vehicle sort : MOTO

    void on_radioButton_4_clicked();                                //Copy sort : ALL
    void on_radioButton_5_clicked();                                //Copy sort : CAR
    void on_radioButton_6_clicked();                                //Copy sort : MOTO

private:
    Ui::MainWindow *ui;

    //Containers
    BorrowerContainer _borrowerContainer;
    VehicleContainer _vehicleContainer;
    CopyContainer _copyContainer;
    std::vector<Rent*> _rentContainer;

    //Selected attributes
    Vehicle* selectedVehicle;
    Borrower* selectedBorrower;
    Copy* selectedCopy;
    Rent* selectedRent;

    //Render function
    void renderBorrowerContainer();
    void renderVehicleContainer();
    void renderCopyContainer();
    void renderRentContainer();

    //Tools for editing QTableWidget
    void removeAllRows(QTableWidget* table);
    void renderRowInTable(QTableWidget* table, int row, std::vector<std::string> list);

    //Other cool functions
    std::vector<Vehicle*> stats(Vehicle::Type c);
    int calculatePrice(int price, bool insu, int NbOfDay, int nbKm, int fuelMalus=0, int damageMalus=0, int daysOver=0);
};

#endif // MAINWINDOW_H
