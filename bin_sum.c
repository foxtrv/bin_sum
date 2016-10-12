/***********************************************************
* Assignment:   Lab 2                                      *
* File:         foxH2.cpp                                  *
* Author:       Trevor Fox                                 *
* Date:         8/29/16                                    *
* Time taken:   ~7 hours                                   *
* Description:  Reads a list of binomials from a text      *
*               file, sorts them, then outputs the sum.    *
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Custom object to hold coefficient and constant of a binomial
typedef struct {
	float coeff;
	float constant;
} binomial;

// Helper function for qsort
int compare(const void * a, const void * b) {
	binomial *ia = (binomial *)a;
	binomial *ib = (binomial *)b;
	if (ia->coeff != ib->coeff) return ib->coeff < ia->coeff;
	return ib->constant < ia->constant;
}

int main(int argc, char* argv[]) {

	// Using a pipe to execute the syscall to count number of lines from input file
	FILE *fp;
	char output[1024];

	// Concatenate "argv[1]" with "wc -l" in one string (because C)
	char* file = argv[1];
	char* in = "wc -l ";
	char* res = malloc(strlen(in)+strlen(file)+1);
	strcat(res, in);
	strcat(res, file);

	// System call
	fp = popen(res, "r");
	if (fp == NULL)
		exit(1);
	// Grab the output from the system call
	while (fgets(output, 1023, fp) != NULL)
	pclose(fp);

	// Store number of lines counted in variable numlines
	int numlines;
	sscanf(output, "%d", &numlines);

	// Read file 
	FILE * input = fopen(argv[1], "r");

	// Initialize binomial array
	binomial v[numlines];
	int k = 0;
	float total_coeff = 0;
	float total_const = 0;

	// Scan file and print contents
	while (!feof(input)){
		binomial b; // Initialize binomial struct
		
		// We are reading 2 floats per line
		if (fscanf(input, "%fx%f", &b.coeff, &b.constant) == 2)
			v[k++] = b; // store binomial into binomial array
	} 

	fclose(input); // explicitly close file

	// print sorted binomials
	printf("Unsorted input: "); 
	for (int i = 0; i < numlines; i++){
		printf("\n%.1fx", v[i].coeff);
		printf("%s", v[i].constant < 0 ? "" : "+"); // print “+” or “”
		printf("%.1f", v[i].constant);
	}

	// sort the vector of binomials by coefficients first, then constants
	qsort((void *)&v, numlines, sizeof(binomial), compare);
	
	// find sum of sorted binomials
	for (int i = 0; i < numlines; i++){
		total_coeff += v[i].coeff;
		total_const += v[i].constant;
	}

	// print sorted binomials
	printf("\n\nSorted input: "); 
	for (int i = 0; i < numlines; i++){
		printf("\n%.1fx", v[i].coeff);
		printf("%s", v[i].constant < 0 ? "" : "+"); // print “+” or “”
		printf("%.1f", v[i].constant);
	}

	// print totals
	printf("\n\nThe sum of the sorted binomials is: %.1fx", total_coeff);
	printf("%s", total_const < 0 ? "" : "+");
	printf("%.1f\n", total_const);

	return 0;
}
