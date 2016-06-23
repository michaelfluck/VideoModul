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
    void getConfig();
private:
    QFile file;
    QXmlStreamReader reader;

};

#endif // XMLREADER_H
