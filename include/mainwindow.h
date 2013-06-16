#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "../include/Rent.h"
#include "../include/BorrowerContainer.h"
#include "../include/VehicleContainer.h"
#include "../include/CopyContainer.h"
#include "../include/XmlBorrower.h"
#include "../include/Borrower.h"
#include "../include/Address.h"
#include "../include/Date.h"
#include "../include/XmlCopy.h"

std::string toString(const int& i);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void renderVehicleList();
    
private slots:
    void on_NewBorrower_Clicked();
    void on_ListBorrower_Clicked();
    void on_ListVehicle_Clicked();
    void on_NewVehicle_Clicked();
    void on_NewRent_Clicked();
    void on_ListCopy_Clicked();
    void on_RentList_Clicked();

    void on_button_newBorrower_clicked();

    void on_button_newvehicle_clicked();

    void on_table_vehicle_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_tableWidget_2_cellChanged(int row, int column);

    void on_tableWidget_2_clicked(const QModelIndex &index);

    void on_date_rent_return_userDateChanged(const QDate &date);

    void on_date_rent_start_userDateChanged(const QDate &date);

    void on_pushButton_2_clicked();

    void on_save_clicked();

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

    //Render function
    void renderBorrowerContainer();
    void renderVehicleContainer();
    void renderCopyContainer();
    void renderRentContainer();

    //Tools for editing QTableWidget
    void removeAllRows(QTableWidget* table);
    void renderRowInTable(QTableWidget* table, int row, std::vector<std::string> list);
};

#endif // MAINWINDOW_H
