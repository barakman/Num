#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\RationalNum.h"


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


//Calculate some square roots.
void Test1()
{
	const unsigned int ITERATIONS=64;

	char aResult[100];
	RationalNum cRationalNum;
	RationalNum cRationalNumRoot;

	for (unsigned int i=1; i<=ITERATIONS; i++)
	{
		cRationalNum=i;
		cRationalNumRoot=cRationalNum.Root(2);
		cRationalNumRoot.ToString(aResult,10,8);
		printf("Square Root [%u] = %s\n",i,aResult);
	}
}


//Calculate the values of PI and PHI.
void Test2()
{
	const unsigned int PI_ITERATIONS=64;
	const unsigned int PHI_ITERATIONS=32;

	char aPi[100];
	char aPhi[100];
	RationalNum cPi=0;
	RationalNum cPhi=1;

	for (unsigned int i=0; i<PI_ITERATIONS; i++)
	{
		if ((i%2)==0)
			cPi+=(RationalNum)4/(i*2+1);
		else
			cPi-=(RationalNum)4/(i*2+1);
		cPi.ToString(aPi,10,12);
		printf("PI ~ %s\n",aPi);
	}

	for (unsigned int j=0; j<PHI_ITERATIONS; j++)
	{
		cPhi=1+1/cPhi;
		cPhi.ToString(aPhi,10,12);
		printf("PHI ~ %s\n",aPhi);
	}
}


//Test the RationalNum assignment operators.
void Test3()
{
	const unsigned int ITERATIONS=40;

	double	    fDoub;
	RationalNum cRnum;
	char aDoubResult[100];
	char aRnumResult[100];

	for (unsigned int i=0; i<ITERATIONS; i++)
	{
		double fOperand1=((rand()%2)*2-1)*(double)rand()/((double)rand()+1);
		double fOperand2=((rand()%2)*2-1)*(double)rand()/((double)rand()+1);
		unsigned int iOperator=(unsigned int)rand();
		switch (iOperator%4)
		{
		case 0://operator+=
			fDoub=fOperand1;
			cRnum=fOperand1;
			fDoub+=fOperand2;
			cRnum+=fOperand2;
			break;
		case 1://operator-=
			fDoub=fOperand1;
			cRnum=fOperand1;
			fDoub-=fOperand2;
			cRnum-=fOperand2;
			break;
		case 2://operator*=
			fDoub=fOperand1;
			cRnum=fOperand1;
			fDoub*=fOperand2;
			cRnum*=fOperand2;
			break;
		case 3://operator/=
			fDoub=fOperand1;
			cRnum=fOperand1;
			fDoub/=fOperand2+1;
			cRnum/=fOperand2+1;
			break;
		}
		sprintf(aDoubResult,"%.8lf",fDoub);
		cRnum.ToString(aRnumResult,10,8);
		printf("double:	     %s\n",aDoubResult);
		printf("RationalNum: %s\n",aRnumResult);
	}
}


//Test the RationalNum string conversion routines.
void Test4()
{
	const unsigned int ITERATIONS=20;

	char aString1[100];
	char aString2[100];

	for (unsigned int i=0; i<ITERATIONS; i++)
	{
		RationalNum cRationalNum=((rand()%2)*2-1)*(double)rand()/((double)rand()+1);
		unsigned int iBase=(unsigned int)(2+(rand()%15));
		unsigned int iPrecision=(unsigned int)(rand()%20);
		cRationalNum.ToString(aString1,iBase,iPrecision);
		cRationalNum=StringToRationalNum(aString1,iBase);
		cRationalNum.ToString(aString2,iBase,iPrecision);
		printf("%s\n",aString1);
		printf("%s\n",aString2);
	}
}
