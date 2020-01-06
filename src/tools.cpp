#include <iostream>
#include <iomanip>
#include <sstream>

#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "tools.h"

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

std::string HexToStr( const std::vector<uint8_t>& in) {
	std::stringstream str;
	for(size_t i=0;i<in.size();i++)	{
		str << std::hex << std::setfill('0') << std::setw(2) << static_cast<uint16_t>(in[i]);
	}
	return str.str();
}
std::string HexToStr( const uint8_t* in, int len) {
    std::stringstream str;
    for(size_t i=0;i<len;i++)	{
        str << std::hex << std::setfill('0') << std::setw(2) << static_cast<uint16_t>(in[i]);
    }
    return str.str();
}
std::vector<uint8_t> StrToHex( const std::string& in) {
	std::vector<uint8_t> hex;
	std::string val;

	if(in.length()%2==0) {
		val=in;
	} else {
		val="0"+in;
	}

	for(size_t i=0; i < val.length(); i+=2){
		int num;
		std::stringstream(val.substr(i,2)) >> std::hex >> num;
		//std::cout << std::hex << "i: " << num << std::endl;
		hex.push_back(static_cast<uint8_t>(num));
	}
	return hex;
}
std::string FixedLenPadString(const std::string& val,int len){
	std::string str=std::string(len-val.size(),'0')+val;
	return str;
}

// Fixed len BCD
std::string PaddedFixedLenString(const std::string& val,int len, char ch){
	std::string str=std::string(len-val.size(),ch)+val;
	return str;
}
std::string PaddedFixedLenDecString(uint32_t val,int len){
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(len) << val ;
	return ss.str();
}


std::string FixedLenDecString(uint32_t val,int len){
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(len) << val ;
	return ss.str();
}
std::string AsciiToHex(const std::string& str){
	return HexString(str);
}
std::string HexToAscii(std::vector<uint8_t> binary){
	std::stringstream ss;
	for(size_t i=0; i<binary.size();i++){
		ss << binary[i] ;
	}
	return ss.str();
}
std::string HexToAscii(const std::string& str){
	std::stringstream ss;
	std::vector<uint8_t> binary=StrToHex(str);
	for(size_t i=0; i<binary.size();i++){
		ss << binary[i] ;
	}
	return ss.str();
}
std::string HexString(const std::string& val){
	std::stringstream ss;
	for (size_t i=0; i< val.size(); i++){
		ss << std::hex << std::setfill('0') << std::setw(2) << static_cast<uint16_t>(static_cast<uint8_t>(val[i]));
	}
	return ss.str();
}
std::string FixedLenHexString(uint32_t val,int len){
	std::string ss = FixedLenDecString(val,len/2);
	return HexString(ss);
}


int StrToHex( const char *in, int len, uint8_t *out)	{
	int i,j;
	char temp[3];
	if(len%2!=0){
		return 0;
	}
	for (i = 0, j=0; i < len; i+=2, j++){
		temp[0]=in[i];
		temp[1]=in[i+1];
		temp[2]=0;
		out[j] = strtol(temp, NULL, 16);
	}
	return j;
}

std::string MiladiToShamsi(const std::string& miladiDate) {
	std::string shamsiDate;
	int sumDayMiladiMonth[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
	int sumDayMiladiMonthLeap[] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 };

	int iMiladiMonth, iMiladiDay, iMiladiYear;
	int shamsiDay, shamsiMonth, shamsiYear;
	int dayCount, farvardinDayDiff, deyDayDiff;

	iMiladiYear = atoi(miladiDate.substr(0,4).c_str());
	iMiladiMonth = atoi(miladiDate.substr(4,2).c_str());
	iMiladiDay = atoi(miladiDate.substr(6,2).c_str());

	farvardinDayDiff = 79;

	if (MiladiIsLeap(iMiladiYear)) {
		dayCount = sumDayMiladiMonthLeap[iMiladiMonth - 1] + iMiladiDay;
	}
	else {
		dayCount = sumDayMiladiMonth[iMiladiMonth - 1] + iMiladiDay;
	}

	if (MiladiIsLeap(iMiladiYear - 1)) {
		deyDayDiff = 11;
	}
	else {
		deyDayDiff = 10;
	}

	if (dayCount > farvardinDayDiff) {
		dayCount = dayCount - farvardinDayDiff;
		if (dayCount <= 186) {
			switch (dayCount % 31)
			{
			case 0:
				shamsiMonth = dayCount / 31;
				shamsiDay = 31;
				break;

			default:
				shamsiMonth = (dayCount / 31) + 1;
				shamsiDay = (dayCount % 31);
				break;
			}
			shamsiYear = iMiladiYear - 621;
		}
		else {
			dayCount = dayCount - 186;
			switch (dayCount % 30)
			{
			case 0:
				shamsiMonth = (dayCount / 30) + 6;
				shamsiDay = 30;
				break;

			default:
				shamsiMonth = (dayCount / 30) + 7;
				shamsiDay = (dayCount % 30);
				break;
			}
			shamsiYear = iMiladiYear - 621;
		}
	}
	else {
		dayCount = dayCount + deyDayDiff;

		switch (dayCount % 30)
		{
		case 0:
			shamsiMonth = (dayCount / 30) + 9;
			shamsiDay = 30;
			break;

		default:
			shamsiMonth = (dayCount / 30) + 10;
			shamsiDay = (dayCount % 30);
			break;
		}
		shamsiYear = iMiladiYear - 622;

	}
	shamsiDate = toString(shamsiYear)+ PaddedFixedLenDecString(shamsiMonth,2) + PaddedFixedLenDecString(shamsiDay,2);
	return shamsiDate;
}

bool MiladiIsLeap(int miladiYear) {
	if (((miladiYear % 100) != 0 && (miladiYear % 4) == 0) || ((miladiYear % 100) == 0 && (miladiYear % 400) == 0)) {
		return true;
	} else {
		return false;
	}
}
std::string GetPanFromTr2(const std::string tr2) {
    return tr2.substr(0,tr2.find('='));
}


int generateCRC16(const std::vector<uint8_t> &p, unsigned long len)
{
	unsigned long i, j, bit;
	unsigned long ii, jj = 1, crcout;
	unsigned long crcmask = ((((unsigned long)1 << (15)) - 1) << 1) | 1;
	unsigned long crchighbit = (unsigned long)1 << (15);
	unsigned long crc = 0;

	for (i = 0; i<len; i++) {
		//unsigned long c = (unsigned long)*p++;
		unsigned long c = (unsigned long)p[i];

		crcout = 0;
		jj = 1;
		for (ii = (unsigned long)1 << (7); ii; ii >>= 1) {
			if (c & ii) crcout |= jj;
			jj <<= 1;
		}
		c = crcout;
		for (j = 0x80; j; j >>= 1) {

			bit = crc & crchighbit;
			crc <<= 1;
			if (c & j) bit ^= crchighbit;
			if (bit) crc ^= 0x8005;
		}
	}
	crcout = 0;
	jj = 1;
	for (ii = (unsigned long)1 << (15); ii; ii >>= 1) {
		if (crc & ii) crcout |= jj;
		jj <<= 1;
	}
	crc = crcout;
	crc ^= 0;
	crc &= crcmask;
	return(crc);
}

