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
#include <fstream>
#include <iostream>
#include "AidMan.h"
#include "Date.h"
#include "Utils.h"
#include "iProduct.h"
#include "Perishable.h"
#include "Item.h"
namespace sdds {
	unsigned AidMan::menus() const{
		unsigned option = 0;
		std::cout << "Aid Management System Version 0.1" << std::endl;
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
				if (m_ptrArr[i]) {
					m_ptrArr[i]->save(saveIn)<<"\n";
				}
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
			for (int i = 0; i < sdds_max_num_items; i++){
				read.clear();
				char firstC = 0;
				firstC = read.peek();
				if (int(firstC) >= '1' && int(firstC) <= '3') {
					m_ptrArr[i] = new Perishable;
				}
				// comparing asiic num actually// 
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
					// if true, number of iProduct Items is added by one, 
					// if false the loaded item is deleted.
					// can be simplified // 
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
			  std::cout << "\n****" << "List Items" << "****\n" << std::endl;
			  if (list()) {
				  bool flag = true;
				  int RowNum = 0;
				  std::cout << "Enter row number to display details or <ENTER> to continue:\n>";
				  RowNum = ut.getRowNum(1, m_tracker);
				  // -10 means user entered \n as the entry for the row num//
				  if (RowNum!=-10){
					  m_ptrArr[RowNum-1]->linear(false);
					  m_ptrArr[RowNum-1]->display(std::cout)<<std::endl;
				  }
			  }
			  break;
		  case 2:
			  std::cout <<"\n****" << "Add Item" <<"****\n" << std::endl;
			  addItem();
			  break;
		  case 3:
			  std::cout << "\n****" << "Remove Item" << "****\n" << std::endl;
			  break;
		  case 4:
			  std::cout << "\n****" << "Update Quantity" << "****\n" << std::endl;
			  break;
		  case 5:
			  std::cout << "\n****" << "Sort" << "****\n" << std::endl;
			  break;
		  case 6:
			  std::cout << "\n****" << "Ship Items" << "****\n" << std::endl;
			  break;
		  case 7:
			  std::cout << "\n****" << "New/Open Aid Database" << "****" << std::endl;
		  	  // prompt to get the filename//
			  std::cout << "Enter file name:";
			  std::cin.ignore(1000, '\n');
			  std::cin.get(tempName,49,'\n');
			  ut.alocpy(m_fileName, tempName);
			  // deallocate memory//
			  // load all the records//
			  load();
			  break;
		  default:
			  break;
		  }
		} while (userSelection);
		//call the save function//
		save();
		std::cout << "Exiting Program!" << std::endl;
	}

	int AidMan::list(const char* sub_desc){
		if (sub_desc){
			for (int i = 0; i < m_tracker; i++){
				m_ptrArr[i]->linear(false);
				m_ptrArr[i]->display(std::cout);
			}
		}
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
			// TD simplify this//
			if (*m_ptrArr[i] == sku) {
				index = i;
			}
		}
		return index;
	}

	void AidMan::addItem(){
		if (m_tracker == sdds_max_num_items){
			std::cout << "Database full!" << std::endl;
		}
		else{
			int input = 0;
			input = ut.getint(0, 2, "1- Perishable\n2- Non - Perishable\n-----------------\n0 - Exit\n>");
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
					}
					else{
						std::cout << "Sku: "<<tempSKU<< "is already in the system, try updating quantity instead.\n";
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
						std::cout << "Sku: " << tempSKU << " is already in the system, try updating quantity instead.\n";
					}
				}
				
			}
		}
	}
}