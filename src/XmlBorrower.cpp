#include "include/XmlBorrower.h"
#include <iostream>

XmlBorrower::XmlBorrower(QWidget *parent) :
    QWidget(parent){

}

bool XmlBorrower::read(BorrowerContainer* borrowerContainer) {
    QDomDocument *dom = new QDomDocument("BorrowerList"); // Création de l'objet DOM
    QFile xml_doc("BorrowerList.xml"); // On choisit le fichier contenant les informations XML.
    if(!xml_doc.open(QIODevice::ReadOnly))// Si l'on n'arrive pas à ouvrir le fichier XML.
    {
        QMessageBox::warning(this,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Vérifiez que le nom est le bon et que le document est bien placé");
        return false;
    }
    if (!dom->setContent(&xml_doc)) // Si l'on n'arrive pas à associer le fichier XML à l'objet DOM.
    {
        xml_doc.close();
        QMessageBox::warning(this,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être attribué à l'objet QDomDocument.");
        return false;
    }


    int i(0), j(0);
    // QString affichage;
    QDomNodeList tab1, tab2;
    QDomElement mesure;
    QDomNode n;
    // QMessageBox a(0);
    QDomElement racine = dom->documentElement(); // renvoie la balise racine
    QDomNode noeud = racine.firstChild(); // renvoie la première balise « mesure »
    std::string firstname("Default"), lastname("Default"), phoneNumber("Default");
    Address address;


    while(!noeud.isNull())
    {
        // convertit le nœud en élément pour utiliser les
        // méthodes tagName() et attribute()
        mesure = noeud.toElement();
        // vérifie la présence de la balise « mesure »
        if (mesure.tagName() == "borrower")
        {
            tab1 = mesure.childNodes(); // crée un tableau des enfants de « mesure »
            for(i = 0; i < tab1.length(); i++)
            {
                // pour chaque enfant, on extrait la donnée et on concatène
                n = tab1.item(i);
                // affichage = affichage + " " + n.firstChild().toText().data();
                if (n.toElement().tagName() == "firstname") firstname = n.firstChild().toText().data().toStdString();
                else if (n.toElement().tagName() == "lastname") lastname = n.firstChild().toText().data().toStdString();
                else if (n.toElement().tagName() == "phone") phoneNumber = n.firstChild().toText().data().toStdString();
                else if (n.toElement().tagName() == "address") { // On réitère le traitement dans le cas d'une adresse
                    tab2 = n.toElement().childNodes();
                    for(j = 0; j < tab2.length(); j++) {
                        n = tab2.item(j);
                        // affichage = affichage + " " + n.firstChild().toText().data();
                        if (n.toElement().tagName() == "street") address.setStreet(n.firstChild().toText().data().toStdString());
                        else if(n.toElement().tagName() == "nb") address.setNumber(n.firstChild().toText().data().toInt());
                        else if(n.toElement().tagName() == "city") address.setCity(n.firstChild().toText().data().toStdString());
                        else if(n.toElement().tagName() == "pc") address.setPc(n.firstChild().toText().data().toStdString());
                    }
                }
            }
            // a.setText(affichage); // affichage dans un QMessageBox
            // a.exec();
            borrowerContainer->add(firstname, lastname, address, phoneNumber);
        }
        noeud = noeud.nextSibling(); // passe à la "mesure" suivante
    }
    xml_doc.close();
    return true;
}

XmlBorrower::~XmlBorrower() {
}
