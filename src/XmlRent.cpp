#include "include/XmlRent.h"

XmlRent::XmlRent(QWidget *parent) :
    QWidget(parent)
{
}

bool XmlRent::read(std::vector<Rent *> *rentContainer, CopyContainer* copyContainer, BorrowerContainer* borrowerContainer) {

    QDomDocument *dom = new QDomDocument("RentList"); // Création de l'objet DOM
    QFile xml_doc("RentList.xml"); // On choisit le fichier contenant les informations XML.
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

    Date begin, end;
    int copyID, borrowerID;
    bool status(false), insurance(false);


    while(!noeud.isNull())
    {
        // convertit le nœud en élément pour utiliser les
        // méthodes tagName() et attribute()
        mesure = noeud.toElement();
        // vérifie la présence de la balise « mesure »
        if (mesure.tagName() == "rent")
        {
            tab1 = mesure.childNodes(); // crée un tableau des enfants de « mesure »
            for(i = 0; i < tab1.length(); i++)
            {
                // pour chaque enfant, on extrait la donnée et on concatène
                n = tab1.item(i);
                // affichage = affichage + " " + n.firstChild().toText().data();
                if (n.toElement().tagName() == "copy") copyID = n.firstChild().toText().data().toInt();
                else if (n.toElement().tagName() == "borrower") borrowerID = n.firstChild().toText().data().toInt();
                else if (n.toElement().tagName() == "status") status = n.firstChild().toText().data().toInt();
                else if (n.toElement().tagName() == "insurance") insurance = n.firstChild().toText().data().toInt();
                else if (n.toElement().tagName() == "begin") { // On réitère le traitement dans le cas d'une date
                    tab2 = n.toElement().childNodes();
                    for(j = 0; j < tab2.length(); j++) {
                        n = tab2.item(j);
                        // affichage = affichage + " " + n.firstChild().toText().data();
                        if(n.toElement().tagName() == "day1") begin.setDay(n.firstChild().toText().data().toInt());
                        else if(n.toElement().tagName() == "month1") begin.setMonth(n.firstChild().toText().data().toInt());
                        else if(n.toElement().tagName() == "year1") begin.setYear(n.firstChild().toText().data().toInt());
                    }
                }
                else if (n.toElement().tagName() == "end") {
                    tab2 = n.toElement().childNodes();
                    for(j = 0; j < tab2.length(); j++) {
                        n = tab2.item(j);
                        // affichage = affichage + " " + n.firstChild().toText().data();
                        if(n.toElement().tagName() == "day2") end.setDay(n.firstChild().toText().data().toInt());
                        else if(n.toElement().tagName() == "month2") end.setMonth(n.firstChild().toText().data().toInt());
                        else if(n.toElement().tagName() == "year2") end.setYear(n.firstChild().toText().data().toInt());
                    }
                }
            }
            // a.setText(affichage); // affichage dans un QMessageBox
            // a.exec();
            Rent* a = new Rent(copyContainer->getCopyContainer().at(copyID), borrowerContainer->getBorrowerContainer().at(borrowerID), begin, end);
            a->setInsurance(insurance);
            a->setStatus(status);
            rentContainer->push_back(a);
        }
        noeud = noeud.nextSibling(); // passe à la "mesure" suivante
    }
    xml_doc.close();
    return true;
}

bool XmlRent::write(std::vector<Rent*> rent) {

    /* Tests
    BorrowerContainer *borrowerContainer = new BorrowerContainer;
    Address addresss;
    borrowerContainer->add("Jean", "Jacques", addresss, "465789123");
    borrowerContainer->add("Jean", "Lapin", addresss, "465487496546");
    */

    std::vector<Rent*>::iterator it;
    QDomElement xml;
    QTextStream out;
    QDomDocument *dom = new QDomDocument("RentList"); // Création de l'objet DOM
    QFile file("RentList.xml"); // On choisit le fichier contenant les informations XML.
    file.remove();
    xml = dom->createElement("xml"); // création de la balise "xml"
    dom->appendChild(xml); // filiation de la balise "xml"
    if (!file.open(QIODevice::WriteOnly)) // ouverture du fichier de sauvegarde
        return false; // en écriture
    out.setDevice(&file); // association du flux au fichier

    for(it = rent.begin(); it != rent.end(); it++) {
        QDomElement rent = dom->createElement("rent");
        xml.appendChild(rent);

        QDomElement copy = dom->createElement("copy");
        rent.appendChild(copy);
        QDomElement borrower = dom->createElement("borrower");
        rent.appendChild(borrower);
        QDomElement begin = dom->createElement("begin");
        rent.appendChild(begin);
        QDomElement end = dom->createElement("end");
        rent.appendChild(end);
        QDomElement status = dom->createElement("status");
        rent.appendChild(status);
        QDomElement insurance = dom->createElement("insurance");
        rent.appendChild(insurance);

        QDomElement day1 = dom->createElement("day1");
        begin.appendChild(day1);
        QDomElement day2 = dom->createElement("day2");
        end.appendChild(day2);
        QDomElement month1 = dom->createElement("month1");
        begin.appendChild(month1);
        QDomElement month2 = dom->createElement("month2");
        end.appendChild(month2);
        QDomElement year1 = dom->createElement("year1");
        begin.appendChild(year1);
        QDomElement year2 = dom->createElement("year2");
        end.appendChild(year2);

        copy.appendChild(QDomText(dom->createTextNode(QString::number((*it)->getCopy()->getId()))));
        borrower.appendChild(QDomText(dom->createTextNode(QString::number((*it)->getBorrower()->getId()))));
        day1.appendChild(QDomText(dom->createTextNode(QString::number((*it)->getBegin().getDay()))));
        day2.appendChild(QDomText(dom->createTextNode(QString::number((*it)->getEnd().getDay()))));
        month1.appendChild(QDomText(dom->createTextNode(QString::number((*it)->getBegin().getMonth()))));
        month2.appendChild(QDomText(dom->createTextNode(QString::number((*it)->getEnd().getMonth()))));
        year1.appendChild(QDomText(dom->createTextNode(QString::number((*it)->getBegin().getYear()))));
        year2.appendChild(QDomText(dom->createTextNode(QString::number((*it)->getEnd().getYear()))));
        status.appendChild(QDomText(dom->createTextNode(QString::number((*it)->getStatus()))));
        insurance.appendChild(QDomText(dom->createTextNode(QString::number((*it)->getInsurance()))));

    }

    // insertion en début de document de <?xml version="1.0" ?>
    QDomNode noeud = dom->createProcessingInstruction("xml","version=\"1.0\"");
    dom->insertBefore(noeud, dom->firstChild());
    // sauvegarde dans le flux (deux espaces de décalage dans l'arborescence)
    dom->save(out,2);
    file.close();
    return true;
}

XmlRent::~XmlRent() {
}
