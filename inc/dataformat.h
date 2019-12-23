#ifndef _DATAFORMAT_H_
#define _DATAFORMAT_H_

#define S1(x) #x
#define S2(x) S1(x)
#define LOCATION std::string("::") + __func__ + "/" + __FILE__ + ":" S2(__LINE__)
#define NAME(x) std::string(typeid(x).name())

class DataFormat {
	enum DataFormat {
		BIN,
		BCD,
		XBCD,
		ASC,
	};

	enum PackagingType {
		FIX,
		VAR,
	};
}
	std::map<short,std::vector<short>> format;
	std::map<std::string,std::map<short,char>> fields;

	public:
	DataFormat(){
		InitFormats();
		InitFields();
	}


	virtual void InitFields () = 0;

	virtual void InitFormats () = 0;

	std::vector<uint8_t> GetFieldFormat(short fieldNumber) {
		std::map<short,std::vector<short>>::iterator it = format.find(fieldNumber);
		if ( it != format.end() ) {
			return it->second;
		}else{
			std::stringstream err;
			err << NAME(this) << LOCATION << ", No such field: " << fieldNumber ;
			throw std::logic_error(err.str());
		}
	}

	std::map<short,char> GetFields(const std::string& mit) {
		std::map<std::string,std::map<short,char>>::iterator it = fields.find(mit);
		if ( it != fields.end() ) {
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

#endif // _DATAFORMAT_H_

