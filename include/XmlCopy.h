#ifndef XMLCOPY_H
#define XMLCOPY_H

#include <QWidget>
#include <QtGui>
#include <QtXml>
#include <QMessageBox>
#include "../include/VehicleContainer.h"
#include "../include/CopyContainer.h"

class XmlCopy : public QWidget
{
    Q_OBJECT
public:
    explicit XmlCopy(QWidget *parent = 0);
    virtual ~XmlCopy();
    // Lecture du fichier CopyList.xml
    bool read(VehicleContainer* vehicleContainer, CopyContainer* copyContainer);
    // Ecriture dans le fichier CopyList.xml
    bool write(CopyContainer* copyContainer);   
};

#endif // XMLCOPY_H
