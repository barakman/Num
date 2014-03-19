#ifndef NATURAL_NUM_H
#define NATURAL_NUM_H


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// CLASS NAME:  NaturalNum                                              //
//                                                                      //
// DESCRIPTION: Stores a natural number of any conceivable size.        //
//              Supports any arithmetic operation provided by C++.      //
//              Although the number is maintained as little-endian,     //
//              the code is compatible with both types of processors.   //
//                                                                      //
// REMARKS:     An exception is thrown when the result is either        //
//              negative (X-Y and X<Y) or infinite (X/Y and Y==0).      //
//                                                                      //
// AUTHOR:      Barakman (barakman@yahoo.com)                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


class NaturalNum
{
public: //Constructors + Destructor
	NaturalNum();
	virtual ~NaturalNum();
	NaturalNum(unsigned int iNaturalNum);
	NaturalNum(const NaturalNum& cNaturalNum);
	//---------------------------------------------------------------------------------------------
public: //Assignment Operators
	virtual const NaturalNum& operator=(const NaturalNum& cNaturalNum);
	virtual const NaturalNum& operator+=(const NaturalNum& cNaturalNum);
	virtual const NaturalNum& operator-=(const NaturalNum& cNaturalNum);
	virtual const NaturalNum& operator*=(const NaturalNum& cNaturalNum);
	virtual const NaturalNum& operator/=(const NaturalNum& cNaturalNum);
	virtual const NaturalNum& operator%=(const NaturalNum& cNaturalNum);
	virtual const NaturalNum& operator|=(const NaturalNum& cNaturalNum);
	virtual const NaturalNum& operator&=(const NaturalNum& cNaturalNum);
	virtual const NaturalNum& operator^=(const NaturalNum& cNaturalNum);
	virtual const NaturalNum& operator<<=(unsigned int iShift);
	virtual const NaturalNum& operator>>=(unsigned int iShift);
	//---------------------------------------------------------------------------------------------
public: //Unary Operators
	virtual NaturalNum operator~() const;
	virtual const NaturalNum& operator++();
	virtual const NaturalNum& operator--();
	virtual NaturalNum operator++(int dummy);
	virtual NaturalNum operator--(int dummy);
	//---------------------------------------------------------------------------------------------
public: //Binary Operators
	friend NaturalNum operator+(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2);
	friend NaturalNum operator-(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2);
	friend NaturalNum operator*(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2);
	friend NaturalNum operator/(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2);
	friend NaturalNum operator%(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2);
	friend NaturalNum operator|(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2);
	friend NaturalNum operator&(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2);
	friend NaturalNum operator^(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2);
	virtual NaturalNum operator<<(unsigned int iShift) const;
	virtual NaturalNum operator>>(unsigned int iShift) const;
	//---------------------------------------------------------------------------------------------
public: //Binary Comperators
	friend bool operator<(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2);
	friend bool operator>(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2);
	friend bool operator==(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2);
	friend bool operator<=(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2);
	friend bool operator>=(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2);
	friend bool operator!=(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2);
	//---------------------------------------------------------------------------------------------
public: //Interface Routines
	unsigned int BitCount() const;
	void ToBuffer(unsigned char aBuffer[]) const;
	void ToString(char aString[],unsigned int iBase) const;
	friend NaturalNum StringToNaturalNum(const char aString[],unsigned int iBase);
	//---------------------------------------------------------------------------------------------
protected: //Internal Routines
	void Allocate(unsigned int iBytes);
	void DeallocateAll();
	void RemoveRedundantZeros();
	//---------------------------------------------------------------------------------------------
protected: //Object Attributes
	unsigned int   m_iLength;
	unsigned char* m_aValues;
	//---------------------------------------------------------------------------------------------
};


#endif
