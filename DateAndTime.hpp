#pragma once
#include <cmath>
#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include "MyException.hpp"
#include <iomanip>

using namespace std;

class DateAndTime
{
public:
  DateAndTime() : day(0), month(0), year(0)
  {
    date = new char[i];
    numberObj++;
  }
  DateAndTime(int d) : day(d), month(0), year(d)
  {
    numberObj++;
  }
  DateAndTime(int d, int m) : day(d), month(m), year(0)
  {
    numberObj++;
  }
  DateAndTime(int d, int m, int y) : day(d), month(m), year(y)
  {
    numberObj++;
    date = new char[i];
  }
  

  // ~DateAndTime()
  // {
  //   delete[] date;
  //   numberObj--;
  // }

  int get_day();
  int get_month();
  int get_year();
  static int get_numberObj();
  char *get_date();

  void set_day(int);
  void set_month(int);
  void set_year(int);
  void set_numberObj(int);

  DateAndTime(const DateAndTime &);

  void increaseDay();
  void increaseMonth();
  void increaseYear();
  void decreaseYear();
  void decreaseMonth();
  void decreaseDay();
  void set_obj();
  virtual char *get_String()
{
    this->set_obj();
    char *datTime = new char[10];
    strcpy(datTime, this->date);
    return datTime;
}

virtual int get_size()
{
    int size = strlen(this->get_String());
    return size;
}
friend fstream &operator>>(fstream&, DateAndTime&);
friend fstream &operator<<(fstream&, DateAndTime&);

friend ostream &operator<<(ostream&, DateAndTime&);

DateAndTime operator=(DateAndTime &a);


friend bool operator>(DateAndTime &a1 , DateAndTime &a2);

friend bool operator<(DateAndTime& , DateAndTime&);





private:
  int day;
  int month;
  int year;
  char *date;
  static int numberObj;
  int i = 0;
};
int DateAndTime::numberObj = 0;
