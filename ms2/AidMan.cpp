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
#include<iostream>
#include"AidMan.h"
#include"Date.h"
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
		  	  break;
		  default:
			  break;
		  }
		} while (userSelection);
		std::cout << "Exiting Program!" << std::endl;
	}
}