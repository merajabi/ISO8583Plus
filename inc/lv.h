#ifndef _LV_H_
#define _LV_H_

class LV : public DataPackager {

public:
	DataPackager& Set();
	std::string Pack(const std::string& in);
	std::string UnPack(const std::string& in,int& len);

};

#endif //_LV_H_




