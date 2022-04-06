/* ------------------------------------------------------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.

Project MS4
Course title:OOP244 NBB
Module:      Item
Filename:    Item.h
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
#include <fstream>
#include <cstring>
#include "Item.h"
#include "Status.h"
namespace sdds {
   bool sdds::Item::linear() const{
      return m_flag;
   }

   Item::Item(const Item& src){
      *this = src;
   }

   Item& Item::operator=(const Item& src){
      if (this!=&src){
         ut.alocpy(m_desc, src.m_desc);
         m_price = src.m_price;
         m_onHand = src.m_onHand;
         m_inNeed = src.m_inNeed;
         m_flag = src.m_flag;
         m_stateOfItem = src.m_stateOfItem;
         m_SKU = src.m_SKU;
      }
      return *this;
   }

   Item::~Item(){
      delete[] m_desc;
   }


   int Item::qtyNeeded() const{
      return m_inNeed;
   }

   int Item::qty() const{
      return m_onHand;
   }

   Item::operator double() const{
      return m_price;
   }

   Item::operator bool() const{
      return m_stateOfItem;
   }

   int Item::operator-=(int deductVal){
      int res = deductVal;
      m_onHand -= deductVal;
      return res;
   }

   int Item::operator+=(int increaseVal){
      int res = increaseVal;
      m_onHand += increaseVal;
      return res;
   }

   void Item::linear(bool flag){
      m_flag = flag;
   }

   Item& Item::clear(){
      m_stateOfItem.clear();
      return *this;
   }

   bool Item::operator==(int srcSKU) const{  
      return m_SKU == srcSKU;
   }

   bool Item::operator==(const char* srcSTR) const{
      return (strstr(m_desc, srcSTR) && srcSTR);
   }

   std::ofstream& Item::save(std::ofstream& ofstr) const{
      if (bool(m_stateOfItem)){
         ofstr << m_SKU << "\t" << m_desc << "\t" << m_onHand << "\t" << m_inNeed<< "\t" << m_price;
      }     
      return ofstr;
   }

   std::ifstream& Item::load(std::ifstream& ifstr) {
      char tempDesc[350]{};
      delete[] m_desc;
      ifstr >> m_SKU;
      ifstr.ignore();
      // reading the desc// 
      ifstr.get(tempDesc, 350, '\t');
      ifstr.ignore();
      m_desc = new char[strlen(tempDesc) + 1];
      strcpy(m_desc, tempDesc);
      // reading the on-hand quantity//
      ifstr >> m_onHand;
      ifstr.ignore();
      // reading the needed//
      ifstr >> m_inNeed;
      ifstr.ignore();
      // reading the price//
      ifstr >> m_price;
      ifstr.ignore();
      return ifstr;
   }

   std::ostream& Item::display(std::ostream& ostr) const{
      if (!bool(m_stateOfItem)){
         ostr << m_stateOfItem;
      }
      else{
         //print in the linear//
         if (m_flag){
            ostr.width(5);
            ostr << m_SKU << " | ";
            // For loop inherited from Fardad coding style, so concise//
            // strlen will return a unsigned, learned it from a hard way//
            for (unsigned i = 0; i < 35; i++) 
               ostr << ((i < strlen(m_desc) ? m_desc[i] : ' '));
            ostr << " | ";
            ostr.setf(std::ios::right);
            ostr.fill(' ');
            ostr.width(4);
            ostr << m_onHand<<" | ";
            ostr.width(4);
            ostr << m_inNeed<<" | ";
            ostr.width(7);
            ostr.setf(std::ios::fixed);
            ostr.precision(2);
            ostr << m_price << " |";
            ostr.unsetf(std::ios::right);
            ostr.unsetf(std::ios::fixed);
         }
         //print in the descriptive//
         else{
            ostr << "AMA Item:" << std::endl;
            ostr << m_SKU<<": " << m_desc << std::endl;
            ostr << "Quantity Needed: "<<m_inNeed<< std::endl;
            ostr << "Quantity Available: " << m_onHand << std::endl;
            ostr.setf(std::ios::fixed);
            ostr.precision(2);
            ostr << "Unit Price: $" << m_price << std::endl;
            ostr << "Needed Purchase Fund: $" << m_price*(m_inNeed-m_onHand) << std::endl;
            ostr.unsetf(std::ios::fixed);
         }
      }
      return ostr;
   }

   std::istream& Item::read(std::istream& istr){
      std::cout << "AMA Item:\n" << "SKU: " << m_SKU << std::endl;
      std::cout << "Description: ";
      char tempDesc[200]{};
      // taking desc//
      istr.ignore();
      if (istr.getline(tempDesc, 199)) {
         ut.alocpy(m_desc, tempDesc);
         m_inNeed = ut.getint(1, 9999, "Quantity Needed: ");
         m_onHand = ut.getint(0, m_inNeed, "Quantity On Hand: ");
         m_price = ut.getDoubleAvecRange(0.0, 9999.0, "Unit Price: $");
      }
      else{
         m_stateOfItem = "Console entry failed!";
      }
      return istr;
   }

   int Item::readSku(std::istream& istr){
      std::cout << "SKU: ";
      m_SKU = ut.getint(40000, 99999);
      return m_SKU;
   }


   




}