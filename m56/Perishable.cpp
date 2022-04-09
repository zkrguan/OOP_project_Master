/* ------------------------------------------------------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.

Project MS5
Course title:OOP244 NBB
Module:      Perishable
Filename:    Perishable.h
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
#include <fstream>
#include <cstring>
#include "Perishable.h"
#include "Utils.h"
#include "Date.h"
namespace sdds {
   Perishable::Perishable(const Perishable& src) {
      *this = src;
   }

   const Perishable& Perishable::operator=(const Perishable& src) {
      if (this!=&src){
         Item::operator=(src);
         ut.alocpy(m_instruct, src.m_instruct);
         m_expiryDate = src.m_expiryDate;
      }
      return *this;
   }

   Perishable::~Perishable(){
      delete[] m_instruct;
   }

   Perishable::operator bool() const{
      return m_SKU;
   }

   const Date& Perishable::expiry(){
      return m_expiryDate;
   }

   int Perishable::readSku(std::istream& istr){
      std::cout << "SKU: ";
      m_SKU = ut.getint(10000, 39999);
      return m_SKU;
   }

   std::ofstream& Perishable::save(std::ofstream& ofstr) const{
      if (bool(m_stateOfItem)) {
         Item::save(ofstr);
         ofstr << "\t";
         if (m_instruct && strlen(m_instruct))
            ofstr << m_instruct; 
         ofstr << "\t";
         ofstr << Date(m_expiryDate).formatted(false);
      }
      return ofstr;
   }

   std::ifstream& Perishable::load(std::ifstream& ifstr){
      Item::load(ifstr);
      char tempInstruct[350]{};
      delete[]m_instruct;
      ifstr.get(tempInstruct, 349, '\t');
      ifstr.ignore();
      m_instruct = new char[strlen(tempInstruct) + 1];
      strcpy(m_instruct, tempInstruct);
      if (!ifstr){
         ifstr.clear();
         ifstr.ignore();
      }
      m_expiryDate.read(ifstr);
      if(!ifstr)
         m_stateOfItem = "Input file stream read (perishable) failed!";     
      return ifstr;
   }

   std::ostream& Perishable::display(std::ostream& ostr) const{
      if (bool(m_stateOfItem)){
         if (linear()){
            Item::display(ostr);
            ostr << (m_instruct && strlen(m_instruct) ? "*" : " ");
            ostr << m_expiryDate;
         }
         else{
            ostr << "Perishable ";
            Item::display(ostr);
            ostr << "Expiry date: ";
            ostr << m_expiryDate;
            if (m_instruct && strlen(m_instruct))
               ostr << "\nHandling Instructions: " << m_instruct;
            ostr << "\n";
         }
      }
      else
         ostr << m_stateOfItem;
      return ostr;
   }

   std::istream& Perishable::read(std::istream& istr){
      Item::read(istr);
      delete[] m_instruct;
      m_instruct = nullptr;
      istr.ignore();
      std::cout << "Expiry date (YYMMDD): ";
      m_expiryDate.read(istr);
      std::cout << "Handling Instructions, ENTER to skip: ";
      // this is the static char array reading//
      /* if (istr.peek() != '\n'){
         char tempInst[101]{};
         istr.get(tempInst, 100, '\n');
         ut.alocpy(m_instruct, tempInst);
      }*/
      
      // I perform the dynamic reading //
      // just for getting the BONUS MARK//
      // please take a look at this function in my utils//
      if (!ut.dynamicReadStr(m_instruct,istr))
         m_stateOfItem = "Perishable console date entry failed!";
      return istr;
   }







}