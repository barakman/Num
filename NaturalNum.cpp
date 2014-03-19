#include "NaturalNum.h"


///////////////////////////////////////
// Constructors + Destructor (below) //


NaturalNum::NaturalNum()
{
	Allocate(0);
}


NaturalNum::~NaturalNum()
{
	DeallocateAll();
}


NaturalNum::NaturalNum(unsigned int iNaturalNum)
{
	Allocate(sizeof(iNaturalNum));

	for (unsigned int i=0; i<m_iLength; i++)
		m_aValues[i]=iNaturalNum>>(i*8);

	RemoveRedundantZeros();
}


NaturalNum::NaturalNum(const NaturalNum& cNaturalNum)
{
	Allocate(0);
	*this=cNaturalNum;
}


// Constructors + Destructor (above) //
///////////////////////////////////////


//////////////////////////////////
// Assignment Operators (below) //


const NaturalNum& NaturalNum::operator=(const NaturalNum& cNaturalNum)
{
	if (this==&cNaturalNum)
		return *this;

	DeallocateAll();
	Allocate(cNaturalNum.m_iLength);

	for (unsigned int i=0; i<m_iLength; i++)
		m_aValues[i]=cNaturalNum.m_aValues[i];

	return *this;
}


const NaturalNum& NaturalNum::operator+=(const NaturalNum& cNaturalNum)
{
	return *this=*this+cNaturalNum;
}


const NaturalNum& NaturalNum::operator-=(const NaturalNum& cNaturalNum)
{
	return *this=*this-cNaturalNum;
}


const NaturalNum& NaturalNum::operator*=(const NaturalNum& cNaturalNum)
{
	return *this=*this*cNaturalNum;
}


const NaturalNum& NaturalNum::operator/=(const NaturalNum& cNaturalNum)
{
	return *this=*this/cNaturalNum;
}


const NaturalNum& NaturalNum::operator%=(const NaturalNum& cNaturalNum)
{
	return *this=*this%cNaturalNum;
}


const NaturalNum& NaturalNum::operator|=(const NaturalNum& cNaturalNum)
{
	return *this=*this|cNaturalNum;
}


const NaturalNum& NaturalNum::operator&=(const NaturalNum& cNaturalNum)
{
	return *this=*this&cNaturalNum;
}


const NaturalNum& NaturalNum::operator^=(const NaturalNum& cNaturalNum)
{
	return *this=*this^cNaturalNum;
}


const NaturalNum& NaturalNum::operator<<=(unsigned int iShift)
{
	return *this=*this<<iShift;
}


const NaturalNum& NaturalNum::operator>>=(unsigned int iShift)
{
	return *this=*this>>iShift;
}


// Assignment Operators (above) //
//////////////////////////////////


/////////////////////////////
// Unary Operators (below) //


NaturalNum NaturalNum::operator~() const
{
	NaturalNum cRes;
	cRes.Allocate(m_iLength);

	for (unsigned int i=0; i<m_iLength; i++)
		cRes.m_aValues[i]=~m_aValues[i];

	return cRes;
}


const NaturalNum& NaturalNum::operator++()
{
	*this+=1;
	return *this;
}


const NaturalNum& NaturalNum::operator--()
{
	*this-=1;
	return *this;
}


NaturalNum NaturalNum::operator++(int dummy)
{
	NaturalNum cRes=*this;
	*this+=1;
	return cRes;
}


NaturalNum NaturalNum::operator--(int dummy)
{
	NaturalNum cRes=*this;
	*this-=1;
	return cRes;
}


// Unary Operators (above) //
/////////////////////////////


//////////////////////////////
// Binary Operators (below) //


NaturalNum operator+(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2)
{
	if (cNaturalNum2.m_iLength<cNaturalNum1.m_iLength)
		return cNaturalNum2+cNaturalNum1;

	NaturalNum cRes;
	cRes.Allocate(cNaturalNum2.m_iLength+1);

	unsigned int   i;
	unsigned short iSum;
	unsigned char  iRem=0;

	for (i=0; i<cNaturalNum1.m_iLength; i++)
	{
		iSum=iRem+cNaturalNum1.m_aValues[i]+cNaturalNum2.m_aValues[i];
		cRes.m_aValues[i]=iSum&0xFF;
		iRem=iSum>>8;
	}
	for (; i<cNaturalNum2.m_iLength; i++)
	{
		iSum=iRem+cNaturalNum2.m_aValues[i];
		cRes.m_aValues[i]=iSum&0xFF;
		iRem=iSum>>8;
	}
	cRes.m_aValues[i]=iRem;

	cRes.RemoveRedundantZeros();
	return cRes;
}


NaturalNum operator-(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2)
{
	if (cNaturalNum2>cNaturalNum1)
		throw "Negative Result";

	NaturalNum cRes;
	cRes.Allocate(cNaturalNum1.m_iLength);

	unsigned int i;
	signed short iDif;
	signed char  iRem=0;

	for (i=0; i<cNaturalNum2.m_iLength; i++)
	{
		iDif=iRem+cNaturalNum1.m_aValues[i]-cNaturalNum2.m_aValues[i];
		cRes.m_aValues[i]=iDif&0xFF;
		iRem=iDif>>8;
	}
	for (; i<cNaturalNum1.m_iLength; i++)
	{
		iDif=iRem+cNaturalNum1.m_aValues[i];
		cRes.m_aValues[i]=iDif&0xFF;
		iRem=iDif>>8;
	}

	cRes.RemoveRedundantZeros();
	return cRes;
}


NaturalNum operator*(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2)
{
	NaturalNum cRes=0;

	for (unsigned int i=0; i<cNaturalNum1.m_iLength; i++)
		for (unsigned int j=0; j<cNaturalNum2.m_iLength; j++)
			cRes+=(NaturalNum)(cNaturalNum1.m_aValues[i]*cNaturalNum2.m_aValues[j])<<((i+j)*8);

	return cRes;
}


NaturalNum operator/(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2)
{
	if (cNaturalNum2==0)
		throw "Infinite Result";

	NaturalNum cRes=0;

	NaturalNum cTmp1=cNaturalNum1;
	unsigned int iTmp1Len=cTmp1.BitCount();
	unsigned int iNaturalNum2Len=cNaturalNum2.BitCount();

	while (iTmp1Len>iNaturalNum2Len)
	{
		cRes+=(NaturalNum)1<<(iTmp1Len-iNaturalNum2Len-1);
		cTmp1-=cNaturalNum2<<(iTmp1Len-iNaturalNum2Len-1);
		iTmp1Len=cTmp1.BitCount();
	}

	if (cTmp1>=cNaturalNum2)
		return cRes+1;

	return cRes;
}


NaturalNum operator%(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2)
{
	return cNaturalNum1-cNaturalNum1/cNaturalNum2*cNaturalNum2;
}


NaturalNum operator|(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2)
{
	if (cNaturalNum2.m_iLength<cNaturalNum1.m_iLength)
		return cNaturalNum2|cNaturalNum1;

	NaturalNum cRes;
	cRes.Allocate(cNaturalNum2.m_iLength);

	unsigned int i;
	for (i=0; i<cNaturalNum1.m_iLength; i++)
		cRes.m_aValues[i]=cNaturalNum1.m_aValues[i]|cNaturalNum2.m_aValues[i];
	for (; i<cNaturalNum2.m_iLength; i++)
		cRes.m_aValues[i]=0|cNaturalNum2.m_aValues[i];

	cRes.RemoveRedundantZeros();
	return cRes;
}


NaturalNum operator&(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2)
{
	if (cNaturalNum2.m_iLength<cNaturalNum1.m_iLength)
		return cNaturalNum2&cNaturalNum1;

	NaturalNum cRes;
	cRes.Allocate(cNaturalNum2.m_iLength);

	unsigned int i;
	for (i=0; i<cNaturalNum1.m_iLength; i++)
		cRes.m_aValues[i]=cNaturalNum1.m_aValues[i]&cNaturalNum2.m_aValues[i];
	for (; i<cNaturalNum2.m_iLength; i++)
		cRes.m_aValues[i]=0&cNaturalNum2.m_aValues[i];

	cRes.RemoveRedundantZeros();
	return cRes;
}


NaturalNum operator^(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2)
{
	if (cNaturalNum2.m_iLength<cNaturalNum1.m_iLength)
		return cNaturalNum2^cNaturalNum1;

	NaturalNum cRes;
	cRes.Allocate(cNaturalNum2.m_iLength);

	unsigned int i;
	for (i=0; i<cNaturalNum1.m_iLength; i++)
		cRes.m_aValues[i]=cNaturalNum1.m_aValues[i]^cNaturalNum2.m_aValues[i];
	for (; i<cNaturalNum2.m_iLength; i++)
		cRes.m_aValues[i]=0^cNaturalNum2.m_aValues[i];

	cRes.RemoveRedundantZeros();
	return cRes;
}


NaturalNum NaturalNum::operator<<(unsigned int iShift) const
{
	unsigned int iByteShift=iShift/8;
	unsigned int iBitsShift=iShift%8;

	if (m_iLength==0)
		return 0;

	NaturalNum cRes;
	cRes.Allocate(m_iLength+iByteShift+1);

	for (unsigned int n=0; n<iByteShift; n++)
		cRes.m_aValues[n]=0;

	unsigned int  i;
	unsigned char iRem=0;
	for (i=iByteShift; i<m_iLength+iByteShift; i++)
	{
		cRes.m_aValues[i]=(m_aValues[i-iByteShift]<<iBitsShift)|iRem;
		iRem=m_aValues[i-iByteShift]>>(8-iBitsShift);
	}
	cRes.m_aValues[i]=iRem;

	cRes.RemoveRedundantZeros();
	return cRes;
}


NaturalNum NaturalNum::operator>>(unsigned int iShift) const
{
	unsigned int iByteShift=iShift/8;
	unsigned int iBitsShift=iShift%8;

	if (m_iLength<=iByteShift)
		return 0;

	NaturalNum cRes;
	cRes.Allocate(m_iLength-iByteShift);

	unsigned int  i;
	unsigned char iRem;
	for (i=0; i<m_iLength-iByteShift-1; i++)
	{
		iRem=m_aValues[i+iByteShift+1]<<(8-iBitsShift);
		cRes.m_aValues[i]=(m_aValues[i+iByteShift]>>iBitsShift)|iRem;
	}
	iRem=m_aValues[i+iByteShift]>>iBitsShift;
	cRes.m_aValues[i]=iRem;

	cRes.RemoveRedundantZeros();
	return cRes;
}


// Binary Operators (above) //
//////////////////////////////


////////////////////////////////
// Binary Comperators (below) //


bool operator<(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2)
{
	if (cNaturalNum1.m_iLength!=cNaturalNum2.m_iLength)
		return cNaturalNum1.m_iLength<cNaturalNum2.m_iLength;

	for (unsigned int i=cNaturalNum1.m_iLength; i>0; i--)
		if (cNaturalNum1.m_aValues[i-1]!=cNaturalNum2.m_aValues[i-1])
			return cNaturalNum1.m_aValues[i-1]<cNaturalNum2.m_aValues[i-1];

	return false;
}


bool operator>(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2)
{
	if (cNaturalNum1.m_iLength!=cNaturalNum2.m_iLength)
		return cNaturalNum1.m_iLength>cNaturalNum2.m_iLength;

	for (unsigned int i=cNaturalNum1.m_iLength; i>0; i--)
		if (cNaturalNum1.m_aValues[i-1]!=cNaturalNum2.m_aValues[i-1])
			return cNaturalNum1.m_aValues[i-1]>cNaturalNum2.m_aValues[i-1];

	return false;
}


bool operator==(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2)
{
	if (cNaturalNum1.m_iLength!=cNaturalNum2.m_iLength)
		return false;

	for (unsigned int i=cNaturalNum1.m_iLength; i>0; i--)
		if (cNaturalNum1.m_aValues[i-1]!=cNaturalNum2.m_aValues[i-1])
			return false;

	return true;
}


bool operator<=(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2)
{
	return !(cNaturalNum1>cNaturalNum2);
}


bool operator>=(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2)
{
	return !(cNaturalNum1<cNaturalNum2);
}


bool operator!=(const NaturalNum& cNaturalNum1,const NaturalNum& cNaturalNum2)
{
	return !(cNaturalNum1==cNaturalNum2);
}


// Binary Comperators (above) //
////////////////////////////////


////////////////////////////////
// Interface Routines (below) //


unsigned int NaturalNum::BitCount() const
{
	if (m_iLength==0)
		return 0;

	unsigned int iBitCount=(m_iLength-1)*8;
	for (unsigned int i=1; i<=m_aValues[m_iLength-1]; i<<=1)
		iBitCount++;

	return iBitCount;
}


void NaturalNum::ToBuffer(unsigned char aBuffer[]) const
{
	for (unsigned int i=0; i<m_iLength; i++)
		aBuffer[i]=m_aValues[i];
}


void NaturalNum::ToString(char aString[],unsigned int iBase) const
{
	unsigned int iIndex=0;

	for (NaturalNum cTmp=*this; cTmp>0; cTmp/=iBase)
	{
		NaturalNum cDigit=cTmp%iBase;
		if (cDigit==0)
			aString[iIndex]='0';
		else if (cDigit<10)
			aString[iIndex]='0'+cDigit.m_aValues[0];
		else
			aString[iIndex]='A'+cDigit.m_aValues[0]-10;
		iIndex++;
	}

	for (unsigned int i=0; i<iIndex/2; i++)
	{
		char iDigit=aString[i];
		aString[i]=aString[iIndex-1-i];
		aString[iIndex-1-i]=iDigit;
	}

	if (iIndex==0)
		aString[iIndex++]='0';

	aString[iIndex]=0;
}


NaturalNum StringToNaturalNum(const char aString[],unsigned int iBase)
{
	NaturalNum cRes=0;

	for (unsigned int i=0; aString[i]!=0; i++)
	{
		NaturalNum cDigit;
		if ('0'<=aString[i] && aString[i]<='9')
			cDigit=aString[i]-'0';
		else if ('A'<=aString[i] && aString[i]<='Z')
			cDigit=aString[i]-'A'+10;
		else if ('a'<=aString[i] && aString[i]<='z')
			cDigit=aString[i]-'a'+10;
		else
			break;
		cRes*=iBase;
		cRes+=cDigit;
	}

	return cRes;
}


// Interface Routines (above) //
////////////////////////////////


///////////////////////////////
// Internal Routines (below) //


void NaturalNum::Allocate(unsigned int iBytes)
{
	m_iLength=iBytes;
	if (m_iLength>0)
		m_aValues=new unsigned char[m_iLength];
}


void NaturalNum::DeallocateAll()
{
	if (m_iLength>0)
		delete[] m_aValues;
	m_iLength=0;
}


void NaturalNum::RemoveRedundantZeros()
{
	while (m_iLength>0 && m_aValues[m_iLength-1]==0)
		if (--m_iLength==0)
			delete[] m_aValues;
}


// Internal Routines (above) //
///////////////////////////////
