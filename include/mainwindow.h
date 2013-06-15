#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../include/Rent.h"
#include "../include/BorrowerContainer.h"
#include "../include/VehicleContainer.h"
#include "../include/CopyContainer.h"
#include "../include/Borrower.h"
#include "../include/Address.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void renderBorrowerList();
    void renderVehicleList();
    
private slots:
    void on_NewBorrower_Clicked();
    void on_ListBorrower_Clicked();
    void on_ListVehicle_Clicked();
    void on_NewVehicle_Clicked();
    void on_NewRent_Clicked();

    void on_button_newBorrower_clicked();

    void on_button_newvehicle_clicked();

    void on_table_vehicle_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_tableWidget_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    BorrowerContainer _borrowerContainer;
    VehicleContainer _vehicleContainer;
    CopyContainer _copyContainer;

    Vehicle* selectedVehicle;
    Borrower* selectedBorrower;
};

#endif // MAINWINDOW_H
