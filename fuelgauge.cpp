#include "fuelgauge.h"

FuelGauge::FuelGauge()
{
    qDebug() << "FuelGauge GO";
}

FuelGauge::~FuelGauge()
{
    qDebug() << "FuelGauge STOPP";
}

void FuelGauge::run()
{
    QXmlStreamWriter writer;
    QFile file("/var/www/html/config/fuelgauge.xml");

    while(1)
    {
        int c = getCharge();
        setFuelGaugeLEDs(c);

        if(!file.open(QIODevice::WriteOnly))
        {
            qDebug() << "Error XMLWriter";
        }
        else
        {
            writer.setDevice(&file);
            writer.setAutoFormatting(true);

            writer.writeStartDocument();

            writer.writeStartElement("Video");

            writer.writeStartElement("Fuel");

            writer.writeCharacters(QString::number(c));

            writer.writeEndElement();
            writer.writeEndElement();
            writer.writeEndDocument();
            file.close();
        }
        sleep(30); // 30 Sekunden sleep
    }
}
