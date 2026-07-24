#pragma once
#include<string>
#include<iostream>
using namespace std;
enum class Weather
{
    Sunny,
    Rain,
    Fog,
    Night
};

class WeatherManager
{
private:
    Weather currentWeather;

public:
    WeatherManager();

    void readWeather();

    void setWeather(Weather weather);

    Weather getWeather() const;

    string getWeatherName() const;
    
    int getAdditionalGreenTime() const;
};