#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "Date.h"
#include "Utils.h"

namespace sdds {
   int Date::uniqueDateVal() const{
      return m_year*372 + m_month*31+m_day;
   }

   bool Date::validate() {
      bool flag = false;
      if (m_year<2022||m_year>MAX_YEAR){
         m_state = "Invalid year in date";
         m_state = 1;
      }
      else if (m_month<1||m_month>12){
         m_state = "Invalid month in date";
         m_state = 2;
      }
      else if (m_day>ut.daysOfMon(m_month,m_year)||m_day<0){
         m_state = "Invalid day in date";
         m_state = 3;
      }
      else{
         m_state.clear();
         flag = true;
      }
      return flag;
   }

   Date::Date(){
      ut.getSystemDate(&m_year, &m_month, &m_day);
   }

   Date::Date(int year, int month, int day) {
      m_year = year;
      m_month = month;
      m_day = day;
      validate();
   }

   bool Date::operator==(const Date& cmpTo) const{
      return this->uniqueDateVal() == cmpTo.uniqueDateVal();
   }

   bool Date::operator!=(const Date& cmpTo) const{
      return this->uniqueDateVal() != cmpTo.uniqueDateVal();
   }

   bool Date::operator<(const Date& cmpTo) const{
      return this->uniqueDateVal() < cmpTo.uniqueDateVal();
   }

   bool Date::operator>(const Date& cmpTo) const{
      return this->uniqueDateVal() > cmpTo.uniqueDateVal();
   }

   bool Date::operator<=(const Date& cmpTo) const{
      return this->uniqueDateVal()<=cmpTo.uniqueDateVal();
   }

   bool Date::operator>=(const Date& cmpTo) const{
      return this->uniqueDateVal() >= cmpTo.uniqueDateVal();
   }

   const Status& Date::state(){
      return this->m_state;
   }

   Date& Date::formatted(bool format){
      m_formatted = format;
      return *this;
   }

   Date::operator bool() const{
      return m_state;
   }

   std::ostream& Date::write(std::ostream& ostr){
      if (validate()){
         if (m_formatted) {
            ostr << m_year << "/";
            ostr.width(2);
            ostr.fill('0');
            ostr << m_month;
            ostr << "/";
            ostr.width(2);
            ostr.fill('0');
            ostr << m_day;
         }
         else {
            ostr << m_year - 2000;
            ostr.width(2);
            ostr.fill('0');
            ostr << m_month;
            ostr.width(2);
            ostr.fill('0');
            ostr << m_day;
         }
      }
      return ostr;
   }

   std::istream& Date::read(std::istream& istr){
      // Had a perfect way by treating input as int, until I see the main code has a flush buffer//
      char inputFirstPart[5]{};
      char inputSecondPart[3]{};
      char formatChecker{};
      istr.get(inputFirstPart, 4);
      if (istr.peek()!='\n'){
         istr.get(inputSecondPart, 2);
         m_year = atoi(inputFirstPart) / 100;
         m_month = atoi(inputFirstPart) - m_year;
         m_day = atoi(inputSecondPart);
      }
      else{
         m_month = atoi(inputFirstPart) / 100;
         m_day = atoi(inputFirstPart) - m_month;
      }
      if (!validate()){
         istr.setstate(std::ios::failbit);
      }
      return istr;
   }
   



   std::ostream& operator<<(std::ostream& ostr, Date& srcVarible){
      return srcVarible.write(ostr);
   }

   std::istream& operator>>(std::istream& istr, Date& desVarible){
      return desVarible.read(istr);
   }


}