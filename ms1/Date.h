/* ------------------------------------------------------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.

Project MS1
Course title:OOP244 NBB
Module:      Date
Filename:    Date.h
Version:     1
student:     Zhaokai Guan
Student Num: 130988215
Email:       zguan25@myseneca.ca
Date:        March 10th 2022

Revision History
-----------------------------------------------------------
Date:   Reason:
-----------------------------------------------------------*/

#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include <iostream>
#include "Status.h"
namespace sdds {
   const int MAX_YEAR = 2030;
   class Date {
      int m_year{};
      int m_month{};
      int m_day{};
      Status m_state{};
      bool m_formatted = true;
      // private method // 
      int uniqueDateVal() const;
   public:
   bool validate();
   Date();
   Date(int year, int month, int day);
   bool operator == (const Date& cmpTo) const;
   bool operator != (const Date& cmpTo) const;
   bool operator < (const Date& cmpTo) const;
   bool operator > (const Date& cmpTo) const;
   bool operator <= (const Date& cmpTo) const;
   bool operator >= (const Date& cmpTo) const;
   const Status& state();
   Date& formatted(bool format);
   operator bool()const;
   std::ostream& write(std::ostream& ostr)const;
   std::istream& read(std::istream& istr);
   };
   std::ostream& operator <<(std::ostream& ostr, const Date& srcVarible);
   std::istream& operator >>(std::istream& istr, Date& desVarible);
}
#endif // !SDDS_DATE_H
