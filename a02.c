#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double hullSpeed(double lgth)
{
	// computing the hull speed for the specified boat length,
	// implementing the numerical computation in GNU Assembly Language
	// through use of FPU instructions (without calling sqrt() from math.h)

	double constfp = 1.34;

	asm(
		"		fldl		%[lgthin] 			\n"   //load lgth to stack
		"		fsqrt						\n"   //square the top number of stack
		"		fldl		%[constfpin]			\n"   //put constfp on stack
		"		fmulp						\n"   //mult the 2 num in the stack
		"		fstpl		%[lgthout]			\n"   //pop lgth back to var

		: [lgthout]		 "=m"	 (lgth) 			//outputs
		: [lgthin]		 "m"	 (lgth),			//inputs
		  [constfpin]	 "m"	 (constfp)

		: "eax", "ebx", "ecx"		// clobbers
	);

	return lgth;
}

double hullSpeedC(double lgth)
{
	// this C implementation of the hull speed computation is provided
	// to compare its correct results with the results of the code

	return 1.34 * sqrt(lgth);
}

int main (int argc, char **argv)
{
	double	lgth;
	double	hullSpd, hullSpdC;

	printf("CS201 - Assignment 02 - Bowen Johnson\n");
	if (argc != 2) {
		printf("need 1 argument: boat length\n");
		return -1;
		}
	lgth = atof(argv[1]);
	hullSpd = hullSpeed(lgth);
	hullSpdC = hullSpeedC(lgth);

	printf("hullSpeed(%.0f) = %.3f, %.3f\n", lgth, hullSpd, hullSpdC);

	return 0;
}
