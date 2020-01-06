#ifndef _DATAPACKAGER_H_
#define _DATAPACKAGER_H_

#include <vector>
#include <string>

class DataPackager {
	short lenFormat;
	short dataFormat;
	short dataType;
	short dataLength;

public:
	virtual DataPackager& Set(const std::vector<short>& v) =0;
	virtual std::string Pack(const std::string& in) = 0;
	virtual std::pair<std::string,int> UnPack(const std::string& in) = 0;

};

#endif //_DATAPACKAGER_H_




