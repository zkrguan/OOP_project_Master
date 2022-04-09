/* ------------------------------------------------------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.

Project MS5
Course title:OOP244 NBB
Module:      Utils
Filename:    Utils.cpp
Version:     1
student:     Zhaokai Guan
Student Num: 130988215
Email:       zguan25@myseneca.ca
Date:        April 09th 2022

Revision History
-----------------------------------------------------------
Date:   Reason:
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctype.h>
#include <cstring>
#include <ctime>
#include "Utils.h"
#include "Item.h"
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

   std::istream& Utils::dynamicReadStr(char*& destination, std::istream& istr){
      if (istr.peek() != '\n') {
         char* dynTemp = nullptr;
         char* swapTemp = nullptr;
         int Size = 2;
         int incrementSize = 5;
         int counter = 0;
         // allocate the initial size//
         dynTemp = new char[Size];//2 elements//
         for (int i = 0; istr.peek() != '\n'; i++) {
            if ((Size - 1) == i) {
               //dup a dynamic arr//
               swapTemp = new char[Size];
               for (int j = 0; j < Size - 1; j++) {
                  swapTemp[j] = dynTemp[j];
               }
               //resize dyn//
               delete[] dynTemp;
               dynTemp = new char[Size += incrementSize];
               // copy onto the resized arr// 
               for (int j = 0; j < (Size - incrementSize - 1); j++) {
                  dynTemp[j] = swapTemp[j];
               }
               //get rid off the old one//
               delete[] swapTemp;
            }
            //reading char by char//
            dynTemp[i] = getchar();
            counter++;
         }
         // manually put a stopper//
         dynTemp[counter] = 0;
         // copy the temp onto the destination//
         ut.alocpy(destination, dynTemp);
         // after copy to the m_instruct, dynTemp is useless now//
         delete[]dynTemp;
      }
      istr.ignore();
      return istr;
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

   int Utils::getRowNum(int min,int max) {
      char input{};
      int convertedInput = -5;
      bool flag = false;
      do {
         cin.ignore();
         input = getchar();
         if (isdigit(input)) {
            // if the input is a digit char, use input's asiic code to minus the 0's asiic code//
            // will get the actual int value of the input// 
            convertedInput = input - '0';
            if (convertedInput< min || convertedInput>max){
               cout << "Value out of range " << "[" << min << "<=" << "val" << "<=" << max << "]" << ": ";
               flag = true;
            }
            else{
               flag = false;
            }
         }
         else if (input=='\n') {
            // -10 is the exit flag for the menu option1//
            convertedInput = -10;
            cout << "\n";
         } 
         else{
            cout << "Invalid Entry, retry: ";
            flag = true;
            cin.clear();
            cin.ignore(1000, '\n');
         }
      } while (flag);
      return convertedInput;
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