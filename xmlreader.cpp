/*  --------------------------------------------------------------------------
*   Title:      NTB Bachelorarbeit "VideoModul für ein Kanalreinigungssystem"
*   Autor:      M.Fluck, S.Lutz
*   Datum:      01.07.2016
*   Version:    1.0
*   Zweck:      Auslesen von XML-Files welche über das Webinterface 
*               geschrieben werden.
    --------------------------------------------------------------------------*/
#include "xmlreader.h"

XMLReader::XMLReader()
{
    qDebug() << "XMLReader GO";
}

XMLReader::~XMLReader()
{
    qDebug() << "XMLReader STOPP";
}

bool XMLReader::getStatus()
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

int XMLReader::getResolution()
{
    QXmlStreamReader reader;
    int resolutionW;
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
                                    resolutionW = reader.readElementText().toInt();
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
    return resolutionW;

}

std::string XMLReader::getFPS()
{
    QXmlStreamReader reader;
    QFile file(configXML);
    std::string fps;
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
                                    fps = reader.readElementText().toAscii().constData();
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
    return fps;
}

QString XMLReader::getOperator()
{
    QXmlStreamReader reader;
    QFile file(configXML);
    QString op;
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
                                    op = reader.readElementText();
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
    return op;
}

QString XMLReader::getZiel()
{
    QXmlStreamReader reader;
    QFile file(configXML);
    QString ziel;
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
                                    ziel = reader.readElementText();
                                    if(ziel == "")
                                    {
                                        ziel = "noData";
                                    }
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
    return ziel;
}

QString XMLReader::getStart()
{
    QXmlStreamReader reader;
    QFile file(configXML);
    QString start;
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
                                    start = reader.readElementText();
                                    if(start == "")
                                    {
                                        start = "noData";
                                    }
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
    return start;
}

QString XMLReader::getDatum()
{
    QXmlStreamReader reader;
    QFile file(configXML);
    QString datum;
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
                                    datum = reader.readElementText();
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
    return datum;
}

std::string XMLReader::getOffsetBlende()
{
    QXmlStreamReader reader;
    QFile file(configXML);
    std::string offsetBlende;
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
            else if(reader.name() == "Kanal")
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
                        if(reader.name() == "Kanal")
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
                                    offsetBlende = reader.readElementText().toAscii().constData();
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
    return offsetBlende;
}
