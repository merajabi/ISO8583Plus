#ifndef _LV_H_
#define _LV_H_

#include "datapackager.h"

class LV : public DataPackager {

public:
	DataPackager& Set(const std::vector<short>& v){
		short lenFormat = v[0];
		short dataFormat = v[1];
		short dataType = v[2];
		short dataLength = v[3];

		if (lenFormat != DataFormat::BIN && 
			lenFormat != DataFormat::BCD && 
			lenFormat != DataFormat::ASC ){
				std::stringstream err;
				err << NAME(this) << LOCATION << ", Invalid input len format: " << lenFormat ;
				throw std::logic_error(err.str());
		}

		if( dataFormat != DataFormat::BIN && 
			dataFormat != DataFormat::BCD && 
			dataFormat != DataFormat::XBCD && 
			dataFormat != DataFormat::ASC ){
				std::stringstream err;
				err << NAME(this) << LOCATION << ", Invalid input data format: " << dataFormat ;
				throw std::logic_error(err.str());
		}

		if( dataType != DataFormat::FIX &&
			dataType != DataFormat::VAR ){
				std::stringstream err;
				err << NAME(this) << LOCATION << ", Invalid input data type: " << dataType ;
				throw std::logic_error(err.str());
		}

		if( datalength < 0 ){
				std::stringstream err;
				err << NAME(this) << LOCATION << ", Invalid input data length: " << datalength ;
				throw std::logic_error(err.str());
		}
		else if(dataFormat == DataFormat::BIN && dataLength%2 != 0){
				std::stringstream err;
				err << NAME(this) << LOCATION << ", BIN input len must be even:" << datalength ;
				throw std::logic_error(err.str());
		}		

		this->lenFormat = lenFormat;
		this->dataFormat = dataFormat;
		this->dataType = dataType;
		this->dataLength = dataLength;

		return *this;
	}

	std::string Pack(const std::string& in){
		std::string out;

		if( dataType == DataFormat::FIX){
			if( dataFormat == DataFormat::BIN ){
				out = PackFixBIN(in);
			}
			else if( dataFormat == DataFormat::BCD ) {
				out = PackFixBCD(in);
			}
			else if( dataFormat == DataFormat::XBCD ) {
				out = PackFixXBCD(in);
			}
			else if( dataFormat == DataFormat::ASC) {
				out = PackFixASC(in);
			}
			else{
				std::stringstream err;
				err << NAME(this) << LOCATION << ", Invalid input data Format:" << dataFormat ;
				throw std::logic_error(err.str());
			}
		}
		else if ( dataType == DataFormat::VAR ){
			if( dataFormat == DataFormat::BIN ){
				out = PackVarBIN(in);
			}
			else if( dataFormat == DataFormat::BCD ) {
				out = PackVarBCD(in);
			}
			else if( dataFormat == DataFormat::XBCD) {
				out = PackVarXBCD(in);
			}
			else if( dataFormat == DataFormat::ASC ) {
				out = PackVarASC(in);
			}
			else{
				std::stringstream err;
				err << NAME(this) << LOCATION << ", Invalid input data Format:" << dataFormat ;
				throw std::logic_error(err.str());
			}
		}
		else{
			std::stringstream err;
			err << NAME(this) << LOCATION << ", Invalid input data Type:" << dataType ;
			throw std::logic_error(err.str());
		}

		return out;
	}

	std::pair<std::string,int> UnPack(const std::string& in){
		std::pair<std::string,int> out;

		if( dataType == DataFormat::FIX){
			if( dataFormat == DataFormat::BIN){
				out = UnPackFixBIN(in);
			}
			else if( dataFormat == DataFormat::BCD) {
				out = UnPackFixBCD(in);
			}
			else if( dataFormat == DataFormat::XBCD) {
				out = UnPackFixXBCD(in);
			}
			else if( dataFormat == DataFormat::ASC) {
				out = UnPackFixASC(in);
			}
			else{
				std::stringstream err;
				err << NAME(this) << LOCATION << ", Invalid input data Format:" << dataFormat ;
				throw std::logic_error(err.str());
			}
		}
		else if ( dataType == DataFormat::VAR){

			if( dataFormat == DataFormat::BIN){
				out = UnPackVarBIN(in);
			}
			else if( dataFormat == DataFormat::BCD) {
				out = UnPackVarBCD(in);
			}
			else if( dataFormat == DataFormat::XBCD) {
				out = UnPackVarXBCD(in);
			}
			else if( dataFormat == DataFormat::ASC) {
				out = UnPackVarASC(in);
			}
			else{
				std::stringstream err;
				err << NAME(this) << LOCATION << ", Invalid input data Format:" << dataFormat ;
				throw std::logic_error(err.str());
			}
		}
		else{
			std::stringstream err;
			err << NAME(this) << LOCATION << ", Invalid input data Type:" << dataType ;
			throw std::logic_error(err.str());
		}

		return out;
	}

private:
	std::string PackLen (const std::string& len) {
		std::string out;

		if( lenFormat == DataFormat::BIN){
			out = HexString(PaddedFixedLenString(len,dataLength/8));
		}
		else if( lenFormat == DataFormat::BCD) {
			out = PaddedFixedLenString( len, toString(dataLength).size() + toString(dataLength).size()%2 );
		}
		else if( lenFormat == DataFormat::ASC) {
			out = HexString(PaddedFixedLenString( len, toString(dataLength).size() ));
		}
		else{
			std::stringstream err;
			err << NAME(this) << LOCATION << ",Invalid input len format:" << lenFormat ;
			throw std::logic_error(err.str());
		}

		return out;
	}

	std::pair<std::string,int> UnPackLen (const std::string& in) {
		int len;
		std::string out;

		if(lenFormat == DataFormat::BIN){
			//$out = HexString(in.substr(0,dataLength/8));
		}
		else if(lenFormat == DataFormat::BCD) {
			len = toString(dataLength).size() + toString(dataLength).size()%2;
			out = in.substr(0, len);
		}
		else if(lenFormat == DataFormat::ASC) {
			len = 2*toString(dataLength).size();
			out = HexToAscii( in.substr(0, len) );
		}
		else{
			std::stringstream err;
			err << NAME(this) << LOCATION << ",Invalid input len format:" << lenFormat ;
			throw std::logic_error(err.str());
		}

		return std::pair<std::string,int>(out,len);
	}

	std::string PackFixBIN(const std::string& in){
		if( 4*in.size() == dataLength ){ // in.size()/2==dataLength/8
			out = in;
		}else{
			std::stringstream err;
			err << NAME(this) << LOCATION << ", FIX sized BIN input len must be 4 times of Filter len:" << in.size() ;
			throw std::logic_error(err.str());
		}
	}

	std::pair<std::string,int> UnPackFixBIN(const std::string& in){
		std::string out = in.substr(0,dataLength/4);
		int len = dataLength/4;
		return std::pair<std::string,int>(out,len);
	}

	std::string PackFixBCD(const std::string& in){
		if( in.size() <= dataLength ){
			out = PaddedFixedLenString(in,dataLength+dataLength%2, $self->{'PadCharBCD'}, $self->{'PadAlignBCD'});
		}else{
			std::stringstream err;
			err << NAME(this) << LOCATION << ", FIX sized BCD input len must be less than or equal to Filter len:" << in.size() ;
			throw std::logic_error(err.str());
		}
	}

	std::pair<std::string,int> UnPackFixBCD(const std::string& in){
		std::string out = in.substr(0,dataLength+dataLength%2);
		if($self->{'PadAlignBCD'} == "LEFT"){
			//#$out =~ s/^$self->{'PadCharBCD'}*//;
		}else{
			//#$out =~ s/$self->{'PadCharBCD'}*$//;
		}
		int len=dataLength+dataLength%2;

		return std::pair<std::string,int>(out,len);
	}

	std::string PackFixXBCD(const std::string& in){
		if( in.size() <= dataLength-1 ){
			out = std::string( (std::stol(in)>=0)?'C':'D' )+PaddedFixedLenString(in,dataLength+dataLength%2-1, $self->{'PadCharBCD'}, $self->{'PadAlignBCD'});
		}else{
			std::stringstream err;
			err << NAME(this) << LOCATION << ", FIX sized XBCD input len must be less than or equal to Filter len-1:" << in.size() ;
			throw std::logic_error(err.str());
		}
	}

	std::pair<std::string,int> UnPackFixXBCD(const std::string& in){
		std::string out = in.substr(1,dataLength-1);
		if($self->{'PadAlignBCD'} eq "LEFT"){
			//$out =~ s/^$self->{'PadCharBCD'}*//;
		}else{
			//$out =~ s/$self->{'PadCharBCD'}*$//;
		}
		int len=dataLength+dataLength%2;

		return std::pair<std::string,int>(out,len);
	}

	std::string PackFixASC(const std::string& in){
		if( in.size() <= dataLength ){
			out = HexString(PaddedFixedLenString(in,dataLength, $self->{'PadCharASC'}, $self->{'PadAlignASC'}));
		}else{
			std::stringstream err;
			err << NAME(this) << LOCATION << ", FIX sized ASC input len must be less than or equal to Filter len:" << in.size() ;
			throw std::logic_error(err.str());
		}
	}

	std::pair<std::string,int> UnPackFixASC(const std::string& in){
		std::string out = HexToAscii(in.substr(0,dataLength*2));
		if($self->{'PadAlignASC'} eq "LEFT"){
			$out =~ s/^$self->{'PadCharASC'}*//;
		}else{
			$out =~ s/$self->{'PadCharASC'}*$//;
		}
		int len=dataLength*2;

		return std::pair<std::string,int>(out,len);
	}

	std::string PackVarBIN(const std::string& in){
		if( in.size()%2 != 0){
			std::stringstream err;
			err << NAME(this) << LOCATION << ", VAR sized BIN input len must be even:" << in.size() ;
			throw std::logic_error(err.str());
		}

		if( 4*in.size() <= dataLength ){
			std::string lenStr = PackLen( in.size()/2 );
			out = lenStr+in;
		}else{
			std::stringstream err;
			err << NAME(this) << LOCATION << ", VAR sized BIN input len must be less than or equal to Filter len:" << in.size() ;
			throw std::logic_error(err.str());
		}
	}

	std::pair<std::string,int> UnPackVarBIN(const std::string& in){
		std::pair<std::string,int> lenUnPacked = UnPackLen(in);
		int lenData = std::stol(lenUnPacked.first);
		int lenLen  = lenUnPacked.second;

		lenData*=2;
		std::string out = in.substr(lenLen,lenData);
		int len = lenData + lenLen;

		return std::pair<std::string,int>(out,len);
	}

	std::string PackVarBCD(const std::string& in){
		if( in.size() <= dataLength ){
			std::string lenStr = PackLen( in.size() );
			out = lenStr. PaddedFixedLenString(in,in.size()+in.size()%2, $self->{'PadCharBCD'}, $self->{'PadAlignBCD'});
		}else{
			std::stringstream err;
			err << NAME(this) << LOCATION << ", VAR sized BCD input len must be less than or equal to Filter len:" << in.size() ;
			throw std::logic_error(err.str());
		}
	}

	std::pair<std::string,int> UnPackVarBCD(const std::string& in){
		std::pair<std::string,int> lenUnPacked = UnPackLen(in);
		int lenData = std::stol(lenUnPacked.first);
		int lenLen  = lenUnPacked.second;

		lenData+=lenData%2;
		std::string out = in.substr(lenLen,lenData);
		if($self->{'PadAlignBCD'} eq "LEFT"){
			//$out =~ s/^$self->{'PadCharBCD'}*//;
		}else{
			//$out =~ s/$self->{'PadCharBCD'}*$//;
		}

		int len = lenLen + lenData;

		return std::pair<std::string,int>(out,len);
	}

	std::string PackVarXBCD(const std::string& in){
		if( in.size() <= dataLength-1 ){
			std::string lenStr = PackLen( in.size()+1 );
			out = lenStr + std::string( (std::stol(in)>=0)?'C':'D' ) + PaddedFixedLenString( in,in.size()+in.size()%2-1 );
		}else{
			std::stringstream err;
			err << NAME(this) << LOCATION << ", VAR sized BCD input len must be less than or equal to Filter len:" << in.size() ;
			throw std::logic_error(err.str());
		}
	}

	std::pair<std::string,int> UnPackVarXBCD(const std::string& in){
			std::pair<std::string,int> lenUnPacked = UnPackLen(in);
			int lenData = std::stol(lenUnPacked.first);
			int lenLen  = lenUnPacked.second;

		return std::pair<std::string,int>(out,len);
	}

	std::string PackVarASC(const std::string& in){
		if( in.size() <= dataLength ){
			std::string lenStr = PackLen( in.size() );
			out = lenStr + HexString(in);
		}else{
			std::stringstream err;
			err << NAME(this) << LOCATION << ", VAR sized ASC input len must be less than or equal to Filter len:" << in.size() ;
			throw std::logic_error(err.str());
		}
	}

	std::pair<std::string,int> UnPackVarASC(const std::string& in){
		std::pair<std::string,int> lenUnPacked = UnPackLen(in);
		int lenData = std::stol(lenUnPacked.first);
		int lenLen  = lenUnPacked.second;

		std::string	out = HexToAscii(in.substr(lenLen,2*lenData));
		int len = lenLen + 2*lenData;

		return std::pair<std::string,int>(out,len);
	}

};

#endif //_LV_H_




