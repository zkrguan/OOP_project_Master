/* ------------------------------------------------------
I have done all the coding by myself and
only copied the code that my professor provided
to complete my workshops and assignments.

Project MS2
Course title:OOP244 NBB
Module:      Menu
Filename:    Menu.cpp
Version:     1
student:     Zhaokai Guan
Student Num: 130988215
Email:       zguan25@myseneca.ca
Date:        March 10th 2022

Revision History
-----------------------------------------------------------
Date:   Reason:
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Menu.h"
#include "Utils.h"
namespace sdds {
	menu::menu(){
		m_options = nullptr;
		m_numOfOptions = 0;
	}

	menu::menu(unsigned num, const char* cString){
		if (num>15||!cString){
			m_numOfOptions = 0;
			delete[] m_options;
			m_options = nullptr;
		}
		else{
			delete [] m_options;
			m_options = new char[strlen(cString) + 1];
			strcpy(m_options, cString);
		}
	}

	void menu::set(const char* srcString, unsigned numOptions){
		delete[] m_options;
		m_options = new char[strlen(srcString) + 1];
		strcpy(m_options, srcString);
		m_numOfOptions = numOptions;
	}

	menu::~menu(){
		delete[] m_options;
	}

	unsigned menu::run()const{
		unsigned userInput = 0;
		std::cout << m_options;
		std::cout << "> ";
		userInput = ut.getint(0, m_numOfOptions);
		return userInput;
	}


}