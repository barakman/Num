#ifndef RATIONAL_NUM_H
#define RATIONAL_NUM_H


#include "NaturalNum.h"


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// CLASS NAME:  RationalNum                                             //
//                                                                      //
// DESCRIPTION: Stores a rational number of any conceivable size.       //
//              Supports any arithmetic operation provided by C++.      //
//              Achieves complete accuracy (unlike type double), by     //
//              maintaining the number as enumerator and denominator.   //
//                                                                      //
// REMARKS:     An exception is thrown when the result is either        //
//              infinite (INF constant) or undefined (NaN constant).    //
//                                                                      //
// AUTHOR:      Barakman (barakman@yahoo.com)                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


class RationalNum
{
public: //Constructors + Destructor
	RationalNum();
	virtual ~RationalNum();
	RationalNum(double fRationalNum);
	RationalNum(const NaturalNum& cNaturalNum);
	RationalNum(const RationalNum& cRationalNum);
	//---------------------------------------------------------------------------------------------
public: //Assignment Operators
	virtual const RationalNum& operator=(const RationalNum& cRationalNum);
	virtual const RationalNum& operator+=(const RationalNum& cRationalNum);
	virtual const RationalNum& operator-=(const RationalNum& cRationalNum);
	virtual const RationalNum& operator*=(const RationalNum& cRationalNum);
	virtual const RationalNum& operator/=(const RationalNum& cRationalNum);
	//---------------------------------------------------------------------------------------------
public: //Unary Operators
	virtual operator NaturalNum() const;
	virtual RationalNum operator+() const;
	virtual RationalNum operator-() const;
	virtual const RationalNum& operator++();
	virtual const RationalNum& operator--();
	virtual RationalNum operator++(int dummy);
	virtual RationalNum operator--(int dummy);
	//---------------------------------------------------------------------------------------------
public: //Binary Operators
	friend RationalNum operator+(const RationalNum& cRationalNum1,const RationalNum& cRationalNum2);
	friend RationalNum operator-(const RationalNum& cRationalNum1,const RationalNum& cRationalNum2);
	friend RationalNum operator*(const RationalNum& cRationalNum1,const RationalNum& cRationalNum2);
	friend RationalNum operator/(const RationalNum& cRationalNum1,const RationalNum& cRationalNum2);
	//---------------------------------------------------------------------------------------------
public: //Binary Comperators
	friend bool operator<(const RationalNum& cRationalNum1,const RationalNum& cRationalNum2);
	friend bool operator>(const RationalNum& cRationalNum1,const RationalNum& cRationalNum2);
	friend bool operator==(const RationalNum& cRationalNum1,const RationalNum& cRationalNum2);
	friend bool operator<=(const RationalNum& cRationalNum1,const RationalNum& cRationalNum2);
	friend bool operator>=(const RationalNum& cRationalNum1,const RationalNum& cRationalNum2);
	friend bool operator!=(const RationalNum& cRationalNum1,const RationalNum& cRationalNum2);
	//---------------------------------------------------------------------------------------------
public: //Interface Routines
	NaturalNum Enumerator() const;
	NaturalNum Denominator() const;
	RationalNum Power(unsigned int iExponent) const;
	RationalNum Root(unsigned int iExponent,unsigned int iAccuracy=4) const;
	void ToString(char aString[],unsigned int iBase,unsigned int iPrecision) const;
	friend RationalNum StringToRationalNum(const char aString[],unsigned int iBase);
	//---------------------------------------------------------------------------------------------
protected: //Internal Routines
	void RemoveRedundantFactors();
	//---------------------------------------------------------------------------------------------
protected: //Object Attributes
	bool       m_bSign;
	NaturalNum m_cEnumerator;
	NaturalNum m_cDenominator;
	//---------------------------------------------------------------------------------------------
};


#endif
