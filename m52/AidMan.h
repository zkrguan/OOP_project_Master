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
#include "iProduct.h"
namespace sdds {
	const int sdds_max_num_items = 100;
	class AidMan {
		char* m_fileName{};
		menu m_mainMenu{};
		iProduct* m_ptrArr[sdds_max_num_items]{};
		// tracker can not go above than 100//
		int m_tracker{};
		//Private method//
		unsigned menus() const;
		void save();
		bool load();
		void deallocate();

	public:
		AidMan();
		AidMan(const AidMan& src) = delete;
		~AidMan();
		AidMan& operator = (const AidMan& src) = delete;
		// ms51//
		void run();
		int list(const char* sub_desc = nullptr);
		// ms52//
		int search(int sku) const;
		void addItem();
		void remove(int index);
		bool seachByStr();
		void updateQuantity(int index);
		void sort();
	};
	// created a global just in case the other module needs this//
}
#endif // !SDDS_AIDMAN_H
