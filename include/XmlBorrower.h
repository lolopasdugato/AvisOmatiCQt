#ifndef XMLBORROWER_H
#define XMLBORROWER_H

#include <QWidget>
#include <QtGui>
#include <QtXml>
#include <QMessageBox>
#include "../include/BorrowerContainer.h"
#include "../include/Address.h"

class XmlBorrower : public QWidget
{
    Q_OBJECT

public:
    explicit XmlBorrower(QWidget *parent = 0);
    virtual ~XmlBorrower();

    // Lecture du fichier BorrowerList.xml
    bool read(BorrowerContainer* borrowerContainer);
    // Ecriture dans le fichier BorrowerList.xml
    bool write(BorrowerContainer* borrowerContainer);    
};

#endif // XMLBORROWER_H
