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

QString xmlReader::getAufloesung()
{
    QXmlStreamReader reader;
    QFile file(configXML);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Error at reading XML-File" + configXML;
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
                    if(reader.isEndElement())
                    {
                        reader.readNext();
                        break;
                    }
                    else if(reader.isCharacters())
                    {
                        reader.readNext();
                    }
                    else if(reader.isStartElement())
                    {
                        if(reader.name() == "Aufloesung")
                        {
                            while(!reader.atEnd())
                            {
                                if(reader.isEndElement())
                                {
                                    reader.readNext();
                                    break;
                                }
                                else if(reader.isStartElement())
                                {
                                    return reader.readElementText();
                                    reader.readNext();
                                    break;
                                }
                                else if(reader.isCharacters())
                                {
                                    reader.readNext();
                                }
                                else
                                {
                                    reader.readNext();
                                }
                            }
                        }
                        reader.readNext();
                    }
                }
            }
            else
            {
                reader.readNext();
            }
        }
        else
        {
            reader.readNext();
        }
    }
    file.close();
}

QString xmlReader::getFPS()
{
    QXmlStreamReader reader;
    QFile file(configXML);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Error at reading XML-File" + configXML;
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
            else if(reader.name() == "FPS")
            {
                while(!reader.atEnd())
                {
                    if(reader.isEndElement())
                    {
                        reader.readNext();
                        break;
                    }
                    else if(reader.isCharacters())
                    {
                        reader.readNext();
                    }
                    else if(reader.isStartElement())
                    {
                        if(reader.name() == "FPS")
                        {
                            while(!reader.atEnd())
                            {
                                if(reader.isEndElement())
                                {
                                    reader.readNext();
                                    break;
                                }
                                else if(reader.isStartElement())
                                {
                                    return reader.readElementText();
                                    reader.readNext();
                                    break;
                                }
                                else if(reader.isCharacters())
                                {
                                    reader.readNext();
                                }
                                else
                                {
                                    reader.readNext();
                                }
                            }
                        }
                        reader.readNext();
                    }
                }
            }
            else
            {
                reader.readNext();
            }
        }
        else
        {
            reader.readNext();
        }
    }
    file.close();
}

QString xmlReader::getOperator()
{
    QXmlStreamReader reader;
    QFile file(configXML);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Error at reading XML-File" + configXML;
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
            else if(reader.name() == "Operator")
            {
                while(!reader.atEnd())
                {
                    if(reader.isEndElement())
                    {
                        reader.readNext();
                        break;
                    }
                    else if(reader.isCharacters())
                    {
                        reader.readNext();
                    }
                    else if(reader.isStartElement())
                    {
                        if(reader.name() == "Operator")
                        {
                            while(!reader.atEnd())
                            {
                                if(reader.isEndElement())
                                {
                                    reader.readNext();
                                    break;
                                }
                                else if(reader.isStartElement())
                                {
                                    return reader.readElementText();
                                    reader.readNext();
                                    break;
                                }
                                else if(reader.isCharacters())
                                {
                                    reader.readNext();
                                }
                                else
                                {
                                    reader.readNext();
                                }
                            }
                        }
                        reader.readNext();
                    }
                }
            }
            else
            {
                reader.readNext();
            }
        }
        else
        {
            reader.readNext();
        }
    }
    file.close();
}

QString xmlReader::getZiel()
{
    QXmlStreamReader reader;
    QFile file(configXML);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Error at reading XML-File" + configXML;
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
            else if(reader.name() == "Ziel")
            {
                while(!reader.atEnd())
                {
                    if(reader.isEndElement())
                    {
                        reader.readNext();
                        break;
                    }
                    else if(reader.isCharacters())
                    {
                        reader.readNext();
                    }
                    else if(reader.isStartElement())
                    {
                        if(reader.name() == "Ziel")
                        {
                            while(!reader.atEnd())
                            {
                                if(reader.isEndElement())
                                {
                                    reader.readNext();
                                    break;
                                }
                                else if(reader.isStartElement())
                                {
                                    return reader.readElementText();
                                    reader.readNext();
                                    break;
                                }
                                else if(reader.isCharacters())
                                {
                                    reader.readNext();
                                }
                                else
                                {
                                    reader.readNext();
                                }
                            }
                        }
                        reader.readNext();
                    }
                }
            }
            else
            {
                reader.readNext();
            }
        }
        else
        {
            reader.readNext();
        }
    }
    file.close();
}

QString xmlReader::getStart()
{
    QXmlStreamReader reader;
    QFile file(configXML);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Error at reading XML-File" + configXML;
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
            else if(reader.name() == "Start")
            {
                while(!reader.atEnd())
                {
                    if(reader.isEndElement())
                    {
                        reader.readNext();
                        break;
                    }
                    else if(reader.isCharacters())
                    {
                        reader.readNext();
                    }
                    else if(reader.isStartElement())
                    {
                        if(reader.name() == "Start")
                        {
                            while(!reader.atEnd())
                            {
                                if(reader.isEndElement())
                                {
                                    reader.readNext();
                                    break;
                                }
                                else if(reader.isStartElement())
                                {
                                    return reader.readElementText();
                                    reader.readNext();
                                    break;
                                }
                                else if(reader.isCharacters())
                                {
                                    reader.readNext();
                                }
                                else
                                {
                                    reader.readNext();
                                }
                            }
                        }
                        reader.readNext();
                    }
                }
            }
            else
            {
                reader.readNext();
            }
        }
        else
        {
            reader.readNext();
        }
    }
    file.close();
}

QString xmlReader::getDatum()
{
    QXmlStreamReader reader;
    QFile file(configXML);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Error at reading XML-File" + configXML;
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
            else if(reader.name() == "Date")
            {
                while(!reader.atEnd())
                {
                    if(reader.isEndElement())
                    {
                        reader.readNext();
                        break;
                    }
                    else if(reader.isCharacters())
                    {
                        reader.readNext();
                    }
                    else if(reader.isStartElement())
                    {
                        if(reader.name() == "Date")
                        {
                            while(!reader.atEnd())
                            {
                                if(reader.isEndElement())
                                {
                                    reader.readNext();
                                    break;
                                }
                                else if(reader.isStartElement())
                                {
                                    return reader.readElementText();
                                    reader.readNext();
                                    break;
                                }
                                else if(reader.isCharacters())
                                {
                                    reader.readNext();
                                }
                                else
                                {
                                    reader.readNext();
                                }
                            }
                        }
                        reader.readNext();
                    }
                }
            }
            else
            {
                reader.readNext();
            }
        }
        else
        {
            reader.readNext();
        }
    }
    file.close();
}
