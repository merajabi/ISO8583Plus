#include<iostream>

#include "Bitmap.h"

int main() {

	std::string str;
	try	{
		Bitmap bitmap(64);
		std::vector<uint8_t> fields = { 3, 4, 7, 11, 14, 42, 64};
		bitmap.SetBits(fields);
		str=bitmap.GetHexStr();

		std::cout<< "bitmap: " << str << std::endl;

	} catch (const std::exception& e){
		std::cout<< "Error: " << e.what() << std::endl;
	}

	try {
		Bitmap bitmap(64);

		bitmap.SetHexStr(str);
		std::vector<uint8_t> fields = bitmap.GetBits();
		for (int i=0 ; i< fields.size(); i++){
			std::cout<< "fields: " << i<< ":" << static_cast<uint16_t>(fields[i]) << std::endl;
		}
	} catch (const std::exception& e){
		std::cout<< "Error: " << e.what() << std::endl;
	}

	try	{
		Bitmap bitmap(128);
		std::vector<uint8_t> fields = { 3, 4, 7, 11, 14, 42, 100, 103, 107, 126, 128};
		bitmap.SetBits(fields);
		str=bitmap.GetHexStr();

		std::cout<< "bitmap: " << str << std::endl;

	} catch (const std::exception& e){
		std::cout<< "Error: " << e.what() << std::endl;
	}

	try {
		Bitmap bitmap(128);

		bitmap.SetHexStr(str);
		std::vector<uint8_t> fields = bitmap.GetBits();
		for (int i=0 ; i< fields.size(); i++){
			std::cout<< "fields: " << i<< ":" << static_cast<uint16_t>(fields[i]) << std::endl;
		}
	} catch (const std::exception& e){
		std::cout<< "Error: " << e.what() << std::endl;
	}

	return 0;
}
