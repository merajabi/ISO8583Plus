#ifndef _DATAFORMAT_H_
#define _DATAFORMAT_H_

#define S1(x) #x
#define S2(x) S1(x)
#define LOCATION std::string("::") + __func__ + "/" + __FILE__ + ":" S2(__LINE__)
#define NAME(x) std::string(typeid(x).name())

#include <map>
#include <vector>
#include <string>
#include <sstream>

namespace  DataPackager {
class DataFormat {

	protected:
	std::map<short,std::vector<short>> format;
	std::map<std::string,std::map<short,char>> fields;

	public:
	enum Format {
		BIN,
		BCD,
		XBCD,
		ASC,
	};

	enum Type {
		FIX,
		VAR,
	};

	DataFormat(){
	}


	virtual void InitFields () {
		std::cout<< "DataFormat::InitFields" << std::endl;

	};

	virtual void InitFormats () {
		std::cout<< "DataFormat::InitFormats" << std::endl;

	};

	std::vector<short> GetFieldFormat(short fieldNumber) {
		std::cout<< "DataFormat::GetFieldFormat 1: "<< fieldNumber << std::endl;
		std::map<short,std::vector<short>>::iterator it = format.find(fieldNumber);

		if ( it != format.end() ) {
			std::cout<< "DataFormat::GetFieldFormat 2" << std::endl;
			return it->second;
		}else{
			std::stringstream err;
			err << NAME(this) << LOCATION << ", No such field: " << fieldNumber ;
			throw std::logic_error(err.str());
		}
	}

	std::map<short,char> GetFields(const std::string& mit) {
		std::cout<< "DataFormat::GetFields 1: "<< mit << std::endl;
		std::map<std::string,std::map<short,char>>::iterator it = fields.find(mit);

		if ( it != fields.end() ) {
			std::cout<< "DataFormat::GetFields 2" << std::endl;
			return it->second;
		}else{
			it = fields.find(mit.substr(0,4));
			if ( it != fields.end() ) {
				return it->second;
			} else {
				std::stringstream err;
				err << NAME(this) << LOCATION << ", No such MIT & Process code: " << mit ;
				throw std::logic_error(err.str());
			}
		}
	}
};
} // DataPackager
#endif // _DATAFORMAT_H_

