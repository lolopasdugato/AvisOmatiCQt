#include "../include/mainwindow.h"

std::string toString(const int& i){
    std::ostringstream oss;
    oss << i;
    return oss.str();
}

std::vector<std::string> split(QString string){
    std::vector<std::string> returnValue;
    QStringList fields = string.split(QRegExp(",| "));

    for(int i = 0; i<fields.size(); ++i){
        returnValue.push_back(fields[i].toStdString());
    }

    return returnValue;
}
