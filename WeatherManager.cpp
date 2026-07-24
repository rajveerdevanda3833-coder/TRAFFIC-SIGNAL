#include "WeatherManager.h"
#include <limits>

WeatherManager::WeatherManager()
    : currentWeather(Weather::Sunny)
{
}

void WeatherManager::readWeather()
{
    int choice;

    while (true)
    {
        cout << "\n========== WEATHER MENU ==========\n";
        cout << "1. Sunny\n";
        cout << "2. Rain\n";
        cout << "3. Fog\n";
        cout << "4. Night\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cin.clear();                   // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input

            cout << "\n❌ Invalid input! Please enter a number.\n";
            continue;
        }
        if (choice < 1 || choice > 4)
        {
            cout << "Invalid choice! Please enter between 1 and 4.\n";  // Discard invalid input
            continue;
        }
        switch (choice)
        {
        case 1:
            setWeather(Weather::Sunny);
            return;

        case 2:
            setWeather(Weather::Rain);
            return;

        case 3:
            setWeather(Weather::Fog);
            return;

        case 4:
            setWeather(Weather::Night);
            return;

        default:
            cout << "\n❌ Invalid choice! Please enter a number between 1 and 4.\n";
        }
    }
}

void WeatherManager::setWeather(Weather weather)
{
    currentWeather = weather;
}

Weather WeatherManager::getWeather() const
{
    return currentWeather;
}

string WeatherManager::getWeatherName() const
{
    switch (currentWeather)
    {
    case Weather::Sunny:
        return "Sunny";

    case Weather::Rain:
        return "Rain";

    case Weather::Fog:
        return "Fog";

    case Weather::Night:
        return "Night";

    default:
        return "Unknown";
    }
}
int WeatherManager::getAdditionalGreenTime() const
{
    switch (currentWeather)
    {
    case Weather::Sunny:
        return 0;

    case Weather::Rain:
        return 5;

    case Weather::Fog:
        return 7;

    case Weather::Night:
        return 2;
    default :
    return 0;    
    }

}