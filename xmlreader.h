#ifndef XMLREADER_H
#define XMLREADER_H
#include <QXmlStreamReader>
#include <QFile>
#include <QString>

#include "const_global.h"

class xmlReader
{
public:
    xmlReader();
    ~xmlReader();
    bool getStatus();
    int getResolution();
    std::string getFPS();
    QString getOperator();
    QString getStart();
    QString getZiel();
    QString getDatum();
    std::string getOffsetBlende();
private:
    QFile file;
    QXmlStreamReader reader;
    QString readElement;
};

#endif // XMLREADER_H
