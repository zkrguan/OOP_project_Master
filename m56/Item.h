/* ------------------------------------------------------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.

Project MS5
Course title:OOP244 NBB
Module:      Item
Filename:    Item.h
Version:     1
student:     Zhaokai Guan
Student Num: 130988215
Email:       zguan25@myseneca.ca
Date:        April 09th 2022

Revision History
-----------------------------------------------------------
Date:   Reason:
-----------------------------------------------------------*/
#ifndef SDDS_Item_H
#define SDDS_Item_H
#include <iostream>
#include "iProduct.h"
#include "Status.h"
#include "Utils.h"
namespace sdds {
	class Item : public iProduct{
		double m_price{};
		int m_onHand{};
		int m_inNeed{};
		char* m_desc{};
		bool m_flag{};
	protected:
		Status m_stateOfItem{};
		int m_SKU{};
		bool linear() const;
	public:
		// Make everything empty//
		Item()=default;
		Item(const Item& src);
		Item& operator = (const Item& src);
		// clear the m_desc//
		~Item();
		//return the need//
		virtual int qtyNeeded () const;
		// returns the onhand//
		virtual int qty() const;
		// returns price//
		virtual operator double() const;
		// returns state //
		virtual operator bool() const;
		//modifiers//
		// reduces the on-hand quantity by the received value//
		virtual int operator -= (int deductVal);
		//increases the on-hand quantity by the received value//
		virtual int operator += (int increaseVal);
		// sets the linear flag for print//
		virtual void linear(bool flag);
		// clear sets the state of the Item object back to good // 
		// by resetting the state attribute.//
		Item& clear();
		// true if the SKU attribute matches the received value // 
		// further details are on git hub//
		virtual bool operator == (const int srcSKU)const;
		virtual bool operator == (const char* srcSTR)const;
		//  state is good,write SKU, description, on-hand quantity, 
		//  needed quantity and price 
		//  in tab-separated format.
		//  No newline is added.
		//  state is bad do nothing
		virtual std::ofstream& save(std::ofstream& ofstr) const;
		//  After deallocating the description:
		//  The tab-separated SKU, description, on-hand quantity, 
		//  needed quantity and price are read into their corresponding attributes
		//  and then a single character is discarded from the file.( \n)
		//  if istr is bad state
		//  change the state to "Input file stream read failed!"
		virtual std::ifstream& load(std::ifstream& ifstr) ;
		// If the state is bad, the state is printed instead.
		// If the state is good the following will be done.
		virtual std::ostream& display(std::ostream& ostr)const;
		// still have read and read SKU//
		virtual std::istream& read(std::istream& istr);
		virtual int readSku(std::istream& istr);
	};
}

#endif // !SDDS_Item_H
