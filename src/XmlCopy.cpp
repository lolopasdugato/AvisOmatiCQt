#include "include/XmlCopy.h"

XmlCopy::XmlCopy(QWidget *parent) :
    QWidget(parent)
{
}

bool XmlCopy::read(VehicleContainer* vehicleContainer, CopyContainer* copyContainer) {

    QDomDocument *dom = new QDomDocument("CopyList"); // Création de l'objet DOM
    QFile xml_doc("CopyList.xml"); // On choisit le fichier contenant les informations XML.
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

    int i(0);
    QDomNodeList tab1;
    QDomElement copyElement, VehCharElement;
    QDomNode n;
    QDomElement racine = dom->documentElement(); // renvoie la balise racine
    QDomNode noeud = racine.firstChild(), noeud2; // renvoie la première balise « copy »
    std::vector<Vehicle*> b;

    // variables liées à un exemplaire
    int kilometers(0);
    Copy::Status status = Copy::NEW;
    bool dispo(false);
    int id(-1);
    bool active=false;

    // variables liées à un véhicule
    std::string brand("Default"), name("Default"), stringType("Default");
    float cost(0);
    Vehicle::Type type = Vehicle::car;

    while(!noeud.isNull())
    {
        // convertit le nœud en élément pour utiliser les
        // méthodes tagName() et attribute()
        copyElement = noeud.toElement();
        // vérifie la présence de la balise « copy »
        if (copyElement.tagName() == "copy")
        {
            noeud2 = copyElement.firstChild();
            while (!noeud2.isNull()) {

                VehCharElement = noeud2.toElement();
                // récupère les valeurs liées à un véhicule
                if (VehCharElement.tagName() == "vehicle") {
                    tab1 = VehCharElement.childNodes();
                    for(i = 0; i < tab1.length(); i++) {
                        n = tab1.item(i);
                        if (n.toElement().tagName() == "type") {
                            stringType = n.firstChild().toText().data().toStdString();
                            if (stringType == "moto") type = Vehicle::moto;
                        }
                        else if (n.toElement().tagName() == "brand") brand = n.firstChild().toText().data().toStdString();
                        else if (n.toElement().tagName() == "model") name = n.firstChild().toText().data().toStdString();
                        else if (n.toElement().tagName() == "dailyprice") cost = n.firstChild().toText().data().toFloat();
                    }

                    std::vector<std::string> a;

                    a.push_back(brand);
                    a.push_back(name);
                    b = vehicleContainer->search(a);
                    if (b.size() == 0 || (b.size() != 0 && !(b.front()->getName() == name && b.front()->getBrand() == brand))) vehicleContainer->add(brand, name, type, cost);

                }
                // Récupère les valeurs liées à un exemplaire
                else if (VehCharElement.tagName() == "characteristics") {
                    tab1 = VehCharElement.childNodes();
                    for(i = 0; i < tab1.length(); i++) {
                        n = tab1.item(i);
                        if (n.toElement().tagName() == "kilometers") kilometers = n.firstChild().toText().data().toInt();
                        else if (n.toElement().tagName() == "status") {
                            if(n.firstChild().toText().data() == "new") status = Copy::NEW;
                            else if (n.firstChild().toText().data() == "damaged") status = Copy::DAMAGED;
                            else status = Copy::UNUSABLE;
                        }
                        else if (n.toElement().tagName() == "dispo") dispo = n.firstChild().toText().data().toInt();
                        else if (n.toElement().tagName() == "id") id = n.firstChild().toText().data().toInt();
                        else if (n.toElement().tagName() == "active") active = n.firstChild().toText().data().toInt();
                    }
                    if (b.size() == 0 || (b.size() != 0 && !(b.front()->getName() == name && b.front()->getBrand() == brand))) copyContainer->add(kilometers, status, dispo, vehicleContainer->getVehicleList().back(), id);
                    else copyContainer->add(kilometers, status, dispo, b.front(), id, active);
                }
                noeud2 = noeud2.nextSibling();
            }
            // a.setText(affichage); // affichage dans un QMessageBox
            // a.exec();
        }
        noeud = noeud.nextSibling(); // passe à la "copy" suivante
    }
    xml_doc.close();
    return true;
}

bool XmlCopy::write(CopyContainer* copyContainer) {

    std::map<int, Copy*>::iterator it;
    std::map<int, Copy*> container = copyContainer->getCopyContainer();
    QDomElement xml;
    QTextStream out;
    QDomDocument *dom = new QDomDocument("CopyList"); // Création de l'objet DOM
    QFile file("CopyList.xml"); // On choisit le fichier contenant les informations XML.
    file.remove();

    xml = dom->createElement("xml"); // création de la balise "xml"
    dom->appendChild(xml); // filiation de la balise "xml"
    if (!file.open(QIODevice::WriteOnly)) // ouverture du fichier de sauvegarde
        return false; // en écriture
    out.setDevice(&file); // association du flux au fichier

    for(it = container.begin(); it != container.end(); it++) {
        QDomElement copy = dom->createElement("copy");
        xml.appendChild(copy);

        //Affiliation au noeud copy
        QDomElement vehicle = dom->createElement("vehicle");
        copy.appendChild(vehicle);
        QDomElement characteristics = dom->createElement("characteristics");
        copy.appendChild(characteristics);

        // Affiliation au noeud vehicle
        QDomElement type = dom->createElement("type");
        vehicle.appendChild(type);
        QDomElement brand = dom->createElement("brand");
        vehicle.appendChild(brand);
        QDomElement model = dom->createElement("model");
        vehicle.appendChild(model);
        QDomElement dailyprice = dom->createElement("dailyprice");
        vehicle.appendChild(dailyprice);

        // Affiliation au noeud characteristics
        QDomElement kilometers = dom->createElement("kilometers");
        characteristics.appendChild(kilometers);
        QDomElement status = dom->createElement("status");
        characteristics.appendChild(status);
        QDomElement dispo = dom->createElement("dispo");
        characteristics.appendChild(dispo);
        QDomElement id = dom->createElement("id");
        characteristics.appendChild(id);
        QDomElement active = dom->createElement("active");
        characteristics.appendChild(active);

        // Ecriture des données en mémoire pour le véhicule
        if((*it).second->getVehicle()->getType() == Vehicle::moto) type.appendChild(QDomText(dom->createTextNode("moto")));
        else type.appendChild(QDomText(dom->createTextNode("auto")));
        brand.appendChild(QDomText(dom->createTextNode((*it).second->getVehicle()->getBrand().c_str())));
        model.appendChild(QDomText(dom->createTextNode((*it).second->getVehicle()->getName().c_str())));
        dailyprice.appendChild(QDomText(dom->createTextNode(QString::number((*it).second->getVehicle()->getDailyCost()))));

        // Ecriture des données en mémoire des exemplaires
        kilometers.appendChild(QDomText(dom->createTextNode(QString::number((*it).second->getKilometers()))));
        dispo.appendChild(QDomText(dom->createTextNode(QString::number((*it).second->isDispo()))));
        if((*it).second->getStatus() == Copy::NEW) status.appendChild(QDomText(dom->createTextNode("new")));
        else if((*it).second->getStatus() == Copy::DAMAGED) status.appendChild(QDomText(dom->createTextNode("damaged")));
        else status.appendChild(QDomText(dom->createTextNode("unusable")));
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

XmlCopy::~XmlCopy() {
}
