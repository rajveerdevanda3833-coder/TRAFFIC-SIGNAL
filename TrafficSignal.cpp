#include "TrafficSignal.h"

TrafficSignal::TrafficSignal()
{

    updateDateTime();

    completed['A'] = false;
    completed['B'] = false;
    completed['C'] = false;
    completed['D'] = false;

    weatherManager.readWeather();
}

void TrafficSignal::updateDateTime()
{
    time_t now = time(0);

    tm *ltm = localtime(&now);

    day = ltm->tm_mday;
    month = ltm->tm_mon + 1;
    year = ltm->tm_year + 1900;

    hr = ltm->tm_hour;
    min = ltm->tm_min;
    sec = ltm->tm_sec;
    dayName = days[ltm->tm_wday];
}

void TrafficSignal::inputData()
{
    roads.clear(); // Purana data delete

    for (char road = 'A'; road <= 'D'; road++)
    {
        int count;

        cout << "Enter vehicles on Road " << road << " : ";

        while (!(cin >> count) || count < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input. Enter again : ";
        }

        roads.push_back(Road(road, count));
    }
}

void TrafficSignal::sortRoads()
{
    sort(roads.begin(),
         roads.end(),
         compare);
}

void TrafficSignal::displayPriority()
{
    cout << "\n";
    cout << "<< ===== TRAFFIC PRIORITY ===== >>\n";

    for (size_t i = 0; i < roads.size(); i++)
    {
        cout << i + 1
             << ". ROAD "
             << roads[i].getRoadName()
             << " : "
             << roads[i].getVehicleCount()
             << " Vehicles\n";
    }

    cout << "\n";
}

bool TrafficSignal::compare(const Road &a, const Road &b)
{
    return a.getVehicleCount() > b.getVehicleCount();
}
void TrafficSignal::countdown(int time)
{
    while (time > 0)
    {
        cout << "Remaining Time : " << time << endl;

        this_thread::sleep_for(chrono::seconds(1));

        time--;
    }
}

void TrafficSignal::greenSignal(Road &road)
{
    road.setSignalStatus("GREEN");

    for (auto &r : roads)
    {
        cout << "Road "
             << r.getRoadName()
             << " : "
             << r.getSignalStatus()
             << endl;
    }

    int finalGreenTime =
        road.getGreenTime() +
        weatherManager.getAdditionalGreenTime();

    countdown(finalGreenTime);

    road.setSignalStatus("RED");
}
void TrafficSignal::yellowSignal(Road &road)
{
    road.setSignalStatus("YELLOW");

    for (auto &r : roads)
    {
        cout << "Road "
             << r.getRoadName()
             << " : "
             << r.getSignalStatus()
             << endl;
    }

    countdown(YELLOW_TIME);

    road.setSignalStatus("RED");
}
void TrafficSignal::activateRoad(Road &road)
{
    greenSignal(road);

    yellowSignal(road);
}
void TrafficSignal::emergencyMode(Road &road)
{
    cout << "\nEmergency Vehicle Detected!\n";

    activateRoad(road);
}
void TrafficSignal::takeEmergencyInput()
{
    char road;

    cout << "Enter Emergency Road (A/B/C/D) : ";

    cin >> road;

    road = toupper(road);

    if (road == 'A' ||
        road == 'B' ||
        road == 'C' ||
        road == 'D')
    {
        if (completed[road])
        {
            cout << "Emergency on Road "
                 << road
                 << " is already handled.\n";

            return;
        }

        totalEmergencyVehicle++;

        for (auto &r : roads)
        {
            if (r.getRoadName() == road)
            {
                emergencyMode(r);
                break;
            }
        }

        completed[road] = true;
    }
    else
    {
        cout << "Invalid Road\n";
    }
}
void TrafficSignal::normalTraffic()
{
    for (auto &road : roads)
    {
        if (completed[road.getRoadName()])
            continue;

        char choice;

        // Valid input lena
        do
        {
            cout << "\nAny Emergency (Y/N): ";
            cin >> choice;

            choice = toupper(choice);

            if (choice != 'Y' && choice != 'N')
            {
                cout << "Invalid Input! Please enter Y or N.\n";
            }

        } while (choice != 'Y' && choice != 'N');

        // Emergency handle karna
        if (choice == 'Y')
        {
            takeEmergencyInput();
        }

        // Agar ye road emergency me handle nahi hui,
        // to normal signal chalao.
        if (!completed[road.getRoadName()])
        {
            activateRoad(road);

            completed[road.getRoadName()] = true;
        }
    }
}
void TrafficSignal::run()
{
    inputData();

    sortRoads();

    displayPriority();

    normalTraffic();

    updateDateTime();

    displayFinalReport(cout);

    ofstream file("Traffic Signal Report.txt", ios::app);

    if (!file)
    {
        cout << "File Opening Failed\n";
        return;
    }
    displayFinalReport(file);

    file.close();
}
int TrafficSignal::calculateTotalVehicles()
{
    int total = 0;

    for (const auto &r : roads)
    {
        total += r.getVehicleCount();
    }

    return total;
}
void TrafficSignal::calculateAverageVehicles(ostream &out)
{
    if (roads.empty())
    {
        out << "No Data\n";
        return;
    }
    double average =
        (double)calculateTotalVehicles() / roads.size();

    out << setw(35)
        << "Average Vehicles"
        << ": "
        << average
        << endl;

    if (average < 10)
        out << setw(35) << "Traffic Status" << ": Low" << endl;

    else if (average <= 25)
        out << setw(35) << "Traffic Status" << ": Medium" << endl;

    else
        out << setw(35) << "Traffic Status" << ": High" << endl;
}
int TrafficSignal::calculateTotalGreenTime()
{
    int total = 0;

    for (const auto &r : roads)
    {
        total += r.getGreenTime();
    }

    return total;
}
int TrafficSignal::totalCycleTime()
{
    return calculateTotalGreenTime() +
           roads.size() * YELLOW_TIME;
}
void TrafficSignal::displayFinalReport(ostream &out)
{
    if (roads.empty())
    {
        out << "No Vehicle Data Available\n";
        return;
    }
    out << setfill('0');

    out << "Date : "
        << setw(2) << day << "/"
        << setw(2) << month << "/"
        << year << endl;

    out << "Day : " << dayName << endl;

    out << "Time : "
        << setw(2) << hr << ":"
        << setw(2) << min << ":"
        << setw(2) << sec << endl;

    out << setfill(' ');

    out << "\n=============================================\n";
    out << "     SMART TRAFFIC MANAGEMENT REPORT\n";
    out << "=============================================\n\n";

    out << left;
    out<<setw(35)<<"Current Weather"<<": "<<weatherManager.getWeatherName()<<endl;
    out<<setw(35)<<"Additional Green Time"<<": "<<weatherManager.getAdditionalGreenTime()<<" sec"<<endl;
    auto busiest = roads.front();
    auto least = roads.back();
    out << setw(35) << "Total Roads"
        << ": "
        << roads.size()
        << endl;

    out << setw(35) << "Total Vehicles"
        << ": "
        << calculateTotalVehicles()
        << endl;

    calculateAverageVehicles(out);

    out << setw(35)
        << "Most Busy Road"
        << ": "
        << busiest.getRoadName()
        << " ("
        << busiest.getVehicleCount()
        << " Vehicles)"
        << endl;

    out << setw(35)
        << "Least Busy Road"
        << ": "
        << least.getRoadName()
        << " ("
        << least.getVehicleCount()
        << " Vehicles)"
        << endl;

    out << setw(35)
        << "Highest Green Time"
        << ": "
        << busiest.getGreenTime()
        << " sec"
        << endl;

    out << setw(35)
        << "Lowest Green Time"
        << ": "
        << least.getGreenTime()
        << " sec"
        << endl;

    out << setw(35)
        << "Yellow Time"
        << ": "
        << YELLOW_TIME
        << " sec"
        << endl;

    out << setw(35)
        << "Total Green Time"
        << ": "
        << calculateTotalGreenTime()
        << " sec"
        << endl;

    out << setw(35)
        << "Total Yellow Time"
        << ": "
        << roads.size() * YELLOW_TIME
        << " sec"
        << endl;

    out << setw(35)
        << "Total Cycle Time"
        << ": "
        << totalCycleTime()
        << " sec"
        << endl;

    out << setw(35)
        << "Emergency Vehicles"
        << ": "
        << totalEmergencyVehicle
        << endl;

    out << "=========================================\n";
}
