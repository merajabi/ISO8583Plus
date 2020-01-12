#include<iostream>

#include "lv.h"
#include "iso8583v03.h"
//#include "bitmap.h"

int main() {
	LV f;
	std::string p1;
	try	{
		//	‌Bitmap bitmap(64);

		std::vector<int> fields = { 3, 4, 7, 11, 14, 42, 64};
		//	bitmap.SetBits(fields);

		//	std::cout<< "bitmap: " << bitmap.GetHexStr() << std::endl;

		p1 += f.Set({DataFormat::BCD, DataFormat::BCD, DataFormat::FIX, 4}).Pack("0100");				//# MTI code
		//	p1 += f.Set(BIN, BIN, FIX, 64)->Pack(bitmap.GetHexStr());	//# BITMAP

		p1 += f.Set({DataFormat::BCD, DataFormat::BCD, DataFormat::FIX, 6}).Pack("003000");				//# 3 Processing Code
		p1 += f.Set({DataFormat::BCD, DataFormat::BCD, DataFormat::FIX, 12}).Pack("100");				//# 4 Transaction Amount
		p1 += f.Set({DataFormat::BCD, DataFormat::BCD, DataFormat::FIX, 10}).Pack("1225084821");			//# 7 Transmission Date & Time
		p1 += f.Set({DataFormat::BCD, DataFormat::BCD, DataFormat::FIX, 6}).Pack("5860");				//# 11 Systems Trace Audit Number (STAN)
		p1 += f.Set({DataFormat::BCD, DataFormat::BCD, DataFormat::FIX, 4}).Pack("2108");				//# 14 Expiration Date
		p1 += f.Set({DataFormat::ASC, DataFormat::ASC, DataFormat::FIX, 15}).Pack("1234567890");			//# 42 Card Acceptor Identification Code

		std::cout<< "data: " << p1 << std::endl;
	} catch (const std::exception& e){
		std::cout<< "Error: " << e.what() << std::endl;
	}

	try {
		//my ($out,$len,$str);
		//	‌Bitmap bitmap(64);
		//$str = $p2->Data();
		std::pair<std::string,int> out;
		std::string str=p1;
		int index=0;

		out = f.Set({DataFormat::BIN, DataFormat::BIN, DataFormat::FIX, 40}).UnPack(str.substr(index));		//# TPDU	uncomment this line if your implimentation need TPDU header
		index+=out.second;
		std::cout<< "out: " << out.first << "\tlen: " << out.second << std::endl;
		out = f.Set({DataFormat::BCD, DataFormat::BCD, DataFormat::FIX, 4}).UnPack(str.substr(index));		//# MTI
		index+=out.second;
		out = f.Set({DataFormat::BIN, DataFormat::BIN, DataFormat::FIX, 64}).UnPack(str.substr(index));		//# bitmap
		index+=out.second;

		//bitmap.SetHexStr(out);
		//std::vector<int> fields = bitmap.GetBits();
		//print "bitmap fields: ",join( ,@fields),"\n";

		out = f.Set({DataFormat::BCD, DataFormat::BCD, DataFormat::FIX, 6}).UnPack(str.substr(index));		//# 3 Processing Code
		index+=out.second;
		out = f.Set({DataFormat::BCD, DataFormat::BCD, DataFormat::FIX, 12}).UnPack(str.substr(index));		//# 4 Transaction Amount
		index+=out.second;
		out = f.Set({DataFormat::BCD, DataFormat::BCD, DataFormat::FIX, 10}).UnPack(str.substr(index));		//# 7 Transmission Date & Time
		index+=out.second;
		out = f.Set({DataFormat::BCD, DataFormat::BCD, DataFormat::FIX, 6}).UnPack(str.substr(index));		//# 11 Systems Trace Audit Number (STAN)
		index+=out.second;
		out = f.Set({DataFormat::BCD, DataFormat::BCD, DataFormat::FIX, 4}).UnPack(str.substr(index));		//# 14 Expiration Date
		index+=out.second;
		out = f.Set({DataFormat::ASC, DataFormat::ASC, DataFormat::FIX, 15}).UnPack(str.substr(index));		//# 42 Card Acceptor Identification Code
		index+=out.second;
		out = f.Set({DataFormat::BIN, DataFormat::BIN, DataFormat::FIX, 64}).UnPack(str.substr(index));		//# 64 or 128 Message Authentication Code (MAC)
		index+=out.second;
		std::cout<< "out: " << out.first << "\tlen: " << out.second << std::endl;
	} catch (const std::exception& e){
		std::cout<< "Error: " << e.what() << std::endl;
	}

	return 0;
}
