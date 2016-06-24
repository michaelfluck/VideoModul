#ifndef XMLREADER_H
#define XMLREADER_H
#include <QXmlStreamReader>
#include <QFile>
#include <QString>

class xmlReader
{
public:
    xmlReader();
    ~xmlReader();
    bool getStatus();
    QString getAufloesung();
    QString getFPS();
    QString getOperator();
    QString getOrt();
    QString getFreitext();
private:
    QFile file;
    QXmlStreamReader reader;
    QString readElement;

};

#endif // XMLREADER_H
