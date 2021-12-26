#include "header.hpp"
#include <iostream>
#include <string>
#include "DataMethods.hpp"
using namespace std;

string dat = ".dat";

int main()
{
     int k = 0;
     int t = 0;
     string fileName;
     cout << "-------------------------" << endl;
     cout << "Введите имя файла: ";
     cin >> fileName;
     fileName = fileName + dat;
     cout << "-------------------------" << endl;
     cout << "Выберите какой файл создать: "
          << "\n";
     cout << "[1] - int "
          << "\n";
     cout << "[2] - DateAndTime"
          << "\n";
     cin >> k;
     if (k == 1)
     {
          bool a = true;
          BinaryFile<int> IntFile(fileName);
          while (a == true)
          {

               int f = 0;
               cout << "Выберите действие с (int) файлом: "
                    << "\n";
               cout << "[1] - Просмотр файла: "
                    << "\n";
               cout << "[2] - Добавление элемента "
                    << "\n";
               cout << "[3] - Удаление элемента "
                    << "\n";
               cout << "[4] - Обновление файла "
                    << "\n";
               cout << "[5] - Сортировка файла "
                    << "\n";
               cout << "[6] - Выход "
                    << "\n";

               cin >> f;
               if (f == 1)
                    IntFile.Review();
               else if (f == 2)
               {
                    int c;
                    string b;
                    while(b!="no") {
                    cout << "ВВедите число который хотите записать в бинарный файл:";
                    cin >> c;
                    IntFile.AddElement(c);
                    cout << "Еще число ввести?[yes][no]: ";
                    cin >> b;
                    }
               }
               else if (f == 3)
                    //IntFile.getArrayPos();
                    IntFile.DeleteElement();

               else if (f == 4)
               {
                    cout << "Введите имя копии основного файла: ";
                    string fileN;
                    cin >> fileN;
                    fileN = fileN + dat;
                    IntFile.Update(fileN);
               }
               else if (f == 5)
                    IntFile.Sort();

               else if (f == 6)
               {

                    a = false;
               }
          }
     }
     else if (k == 2)
     {
          bool b = true;
          BinaryFile<DateAndTime> DateFile(fileName);
          while (b == true)
          {

               int f = 0;
               cout << "Выберите дествие с (DateAndTime) файлом: "
                    << "\n";
               cout << "[1] - Просмотр файла: "
                    << "\n";
               cout << "[2] - Добавление элемента "
                    << "\n";
               cout << "[3] - Удаление элемента "
                    << "\n";
               cout << "[4] - Обновление файла "
                    << "\n";
               cout << "[5] - Сортировка файла "
                    << "\n";
               cout << "[6] - Выход " << endl;

               cin >> f;
               if (f == 1)

                    DateFile.Review();

               else if (f == 2)
               {
                    int d, m, y;
                    cout << "Введите день: ";
                    cin >> d;
                    cout << "Введите месяц: ";
                    cin >> m;
                    cout << "Введите год: ";
                    cin >> y;

                    DateAndTime d1(d, m, y);
                    DateFile.AddElement(d1);
               }
               else if (f == 3)

                    DateFile.DeleteElement();
                    
               else if (f == 4)
               {
                    cout << "Введите имя копии основного файла: ";
                    string fileN;
                    cin >> fileN;
                    fileN = fileN + dat;
                    DateFile.Update(fileN);
               }
               else if (f == 5)
                    DateFile.Sort();
               else if (f == 6)
               {
                    b = false;
               }
          }
     }
     return 0;
}