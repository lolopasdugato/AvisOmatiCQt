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
    bool read(BorrowerContainer* borrower);
    bool write();
    
signals:
    
public slots:
    
};

#endif // XMLBORROWER_H
