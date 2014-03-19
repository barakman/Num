#include "RationalNum.h"


///////////////////////////////////////
// Constructors + Destructor (below) //


RationalNum::RationalNum()
{
	m_bSign=false;
	m_cEnumerator=0;
	m_cDenominator=1;
}


RationalNum::~RationalNum()
{
}


RationalNum::RationalNum(double fRationalNum)
{
	if (fRationalNum==fRationalNum+1)
		throw "Infinite Value";
	if (fRationalNum!=fRationalNum)
		throw "Undefined Value";

	m_bSign=false;
	m_cEnumerator=0;
	m_cDenominator=1;

	if (fRationalNum<0)
	{
		m_bSign=true;
		fRationalNum=-fRationalNum;
	}

	while (fRationalNum>0)
	{
		unsigned int iInteger=(unsigned int)fRationalNum;
		fRationalNum-=iInteger;
		m_cEnumerator+=iInteger;
		fRationalNum*=2;
		m_cEnumerator*=2;
		m_cDenominator*=2;
	}

	RemoveRedundantFactors();
}


RationalNum::RationalNum(const NaturalNum& cNaturalNum)
{
	m_bSign=false;
	m_cEnumerator=cNaturalNum;
	m_cDenominator=1;
}


RationalNum::RationalNum(const RationalNum& cRationalNum)
{
	*this=cRationalNum;
}


// Constructors + Destructor (above) //
///////////////////////////////////////


//////////////////////////////////
// Assignment Operators (below) //


const RationalNum& RationalNum::operator=(const RationalNum& cRationalNum)
{
	m_bSign=cRationalNum.m_bSign;
	m_cEnumerator=cRationalNum.m_cEnumerator;
	m_cDenominator=cRationalNum.m_cDenominator;

	return *this;
}


const RationalNum& RationalNum::operator+=(const RationalNum& cRationalNum)
{
	return *this=*this+cRationalNum;
}


const RationalNum& RationalNum::operator-=(const RationalNum& cRationalNum)
{
	return *this=*this-cRationalNum;
}


const RationalNum& RationalNum::operator*=(const RationalNum& cRationalNum)
{
	return *this=*this*cRationalNum;
}


const RationalNum& RationalNum::operator/=(const RationalNum& cRationalNum)
{
	return *this=*this/cRationalNum;
}


// Assignment Operators (above) //
//////////////////////////////////


/////////////////////////////
// Unary Operators (below) //


RationalNum::operator NaturalNum() const
{
	return m_cEnumerator/m_cDenominator;
}


RationalNum RationalNum::operator+() const
{
	return 0+*this;
}


RationalNum RationalNum::operator-() const
{
	return 0-*this;
}


const RationalNum& RationalNum::operator++()
{
	*this+=1;
	return *this;
}


const RationalNum& RationalNum::operator--()
{
	*this-=1;
	return *this;
}


RationalNum RationalNum::operator++(int dummy)
{
	RationalNum cRes=*this;
	*this+=1;
	return cRes;
}


RationalNum RationalNum::operator--(int dummy)
{
	RationalNum cRes=*this;
	*this-=1;
	return cRes;
}


// Unary Operators (above) //
/////////////////////////////


//////////////////////////////
// Binary Operators (below) //


RationalNum operator+(const RationalNum& cRationalNum1,const RationalNum& cRationalNum2)
{
	RationalNum cRes;

	NaturalNum cEnumerator1=cRationalNum1.m_cEnumerator*cRationalNum2.m_cDenominator;
	NaturalNum cEnumerator2=cRationalNum2.m_cEnumerator*cRationalNum1.m_cDenominator;

	if (cRationalNum1.m_bSign==cRationalNum2.m_bSign)
	{
		cRes.m_bSign=cRationalNum1.m_bSign;
		cRes.m_cEnumerator=cEnumerator1+cEnumerator2;
	}
	else if (cEnumerator1>cEnumerator2)
	{
		cRes.m_bSign=cRationalNum1.m_bSign;
		cRes.m_cEnumerator=cEnumerator1-cEnumerator2;
	}
	else
	{
		cRes.m_bSign=cRationalNum2.m_bSign;
		cRes.m_cEnumerator=cEnumerator2-cEnumerator1;
	}
	cRes.m_cDenominator=cRationalNum1.m_cDenominator*cRationalNum2.m_cDenominator;

	cRes.RemoveRedundantFactors();
	return cRes;
}


RationalNum operator-(const RationalNum& cRationalNum1,const RationalNum& cRationalNum2)
{
	RationalNum cOpposite2;

	cOpposite2.m_bSign=!cRationalNum2.m_bSign;
	cOpposite2.m_cEnumerator=cRationalNum2.m_cEnumerator;
	cOpposite2.m_cDenominator=cRationalNum2.m_cDenominator;

	return cRationalNum1+cOpposite2;
}


RationalNum operator*(const RationalNum& cRationalNum1,const RationalNum& cRationalNum2)
{
	RationalNum cRes;

	cRes.m_bSign=cRationalNum1.m_bSign^cRationalNum2.m_bSign;
	cRes.m_cEnumerator=cRationalNum1.m_cEnumerator*cRationalNum2.m_cEnumerator;
	cRes.m_cDenominator=cRationalNum1.m_cDenominator*cRationalNum2.m_cDenominator;

	cRes.RemoveRedundantFactors();
	return cRes;
}


RationalNum operator/(const RationalNum& cRationalNum1,const RationalNum& cRationalNum2)
{
	RationalNum cReciprocal2;

	cReciprocal2.m_bSign=cRationalNum2.m_bSign;
	cReciprocal2.m_cEnumerator=cRationalNum2.m_cDenominator;
	cReciprocal2.m_cDenominator=cRationalNum2.m_cEnumerator;

	return cRationalNum1*cReciprocal2;
}


// Binary Operators (above) //
//////////////////////////////


////////////////////////////////
// Binary Comperators (below) //


bool operator<(const RationalNum& cRationalNum1,const RationalNum& cRationalNum2)
{
	if (cRationalNum1.m_bSign==false && cRationalNum2.m_bSign==false)
		return cRationalNum1.m_cEnumerator*cRationalNum2.m_cDenominator<cRationalNum2.m_cEnumerator*cRationalNum1.m_cDenominator;

	if (cRationalNum1.m_bSign==true && cRationalNum2.m_bSign==true)
		return cRationalNum1.m_cEnumerator*cRationalNum2.m_cDenominator>cRationalNum2.m_cEnumerator*cRationalNum1.m_cDenominator;

	return cRationalNum1.m_bSign;
}


bool operator>(const RationalNum& cRationalNum1,const RationalNum& cRationalNum2)
{
	if (cRationalNum1.m_bSign==false && cRationalNum2.m_bSign==false)
		return cRationalNum1.m_cEnumerator*cRationalNum2.m_cDenominator>cRationalNum2.m_cEnumerator*cRationalNum1.m_cDenominator;

	if (cRationalNum1.m_bSign==true && cRationalNum2.m_bSign==true)
		return cRationalNum1.m_cEnumerator*cRationalNum2.m_cDenominator<cRationalNum2.m_cEnumerator*cRationalNum1.m_cDenominator;

	return cRationalNum2.m_bSign;
}


bool operator==(const RationalNum& cRationalNum1,const RationalNum& cRationalNum2)
{
	return cRationalNum1.m_bSign==cRationalNum2.m_bSign && cRationalNum1.m_cEnumerator==cRationalNum2.m_cEnumerator && cRationalNum1.m_cDenominator==cRationalNum2.m_cDenominator;
}


bool operator<=(const RationalNum& cRationalNum1,const RationalNum& cRationalNum2)
{
	return !(cRationalNum1>cRationalNum2);
}


bool operator>=(const RationalNum& cRationalNum1,const RationalNum& cRationalNum2)
{
	return !(cRationalNum1<cRationalNum2);
}


bool operator!=(const RationalNum& cRationalNum1,const RationalNum& cRationalNum2)
{
	return !(cRationalNum1==cRationalNum2);
}


// Binary Comperators (above) //
////////////////////////////////


////////////////////////////////
// Interface Routines (below) //


NaturalNum RationalNum::Enumerator() const
{
	return m_cEnumerator;
}


NaturalNum RationalNum::Denominator() const
{
	return m_cDenominator;
}


RationalNum RationalNum::Power(unsigned int iExponent) const
{
	RationalNum cRes;

	cRes.m_bSign=false;
	cRes.m_cEnumerator=1;
	cRes.m_cDenominator=1;

	for (unsigned int i=0; i<iExponent; i++)
	{
		cRes.m_bSign^=m_bSign;
		cRes.m_cEnumerator*=m_cEnumerator;
		cRes.m_cDenominator*=m_cDenominator;
	}

	return cRes;
}


RationalNum RationalNum::Root(unsigned int iExponent,unsigned int iAccuracy) const
{
	if (iExponent==0)
		throw "Infinite Result";
	if (m_bSign==true && (iExponent%2)==0)
		throw "Undefined Result";

	if (m_cEnumerator==0)
		return 0;

	RationalNum cRes;

	cRes.m_bSign=m_bSign;
	cRes.m_cEnumerator=(NaturalNum)1<<(m_cEnumerator.BitCount()/m_cDenominator.BitCount()/iExponent);
	cRes.m_cDenominator=(NaturalNum)1<<(m_cDenominator.BitCount()/m_cEnumerator.BitCount()/iExponent);

	for (unsigned int i=0; i<iAccuracy; i++)
	{
		RationalNum cTmp=cRes.Power(iExponent-1);
		cRes-=(cRes*cTmp-*this)/(iExponent*cTmp);
	}

	return cRes;
}


void RationalNum::ToString(char aString[],unsigned int iBase,unsigned int iPrecision) const
{
	unsigned int iIndex=0;
	if (m_bSign==true)
	{
		aString[0]='-';
		iIndex=1;
	}

	NaturalNum cInteger=m_cEnumerator/m_cDenominator;
	cInteger.ToString(aString+iIndex,iBase);
	if (iPrecision==0)
		return;

	while (aString[iIndex]!=0)
		iIndex++;
	aString[iIndex++]='.';

	NaturalNum cFraction=m_cEnumerator%m_cDenominator;
	for (unsigned int i=0; i<iPrecision; i++)
	{
		cFraction*=iBase;
		if (cFraction<m_cDenominator)
			aString[iIndex++]='0';
	}

	cFraction/=m_cDenominator;
	if (cFraction>0)
		cFraction.ToString(aString+iIndex,iBase);
	else
		aString[iIndex]=0;
}


RationalNum StringToRationalNum(const char aString[],unsigned int iBase)
{
	signed int   iSign=+1;
	unsigned int iIndex=0;
	if (aString[0]=='-')
	{
		iSign=-1;
		iIndex=1;
	}

	NaturalNum cInteger=StringToNaturalNum(aString+iIndex,iBase);
	while (aString[iIndex]!='.' && aString[iIndex]!=0)
		iIndex++;
	if (aString[iIndex++]==0)
		return iSign*(RationalNum)cInteger;

	NaturalNum cFractionEnumerator=StringToNaturalNum(aString+iIndex,iBase);
	NaturalNum cFractionDenominator=1;
	for (unsigned int i=iIndex; aString[i]!=0; i++)
		cFractionDenominator*=iBase;
	return iSign*((RationalNum)cInteger+(RationalNum)cFractionEnumerator/(RationalNum)cFractionDenominator);
}


// Interface Routines (above) //
////////////////////////////////


///////////////////////////////
// Internal Routines (below) //


void RationalNum::RemoveRedundantFactors()
{
	if (m_cEnumerator==0)
	{
		m_bSign=false;
		m_cDenominator=1;
		return;
	}

	NaturalNum cHi,cLo,cRem;

	if (m_cEnumerator>m_cDenominator)
	{
		cHi=m_cEnumerator;
		cLo=m_cDenominator;
	}
	else
	{
		cHi=m_cDenominator;
		cLo=m_cEnumerator;
	}

	while (true)
	{
		cRem=cHi%cLo;
		if (cRem==0)
			break;
		cHi=cLo;
		cLo=cRem;
	}

	m_cEnumerator/=cLo;
	m_cDenominator/=cLo;
}


// Internal Routines (above) //
///////////////////////////////
