#pragma once  // Is se ye header file ek hi baar include hoti hai.

#include <string>  //Kyun ki hum string use kar rahe hain.

using namespace std;  //Taaki har jagah std::string na likh na pade.

class Road
{
private:
    char roadName;
    int vehicleCount;
    string signalStatus;

public:
    Road(char name, int vehicles);

    char getRoadName() const;

    int getVehicleCount() const;

    string getSignalStatus() const;

    void setSignalStatus(const string &color);

    void setVehicleCount(int vehicles);

    int getGreenTime() const;
};