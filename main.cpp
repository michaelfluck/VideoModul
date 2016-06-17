#include <QCoreApplication>
#include <iostream>
#include "camera.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << "VideoModul läuft..." << endl;

    //camera = new Camera();

    return a.exec();
}
