/* ------------------------------------------------------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.

Project MS5
Course title:OOP244 NBB
Module:      AidMan
Filename:    AidMan.cpp
Version:     1
student:     Zhaokai Guan
Student Num: 130988215
Email:       zguan25@myseneca.ca
Date:        April 9th 2022

Revision History
-----------------------------------------------------------
Date:   Reason:
-----------------------------------------------------------*/
#include <fstream>
#include <iostream>
#include <string.h>
#include <cstring>
#include "AidMan.h"
#include "Date.h"
#include "Utils.h"
#include "iProduct.h"
#include "Perishable.h"
#include "Item.h"
namespace sdds {
	unsigned AidMan::menus() const{
		unsigned option = 0;
		std::cout << "Aid Management System" << std::endl;
		// Used prof's calling constructor to get a temp project to print out the system time//
		// discard it right after used, so good//
		std::cout << "Date: "<<Date() << std::endl;
		std::cout << "Data file: ";
		if (m_fileName){
			std::cout << m_fileName << std::endl;
		}
		else{
			std::cout << "No file" << std::endl;
		}
		std::cout << "---------------------------------" << std::endl;
		option = m_mainMenu.run();
		return option;
	}
	//ms5 func//
	void AidMan::save(){
		if (m_fileName) {
			std::ofstream saveIn;
			saveIn.open(m_fileName,std::ios::out);
			for (int i = 0; i < m_tracker; i++){
				if (m_ptrArr[i]) 
					m_ptrArr[i]->save(saveIn)<<"\n";
			}
			saveIn.close();
		}
	}

	bool AidMan::load(){
		// check if ptrarry is empty//
		if (m_ptrArr[0]) {
			save();
			deallocate();
		}
		std::ifstream read;
		read.open(m_fileName, std::ios::in);
		if (read){
			// eof?//
			for (int i = 0; i < sdds_max_num_items; i++){
				read.clear();
				// use char to peek the first char of each line//
				char firstC = 0;
				firstC = read.peek();
				// allocating the arr element by the comparing asiic num actually// 
				if (int(firstC) >= '1' && int(firstC) <= '3') {
					m_ptrArr[i] = new Perishable;
				}
				else if (int(firstC) >='4' && int(firstC) <='9'){
					m_ptrArr[i] = new Item;
				}
				else{
					// set the failbit so it won't go to read//
					// line 94 won't be dereferecing any nullptr//
					read.setstate(std::ios::failbit);
				}
				if (read) {
					// call the load method of the items to load it into the file
					m_ptrArr[i]->load(read);
					// the loaded item is checked to be in a good state,				
					if (bool(*m_ptrArr[i])){
						m_tracker++;
					}
					else{
						delete m_ptrArr[i];
					}
				}
			}
			std::cout << m_tracker << " records loaded!\n" << std::endl;
		}
		else{
			m_tracker = 0;
			std::cout << "Failed to open " << m_fileName << " for reading!" << std::endl;
			std::cout << "Would you like to create a new data file?" << std::endl;
			int input = ut.getint(0, 1, "1- Yes!\n0- Exit\n>");
			if (input){
				read.open(m_fileName, std::ios::out);
			}
			else{
				delete[] m_fileName;
				m_fileName = nullptr;
			}
		}
		//close the file// 
		read.close();
		return m_tracker;
	}

	void AidMan::deallocate(){
		for (int i = 0; i <sdds_max_num_items; i++){
			delete m_ptrArr [i];
			// set it to nullptr is important at here 
			// Because the remove function design
			m_ptrArr[i] = nullptr;
		}
		m_tracker = 0;
	}

	AidMan::AidMan(){
		const char menuContent[] =
			"1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n0- Exit\n";
		m_mainMenu.set(menuContent, 7);
		// m_filename is initialized as nullptr in the headerfile while defining the class//
	}

	AidMan::~AidMan(){
		delete[] m_fileName;
	}

	void AidMan::run(){
		char tempName[50]{};
		int userSelection = 0;
		do{
		  userSelection = menus();
		  if (!m_fileName&&userSelection !=7&&userSelection){
			  userSelection = 7;
		  }
		  switch (userSelection)
		  {
		  case 1:
			  std::cout << "\n****" << "List Items" << "****" << std::endl;
			  if (list()) {
				  int RowNum = 0;
				  std::cout << "Enter row number to display details or <ENTER> to continue:\n> ";
				  RowNum = ut.getRowNum(1, m_tracker);
				  // -10 means user entered \n as the entry for the row num//
				  if (RowNum!=-10){
					  m_ptrArr[RowNum-1]->linear(false);
					  std::cout << m_ptrArr[RowNum - 1] << std::endl;
				  }
			  }
			  break;
		  case 2:
			  std::cout <<"\n****" << "Add Item" <<"****\n";
			  addItem();
			  break;
		  case 3:
			  std::cout << "\n****" << "Remove Item" << "****\n";
			  std::cout << "Item description: ";
			  if (seachByStr()) {
				  int tempSKU = 0;
				  int index = -2;
				  std::cout << "Enter SKU: ";
				  std::cin >> tempSKU;
				  index = search(tempSKU);
				  if (index > -1){
					  std::cout << "Following item will be removed: " << std::endl;
					  m_ptrArr[index]->linear(false);
					  m_ptrArr[index]->display(std::cout)<<"\n";
					  int userConf = ut.getint(0, 1, "Are you sure?\n1- Yes!\n0- Exit\n> ");
					  if (userConf){
						  remove(index);
						  std::cout << "Item removed!\n" << std::endl;
					  }
					  else{
						  std::cout << "Aborted!\n";
					  }
				  }
				  else{
					  std::cout << "SKU can not be found!\n";
				  }
			  }
			  else{
				  std::cout << "Can't find the item with the input information, please use option 1 to see all the inventory" << std::endl;
			  }
			  break;
		  case 4:
			  std::cout << "\n****" << "Update Quantity" << "****\n";
			  std::cout << "Item description: ";
			  if (seachByStr()) {
				  int tempSKU = 0;
				  int index = -2;
				  std::cout << "Enter SKU: ";
				  std::cin >> tempSKU;
				  index = search(tempSKU);
				  if (index > -1){
					  updateQuantity(index);
				  }
				  else {
					  std::cout << "SKU can not be found!\n";
				  }
			  }
			  else{
				  std::cout << "No Matches can be found\n";
			  }
			  break;
		  case 5:
			  std::cout << "\n****" << "Sort" << "****\n";
			  sort();
			  break;
		  //intentionally added scope for case 6 in order to declare a ofstr variable inside//
		  case 6: {
			   int counter = 0;
				std::cout << "\n****" << "Ship Items" << "****" << std::endl;
				std::ofstream shipping("shippingOrder.txt", std::ios::out); 
				shipping << "Shipping Order, Date: " << Date() << "\n";
				shipping << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry\n";
				shipping << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
				for ( int i = 0;  i < m_tracker; i++){
					if (m_ptrArr[i]->qty() == m_ptrArr[i]->qtyNeeded()) {
						shipping.width(4);
						shipping.fill(' ');
						shipping.setf(std::ios::right);
						shipping << counter + 1 << " | ";
						shipping.unsetf(std::ios::right);
						m_ptrArr[i]->linear(true);
						m_ptrArr[i]->display(shipping);
						shipping << "\n";
						remove(i);
						counter++;
						// otherwise it will skip one element//
						i--;
					}
				}
				shipping << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
				shipping.close();
				std::cout << "Shipping Order for " << counter << " times saved!\n"<<std::endl;
				}
			  break;
		  case 7:
			  std::cout << "\n****" << "New/Open Aid Database" << "****" << std::endl;
		  	  // prompt to get the filename//
			  std::cout << "Enter file name: ";
			  std::cin.ignore(1000, '\n');
			  std::cin.get(tempName,49,'\n');
			  ut.alocpy(m_fileName, tempName);
			  load();
			  break;
		  default:
			  break;
		  }
		} while (userSelection);
		//call the save function//
		save();
		deallocate();
		std::cout << "Exiting Program!" << std::endl;
	}

	int AidMan::list(const char* sub_desc){
		if (sub_desc){
			for (int i = 0; i < m_tracker; i++){
				m_ptrArr[i]->linear(false);
				m_ptrArr[i]->display(std::cout);
			}
		}
		//TD:: this can be a seperated function for all the menu options to share with 
		else{
			if (m_tracker){
				std::cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << std::endl;
				std::cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;
				for (int i = 0; i < m_tracker; i++) {
					std::cout.width(4);
					std::cout.fill(' ');
					std::cout.setf(std::ios::right);
					std::cout << i + 1 << " | ";
					std::cout.unsetf(std::ios::right);
					m_ptrArr[i]->linear(true);
					m_ptrArr[i]->display(std::cout) << std::endl;
				}
				std::cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;
			}
			else{
				std::cout<<"The list is emtpy!" << std::endl;
			}
		}
		return m_tracker;
	}

	int AidMan::search(int sku) const{
		int index = -1;
		for (int i = 0; i < m_tracker&&(index==-1); i++) {
			if (*m_ptrArr[i] == sku) 
				index = i;
		}
		return index;
	}

	void AidMan::addItem(){
		if (m_tracker == sdds_max_num_items){
			std::cout << "Database full!" << std::endl;
		}
		else{
			int input = 0;

			input = ut.getint(0, 2, "1- Perishable\n2- Non-Perishable\n-----------------\n0- Exit\n> ");
			if (!input){
				std::cout << "Aborted\n" << std::endl;
			}
			else{
				// TD: simplify this 
				int tempSKU = 0;
				if (input == 1) {
					Perishable temp;
					tempSKU = temp.readSku(std::cin);
					if (search(tempSKU) == -1) {
						temp.read(std::cin);
						m_ptrArr[m_tracker] = new Perishable(temp);
						m_tracker++;
						std::cout << "\n";
					}
					else{
						std::cout << "Sku: " << tempSKU << "is already in the system, try updating quantity instead.\n\n";
					}
				}
				else {
					Item temp;
					tempSKU=temp.readSku(std::cin);
					if (search(tempSKU) == -1) {
						temp.read(std::cin);
						m_ptrArr[m_tracker] = new Item(temp);
						m_tracker++;
					}
					else {
						std::cout << "Sku: " << tempSKU << " is already in the system, try updating quantity instead.\n\n";
					}
				}
				
			}
		}
	}

	void AidMan::remove(int index){
		bool flag = false;
		delete m_ptrArr[index];
		for (int i = index; i < m_tracker; i++){
			m_ptrArr[i] = m_ptrArr[i + 1];
			flag = true;
		}
		if (flag){
			m_tracker--;
		}
	}
	bool AidMan::seachByStr(){
		bool flag = false;
		std::string tempStrDesc;
		std::cin >> tempStrDesc;
		std::cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << std::endl;
		std::cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;
		for (int i = 0; i < m_tracker; i++){
			if (*m_ptrArr[i] == tempStrDesc.c_str()) {
				std::cout.width(4);
				std::cout.fill(' ');
				std::cout.setf(std::ios::right);
				std::cout << i + 1 << " | ";
				std::cout.unsetf(std::ios::right);
				m_ptrArr[i]->linear(true);
				m_ptrArr[i]->display(std::cout) << std::endl;
				flag = true;
			}
		}
		std::cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;
		return flag;
	}

	void AidMan::updateQuantity(int index){
		int userOptions = ut.getint(0, 2, "1- Add\n2- Reduce\n0- Exit\n> ");
		int quantity = -1;
		int updateRes = 0;
		switch (userOptions){
		case 1:
			if (m_ptrArr[index]->qtyNeeded()== m_ptrArr[index]->qty()){
				std::cout << "Quantity Needed already fulfilled!\n\n";
			}
			else{
				quantity = ut.getint(1, m_ptrArr[index]->qtyNeeded(), "Quantity to add: ");
				updateRes = (*m_ptrArr[index] += quantity);
			   std::cout << updateRes << " items added!\n\n";
			}
			break;
		case 2:
			if (!( m_ptrArr[index]->qty() ) ){
				std::cout << "Quaintity on hand is zero!\n\n";
			}
			else{
				quantity = ut.getint(1, m_ptrArr[index]->qty(), "Quantity to reduce: ");
				updateRes = (*m_ptrArr[index] -= quantity);
				std::cout << updateRes << " items removed!\n\n";
			}
			break;
		default:
			std::cout << "Aborted!\n\n";
			break;
		}
	}

	void AidMan::sort(){
		// using the traditional bubble sort learned from last year to acomplish this//
		int i, j;
		// Will not use i to access each element. //
		// i is more like a round counter in order to run enough times for the sorting..//
		for (i = 0; i < (m_tracker-1); i++) {
			// each round, j will access every arr element to compare from the left to the right// 
			for (j = 0; j < (m_tracker -i-1); j++) {
				// if the left element is bigger than the one from right//
				// shift it to the right by one index//
				if ((m_ptrArr[j]->qtyNeeded()- m_ptrArr[j]->qty() )< (m_ptrArr[j+1]->qtyNeeded() - m_ptrArr[j+1]->qty())) {
					iProduct* temp = m_ptrArr[j];
					m_ptrArr[j] = m_ptrArr[j + 1];
					m_ptrArr[j + 1] = temp;
				}
			}
		}
		std::cout << "Sort completed!\n" << std::endl;
	}

}