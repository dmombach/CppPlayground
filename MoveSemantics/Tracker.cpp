#include "Tracker.h"

Tracker::Tracker()
{
    std::cout << "default constructor\n";
}

Tracker::Tracker(const Tracker& other)
{
    std::cout << "copy constructor\n";
}

Tracker::Tracker(Tracker&& other) noexcept
{
    std::cout << "move constructor\n";
}

Tracker::~Tracker()
{
    std::cout << "destructor\n";
}
