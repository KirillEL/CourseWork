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
     cout << "[1] - string "
          << "\n";
     cout << "[2] - DateAndTime"
          << "\n";
     cin >> k;
     if (k == 1)
     {
          bool a = true;
          BinaryFile<string> StringFile("file.bin");
          while (a == true)
          {
               
               int f = 0;
               cout << "Выберите действие с (string) файлом: "
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

                    StringFile.Review();

               else if (f == 2)
               {    
                    string c;
                    cout << "ВВедите строку который хотите записать в бинарный файл:";
                    cin >> c;
                    StringFile.AddObject(c);
               }
               else if (f == 3)

                    StringFile.RemoveObject();

               else if (f == 4) {
                    int number = 0;
                    cin >> number;
                    StringFile.Update(number);
               }
               else if (f == 5)
                    StringFile.Sort();
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

               else if (f == 4) {
                    int number = 0;
                    cin >> number;
                    DateAndTimeFile.Update(number);
               }
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