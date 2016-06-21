#ifndef XMLREADER_H
#define XMLREADER_H
#include <QXmlStreamReader>
#include <QFile>

class xmlReader
{
public:
    xmlReader();
    bool getStatus();
private:
    QFile file;
    QXmlStreamReader reader;
};

#endif // XMLREADER_H
