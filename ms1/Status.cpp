#include <iostream>
#include "Utils.h"
#include "Status.h"

namespace sdds {
   Status::Status(const char* desc){
      if (desc){
         ut.alocpy(m_description, desc);
      }
      else{
         m_description = nullptr;
      }
      m_statusCode = 0;
   }
   
   Status::Status(const Status& srcVarible){
      *this = srcVarible.m_description;
      *this = srcVarible.m_statusCode;
   }
   
   Status& Status::operator=(const Status& srcVarible){
      delete[] m_description;
      ut.alocpy(m_description, srcVarible.m_description);
      return *this;
   }
   
   Status& Status::operator=(const int srcValue){
      m_statusCode = srcValue;
      return *this;
   }
   
   Status::~Status(){
      delete[] m_description;
   }
   
   Status::operator int() const{
      return m_statusCode;
   }
   
   Status::operator const char* () const{
      return (const char*)m_description;
   }
   
   Status::operator bool() const{
      return !m_description;
   }
   
   Status& Status::clear(){
      delete[] m_description;
      m_description = nullptr;
      m_statusCode = 0;
      return *this;
   }
   
   std::ostream& operator<<(std::ostream& ostr, const Status& source){
      if (!source){
         if (!int(source)){
            ostr << "ERR#" << int(source) << ":" << (const char*)(source);
         }
      }
      return ostr;
   }
   

}