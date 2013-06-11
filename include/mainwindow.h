#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../include/Rent.h"
#include "../include/BorrowerContainer.h"
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
    
private slots:
    void on_NewBorrower_Clicked();
    void on_ListBorrower_Clicked();

    void on_button_newBorrower_clicked();

private:
    Ui::MainWindow *ui;

    BorrowerContainer _borrowerContainer;

};

#endif // MAINWINDOW_H
