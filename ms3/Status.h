/* ------------------------------------------------------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.

Project MS1
Course title:OOP244 NBB
Module:      Status
Filename:    Status.h
Version:     1
student:     Zhaokai Guan
Student Num: 130988215
Email:       zguan25@myseneca.ca
Date:        March 10th 2022

Revision History
-----------------------------------------------------------
Date:   Reason:
-----------------------------------------------------------*/
#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H
namespace sdds {
	class Status{	
		char* m_description{};
		int m_statusCode{};
	public:
		Status(const char * desc= nullptr);
		Status(const Status& srcVarible);
		Status& operator = (const Status& srcVarible);
		Status& operator = (const int srcValue);
		// student defined overloading to make the process easier // 
		Status& operator= (const char* srcStr);
		~Status();
		operator int()const;
		operator const char* ()const;
		operator bool() const;
		Status& clear();
	};
	std::ostream& operator << (std::ostream& ostr, const Status& source);
}
#endif // !SDDS_STATUS_H
