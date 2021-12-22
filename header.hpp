#pragma once
#include <fstream>
#include "MyException.hpp"
#include <iostream>
#include "DateAndTime.hpp"

using namespace std;

template <class typeData>
class BinaryFile : public fstream
{
private:
    typeData **Array;
    int SizeArray = 2;
    int CurrentCountPtr = 0;
    int ArrayAddress = 0;
    fstream file;

public:
    BinaryFile(const char *nameFile)
    {
        try
        {

            file.open(nameFile, ios::binary | ios::in | ios::out);
            if (file.is_open())
            {
                Array = new typeData *[SizeArray];
                for (int i = 0; i < SizeArray; i++)
                    Array[i] = new typeData;
                file.write((char *)&SizeArray, sizeof(int));
                file.write((char *)&CurrentCountPtr, sizeof(int));
                ArrayAddress = tellg();
                file.write((char*)&ArrayAddress, sizeof(int));
                file.write((char *)&Array, (SizeArray) * sizeof(Array[0][0]));
            }
            else
                throw MyException("file doesnt open!");
        }
        catch (MyException &ex)
        {
            cout << ex.What() << endl;
        }
    }

    fstream &operator>>(typeData &obj) {
        file.read((char*)&obj, sizeof(typeData));
        return *this;
    }

    fstream &operator<<(typeData &obj) {
        file.write((char*)&obj, sizeof(typeData));
        return *this;
    }



    void AddElement(typeData &el)
    {
        file.seekp(ios::beg);
        file.read((char *)&SizeArray, sizeof(int));
        file.read((char *)&CurrentCountPtr, sizeof(int));
        file.seekp(ArrayAddress, ios::beg);
        file.read((char *)&Array, (SizeArray) * sizeof(Array[0][0]));
        if (SizeArray == CurrentCountPtr)
        {
            incrementSizeArray(el);
        }
        else
        {
            CurrentCountPtr = CurrentCountPtr + 1;
            Array[CurrentCountPtr-1] = new typeData;
            Array[CurrentCountPtr - 1][0] = el;
            file.seekg(ios::beg);
            file.write((char *)&SizeArray, sizeof(int));
            file.write((char *)&CurrentCountPtr, sizeof(int));
            file.write((char *)&Array, (SizeArray) * sizeof(Array[0][0]));
        }
    }

    void incrementSizeArray(typeData &element)
    {
        SizeArray = SizeArray*2;
        file.seekg(ios::beg);
        file.write((char*)&SizeArray, sizeof(int));

        file.seekp(8, ios::beg);

        int ArrayOld = tellp();

        file.seekg(0, ios::end);
        int ArrayAddress;
        int ArrayNew = tellg();

        for(int i = 0; i < CurrentCountPtr; i++) {
            file.seekp(ArrayOld, ios::beg);
            file.read((char*)&ArrayAddress, sizeof(int));
            ArrayOld = tellp();
            file.seekg(ArrayNew, ios::beg);
            file.write((char *)&ArrayAddress, sizeof(int));
            ArrayNew = tellg();
        }

        file.seekg(8, ios::beg);
        file.write((char *)&Array, sizeof(int));
        AddElement(element);

        
    }

    void Review()
    {
        file.seekp(ios::beg);
        file.read((char *)&SizeArray, sizeof(int));
        file.read((char *)&CurrentCountPtr, sizeof(int));
        file.read((char*)&Array, SizeArray*sizeof(Array[0][0]));
        cout << "Размерность массива указателей: " << SizeArray << endl;
        cout << "Текущее кол-во указателей: " << CurrentCountPtr << endl;
        for(int i = 0; i < CurrentCountPtr; i++) {
            cout << Array[i][0] << endl;
        }
    }


    void DeleteElement() { 
        file.seekp(4, ios::beg);
        file.read((char*)&CurrentCountPtr, sizeof(int));
        if(CurrentCountPtr > 0) {
            CurrentCountPtr--;
            file.seekp(4, ios::beg);
            file.write((char *)&CurrentCountPtr, sizeof(int));

        }
        else {
            cout << "Файл пуст!" << endl;
        }
    }

    void Sort() {
        file.seekg(ArrayAddress , ios::beg);
        file.read((char*)&Array, SizeArray * sizeof(Array[0][0]));
        for(int i = 0; i < CurrentCountPtr; i++) {
            if(Array[i][0] > Array[CurrentCountPtr-1][0]) {
                typeData temp = Array[i][0];
                Array[i][0] = Array[CurrentCountPtr-1][0];
                Array[CurrentCountPtr-1][0] = temp;
                
            }
        }
        file.write((char *)&Array, SizeArray * sizeof(Array[0][0]));
    }


    ~BinaryFile() { 
        SizeArray = 0;
        CurrentCountPtr = 0;
        for(int i = 0; i < SizeArray; i++) {
            delete[] Array[i];
        }
        file.close();
    }
};
