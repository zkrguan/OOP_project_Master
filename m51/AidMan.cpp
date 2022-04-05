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
			std::cout << m_fileName << ".csv" << std::endl;
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
		if (m_fileName){
			std::ofstream writeInto(m_fileName);
			for (int i = 0; i < sdds_max_num_items; i++)
				m_ptrArr[i]->save(writeInto);
		}
	}

	bool AidMan::load(){
		bool res = false;
		save();
		deallocate();
		std::fstream fs;
		std::ifstream read;
		fs.open(m_fileName, std::ios::in);
		if (fs){
			for (int i = 0; i < sdds_max_num_items; i++){
				int firstNum = 0;
				firstNum = read.peek();
				if (firstNum>= 10000&& firstNum<=39999){
					// how to allocate the temp new?????
					m_ptrArr[i] = new Perishable();
					m_tracker++;
				}
				else if (firstNum>=40000&&firstNum<=99999){
					// how to allocate the temp new?????
					m_ptrArr[i] = new Item();
					m_tracker++;
				}
				else{
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
			
		}
		else{
			std::cout << "Failed to open " << m_fileName << " for reading!" << std::endl;
			std::cout << "Would you like to create a new data file?" << std::endl;
			int input = ut.getint(0, 1, "1- Yes!\n0 - Exit\n>");
			if (input){
				fs.open(m_fileName, std::ios::out);
			}
		}
		return res;
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
			  break;
		  case 2:
			  std::cout <<"\n****" << "Add Item" <<"****\n" << std::endl;
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
			  std::cout << "\n****" << "New/Open Aid Database" << "****\n" << std::endl;
		  	  // prompt to get the filename//
			  std::cout << "Enter file name:" << std::endl;
			  char tempName[50]{};
			  std::cin.getline(tempName,49);
			  ut.alocpy(m_fileName, tempName);
			  // deallocate memory//
			  // load all the records//
			  break;
		  default:
			  break;
		  }

		} while (userSelection);
		//call the save function//
		save();
		std::cout << "Exiting Program!" << std::endl;
	}

	
}