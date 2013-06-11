/**
 * \file      main.cpp
 * \author    Lord Nazdar
 * \version   0.0.1
 * \date      Apr 13, 2013
 * \brief     Main file
 * \details  
 */

#include <iostream>
#include <stdlib.h>
#include "../include/mainwindow.h"
#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

