/* ------------------------------------------------------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.

Project MS2
Course title:OOP244 NBB
Module:      AidMan
Filename:    AidMan.h
Version:     1
student:     Zhaokai Guan
Student Num: 130988215
Email:       zguan25@myseneca.ca
Date:        March 10th 2022

Revision History
-----------------------------------------------------------
Date:   Reason:
-----------------------------------------------------------*/
#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H
#include "Menu.h"
namespace sdds {
	class AidMan {
		char* m_fileName{};
		menu m_mainMenu{};
		//Private method//
		unsigned menus() const;
	public:
		AidMan();
		AidMan(const AidMan& src) = delete;
		~AidMan();
		AidMan& operator = (const AidMan& src) = delete;
		void run();
	};
}
#endif // !SDDS_AIDMAN_H
