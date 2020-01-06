#include<iostream>

#include "lv.h"
#include "dataformat.h"
#/*
# *  BINARY: FEDCBA9876543210
# *  BCD:	1234567890
# *  ASCII:	zxclkjsdfouewuoaseuidweigu98234-;akslijwad982137
# */
using namespace DataPackager;
int main () {
	{
		try {
			DataPackager::LV f;
			std::string out = f.Set({DataFormat::BIN,DataFormat::BIN,DataFormat::FIX,64}).Pack("0123456789ABCDEF");
			std::cout << out << std::endl;
		}catch(std::exception& e){
			std::cout << e.what() << std::endl;
		}
	}

	{
		try {
			DataPackager::LV f;
			std::string out = f.Set({DataFormat::BCD,DataFormat::BCD,DataFormat::FIX,12}).Pack("1000");
			std::cout << out << std::endl;
		}catch(std::exception& e){
			std::cout << e.what() << std::endl;
		}
	}

	{
		try {
			DataPackager::LV f;
			std::string out = f.Set({DataFormat::ASC,DataFormat::ASC,DataFormat::FIX,12}).Pack("abcd1234wxyz");
			std::cout << out << std::endl;
		}catch(std::exception& e){
			std::cout << e.what() << std::endl;
		}
	}
	{
		try {
			DataPackager::LV f;
			std::string out = f.Set({DataFormat::BCD,DataFormat::BCD,DataFormat::VAR,19}).Pack("1234567812345678");
			std::cout << out << std::endl;
		}catch(std::exception& e){
			std::cout << e.what() << std::endl;
		}
	}
	{
		try {
			DataPackager::LV f;
			std::string out = f.Set({DataFormat::BCD,DataFormat::ASC,DataFormat::VAR,28}).Pack("1234567812345678=95");
			std::cout << out << std::endl;
		}catch(std::exception& e){
			std::cout << e.what() << std::endl;
		}
	}
	return 0;
}

