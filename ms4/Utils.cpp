/* ------------------------------------------------------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.

Project MS4
Course title:OOP244 NBB
Module:      Utils
Filename:    Utils.cpp
Version:     1
student:     Zhaokai Guan
Student Num: 130988215
Email:       zguan25@myseneca.ca
Date:        March 31th 2022

Revision History
-----------------------------------------------------------
Date:   Reason:
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <ctime>
#include "Utils.h"
using namespace std;
namespace sdds {
   Utils ut;
   void Utils::testMode(bool testmode) {
      m_testMode = testmode;
   }

   void Utils::alocpy(char*& destination, const char* source) {
      delete[] destination;
      if (source) {
         destination = new char[strlen(source) + 1];
         strcpy(destination, source);
      }
   }

   int Utils::getInt(const char* promt) {
      // upgrade the getInt Function Mar10th//
      // convinient to use and concise code//
      int input = 0;
      bool flag = true;
      do {
         if (!(cin >> input)) {
            cout << "Invalid Integer, retry: ";
            cin.clear();
            cin.ignore(1000, '\n');
         }
         else {
            flag = false;
         }
      } while (flag);
      return input;
   }

   int Utils::getint(int min, int max, const char* prompt, const char* errMes) {
      int input = 0;
      bool flag = true;
      if (prompt)
         cout << prompt;
      do {
         input = getInt(prompt);
         if (input > max || input < min) {
            if (errMes) {
               cout << errMes << ", retry: " << endl;
            }
            else {
               cout << "Value out of range " << "[" << min << "<=" << "val" << "<=" << max << "]" << ": ";
            }
         }
         else {
            flag = false;
         }
      } while (flag);
      return input;
   }

   double Utils::getDouble(const char* prompt){
      double input = 0.0;
      bool flag = true;
      do {
        
         if (!(cin >> input)) {
            cout << "Invalid number, retry: ";
            cin.clear();
            cin.ignore(1000, '\n');
         }
         else {
            flag = false;
         }
      } while (flag);
      return input;
   }

   double Utils::getDoubleAvecRange(double min, double max, const char* prompt, const char* errMes){
      double input = 0;
      bool flag = true;
      if (prompt) {
         cout << prompt;
      }
      do {
         input = getDouble(prompt);
         if (input > max || input < min) {
            if (errMes) {
               cout << errMes << ", retry: ";
            }
            else {
               cout.setf(std::ios::fixed);
               cout.precision(2);
               cout << "Value out of range " << "[" << min << "<=" << "val" << "<=" << max << "]" << ": ";
               cout.unsetf(std::ios::right);
               cout.unsetf(std::ios::fixed);
            }
         }
         else {
            flag = false;
         }
      } while (flag);
      return input;
   }

   void Utils::getSystemDate(int* year, int* mon, int* day) {
      if (m_testMode) {
         if (day) *day = sdds_testDay;
         if (mon) *mon = sdds_testMon;
         if (year) *year = sdds_testYear;
      }
      else {
         time_t t = std::time(NULL);
         tm lt = *localtime(&t);
         if (day) *day = lt.tm_mday;
         if (mon) *mon = lt.tm_mon + 1;
         if (year) *year = lt.tm_year + 1900;
      }
   }

   int Utils::daysOfMon(int month, int year)const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = (month >= 1 && month <= 12 ? month : 13) - 1;
      return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
   }

}