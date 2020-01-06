#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <sstream>
#include <vector>
#include <iterator>
#include <string>
#include <cstdio>
#include <stdint.h>

union intUnion {
	uint8_t i8[8];
	uint16_t i16[4];
	uint32_t i32[2];
	uint64_t i64[1];
};

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim);

template<typename T>
std::string toString(const T& value) {
	char str[128];
	double x = static_cast<double>(value);
	sprintf(str,"%.0lf",x);
	return str;
}

std::string HexToStr( const std::vector<uint8_t>& in);
std::vector<uint8_t> StrToHex( const std::string& in);

std::string HexToAscii(const std::string& str);
std::string AsciiToHex(const std::string& str);

std::string HexToAscii(std::vector<uint8_t> binary);

std::string HexString(const std::string& val);

std::string FixedLenPadString(const std::string& val,int len);
std::string PaddedFixedLenString(const std::string& val,int len, char ch='0');

std::string FixedLenDecString(uint32_t val,int len);
std::string FixedLenHexString(uint32_t val,int len);

int strBcdToAsc(int ilen, unsigned char *Sbcd, unsigned char *_DStr);
void HexToStrChar( uint8_t *in, int len, char *out);
int StrToHex( const char *in, int len, uint8_t *out);

bool MiladiIsLeap(int miladiYear);	//	From AMP Code By   : M.Rashidi
std::string MiladiToShamsi(const std::string& miladiDate);	//	From AMP Code By   : M.Rashidi
std::string GetPanFromTr2(const std::string tr2);

int generateCRC16(const std::vector<uint8_t> &p, unsigned long len);

#endif //_TOOLS_H_

