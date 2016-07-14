#include <pigpio.h>
#include <stdio.h>
#include <math.h>

#include "const_global.h"

void gpioInit();
int getAngle();
int getOnOff();
int getVideoOnOff();
void setLEDsOn();
void setLEDsOff();
void setFuelGaugeLEDs(int charge);
void initFuelGauge();
int emptyCheck();
void setChargeFull();
void setChargeEmpty();
int getCharge();
