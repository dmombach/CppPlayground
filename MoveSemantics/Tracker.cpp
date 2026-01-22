#include "Tracker.h"

int Tracker::nextId = 1;

Tracker::Tracker() 
    : id(nextId++), payload("default payload")
{
    std::cout << "default constructor [id = " << id << "]\n";
}

Tracker::Tracker(const Tracker& other)
    : id(nextId++)
{
    std::cout << "copy constructor [from id = " << other.id 
        << " -> new id = " << id << "]\n";
}

Tracker::Tracker(Tracker&& other) noexcept
    : id(nextId++),
    payload(std::move(other.payload))
{
    std::cout << "move assignment [from id = " << other.id
        << " -> new id = " << id << "]\n";

    other.movedFrom = true;
}

Tracker::~Tracker()
{
    std::cout << "destructor [id = " << id << "]\n";
}

Tracker& Tracker::operator=(const Tracker& other)
{
    std::cout << "copy assignment [from id = " << other.id
        << " -> id = " << id << "]\n";

    if (this != &other)
    {
        payload = other.payload;
    }

    return *this;
}

Tracker& Tracker::operator=(Tracker&& other) noexcept
{
    std::cout << "move assignment [from id = " << other.id
        << " -> id = " << id << "]\n";

    if (this != &other)
    {
        payload = std::move(other.payload);
    }

    return *this;
}
