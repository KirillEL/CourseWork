#pragma once
#include <iostream>
#include "MyException.hpp"
#include <fstream>
#include <cstdlib>
#include <string>
#include "DateAndTime.hpp"

using namespace std;

template <class typeData> // шаблон
class BinaryFile : public fstream
{
public:
    BinaryFile(const char *nameFile)
    {
        f.open(nameFile, ios::binary | ios::in | ios::out);
        try
        {
            if (f.is_open())
            {

                f.write((char *)&SizeArray, sizeof(int));
                f.write((char *)&CurrentCountPtr, sizeof(int));
                file_ptr = f.tellg();
                CounterPtr = sizeof(int) + sizeof(typeData);
                f.seekg(file_ptr + CounterPtr, ios::beg);
                PPtrBeginArray = f.tellg();
                f.seekg(file_ptr, ios::beg);
                f.write((char *)&PPtrBeginArray, sizeof(pos_type));
                SizeArray = CurrentCountPtr = 0;
                CounterPtr = 0;
            }
            else
            {
                throw MyException("file doesnt open!");
            }
        }
        catch (MyException &ex)
        {
            cerr << ex.What() << endl;
        }
    }

    fstream &operator<<(typeData &tData)
    {
        f.write((char *)&tData, sizeof(typeData));
        return *this;
    }

    fstream &operator>>(typeData &tData)
    {
        f.read((char *)&tData, sizeof(typeData));
        return *this;
    }

    void Review()
    {
        f.seekp(0, ios::beg);
        f.read((char *)&SizeArray, sizeof(int));
        f.read((char *)&CurrentCountPtr, sizeof(int));
        f.read((char *)&PPtrBeginArray, sizeof(pos_type));
        cout << endl
             << "Размерность массива указателей: " << SizeArray << endl;
        cout << " Текущее кол-во указателей: " << CurrentCountPtr << endl;
        f.seekp(PPtrBeginArray, ios::beg);
        cout << endl;
        pos_type tDataAddress;

        for (int i = 0; i < CurrentCountPtr; i++)
        {
            f.read((char *)&tDataAddress, sizeof(pos_type));
            file_ptr = tellp();
            f.seekp(tDataAddress, ios::beg);

            f.read((char *)&tData, sizeof(typeData));
        

            
            char* s = date.get_String();
            for(int j = 0; j < strlen(s); j++) {
                cout << s[j];
            }
            cout << endl;
            f.seekp(file_ptr, ios::beg);
        }
    }

    void Sort();

    // ------------------------------------------
    void FunctionCounter() // счетчик
    {
        CounterPtr = sizeof(int);
        f.seekp(-CounterPtr, ios::end);
        f.read((char *)&CounterPtr, sizeof(int));
        f.seekp(CounterPtr + sizeof(typeData), ios::beg);
        CounterPtr = f.tellp();
        CounterPtr = CounterPtr - (sizeof(int) * 3);
    }
    // --------------------------------------------

    void AddObject(typeData obj)
    {
        f.seekp(ios::beg);
        f.read((char *)&SizeArray, sizeof(int));
        f.read((char *)&CurrentCountPtr, sizeof(int));
        f.read((char *)&PPtrBeginArray, sizeof(pos_type));
        file_ptr = f.tellp();
        pos_type address;
        if (SizeArray == CurrentCountPtr)
        {
            incrementSizeArray(obj);
        }
        else
        {
            CurrentCountPtr++; // увеличиваем размер массива
            f.seekg(4, ios::beg);
            f.write((char *)&CurrentCountPtr, sizeof(pos_type));
            f.seekg(file_ptr + CounterPtr, ios::beg);
            address = f.tellg();
            f.write((char *)&obj, sizeof(typeData));
            CounterPtr += sizeof(typeData);
            f.seekg(0, ios::end);
            f.write((char *)&address, sizeof(pos_type));
        }
    }

    void RemoveObject() // удаление объекта
    {
        try
        {
            f.seekp(0, ios::beg); //чтение с начала файла
            f.read((char *)&CurrentCountPtr, sizeof(int));
            if (CurrentCountPtr > 0)
            {
                CurrentCountPtr--;
                f.seekp(4, ios::beg); //
                f.write((char *)&CurrentCountPtr, sizeof(int));
                CounterPtr = CounterPtr - sizeof(typeData);
            }
            else
                throw MyException("File is already clear!");
        }
        catch (MyException &ex)
        {
            cerr << ex.What() << endl;
        }
    }

    void Update()
    {
    }

    void incrementSizeArray(typeData obj) // функция увеличения размера массива указателей в 2 раза если массив заполнен
    {
        SizeArray = SizeArray * 2;

        f.seekg(0, ios::beg); // запись в начало файла
        f.write((char *)&SizeArray, sizeof(int));

        f.seekp(PPtrBeginArray, ios::beg); // переход к началу м указателей
        pos_type OldPtr = f.tellp();
        f.seekg(0, ios::end);
        pos_type NewPtr = f.tellg();
        pos_type Address;
        PPtrBeginArray = f.tellg();
        for (int i = 0; i < CurrentCountPtr; i++)
        {
            f.seekp(OldPtr, ios::beg);
            f.read((char *)&Address, sizeof(pos_type));
            OldPtr = f.tellp();
            f.seekg(NewPtr, ios::beg);
            f.write((char *)&Address, sizeof(pos_type));
            NewPtr = f.tellg();
        }
        f.seekg(8, ios::beg);
        f.write((char *)&PPtrBeginArray, sizeof(pos_type));
        AddObject(obj);
    }

    ~BinaryFile()
    {
        SizeArray = CurrentCountPtr = CounterPtr = 0;
        f.close(); // закрываем файл
    }

private:
    fstream f;
    int SizeArray = 1;       // Размер массива указателей
    int CurrentCountPtr = 0; // Текущее кол-во указателей
    pos_type file_ptr;
    pos_type PPtrBeginArray;
    // int *FilePtr = nullptr;       // указатель файла
    // int *PtrBeginArray = nullptr; // адрес начала массива указателей
    int CounterPtr = 0; // счетчик сдвига
    typeData tData;     // временный буфер объекта
};

template <>
void BinaryFile<char>::Sort()
{
    pos_type t1, t2;
    char symbol;
    for (int i = CurrentCountPtr - 1; i >= 0; i--)
    {
        f.seekp(0, ios::beg);
        f.read((char *)&SizeArray, sizeof(int));
        f.read((char *)&CurrentCountPtr, sizeof(int));
        f.read((char *)&PPtrBeginArray, sizeof(int));
        f.seekp(PPtrBeginArray, ios::beg);
        for (int j = 0; j < i; j++)
        {
            f.read((char *)&t1, sizeof(int));
            file_ptr = tellp();
            f.read((char *)&t2, sizeof(int));
            f.seekp(t1, ios::beg);
            *this >> tData;
            f.seekp(t2, ios::beg);
            *this >> symbol;
            if (tData > symbol)
            {
                char temp = tData;
                f.seekg(t1, ios::beg);
                *this << symbol;
                f.seekg(t2, ios::beg);
                *this << temp;
            }
            f.seekp(file_ptr, ios::beg);
        }
    }
}

template <>
void BinaryFile<DateAndTime>::Sort()
{
    pos_type t1, t2;
    DateAndTime date;
    for (int i = CurrentCountPtr - 1; i >= 0; i--)
    {
        f.seekp(0, ios::beg);
        f.read((char *)&SizeArray, sizeof(int));
        f.read((char *)&CurrentCountPtr, sizeof(int));
        f.read((char *)&PPtrBeginArray, sizeof(int));
        f.seekp(PPtrBeginArray, ios::beg);
        for (int j = 0; j < i; j++)
        {
            f.read((char *)&t1, sizeof(int));
            file_ptr = tellp();
            f.read((char *)&t2, sizeof(int));
            f.seekp(t1, ios::beg);
            *this >> tData;
            f.seekp(t2, ios::beg);
            *this >> date;
            if (tData.get_year() > date.get_year())
            {
                DateAndTime temp = tData;
                f.seekg(t1, ios::beg);
                *this << date;
                f.seekg(t2, ios::beg);
                *this << temp;
            }
            f.seekp(file_ptr, ios::beg);
        }
    }
}