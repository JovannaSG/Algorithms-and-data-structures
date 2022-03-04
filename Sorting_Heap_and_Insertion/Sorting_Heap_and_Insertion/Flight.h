#pragma once
struct stime
{
    int hour;
    int minutes;
};

struct flight
{
    stime time;
    std::string airline;
    std::string nflight;
    std::string airport;
};