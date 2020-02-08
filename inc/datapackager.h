#ifndef _DATAPACKAGER_H_
#define _DATAPACKAGER_H_

#include <vector>
#include <string>
namespace  DataPackager {
class DataPackager {

protected:
	short lenFormat;
	short dataFormat;
	short dataType;
	short dataLength;

public:
	virtual const DataPackager& Set(const std::vector<short>& v) =0;
	virtual std::string Pack(const std::string& in) const = 0;
	virtual std::pair<std::string,int> UnPack(const std::string& in) const = 0;

};
} //DataPackager
#endif //_DATAPACKAGER_H_




