#pragma once
#include <stdio.h>
#include "DateAndTime.hpp"
#include <iomanip>
#include <fstream>

int DateAndTime::get_day() { return day; }
int DateAndTime::get_month() { return month; }
int DateAndTime::get_year() { return year; }
int DateAndTime::get_hours() { return hours; }
int DateAndTime::get_min() { return min; }
int DateAndTime::get_seconds() { return seconds; }
int DateAndTime::get_numberObj() { return numberObj; }
char *DateAndTime::get_date() { return date; }

void DateAndTime::set_day(int day)
{
    try
    {
        if (this->get_month() == 1 || this->get_month() == 3 || this->get_month() == 5 || this->get_month() == 7 || this->get_month() == 8 || this->get_month() == 10 || this->get_month() == 12)
        {
            if (day > 31)
                throw MyException("In this month, day must be 31 or less");
        }
        else if (this->get_month() == 2)
        {
            if (this->get_year() % 4 == 0 || this->get_year() % 100 == 0)
            {
                if (day > 28)
                    throw MyException("In this month, day must be 28 or less");
            }
            else
            {
                if (day > 29)
                    throw MyException("In this month, day must be 29 or less");
            }
        }
        else
        {
            if (day > 30)
                throw MyException("In this month, day must be 30 or less");
        }
        this->day = day;
    }
    catch (MyException &ex)
    {
        cerr << ex.What() << "\n";
    }
}
void DateAndTime::set_month(int month)
{
    try
    {
        if (month > 12)
            throw MyException("In Year must be 12 or less months");
        this->month = month;
    }
    catch (MyException &ex)
    {
        cerr << ex.What() << "\n";
    }
}
void DateAndTime::set_year(int year)
{
    this->year = year;
}
void DateAndTime::set_hours(int hours)
{
    try
    {
        if (hours < 0 || hours > 24)
            throw MyException("In a day must be 24 or less hours");
        this->hours = hours;
    }
    catch (MyException &ex)
    {
        cerr << ex.What() << "\n";
    }
}
void DateAndTime::set_min(int min)
{
    try
    {
        if (min < 0 || min > 60)
            throw MyException("In a hour must be 60 or less mins");
        this->min = min;
    }
    catch (MyException &ex)
    {
        cerr << ex.What() << "\n";
    }
}
void DateAndTime::set_seconds(int seconds)
{
    try
    {
        if (seconds < 0 || seconds > 60)
            throw MyException("In a min must be 60 or less seconds");
        this->seconds = seconds;
    }
    catch (MyException &ex)
    {
        cerr << ex.What() << "\n";
    }
}
void DateAndTime::set_numberObj(int number)
{
    this->numberObj = number;
}

DateAndTime::DateAndTime(const DateAndTime &t)
{
    this->set_day(t.day);
    this->set_month(t.month);
    this->set_year(t.year);
    this->set_hours(t.hours);
    this->set_min(t.min);
    this->set_seconds(t.seconds);
    this->date = new char[19];
    strcpy(this->date, t.date);
    numberObj++;
}

void DateAndTime::increaseDay()
{
    if ((this->get_month() == 4 || this->get_month() == 6 ||
         this->get_month() == 9 || this->get_month() == 11) &&
        this->get_day() == 30)
    {
        this->increaseMonth();
        this->set_day(1);
    }
    else if (this->get_month() == 2)
    {
        if (this->get_year() % 4 == 0)
        {
            if (this->get_year() % 100 == 0 && this->get_year() % 400 != 0)
            {
                if (this->get_day() == 28)
                {
                    this->increaseMonth();
                    this->set_day(1);
                }
                else
                {
                    this->set_day(this->get_day() + 1);
                }
            }
            else
            {
                if (this->get_day() == 29)
                {
                    this->increaseMonth();
                    this->set_day(1);
                }
                else
                {
                    this->set_day(this->get_day() + 1);
                }
            }
        }
        else if (this->get_day() == 28)
        {
            this->increaseMonth();
            this->set_day(1);
        }
        else
        {
            this->set_day(this->get_day() + 1);
        }
    }
    else if (this->get_day() == 31)
    {
        this->increaseMonth();
        this->set_day(1);
    }
    else
    {
        this->set_day(this->get_day() + 1);
    }
}

void DateAndTime::increaseMonth()
{
    if (this->month == 12)
    {
        this->increaseYear();
        this->set_month(1);
    }
    this->month++;
}
void DateAndTime::increaseYear()
{
    this->year++;
}
void DateAndTime::increaseHours()
{
    if (this->get_hours() == 23)
    {
        this->increaseDay();
        this->set_hours(0);
    }
    else
        this->set_hours(this->get_hours() + 1);
}
void DateAndTime::increaseMinutes()
{
    if (this->get_min() == 59)
    {
        this->increaseHours();
        this->set_min(0);
    }
    else
    {
        this->min++;
    }
}
void DateAndTime::increaseSeconds()
{
    if (this->get_seconds() == 59)
    {
        this->increaseMinutes();
        this->set_seconds(0);
    }
    else
    {
        this->seconds++;
    }
}
void DateAndTime::decreaseYear()
{
    this->year--;
}
void DateAndTime::decreaseMonth()
{
    if (this->get_month() == 1)
    {
        this->decreaseYear();
        this->set_month(12);
    }
    this->month--;
}
void DateAndTime::decreaseDay()
{
    if (this->get_day() == 1)
    {
        this->decreaseMonth();
        if (this->get_month() == 4 || this->get_month() == 6 || this->get_month() == 9 || this->get_month() == 11)
        {
            this->set_day(30);
        }
        else
        {
            if (this->get_month() == 2)
            {
                if (this->get_year() % 4 == 0 || this->get_year() % 100 == 0)
                {
                    this->set_day(29);
                }
                else
                    this->set_day(28);
            }
            else
            {
                this->set_day(31);
            }
        }
    }
    this->day--;
}
void DateAndTime::decreaseHours()
{
    if (this->get_hours() == 0)
    {
        this->decreaseDay();
        this->set_hours(24);
    }
    this->hours--;
}
void DateAndTime::decreaseMinutes()
{
    if (this->get_min() == 0)
    {
        this->decreaseHours();
        this->set_min(59);
    }
    else
        this->min--;
}
void DateAndTime::decreaseSeconds()
{
    if (this->get_seconds() == 0)
    {
        this->decreaseMinutes();
        this->set_seconds(59);
    }
    else
        this->seconds--;
}

void DateAndTime::set_obj()
{

    sprintf(this->date, "%.2d/%.2d/%.4d %.2d:%.2d:%.2d", this->get_day(), this->get_month(), this->get_year(), this->get_hours(), this->get_min(), this->get_seconds());
}




// // 2 лаба
// DateAndTime &operator+(DateAndTime &, int);
// DateAndTime &operator-(DateAndTime &, int);

// DateAndTime operator+(DateAndTime &, DateAndTime &); // ready
// DateAndTime operator-(DateAndTime &, DateAndTime &); // ready

// // 2 laba
// DateAndTime DateAndTime::operator=(DateAndTime &a)
// {
//     this->set_day(a.day);
//     this->set_month(a.month);
//     this->set_year(a.year);
//     this->set_hours(a.hours);
//     this->set_min(a.min);
//     this->set_seconds(a.seconds);
//     this->date = new char[19];
//     strcpy(this->date, a.date);
//     return *this;
// }
// // ----------------------------------------------

// // 3 лаба
// ostream &operator<<(ostream &os, DateAndTime &obj); // ready

// istream &operator>>(istream &in, DateAndTime &obj); // ready

// // 2 laba

// DateAndTime::operator char *()
// {
//     this->set_obj();
//     return this->get_String();
// }

// DateAndTime operator+(DateAndTime &a, DateAndTime &b)
// {
//     return (DateAndTime(a.day + b.day, a.month + b.month, a.year + b.year, a.hours + b.hours, a.min + b.min, a.seconds + b.seconds));
// }

// DateAndTime operator-(DateAndTime &a, DateAndTime &b)
// {
//     return (DateAndTime(a.day - b.day, a.month - b.month, a.year - b.year, a.hours - b.hours, a.min - b.min, a.seconds - b.seconds));
// }
//---------------------------------------------



// istream &operator>>(istream &in, DateAndTime &obj)
// {
//     int dayI, monthI, yearI, hoursI, minI, secondsI;
//     char date[10];
//     char time[8];
//     in >> date;

//     if (date[0] == 0)
//     {
//         dayI = date[1] - '0';
//     }
//     else
//     {
//         dayI = 10 * (date[0] - '0') + date[1] - '0';
//     }

//     if (date[3] == '0')
//     {
//         monthI = date[4] - '0';
//     }
//     else
//     {
//         monthI = 10 * (date[3] - '0') + date[4] - '0';
//     }

//     if (date[6] == 0)
//     {
//         if (date[7] == 0)
//         {
//             if (date[8] == 0)
//             {
//                 yearI = date[9] - '0';
//             }
//             else
//             {
//                 yearI = 10 * (date[8] - '0') + date[9] - '0';
//             }
//         }
//         else
//         {
//             yearI = 100 * (date[7] - '0') + 10 * (date[8] - '0') + date[9] - '0';
//         }
//     }
//     else
//     {
//         yearI = 1000 * (date[6] - '0') + 100 * (date[7] - '0') + 10 * (date[8] - '0') + date[9] - '0';
//     }

//     in >> time;

//     if (time[0] == 0)
//     {
//         hoursI = time[1] - '0';
//     }
//     else
//     {
//         hoursI = 10 * (time[0] - '0') + time[1] - '0';
//     }

//     if (time[3] == 0)
//     {
//         minI = time[4] - '0';
//     }
//     else
//     {
//         minI = 10 * (time[3] - '0') + time[4] - '0';
//     }

//     if (time[6] == 0)
//     {
//         secondsI = time[7] - '0';
//     }
//     else
//     {
//         secondsI = 10 * (time[6] - '0') + time[7] - '0';
//     }
//     obj.set_day(dayI);
//     obj.set_month(monthI);
//     obj.set_year(yearI);
//     obj.set_hours(hoursI);
//     obj.set_min(minI);
//     obj.set_seconds(secondsI);

//     return in;
// }

// ofstream &outBinary(ofstream &os, DateAndTime &obj)
// {
//     try
//     {

//         if (!os.is_open())
//             throw MyException("file doesn't open");
//         else
//         {

//             os.write((char *)&obj.day, sizeof(int));
//             os.write((char *)&obj.month, sizeof(int));
//             os.write((char *)&obj.year, sizeof(int));
//             os.write((char *)&obj.hours, sizeof(int));
//             os.write((char *)&obj.min, sizeof(int));
//             os.write((char *)&obj.seconds, sizeof(int));

//             os.close();
//         }
//     }
//     catch (MyException &ex)
//     {
//         cerr << ex.What();
//     }
//     return os;
// }

fstream &readBinary(fstream &in, DateAndTime &obj)
{
    try
    {

        if (!in.is_open())
            throw MyException("file doesn't open");
        else
        {

            in.read((char *)&obj.day, sizeof(int));
            in.read((char *)&obj.month, sizeof(int));
            in.read((char *)&obj.year, sizeof(int));
            in.read((char *)&obj.hours, sizeof(int));
            in.read((char *)&obj.min, sizeof(int));
            in.read((char *)&obj.seconds, sizeof(int));
            
            
            in.close();
        }
    }
    catch (MyException &ex)
    {
        cerr << ex.What();
    }
    return in;
}

// // 2 laba

// DateAndTime &operator+(DateAndTime &obj, int num)
// {
//     for (int t = num; t > 0; t--)
//     {
//         obj.increaseHours();
//     }

//     return obj;
// }

// DateAndTime &operator-(DateAndTime &obj, int num)
// {
//     for (; num > 0; num--)
//     {
//         obj.decreaseHours();
//     }
//     return obj;
// }