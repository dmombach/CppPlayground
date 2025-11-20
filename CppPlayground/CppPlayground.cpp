
#include <iostream>
#include <string> // for string functions and objects, if needed 
#include "Utilities.h"
#include "Rectangle.h"
#include "MemoryBlock.h"
#include "Lambda.h"
#include "Exception.h"
#include <iomanip> // for std::setprecision
#include <vector>

/*
* using namespace std; // to avoid adding 'std::' before every standard library usage
* declaring the above can cause issues because std got too many functions and objects.
*/

// To avoid writing 'std::' before every standard library usage
using std::cout;
using std::cin;
using std::string;
using std::endl;

void FilesAndExceptions(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    cout << "Hello Jump Starter !" << endl;

    //int x{ 5 };
    //int y{ 10 };
    //cout << x++ << "\n";
    //cout << ++x << "\n";
    //cout << Add(x, y) << "\n";
    //cout << Multiply(x, y) << "\n";

    //bool check{ "Hello" == "Hello" };
    //cout << check << "\n";

    //int z{ y };
    //cout << "z {y}: " << z << "\n";

    //y += 10;
    //cout << "z [y += 10]: " << z << "\n";

    //z = y;
    //y += 100;
    //cout << "z = y [y += 100]: " << (z == y) << "\n";

    //int a{};
    //cout << "default init a: " << a << "\n";

    //Rectangle rect1{ 2, 3 };
    //cout << "Area of rect1: " << rect1.area() << "\n";

    //Rectangle const rect2{ 4, 5 };
    //cout << "Area of rect2: " << rect2.area() << "\n";

    //int const b{ 1 }; // not modifiable
    //// b = 2; // error: assignment of read-only variable 'b'
    //int const& bref{ b }; // readonly ;) 

    //std::vector<MemoryBlock> mb;
    //mb.push_back(MemoryBlock(25));
    //mb.push_back(MemoryBlock(75));

    //// Insert a new element in the second position of the vector.
    //mb.insert(mb.begin() + 1, MemoryBlock(50));

    //Lambda lambdaObj{};
    //cout << "Lambda test: " << lambdaObj.testLambda() << "\n";

    //try
    //{
    //    Exception ex{};
    //    
    //    ex.MyFunc(300);
    //}
    //catch (const std::invalid_argument& e)
    //{
    //    cout << "Exception caught: " << e.what() << "\n";

    //    return -1;
    //}

    FilesAndExceptions(argc, argv);

    return 0;
}

void FilesAndExceptions(int argc, char* argv[])
{
    string filename1("file1.txt");
    string filename2("file2.txt");

    try
    {
        if (argc > 2)
        {
            filename1 = argv[1];
            filename2 = argv[2];
        }

        cout << "Using file names " << filename1 << " and " << filename2 << endl;

        if (IsFileDiff(filename1, filename2))
        {
            cout << "+++ Files are different." << endl;
        }
        else
        {
            cout << "=== Files match." << endl;
        }
    }
    catch (const Win32Exception& e)
    {
        std::ios state(nullptr);
        state.copyfmt(std::cout); // save cout state
        std::cout << e.what() << endl;
        std::cout << "Error code: 0x" << std::hex << std::uppercase << std::setw(8) << std::setfill('0')
            << e.GetErrorCode() << endl;
        std::cout.copyfmt(state); // restore previous formatting 
    }
}