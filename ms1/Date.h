#ifndef SSDS_DATE_H
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
      bool m_formatted;
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
   std::ostream& write(std::ostream& ostr);
   std::istream& read(std::istream& istr);
   };
   std::ostream& operator <<(std::ostream& ostr, Date& srcVarible);
   std::istream& operator >>(std::istream& istr, Date& desVarible);
}
#endif // !SSDS_DATE_H
