#include <QDebug>
#include <iostream>

#include "xmlreader.h"
#include "const_global.h"



xmlReader::xmlReader()
{
    qDebug() << "XMLReader GO";
}

xmlReader::~xmlReader()
{
    qDebug() << "XMLReader STOPP";
}

bool xmlReader::getStatus()
{
    QXmlStreamReader reader;
    QFile file(onoffXML);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Error at reading XML-File";
    }

    reader.setDevice(&file);
    reader.readNext();
    while(!reader.atEnd())
    {
        if(reader.isStartElement())
        {
            if(reader.name() == "Video")
            {
                reader.readNext();
            }
            else if(reader.name() == "Status")
            {
                while(!reader.atEnd())
                {
                    QString status = reader.readElementText();
                    if(status == "On")
                    {
                        return true;
                    }else{
                        return false;
                    }
                    if(reader.isEndElement())
                    {
                        reader.readNext();
                        break;
                    }
                    else if(reader.isCharacters())
                    {
                        reader.readNext();
                    }
                }
                break;
            }
        }else{
            reader.readNext();
        }
    }
    return false;
}

void xmlReader::getConfig()
{
    QXmlStreamReader reader;
    QFile file(configXML);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Error at reading XML-File";
    }

    reader.setDevice(&file);
    reader.readNext();
    while(!reader.atEnd())
    {
        if(reader.isStartElement())
        {
            if(reader.name() == "Config")
            {
                reader.readNext();
            }
            else if(reader.name() == "Aufloesung")
            {
                while(!reader.atEnd())
                {
                    QString aufloesung = reader.readElementText();
                    if(reader.isEndElement())
                    {
                        reader.readNext();
                        break;
                    }
                    else if(reader.isCharacters())
                    {
                        reader.readNext();
                    }
                }
                break;
            }
        }else{
            reader.readNext();
        }
    }
}
