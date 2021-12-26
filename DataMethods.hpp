#pragma once
#include <stdio.h>
#include "DateAndTime.hpp"
#include <iomanip>
#include <fstream>

int DateAndTime::get_day() { return day; }
int DateAndTime::get_month() { return month; }
int DateAndTime::get_year() { return year; }
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


void DateAndTime::set_numberObj(int number)
{
    this->numberObj = number;
}

DateAndTime::DateAndTime(const DateAndTime &t)
{
    this->set_day(t.day);
    this->set_month(t.month);
    this->set_year(t.year);
    
    this->date = new char[10];
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


void DateAndTime::set_obj()
{

    sprintf(this->date, "%.2d/%.2d/%.4d", this->get_day(), this->get_month(), this->get_year());
}

// // 2 лаба
// DateAndTime &operator+(DateAndTime &, int);
// DateAndTime &operator-(DateAndTime &, int);

// DateAndTime operator+(DateAndTime &, DateAndTime &); // ready
// DateAndTime operator-(DateAndTime &, DateAndTime &); // ready

// // 2 laba
DateAndTime DateAndTime::operator=(DateAndTime &a)
{
    this->set_day(a.day);
    this->set_month(a.month);
    this->set_year(a.year);
    this->date = new char[10];
    strcpy(this->date, a.date);
    return *this;
}
// // ----------------------------------------------

// // 3 лаба
// ready

// istream &operator>>(istream &in, DateAndTime &obj); // ready

// // 2 laba

ostream &operator<<(ostream &os, DateAndTime &obj);

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

fstream &operator<<(fstream &os, DateAndTime &obj)
{

    os.write((char *)&obj.day, sizeof(int));
    os.write((char *)&obj.month, sizeof(int));
    os.write((char *)&obj.year, sizeof(int));
    
    return os;
}

fstream &operator>>(fstream &in, DateAndTime &obj)
{

    in.read((char*)&obj.day, sizeof(int));
    in.read((char *)&obj.month, sizeof(int));
    in.read((char *)&obj.year, sizeof(int));
    return in;
}


ostream &operator<<(ostream &os, DateAndTime &obj) {
    os << obj.get_day() << "/" << obj.get_month() << "/" << obj.get_year();
    return os;
}


bool operator> (DateAndTime &a1, DateAndTime &a2) {
    int Year = a1.get_year();
    int Year2 = a2.get_year();
    int Month1 = a1.get_month();
    int Month2 = a2.get_month();
    int Day1 = a1.get_day();
    int Day2 = a2.get_day();
    int summ1 = 0;
    int summ2 = 0;
    for(int i = 0; i < Year; i++) {
        if((i % 4 == 0 && i % 100 !=0) || (i % 400 == 0)) {
            summ1 = summ1 + 366;
        }
        else {
            summ1 = summ1 + 365;
        }
    }

    for(int i = 0; i < Year2; i++) {
        if((i % 4 == 0 && i % 100 !=0) || (i % 400 == 0)) {
            summ2 = summ2 + 366;
        }
        else {
            summ2 = summ2 + 365;
        }
    }

    for(int i = 1; i < Month1; i++) {
        if(i % 2 !=0 && i!=8) {
            summ1 = summ1 + 31;
        }
        else {
            if(i == 2 && (Year % 4 == 0 && Year % 100 !=0) ) {
                summ1 = summ1 + 29;
            }
            else {
                if(i % 2 == 0 && i!=2) {
                    summ1 = summ1 + 30;
                }
                else {
                    summ1 = summ1 + 28;
                }
            }
            
        }
    }
    for(int i = 1; i < Month2; i++) {
        if(i % 2 !=0 && i!=8) {
            summ2 = summ2 + 31;
        }
        else {
            if(i == 2 && (Year % 4 == 0 && Year % 100 !=0) ) {
                summ2 = summ2 + 29;
            }
            else {
                if(i % 2 == 0 && i!=2) {
                    summ2 = summ2 + 30;
                }
                else {
                    summ2 = summ2 + 28;
                }
            }
            
        }
    }

    summ1 = summ1 + Day1;
    summ2 = summ2 + Day2;

    if(summ1 > summ2) {
        return true;
    }
    
    return false;



}


bool operator<(DateAndTime& obj1, DateAndTime& obj2) {
    int Year = obj1.get_year();
    int Year2 = obj2.get_year();
    int Month1 = obj1.get_month();
    int Month2 = obj2.get_month();
    int Day1 = obj1.get_day();
    int Day2 = obj2.get_day();
    int summ1 = 0;
    int summ2 = 0;
    for(int i = 0; i < Year; i++) {
        if((i % 4 == 0 && i % 100 !=0) || (i % 400 == 0)) {
            summ1 = summ1 + 366;
        }
        else {
            summ1 = summ1 + 365;
        }
    }

    for(int i = 0; i < Year2; i++) {
        if((i % 4 == 0 && i % 100 !=0) || (i % 400 == 0)) {
            summ2 = summ2 + 366;
        }
        else {
            summ2 = summ2 + 365;
        }
    }

    for(int i = 1; i < Month1; i++) {
        if(i % 2 !=0 && i!=8) {
            summ1 = summ1 + 31;
        }
        else {
            if(i == 2 && (Year % 4 == 0 && Year % 100 !=0) ) {
                summ1 = summ1 + 29;
            }
            else {
                if(i % 2 == 0 && i!=2) {
                    summ1 = summ1 + 30;
                }
                else {
                    summ1 = summ1 + 28;
                }
            }
            
        }
    }
    for(int i = 1; i < Month2; i++) {
        if(i % 2 !=0 && i!=8) {
            summ2 = summ2 + 31;
        }
        else {
            if(i == 2 && (Year % 4 == 0 && Year % 100 !=0) ) {
                summ2 = summ2 + 29;
            }
            else {
                if(i % 2 == 0 && i!=2) {
                    summ2 = summ2 + 30;
                }
                else {
                    summ2 = summ2 + 28;
                }
            }
            
        }
    }

    summ1 = summ1 + Day1;
    summ2 = summ2 + Day2;

    if(summ1 < summ2) {
        return true;
    }
    
    return false;

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