/* ------------------------------------------------------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.

Project MS5
Course title:OOP244 NBB
Module:      Menu
Filename:    Menu.h
Version:     1
student:     Zhaokai Guan
Student Num: 130988215
Email:       zguan25@myseneca.ca
Date:        April 09th 2022

Revision History
-----------------------------------------------------------
Date:   Reason:
-----------------------------------------------------------*/
#ifndef SDDS_MENU_H
#define SDDS_MENU_H
namespace sdds {
	class menu {
		char* m_options{};
		unsigned m_numOfOptions{};
	public:
		menu();
		menu(unsigned num,const char* cString);
		menu(const menu& incoming) = delete;
		menu& operator = (const menu& incoming) = delete;
		//student defined function//
		void set(const char* srcString, unsigned numOptions);
		~menu();
		unsigned run()const;
	};
}
#endif // !SDDS_MENU_H
