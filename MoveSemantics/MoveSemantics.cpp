#include "Tracker.h"

Tracker MakeTracker()
{
    Tracker t;
    return t;               // no move, goes through RVO so object is built directly on calling variable (c in main(), in this case)
    return std::move(t);    // forces move, disables RVO
}

int main()
{
    Tracker a;
    Tracker b = a;              // copy
    //Tracker b = std::move(a);   // guaranteed move
    Tracker c = MakeTracker();  // move (usually)
}
