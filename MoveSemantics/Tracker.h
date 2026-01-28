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
    Tracker(int, const char*);
    
    // Destructor
    ~Tracker();

    // Operators
    Tracker& operator=(const Tracker& other);
    Tracker& operator=(Tracker&& other) noexcept;

    void PrintIdentity(const char* label) const
    {
        std::cout << label
            << " | object address = " << this
            << " | id = " << id
            << " | movedFrom = " << std::boolalpha << movedFrom
            << "\n";
    }

private:
    int id;
    static int nextId;
    std::string payload;
    bool movedFrom = false;
};