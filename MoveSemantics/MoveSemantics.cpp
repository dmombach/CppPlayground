#include "Tracker.h"
#include <vector>

Tracker MakeTracker()
{
    Tracker t;
    return t;               // no move, goes through RVO so object is built directly on calling variable (c in main(), in this case)
    return std::move(t);    // forces move, disables RVO
}

void TakeByValue(Tracker t)
{
    std::cout << "Inside TakeByValue\n";
}

void TaksByConstRef(const Tracker& t)
{
    std::cout << "Inside TakeByConstRef\n";
}

void TakeByRvalueRef(Tracker&& t)
{
    std::cout << "Inside TakeByRvalueRef\n";
}

void VectorExperiment()
{
    std::vector<Tracker> v;
    v.reserve(3);   // optional, but helps control behavior

    std::cout << "--- push_back #1 ---\n";
    v.push_back(Tracker{});

    std::cout << "--- push_back #2 ---\n";
    v.push_back(Tracker{});

    std::cout << "--- push_back #3 ---\n";
    v.push_back(Tracker{});

    std::cout << "--- push_back #4 (reallocation happens) ---\n";
    v.push_back(Tracker{});
}

void VectorAssignmentVsConstruction()
{
    std::cout << "--- default construction ---\n";
    std::vector<Tracker> v;
    v.emplace_back();   // default constructor 

    std::cout << "--- copy construction ---\n";
    Tracker t;
    v.push_back(t);   // copy constructor 

    std::cout << "--- move construction ---\n";
    v.push_back(Tracker{});   // move constructor 

    std::cout << "--- reallocation (move or copy constructors) ---\n";
    v.reserve(10);   // triggers moves of existing elements 

    std::cout << "--- copy assignment ---\n";
    Tracker a;
    v[0] = a;   // copy assignment

    std::cout << "--- move assignment ---\n";
    v[1] = Tracker{};   // move assignment

    std::cout << "--- end of function (destructors) ---\n";
}

int main()
{
    //Tracker a;
    //Tracker b = a;              // copy
    ////Tracker b = std::move(a);   // guaranteed move
    //Tracker c = MakeTracker();  // move (usually)

    //std::cout << "\n-- -- --\n\n";

    //Tracker d;
    //TakeByValue(d);             // copy 
    //TakeByValue(std::move(d));  // move 

    //Tracker e;
    //TaksByConstRef(e);          // no copy, no move 
    //TakeByRvalueRef(Tracker{}); // binds to temporary 

    //std::cout << "\n-- -- --\n\n";

    //VectorExperiment();

    VectorAssignmentVsConstruction();
}
