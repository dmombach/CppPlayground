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

void ConstructionVsAssignment()
{
    std::cout << "\n--- Step 1: Start with one element ---\n";
    std::vector<Tracker> v;
    v.emplace_back();   // default constructor

    std::cout << "\n--- Step 2: Add another element ---\n";
    Tracker t;
    v.push_back(t);     // copy constructor

    std::cout << "\n--- Step 3: Replace an element (assignment) ---\n";
    Tracker a;
    v[0] = a;           // copy assignment

    std::cout << "\n--- Step 4: Replace with rvalue (move assignment) ---\n";
    v[1] = Tracker{};   // move assignment

    std::cout << "\n--- Step 5: Force reallocation ---\n";
    v.reserve(10);      // triggers move constructor for each element

    std::cout << "\n--- End of function ---\n";
}

void PrintTrackerIdentity_CopyAssignment()
{
    Tracker a;
    Tracker b;
    
    std::cout << "\n--- Before copy assignment ---\n";
    a.PrintIdentity("a");
    b.PrintIdentity("b");

    std::cout << "\n--- Copy assignment: a = b; ---\n";
    a = b; 

    std::cout << "\n--- After copy assignment ---\n";
    a.PrintIdentity("a");
    b.PrintIdentity("b");
}

void PrintTrackerIdentity_MoveAssignment()
{
    Tracker a;
    Tracker b;

    std::cout << "\n--- Before move assignment ---\n";
    a.PrintIdentity("a");
    b.PrintIdentity("b");

    std::cout << "\n--- Move assignment: a = std::move(b); ---\n";
    a = std::move(b); 

    std::cout << "\n--- After move assignment ---\n";
    a.PrintIdentity("a");
    b.PrintIdentity("b");

    std::cout << "\n---Move construction ---\n";
    Tracker c = std::move(a);
    c.PrintIdentity("c");
    a.PrintIdentity("a (after move)");
}

template <typename T>
void ForwardingTest(T&& value)
{
    std::cout << "Calling ForwardingtTest\n";
    Tracker f(std::forward<T>(value));
}

template <typename... Args>
Tracker MakeTracker_Bad(Args... args)
{
    return Tracker(args...);    // loses rvalue-ness
}

template <typename... Args>
Tracker MakeTracker(Args&&... args)
{
    return Tracker(std::forward<Args>(args)...);
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

    //VectorAssignmentVsConstruction();

    //ConstructionVsAssignment();

    //PrintTrackerIdentity_CopyAssignment();

    //PrintTrackerIdentity_MoveAssignment();

//#pragma region Perfect Forwarding
//
//    Tracker a;
//
//    ForwardingTest(a);              // should COPY 
//    ForwardingTest(std::move(a));   // should MOVE 
//
//    std::cout << "\n--- Passing lvalue --\n";
//    auto t1 = MakeTracker(a);               // should COPY 
//
//    std::cout << "\n--- Passing rvalue ---\n";
//    auto t2 = MakeTracker(std::move(a));    // should MOVE 
//
//#pragma endregion 

//#pragma region Using vector emplace_back 
//
//    std::vector<Tracker> v;
//
//    Tracker a;
//
//    std::cout << "\n--- emplace_back with lvalue ---\n";
//    v.emplace_back(a);               // should COPY 
//
//    std::cout << "\n--- emplace_back with rvalue ---\n";
//    v.emplace_back(std::move(a));    // should MOVE 
//
//    std::cout << "\n--- emplace_back with constructor args ---\n";
//    v.emplace_back(42, "hello");    // constructs directly in place 
//
//#pragma endregion 

#pragma region Vector Reallocations

    std::vector<Tracker> v;
    v.reserve(3);   // optional but helps control the first reallocation

    std::cout << "\n--- push_back #1 ---\n";
    v.push_back(Tracker{ 1, "first" });

    std::cout << "\n--- push_back #2 ---\n";
    v.push_back(Tracker{ 2, "second" });

    std::cout << "\n--- push_back #3 ---\n";
    v.push_back(Tracker{ 3, "third" });

    std::cout << "\n--- push_back #4 (reallocation happens!) ---\n";
    v.push_back(Tracker{ 4, "fourth" });

#pragma endregion

}
