#include "Road.h"   //Road:: use for ---> Yahan Road:: ka matlab hai:
                    // For example : "getRoadName() function Road class ka member function hai."

Road::Road(char name, int vehicles)
    : roadName(name),
      vehicleCount(vehicles),
      signalStatus("RED")
{
}

char Road::getRoadName() const
{
    return roadName;
}

int Road::getVehicleCount() const
{
    return vehicleCount;
}

string Road::getSignalStatus() const
{
    return signalStatus;
}

void Road::setSignalStatus(const string &color)
{
    signalStatus = color;
}

void Road::setVehicleCount(int vehicles)
{
    vehicleCount = vehicles;
}

int Road::getGreenTime() const
{
    if (vehicleCount == 0)
        return 3;
    else if (vehicleCount <= 25)
        return vehicleCount;
    else
        return 30;
}