#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <ctime>
#include <iomanip>
#include <limits>

#include "Road.h"
#include "WeatherManager.h"
using namespace std;

class TrafficSignal
{
private:
    vector<Road> roads;

    int day;
    int month;
    int year;

    int hr;
    int min;
    int sec;

    WeatherManager weatherManager;
    
    const string days[7] =
    {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    };

    string dayName;

    map<char, bool> completed;

    static const int YELLOW_TIME = 4;

    int totalEmergencyVehicle = 0;

public:
    TrafficSignal();

    void updateDateTime();

    void inputData();

    void sortRoads();

    void displayPriority();

    static bool compare(const Road &a, const Road &b);

    void countdown(int time);

    void greenSignal(Road &road);

    void yellowSignal(Road &road);

    void activateRoad(Road &road);

    void emergencyMode(Road &road);

    void takeEmergencyInput();

    void normalTraffic();

    void run();

    int calculateTotalVehicles();

    void calculateAverageVehicles(ostream &out);

    int calculateTotalGreenTime();

    int totalCycleTime();

    void displayFinalReport(ostream &out);
};