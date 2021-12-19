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
  DateAndTime() : day(0), month(0), year(0), hours(0), min(0), seconds(0)
  {
    date = new char[i];
    numberObj++;
  }
  DateAndTime(int d) : day(d), month(0), year(d), hours(0), min(0), seconds(0)
  {
    numberObj++;
  }
  DateAndTime(int d, int m) : day(d), month(m), year(0), hours(0), min(0), seconds(0)
  {
    numberObj++;
  }
  DateAndTime(int d, int m, int y) : day(d), month(m), year(y), hours(0), min(0), seconds(0)
  {
    numberObj++;
  }
  DateAndTime(int d, int m, int y, int hours) : day(d), month(m), year(y), hours(hours)
  {
    numberObj++;
  }
  DateAndTime(int d, int m, int y, int hours, int min) : day(d), month(m), year(y), hours(hours), min(min)
  {
    numberObj++;
  }
  DateAndTime(int d, int m, int y, int hours, int min, int sec)
  {
    set_day(d);
    set_month(m);
    set_year(y);
    set_hours(hours);
    set_min(min);
    set_seconds(sec);
    numberObj++;
    date = new char[i];
  }
  DateAndTime(int d, int m, int y, int hours, int min, int sec, char *dat)
  {
    set_day(d);
    set_month(m);
    set_year(y);
    set_hours(hours);
    set_min(min);
    set_seconds(sec);
    dat = new char[i];
    numberObj++;
  }

  ~DateAndTime()
  {
    numberObj--;
  }

  int get_day();
  int get_month();
  int get_year();
  int get_hours();
  int get_min();
  int get_seconds();
  static int get_numberObj();
  char *get_date();

  void set_day(int);
  void set_month(int);
  void set_year(int);
  void set_hours(int);
  void set_min(int);
  void set_seconds(int);
  void set_numberObj(int);

  DateAndTime(const DateAndTime &);

  void increaseDay();
  void increaseMonth();
  void increaseYear();
  void increaseHours();
  void increaseMinutes();
  void increaseSeconds();
  void decreaseYear();
  void decreaseMonth();
  void decreaseDay();
  void decreaseHours();
  void decreaseMinutes();
  void decreaseSeconds();
  void set_obj();
  virtual char *get_String()
{
    this->set_obj();
    char *datTime = new char[19];
    strcpy(datTime, this->date);
    return datTime;
}

virtual int get_size()
{
    int size = strlen(this->get_String());
    return size;
}
friend fstream &readBinary(fstream&, DateAndTime&);


friend ostream& operator<<(DateAndTime& obj , ostream& out) {
  try
    {
        obj.set_day(obj.day);
        obj.set_month(obj.month);
        obj.set_year(obj.year);
        obj.set_hours(obj.hours);
        obj.set_min(obj.min);
        obj.set_seconds(obj.seconds);
        if (obj.get_day() == 0 || obj.get_month() == 0 || obj.get_year() == 0 || obj.get_hours() == 0 || obj.get_min() == 0 || obj.get_seconds() == 0)
            throw MyException("Date Format is uncorrect!");
        out << setfill('0') << setw(2) << obj.get_day() << "/" << setfill('0') << setw(2) << obj.get_month() << "/" << setfill('0') << setw(4) << obj.get_year() << " " << setfill('0') << setw(2) << obj.get_hours() << ":" << setfill('0') << setw(2) << obj.get_min() << ":" << setfill('0') << setw(2) << obj.get_seconds();
    }
    catch (MyException &ex)
    {
        cerr << ex.What() << "\n";
    }
    return out;
}

private:
  int day;
  int month;
  int year;
  int hours;
  int min;
  int seconds;
  char *date;
  static int numberObj;
  int i = 0;
};
int DateAndTime::numberObj = 0;
