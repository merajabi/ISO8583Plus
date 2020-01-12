/*
=head1 AUTHOR

Mehdi(Raha) Rajabi C<raha.emailbox@gmail.com>

=head1 COPYRIGHT (c)

Copyright 2009-2017 by Mehdi(Raha) Rajabi C<raha.emailbox@gmail.com>

=head1 LICENSE

This module is released under the terms of GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007

=cut
*/
#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

class Bitmap {
	std::vector<uint8_t> bitmap;
public:
	Bitmap(int bits):bitmap(bits/8,0){
	};

	void SetBits(const std::vector<uint8_t>& fields){
		for(int i=0; i < fields.size(); i++){
			int index = (fields[i]-1) / 8;
			int pos = (fields[i]-1) % 8;
			uint8_t val = 128 >> pos;
			bitmap[index] |= val;
		}
		//std::cout << HexToStr(bitmap) << std::endl;
	}

	std::vector<uint8_t> GetBits(){
		std::vector<uint8_t> fields;
		for(int i=0; i < bitmap.size(); i++){
			uint8_t x = bitmap[i];
			for(int j=0; j < 8; j++){
				if( x & 1 ){
					fields.push_back( static_cast<uint8_t>( (8-j) + i*8 ) );
				}
				x = x >>1;
			}
		}
		std::sort(fields.begin(), fields.end());
		return fields;
	}

	std::string GetHexStr() {
		std::stringstream ss;
		for(int i=0; i< bitmap.size(); i++){
			ss << std::hex << std::setfill('0') << std::setw(2) << static_cast<uint16_t>(bitmap[i]);
		}
		return ss.str();
	}

	void SetHexStr(const std::string& hexStr){
		for(int i=0; i < hexStr.size(); i+=2){
			bitmap[i/2] = std::stol(hexStr.substr(i,2),0,16);

			//uint16_t num;
			//std::stringstream(hexStr.substr(i,2)) >> std::hex >> num;
			//bitmap[i/2]=static_cast<uint8_t>(num);
		}
	}

};
#endif //_BITMAP_H_

