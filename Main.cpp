#include "header.hpp"
#include <iostream>
#include <string>
#include "DataMethods.hpp"
using namespace std;

int main()
{
    BinaryFile<int> binFile("DateBinary.dat");

    int a = 12;
    int b = 13;
    int c = 1024;
    
    binFile.AddElement(c);
    binFile.AddElement(b);
    binFile.AddElement(a);
    
    binFile.Sort();
    binFile.Review();

    BinaryFile<DateAndTime> DateFile("binary.dat");

    DateAndTime data(1, 2, 3, 4, 5, 6);
    DateAndTime data2(10, 10, 10, 10, 10, 10);
    DateFile.AddElement(data);
    DateFile.AddElement(data2);
    DateFile.AddElement(data);

    DateFile.Review();

    return 0;
}