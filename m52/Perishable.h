/* ------------------------------------------------------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.

Project MS4
Course title:OOP244 NBB
Module:      Perishable
Filename:    Perishable.h
Version:     1
student:     Zhaokai Guan
Student Num: 130988215
Email:       zguan25@myseneca.ca
Date:        March 31th 2022

Revision History
-----------------------------------------------------------
Date:   Reason:
-----------------------------------------------------------*/
#ifndef SDDS_PERISHABLE
#define SDDS_PERISHABLE
#include "Item.h"
#include "Date.h"
namespace sdds {
   class Perishable : public Item {
      //A Perishable item (10000 to 39999)//
   private: 
      Date m_expiryDate{};
      char* m_instruct{};
   public:
      Perishable() = default;
      Perishable(const Perishable&src);
      const Perishable& operator=(const Perishable& src);
      virtual ~Perishable();

      //query//
      operator bool()const;
      const Date& expiry();
      // shadow the parent methods// 
      virtual int readSku(std::istream& istr);
      virtual std::ofstream& save(std::ofstream& ofstr) const;
      virtual std::ifstream& load(std::ifstream& ifstr);
      virtual std::ostream& display(std::ostream& ostr)const;
      virtual std::istream& read(std::istream& istr);
   };
}
#endif // !SDDS_PERISHABLE
