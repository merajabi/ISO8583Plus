#ifndef _LV_H_
#define _LV_H_

#include "datapackager.h"

class LV : public DataPackager {

public:
	DataPackager& Set(const std::vector<short>& v){
		return *this;
	}
	std::string Pack(const std::string& in){
		return "ABCD";
	}
	std::pair<std::string,int> UnPack(const std::string& in){
		return std::pair<std::string,int>("HI",1);
	}
};

#endif //_LV_H_




