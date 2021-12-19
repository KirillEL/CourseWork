#include <iostream>
#include "HeaderFiles/Header.hpp"
#include "HeaderFiles/DataMethods.hpp"

using namespace std;

int main()
{
     // MENU 
     int k = 0;
     cout << "Выберите какой файл создать: "
          << "\n";
     cout << "[1] - char "
          << "\n";
     cout << "[2] - DateAndTime"
          << "\n";
     cin >> k;
     if (k == 1)
     {
          bool a = true;
          BinaryFile<char> CharFile("file.bin");
          while (a == true)
          {
               //CharFile.Review();
               int f = 0;
               cout << "Выберите действие с (char) файлом: "
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

                    CharFile.Review();

               else if (f == 2)
               {    
                    char c = ' ';
                    cout << "ВВедите символ который хотите записать в бинарный файл:";
                    cin >> c;
                    CharFile.AddObject(c);
               }
               else if (f == 3)

                    CharFile.RemoveObject();

               else if (f == 4)
                    CharFile.Update();

               else if (f == 5)
                    CharFile.Sort();
               if (f == 6)
               {
                    a = false;
                    system("pause");
                    system("cls");
               }
          }
     }
     else if (k == 2)
     {
          bool a = true;
          BinaryFile<DateAndTime> DateAndTimeFile("file.bin");
          while (a == true)
          {
               
               int f = 0;
               cout << "Выберите дествие с (char) файлом: "
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

                    DateAndTimeFile.Review();

               else if (f == 2)
               {
                    DateAndTime d1(1, 2, 3, 4, 5, 6);
                    DateAndTimeFile.AddObject(d1);
               }
               else if (f == 3)

                    DateAndTimeFile.RemoveObject();

               else if (f == 4)
                    DateAndTimeFile.Update();

               else if (f == 5)
                    DateAndTimeFile.Sort();
               if (f == 6)
               {
                    a = false;
                    system("pause");
                    system("cls");
               }
          }
     }
     return 0;
}