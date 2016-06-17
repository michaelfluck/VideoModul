#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "camera.h"
#include "picproc.h"

using namespace std;

int main()
{
    cout << "VideoModul läuft..." << endl;

    Camera cam;
    for (int i = 0; i < 8; ++i)
    {
        cam.getPicture();
        sleep(1);
    }
    cout << "Bilder fertig" << endl;
    procPictures();
    cout << "Bilder kopiert" << endl;
    return 0;
}
