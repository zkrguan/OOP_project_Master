/* ------------------------------------------------------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.

Project MS4
Course title:OOP244 NBB
Module:      Utils
Filename:    Utils.h
Version:     1
student:     Zhaokai Guan
Student Num: 130988215
Email:       zguan25@myseneca.ca
Date:        March 30th 2022

Revision History
-----------------------------------------------------------
Date:   Reason:
-----------------------------------------------------------*/

#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H
namespace sdds {
   const int sdds_testYear = 2022;
   const int sdds_testMon = 03;
   const int sdds_testDay = 31;
   class Utils {
      bool m_testMode = false;
   public:
      void getSystemDate(int* year = nullptr, int* mon = nullptr, int* day = nullptr);
      int daysOfMon(int mon, int year)const;
      void testMode(bool testmode = true);
      // Student Codes start Here//
      void alocpy(char*& destination, const char* source);
      int getInt(const char* promt = nullptr);
      int getint(int min, int max, const char* prompt = nullptr, const char* errMes = nullptr);
      double getDouble(const char* prompt = nullptr);
      double getDoubleAvecRange(double min, double max, const char* prompt = nullptr, const char* errMes = nullptr);

   };
   extern Utils ut;
}

#endif // !SDDS_UTILS_H
