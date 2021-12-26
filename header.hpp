#pragma once
#include <fstream>
#include "MyException.hpp"
#include <iostream>
#include "DateAndTime.hpp"
#include <cstdlib>
#include <string>

using namespace std;

template <class typeData>
class BinaryFile : public fstream
{
private:
    typeData **Array;
    int SizeArray = 2;
    int CurrentCountPtr = 0;
    long ArrayAddress = 0;
    long ArrayPos = 0;
    long backArray = 0;
    long ArrayNew = 0;
    long ArrayOld = 0;

public:
    BinaryFile(string nameFile) : basic_fstream(nameFile, ios::in | ios::binary | ios::out | ios::trunc)
    {
        try
        {

            if (is_open())
            {
                Array = new typeData *[SizeArray];
                for (int i = 0; i < SizeArray; i++)
                    Array[i] = new typeData;
                seekg(0, ios::beg);
                write((char *)&SizeArray, sizeof(int));
                write((char *)&CurrentCountPtr, sizeof(int));
                ArrayAddress = tellg();
                write((char *)&ArrayAddress, sizeof(int));
                ArrayNew = tellg();
                write((char *)&Array, sizeof(typeData));
                ArrayPos = tellg();
            }
            else
                throw MyException("file doesnt open!");
        }
        catch (MyException &ex)
        {
            cout << ex.What() << endl;
        }
    }

    void AddElement(typeData &el)
    {

        seekg(0, ios::beg);
        read((char *)&SizeArray, sizeof(int));
        read((char *)&CurrentCountPtr, sizeof(int));
        read((char *)&ArrayAddress, sizeof(int));
        seekp(ArrayAddress, ios::beg);
        if (SizeArray == CurrentCountPtr)
        {
            incrementSizeArray(el);
        }
        else
        {

            CurrentCountPtr = CurrentCountPtr + 1;
            Array[CurrentCountPtr - 1] = new typeData;
            Array[CurrentCountPtr - 1][0] = el;
            seekg(0, ios::beg);
            write((char *)&SizeArray, sizeof(int));
            write((char *)&CurrentCountPtr, sizeof(int));
            write((char *)&ArrayAddress, sizeof(int));

            write((char *)&Array, sizeof(typeData));
            seekg(ArrayPos, ios::beg);
            for (int i = 0; i < CurrentCountPtr; i++)
            {
                write((char *)&Array[i][0], sizeof(typeData));
            }
        }
    }

    void incrementSizeArray(typeData &element)
    {

        SizeArray = SizeArray * 2;

        seekg(0, ios::beg);
        write((char *)&SizeArray, sizeof(int));

        seekg(ArrayAddress, ios::beg);

        ArrayOld = tellp();

        seekg(0, ios::end);

        ArrayPos = tellg();

        seekp(ArrayOld, ios::beg);
        read((char *)&ArrayAddress, sizeof(int));
        ArrayOld = tellp();
        seekg(ArrayPos, ios::beg);
        ArrayAddress = tellg();
        seekp(8, ios::beg);

        write((char *)&ArrayAddress, sizeof(int));
        seekg(ArrayPos, ios::beg);
        ArrayNew = tellg();

        seekg(ArrayPos, ios::beg);
        for (int i = 0; i < CurrentCountPtr; i++)
        {
            write((char *)&Array[i][0], sizeof(typeData));
        }
        AddElement(element);
    }

    void getArrayPos()
    {
        cout << ArrayAddress << endl;
        cout << ArrayNew << endl;
        cout << ArrayPos << endl;
    }

    void Review()
    {
        seekg(0, ios::beg);
        read((char *)&SizeArray, sizeof(int));
        read((char *)&CurrentCountPtr, sizeof(int));
        read((char *)&ArrayAddress, sizeof(int));
        typeData **NewArray;
        NewArray = new typeData *[SizeArray];
        for (int i = 0; i < SizeArray; i++)
        {
            NewArray[i] = new typeData;
        }
        cout << "Размерность массива указателей: " << SizeArray << endl;
        cout << "Текущее кол-во указателей: " << CurrentCountPtr << endl;
        read((char *)&NewArray, sizeof(typeData));
        seekp(ArrayPos, ios::beg);
        for (int i = 0; i < CurrentCountPtr; i++)
        {
            read((char *)&NewArray[i][0], sizeof(typeData));
            cout << NewArray[i][0] << endl;
        }
    }

    void DeleteElement()
    {
        seekp(4, ios::beg);
        read((char *)&CurrentCountPtr, sizeof(int));
        if (CurrentCountPtr > 0)
        {
            CurrentCountPtr--;
            seekp(4, ios::beg);
            write((char *)&CurrentCountPtr, sizeof(int));
        }
        else
        {
            cout << "Файл пуст!" << endl;
        }
    }

    void Sort()
    {

        seekg(12, ios::beg);
        read((char *)&Array, sizeof(typeData));
        seekg(ArrayPos, ios::beg);
        for (int i = 0; i < CurrentCountPtr; i++)
        {
            read((char *)&Array[i][0], sizeof(typeData));
        }
        for (int startIndex = 0; startIndex < CurrentCountPtr - 1; startIndex++)
        {
            int smallestIndex = startIndex;
            for (int currentIndex = startIndex + 1; currentIndex < CurrentCountPtr; ++currentIndex)
            {
                if (Array[currentIndex][0] < Array[smallestIndex][0])
                {
                    smallestIndex = currentIndex;
                }
            }
            std::swap(Array[startIndex], Array[smallestIndex]);
        }

        seekp(12, ios::beg);
        write((char *)&Array, sizeof(typeData));
        seekg(ArrayPos, ios::beg);
        for (int i = 0; i < CurrentCountPtr; ++i)
        {
            write((char *)&Array[i][0], sizeof(typeData));
        }
    }

    void Update(string fileN)
    {
        fstream fileCopy(fileN, ios::binary | ios::out | ios::trunc);
        if (!fileCopy)
        {
            cout << "file doesnt open";
        }
        else
        {
            int sz;
            int curr;
            int Addr;
            typeData **Arr;
            seekg(0, ios::beg);
            read((char *)&sz, sizeof(int));
            read((char *)&curr, sizeof(int));
            read((char *)&Addr, sizeof(int));
            Arr = new typeData *[sz];
            for (int i = 0; i < sz; i++)
            {
                Arr[i] = new typeData;
            }
            seekg(12, ios::beg);
            read((char *)&Arr, sizeof(typeData));
            seekg(ArrayPos, ios::beg);
            for (int i = 0; i < curr; i++)
            {
                read((char *)&Arr[i][0], sizeof(typeData));
            }
            fileCopy.seekp(0, ios::beg);
            fileCopy.write((char *)&sz, sizeof(int));
            fileCopy.write((char *)&curr, sizeof(int));
            fileCopy.write((char *)&Addr, sizeof(int));
            fileCopy.write((char *)&Arr, sizeof(typeData));
            for (int i = 0; i < curr; i++)
            {
                fileCopy.write((char *)&Arr[i][0], sizeof(typeData));
            }
        }

        fileCopy.close();
    }

    ~BinaryFile()
    {
        for (int i = 0; i < CurrentCountPtr; ++i)
        {
            delete[] Array[i];
        }
        delete[] Array;
        close();
    }
};

template <>

void BinaryFile<DateAndTime>::Sort()
{
    seekg(12, ios::beg);
    read((char*)&Array , sizeof(int));
    seekg(ArrayPos, ios::beg);
        for (int i = 0; i < CurrentCountPtr; i++)
        {
            *this >> Array[i][0];
        }
    //seekg(ArrayPos, ios::beg);
    for (int i = 0; i < CurrentCountPtr - 1; ++i)
    {
        int f = i;
        for (int currentIndex = i + 1; currentIndex < CurrentCountPtr; currentIndex++)
        {
            if (Array[currentIndex][0] < Array[f][0])
            {
                f = currentIndex;
            }
            
            std::swap(Array[i], Array[f]);
        }
    }
    // seekg(ArrayPos, ios::beg);
    seekp(12, ios::beg);
    write((char *)&Array, sizeof(int));
    seekp(ArrayPos, ios::beg);
    for (int i = 0; i < CurrentCountPtr; ++i)
    {
        *this << Array[i][0];
    }
}

template <>
void BinaryFile<DateAndTime>::Review()
{

    seekg(0, ios::beg);
    read((char *)&SizeArray, sizeof(int));
    read((char *)&CurrentCountPtr, sizeof(int));
    read((char *)&ArrayAddress, sizeof(int));
    DateAndTime **NerArray;
    NerArray = new DateAndTime *[SizeArray];
    for (int i = 0; i < SizeArray; i++)
    {
        NerArray[i] = new DateAndTime;
    }
    cout << "Размерность массива указателей: " << SizeArray << endl;
    cout << "Текущее кол-во указателей: " << CurrentCountPtr << endl;
    // seekg(ArrayPos, ios::beg);
    seekg(12, ios::beg);
    //seekg(ArrayNew, ios::beg);
    read((char *)&NerArray, sizeof(int));
    seekg(ArrayPos, ios::beg);
    for (int i = 0; i < CurrentCountPtr; i++)
    {
        *this >> NerArray[i][0];
        cout << NerArray[i][0] << endl;
    }
}

template <>
void BinaryFile<DateAndTime>::AddElement(DateAndTime &obj)
{
    seekg(0, ios::beg);
    read((char *)&SizeArray, sizeof(int));
    read((char *)&CurrentCountPtr, sizeof(int));
    read((char *)&ArrayAddress, sizeof(int));
    seekp(ArrayAddress, ios::beg);
    if (SizeArray == CurrentCountPtr)
    {
        incrementSizeArray(obj);
    }
    else
    {

        CurrentCountPtr = CurrentCountPtr + 1;
        Array[CurrentCountPtr - 1] = new DateAndTime;
        Array[CurrentCountPtr - 1][0].set_day(obj.get_day());
        Array[CurrentCountPtr - 1][0].set_month(obj.get_month());
        Array[CurrentCountPtr - 1][0].set_year(obj.get_year());
        seekp(0, ios::beg);
        write((char *)&SizeArray, sizeof(int));
        write((char *)&CurrentCountPtr, sizeof(int));
        write((char *)&ArrayAddress, sizeof(int));
        seekp(12, ios::beg);
        // seekg(ArrayNew, ios::beg);
        write((char *)&Array, sizeof(int));
        seekp(ArrayPos, ios::beg);
        for (int i = 0; i < CurrentCountPtr; i++)
        {
            *this << Array[i][0];
        }
    }
}