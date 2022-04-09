/* ------------------------------------------------------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.

Project MS5
Course title:OOP244 NBB
Module:      iProduct
Filename:    iProduct.cpp
Version:     1
student:     Zhaokai Guan
Student Num: 130988215
Email:       zguan25@myseneca.ca
Date:        April 09th 2022

Revision History
-----------------------------------------------------------
Date:   Reason:
-----------------------------------------------------------*/
#include "iProduct.h"
namespace sdds {
   std::ostream& operator << (std::ostream& ostr, const iProduct& prdToPrint) {
      return prdToPrint.display(ostr);
   }

   std::istream& operator >> (std::istream& istr, iProduct& prdToRead) {
      return prdToRead.read(istr);
   }
}