#ifndef XMLRENT_H
#define XMLRENT_H

#include "../include/Rent.h"
#include "../include/CopyContainer.h"
#include "../include/BorrowerContainer.h"
#include <QWidget>
#include <QtGui>
#include <QtXml>
#include <QMessageBox>

class XmlRent : public QWidget
{
    Q_OBJECT
public:
    explicit XmlRent(QWidget *parent = 0);
    virtual ~XmlRent();
    // Lecture du fichier RentList.xml
    bool read(std::vector<Rent*>*, CopyContainer* copyContainer, BorrowerContainer* borrowerContainer);
    // Ecriture dans le fichier RentList.xml
    bool write(std::vector<Rent*>);    
};

#endif // XMLRENT_H
