#pragma once
#include <iostream>
#include <string>

class Tracker
{
public:
    // Constructors
    Tracker();
    Tracker(const Tracker& other);
    Tracker(Tracker&& other) noexcept;
    
    // Destructor
    ~Tracker();

    // Operators
    Tracker& operator=(const Tracker& other);
    Tracker& operator=(Tracker&& other) noexcept;

private:
    int id;
    static int nextId;
    std::string payload;
    bool movedFrom = false;
};