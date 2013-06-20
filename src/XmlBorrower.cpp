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
    QDomNodeList tab1, tab2;
    QDomElement borrower;
    QDomNode n;
    QDomElement racine = dom->documentElement(); // renvoie la balise racine (xml)
    QDomNode noeud = racine.firstChild(); // renvoie la première balise « borrower »
    std::string firstname("Default"), lastname("Default"), phoneNumber("Default");
    Address address;
    int id(-1);
    bool active(true);


    while(!noeud.isNull())
    {
        // convertit le nœud en élément pour utiliser les
        // méthodes tagName() et attribute()
        borrower = noeud.toElement();
        // vérifie la présence de la balise « borrower »
        if (borrower.tagName() == "borrower")
        {
            tab1 = borrower.childNodes(); // crée un tableau des enfants de « borrower »
            for(i = 0; i < tab1.length(); i++)
            {
                // pour chaque enfant, on extrait la donnée
                n = tab1.item(i);
                // En fonction de la balise, on enregistre dans une variable spécifique.
                if (n.toElement().tagName() == "firstname") firstname = n.firstChild().toText().data().toStdString();
                else if (n.toElement().tagName() == "lastname") lastname = n.firstChild().toText().data().toStdString();
                else if (n.toElement().tagName() == "phone") phoneNumber = n.firstChild().toText().data().toStdString();
                else if (n.toElement().tagName() == "id") id = n.firstChild().toText().data().toInt();
                else if (n.toElement().tagName() == "active") active = n.firstChild().toText().data().toInt();
                else if (n.toElement().tagName() == "address") { // On réitère le traitement dans le cas d'une adresse
                    tab2 = n.toElement().childNodes();
                    for(j = 0; j < tab2.length(); j++) {
                        n = tab2.item(j);
                        if (n.toElement().tagName() == "street") address.setStreet(n.firstChild().toText().data().toStdString());
                        else if(n.toElement().tagName() == "nb") address.setNumber(n.firstChild().toText().data().toInt());
                        else if(n.toElement().tagName() == "city") address.setCity(n.firstChild().toText().data().toStdString());
                        else if(n.toElement().tagName() == "pc") address.setPc(n.firstChild().toText().data().toStdString());
                    }
                }
            }
            borrowerContainer->add(firstname, lastname, address, phoneNumber, id, active);
        }
        noeud = noeud.nextSibling(); // passe au "borrower" suivant
    }
    xml_doc.close();
    return true;
}

bool XmlBorrower::write(BorrowerContainer* borrowerContainer) {

    std::map<int, Borrower*>::iterator it;
    std::map<int, Borrower*> container = borrowerContainer->getBorrowerContainer();
    QDomElement xml;
    QTextStream out;
    QDomDocument *dom = new QDomDocument("BorrowerList"); // Création de l'objet DOM
    QFile file("BorrowerList.xml"); // On choisit le fichier contenant les informations XML.
    file.remove();
    xml = dom->createElement("xml"); // création de la balise "xml"
    dom->appendChild(xml); // filiation de la balise "xml"
    if (!file.open(QIODevice::WriteOnly)) // ouverture du fichier de sauvegarde
        return false; // en écriture
    out.setDevice(&file); // association du flux au fichier

    // Boucle qui pour chaque élément du conteneur va créer un arborescence XML de type borrower
    for(it = container.begin(); it != container.end(); it++) {
        // Création et filiation de la balise borrower
        QDomElement borrower = dom->createElement("borrower");
        xml.appendChild(borrower);

        // Créations et filiations des sous balises de borrower
        QDomElement firstname = dom->createElement("firstname");
        borrower.appendChild(firstname);
        QDomElement lastname = dom->createElement("lastname");
        borrower.appendChild(lastname);
        QDomElement address = dom->createElement("address");
        borrower.appendChild(address);

        // Créations et filiations des sous balises de adress
        QDomElement street = dom->createElement("street");
        address.appendChild(street);
        QDomElement nb = dom->createElement("nb");
        address.appendChild(nb);
        QDomElement city = dom->createElement("city");
        address.appendChild(city);
        QDomElement pc = dom->createElement("pc");
        address.appendChild(pc);

        // Créations et filiations des sous balises de borrower
        QDomElement phone = dom->createElement("phone");
        borrower.appendChild(phone);
        QDomElement id = dom->createElement("id");
        borrower.appendChild(id);
        QDomElement active = dom->createElement("active");
        borrower.appendChild(active);

        // Ici, pour chaque noeud élément, on crée un noeud texte associé en fonction du contenu du conteneur
        firstname.appendChild(QDomText(dom->createTextNode((*it).second->getFirstName().c_str())));
        lastname.appendChild(QDomText(dom->createTextNode((*it).second->getLastName().c_str())));
        street.appendChild(QDomText(dom->createTextNode((*it).second->getAddress().getStreet().c_str())));
        nb.appendChild(QDomText(dom->createTextNode(QString::number((*it).second->getAddress().getNumber()))));
        city.appendChild(QDomText(dom->createTextNode((*it).second->getAddress().getCity().c_str())));
        pc.appendChild(QDomText(dom->createTextNode((*it).second->getAddress().getPc().c_str())));
        phone.appendChild(QDomText(dom->createTextNode((*it).second->getPhoneNumber().c_str())));
        id.appendChild(QDomText(dom->createTextNode(QString::number((*it).first))));
        active.appendChild(QDomText(dom->createTextNode(QString::number((*it).second->isActive()))));

    }

    // insertion en début de document de <?xml version="1.0" ?>
    QDomNode noeud = dom->createProcessingInstruction("xml","version=\"1.0\"");
    dom->insertBefore(noeud, dom->firstChild());
    // sauvegarde dans le flux (deux espaces de décalage dans l'arborescence)
    dom->save(out,2);
    file.close();
    return true;
}

XmlBorrower::~XmlBorrower() {
}
