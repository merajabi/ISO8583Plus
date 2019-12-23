#ifndef _DATAPACKAGER_H_
#define _DATAPACKAGER_H_

class DataPackager {
	std::vector<short> format;
public:
	virtual DataPackager& Set() =0
	virtual std::string Pack(const std::string& in) = 0;
	virtual std::string UnPack(const std::string& in,int& len) = 0;

};

#endif //_DATAPACKAGER_H_




