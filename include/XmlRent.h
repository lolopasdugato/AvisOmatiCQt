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

    bool read(std::vector<Rent*>*, CopyContainer* copyContainer, BorrowerContainer* borrowerContainer);
    bool write(std::vector<Rent*>);

    virtual ~XmlRent();
    
signals:
    
public slots:
    
};

#endif // XMLRENT_H
