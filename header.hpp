#pragma once
#include <fstream>
#include "MyException.hpp"
#include <iostream>
#include "DateAndTime.hpp"
#include <cstdlib>
#include <string>
#include <time.h>
using namespace std;

template <class typeData>
class BinaryFile : public fstream
{
private:
    int SizeArray = 2;
    int PtrBeginArray = 0;
    int PtrFile = 0;
    int CurrentCountPtr = 0;
    int CounterPtr = 0;
    typeData data;

public:
    BinaryFile(string nameFile) : basic_fstream(nameFile, ios::in | ios::binary | ios::out | ios::trunc)
    {
        try
        {
            if (is_open())
            {
                seekp(0, ios::beg);
                write((char *)&SizeArray, sizeof(int));
                write((char *)&CurrentCountPtr, sizeof(int));
                PtrFile = tellg();
                CounterPtr = sizeof(int);
                seekg(PtrFile + CounterPtr, ios::beg);
                PtrBeginArray = tellg();
                cout << PtrBeginArray << endl;
                seekg(PtrFile, ios::beg);
                write((char *)&PtrBeginArray, sizeof(int));
                SizeArray = CurrentCountPtr = PtrFile = CounterPtr = PtrBeginArray = 0;
            }
            else
                throw MyException("file doesnt open!");
        }
        catch (MyException &ex)
        {
            cout << ex.What() << endl;
        }
    }

    BinaryFile(string nameFile, ios_base::openmode _Mode) : basic_fstream(nameFile, _Mode)
    {
        getPosition();
    }

    fstream &operator<<(typeData &obj)
    {
        write((char *)&obj, sizeof(typeData));
        return *this;
    }

    fstream &operator>>(typeData &obj)
    {
        read((char *)&obj, sizeof(typeData));
        return *this;
    }


    void AddElement(typeData el)
    {
        seekg(0, ios::beg);
        read((char *)&SizeArray, sizeof(int));
        read((char *)&CurrentCountPtr, sizeof(int));
        read((char *)&PtrBeginArray, sizeof(int));

        seekg(PtrBeginArray, ios::beg);
        PtrFile = tellp();
        int DataAddress;
        if (SizeArray != CurrentCountPtr)
        {
            CurrentCountPtr += 1;
            seekg(4, ios::beg);
            write((char *)&CurrentCountPtr, sizeof(int));
            
            seekg(PtrFile + CounterPtr, ios::beg);
            *this << el;
            CounterPtr = CounterPtr + sizeof(typeData);
        }
        else{
            
            incrementSizeArray(el);
            
        }
        PtrBeginArray = SizeArray = CurrentCountPtr = PtrFile = DataAddress = 0;
    }

    void incrementSizeArray(typeData element)
    {
        SizeArray = SizeArray * 2;
        seekg(0, ios::beg);
        write((char *)&SizeArray, sizeof(int));
        seekg(PtrBeginArray, ios::beg);
        int DataOld = tellp();
        seekg(0, ios::end);
        int DataNew = tellg();
        int DataAddress;
        PtrBeginArray = tellg();
        for (int i = 0; i < CurrentCountPtr; i++)
        {
            seekg(DataOld, ios::beg);
            *this >> data;
            DataOld = tellp();
            seekg(DataNew, ios::beg);
            
            
            *this << data;
           
            
            DataNew = tellg();
            
        }
        seekg(8, ios::beg);
        write((char *)&PtrBeginArray, sizeof(int));
        
        AddElement(element);
        DataNew = DataOld =  0;
    }

    void Review()
    {
        seekg(0, ios::beg);
        read((char *)&SizeArray, sizeof(int));
        read((char *)&CurrentCountPtr, sizeof(int));
        read((char *)&PtrBeginArray, sizeof(int));
        cout << "Текущий размер массива --> " << SizeArray << endl;
        cout << "Текущее кол-во указателей --> " << CurrentCountPtr << endl;

        seekp(PtrBeginArray, ios::beg);

        int DataAddress;
        int DataElement;
        for (int i = 0; i < CurrentCountPtr; i++)
        {
            DataAddress = tellg();
            *this >> data;
            
            PtrFile = tellp();
            seekg(DataAddress, ios::beg);
            *this >> data;
            cout << i + 1 << " --> " << data << endl;
            seekg(PtrFile, ios::beg);
        }
        DataAddress = 0;
        DataElement = 0;
    }

    void DeleteElement()
    {
        seekg(4, ios::beg);
        read((char *)&CurrentCountPtr, sizeof(int));
        
        if (CurrentCountPtr > 0)
        {
            CurrentCountPtr--;
            seekg(4, ios::beg);
            write((char *)&CurrentCountPtr, sizeof(int));
            CounterPtr = CounterPtr - sizeof(typeData);
            
        }
        else
        {
            cout << "Файл пуст!";
        }
        SizeArray = CurrentCountPtr = PtrFile = PtrBeginArray = 0;
    }

    void Sort()
    {
        int aData, bData;
        int aDataPos, bDataPos;
        typeData dat;
        for (int i = CurrentCountPtr - 1; i > 0; i--)
        {
            seekg(0, ios::beg);
            read((char *)&SizeArray, sizeof(int));
            read((char *)&CurrentCountPtr, sizeof(int));
            read((char *)&PtrBeginArray, sizeof(int));
            seekp(PtrBeginArray, ios::beg);
            for (int j = 0; j < i; j++)
            {
                aDataPos = tellg();
                *this >> data;
                PtrFile = tellp();
                bDataPos = tellg();
                *this >> data;
                seekg(aDataPos, ios::beg);
                *this >> data;
                seekg(bDataPos, ios::beg);
                *this >> dat;
                if (data > dat)
                {
                    typeData temp = data;
                    seekp(aDataPos, ios::beg);
                    *this << dat;
                    seekg(bDataPos, ios::beg);
                    *this << temp;
                }
                seekp(PtrFile, ios::beg);
            }
        }
        SizeArray = CurrentCountPtr = PtrBeginArray = PtrFile = aData = bData = 0;
    }

    void getPosition()
    {
       seekg(4, ios::beg);
       read((char *)&CurrentCountPtr, sizeof(int));
       read((char*)&PtrBeginArray, sizeof(int));

       CounterPtr = CurrentCountPtr*sizeof(typeData);
        
    }

    void Update(string fileN)
    {

        fstream fileCopy(fileN, ios::binary | ios::in | ios::out | ios::trunc);
        if (!fileCopy)
        {
            cout << "file doesnt open";
        }
        else
        {
            seekg(ios::beg);
            read((char *)&SizeArray, sizeof(int));
            read((char *)&CurrentCountPtr, sizeof(int));
            read((char *)&PtrBeginArray, sizeof(int));

            seekg(PtrBeginArray, ios::beg);

            PtrFile = tellg();
            
            int elAdrress;

            int FileCopyPtr;
            fileCopy.seekp(ios::beg);
            fileCopy.write((char *)&SizeArray, sizeof(int));
            fileCopy.write((char *)&CurrentCountPtr, sizeof(int));
            fileCopy.write((char *)&PtrBeginArray, sizeof(int));
            
            for (int i = 0; i < CurrentCountPtr; i++)
            {
                elAdrress = tellg();
                
                *this >> data;
                PtrFile = tellg();
                FileCopyPtr = tellg();
                seekg(elAdrress, ios::beg);
                
                *this >> data;
                fileCopy << data;
                fileCopy.seekp(4,ios::cur);
                seekg(PtrFile, ios::beg);
                
                
            }
            elAdrress = 0;
            

            fileCopy.close();
        }
    }

    ~BinaryFile()
    {

        close();
    }
};




