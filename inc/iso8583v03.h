#ifndef _ISO8583V03_H_
#define _ISO8583V03_H_

#include "dataformat.h"

class ISO8583v03 : public DataFormat {
	public:

	void InitFields () override {
		fields["2100"] = {{2,'M'},{3,'C'},{4,'O'}} ;
		fields["2110"] = {{2,'M'},{3,'C'},{4,'O'}} ;
	};

	void InitFormats () override {
		format[-3]	= { BIN,	BIN,	FIX,	40	};		//	" TPDU
		format[-2]	= { BCD,	BCD,	FIX,	4	};		//	" Message Type Identifier
		format[-1]	= { BIN,	BIN,	FIX,	128	};		//	" BITMAP

	//					LEN		DATA	TYPE	LEN		Comment
		format[2]	= {	BCD,	BCD,	VAR,	19};			//	"2	Primary Account Number"];
	};

};

#endif // _ISO8583V03_H_

