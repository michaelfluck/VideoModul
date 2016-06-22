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
private:
    QFile file;
    QXmlStreamReader reader;
    QString filename;
};

#endif // XMLREADER_H
