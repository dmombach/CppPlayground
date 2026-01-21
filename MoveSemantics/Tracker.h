#pragma once
#include <iostream>

class Tracker
{
public:
    Tracker();
    Tracker(const Tracker& other);
    Tracker(Tracker&& other) noexcept;
    ~Tracker();
};