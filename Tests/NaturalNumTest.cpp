#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\NaturalNum.h"


void Test1();
void Test2();
void Test3();
void Test4();


int main()
{
	srand((unsigned int)time(NULL));

	Test1();
	printf("\n");

	Test2();
	printf("\n");

	Test3();
	printf("\n");

	Test4();
	printf("\n");

	return 0;
}


//Test the NaturalNum shift operators.
void Test1()
{
	const unsigned int SHIFT=40;

	char aResult[100];
	NaturalNum cNaturalNum;
	NaturalNum cNaturalNumShift;

	cNaturalNum=(NaturalNum)0xFF;
	for (unsigned int i=0; i<=SHIFT; i++)
	{
		cNaturalNumShift=cNaturalNum<<i;
		cNaturalNumShift.ToString(aResult,16);
		printf("%s\n",aResult);
	}

	cNaturalNum=(NaturalNum)0xFF<<SHIFT;
	for (unsigned int j=0; j<=SHIFT; j++)
	{
		cNaturalNumShift=cNaturalNum>>j;
		cNaturalNumShift.ToString(aResult,16);
		printf("%s\n",aResult);
	}
}


//Calculate a Pascal Triangle's row.
void Test2()
{
	const unsigned int ROW=40;

	char aItem[100];
	NaturalNum cItem;
	NaturalNum aFact[ROW+1];

	aFact[0]=1;
	for (unsigned int n=1; n<=ROW; n++)
		aFact[n]=aFact[n-1]*n;

	for (unsigned int i=0; i<=ROW; i++)
	{
		cItem=aFact[ROW]/(aFact[i]*aFact[ROW-i]);
		cItem.ToString(aItem,10);
		printf("%s\n",aItem);
	}
}


//Test the NaturalNum assignment operators.
void Test3()
{
	const unsigned int ITERATIONS=40;

	unsigned int iUint;
	NaturalNum   cNnum;
	char aUintResult[100];
	char aNnumResult[100];

	for (unsigned int i=0; i<ITERATIONS; i++)
	{
		unsigned int iOperand1=(unsigned int)rand();
		unsigned int iOperand2=(unsigned int)rand();
		unsigned int iOperator=(unsigned int)rand();
		switch (iOperator%10)
		{
		case 0://operator+=
			iUint=iOperand1;
			cNnum=iOperand1;
			iUint+=iOperand2;
			cNnum+=iOperand2;
			break;
		case 1://operator-=
			iUint=iOperand1;
			cNnum=iOperand1;
			iUint-=iOperand2&iOperand1;
			cNnum-=iOperand2&iOperand1;
			break;
		case 2://operator*=
			iUint=iOperand1;
			cNnum=iOperand1;
			iUint*=iOperand2;
			cNnum*=iOperand2;
			break;
		case 3://operator/=
			iUint=iOperand1;
			cNnum=iOperand1;
			iUint/=iOperand2+1;
			cNnum/=iOperand2+1;
			break;
		case 4://operator%=
			iUint=iOperand1;
			cNnum=iOperand1;
			iUint%=iOperand2+1;
			cNnum%=iOperand2+1;
			break;
		case 5://operator|=
			iUint=iOperand1;
			cNnum=iOperand1;
			iUint|=iOperand2;
			cNnum|=iOperand2;
			break;
		case 6://operator&=
			iUint=iOperand1;
			cNnum=iOperand1;
			iUint&=iOperand2;
			cNnum&=iOperand2;
			break;
		case 7://operator^=
			iUint=iOperand1;
			cNnum=iOperand1;
			iUint^=iOperand2;
			cNnum^=iOperand2;
			break;
		case 8://operator<<=
			iUint=iOperand1;
			cNnum=iOperand1;
			iUint<<=iOperand2%16;
			cNnum<<=iOperand2%16;
			break;
		case 9://operator>>=
			iUint=iOperand1;
			cNnum=iOperand1;
			iUint>>=iOperand2%16;
			cNnum>>=iOperand2%16;
			break;
		}
		sprintf(aUintResult,"%u",iUint);
		cNnum.ToString(aNnumResult,10);
		printf("unsigned int: %s\n",aUintResult);
		printf("NaturalNum:   %s\n",aNnumResult);
	}
}


//Test the NaturalNum string conversion routines.
void Test4()
{
	const unsigned int ITERATIONS=20;

	char aString1[100];
	char aString2[100];

	for (unsigned int i=0; i<ITERATIONS; i++)
	{
		NaturalNum cNaturalNum=(unsigned int)rand();
		unsigned int iBase=(unsigned int)(2+(rand()%15));
		cNaturalNum.ToString(aString1,iBase);
		cNaturalNum=StringToNaturalNum(aString1,iBase);
		cNaturalNum.ToString(aString2,iBase);
		printf("%s\n",aString1);
		printf("%s\n",aString2);
	}
}
