#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

void testKingdomCards(){
	const int A[] = {INT_MIN, -1, 0, 1, INT_MAX};
	int i, pass = 1, size = 10;

	// Fill with only one integer
	int *r0 = malloc(10 * sizeof(int));
	int *r1 = malloc(10 * sizeof(int));
	int *r2 = malloc(10 * sizeof(int));
	int *r3 = malloc(10 * sizeof(int));
	int *r4 = malloc(10 * sizeof(int));
	r0 = kingdomCards(A[0], A[0], A[0], A[0], A[0], A[0], A[0], A[0], A[0], A[0]);
	r1 = kingdomCards(A[1], A[1], A[1], A[1], A[1], A[1], A[1], A[1], A[1], A[1]);
	r2 = kingdomCards(A[2], A[2], A[2], A[2], A[2], A[2], A[2], A[2], A[2], A[2]);
	r3 = kingdomCards(A[3], A[3], A[3], A[3], A[3], A[3], A[3], A[3], A[3], A[3]);
	r4 = kingdomCards(A[4], A[4], A[4], A[4], A[4], A[4], A[4], A[4], A[4], A[4]);

	printf("\n\n=============================================\n");
	printf("Testing KINGDOMCARDS function from dominion.c\n");
	printf("=============================================\n");
	for(i = 0; i < size; i++){
		if(r0[i] != A[0]){
			printf("FAIL when passed in all 'INT_MIN' values\n");
			pass = 0;
		}
		if(r1[i] != A[1]){
			printf("FAIL when passed in all '-1' values\n");
			pass = 0;
		}
		if(r2[i] != A[2]){
			printf("FAIL when passed in all '0' values\n");
			pass = 0;
		} 
		if(r3[i] != A[3]){
			printf("FAIL when passed in all '1' values\n");
			pass = 0;
		} 
		if(r4[i] != A[4]){
			printf("FAIL when passed in all 'INT_MAX' values\n");
			pass = 0;
		} 
	}
	if(pass == 1) printf("PASS when passed in 10 of the same values: INT_MIN, -1, 0, 1, and INT_MAX\n");

	pass = 1;
	int s0[] = {-10, -9, -8, -7, -6, -5, -4, -3, -2, -1};
	int s1[] = {-9, -8, -7, -6, -5, -4, -3, -2, -1, 0};
	int s2[] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4};
	int s3[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int s4[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	r0 = kingdomCards(-10, -9, -8, -7, -6, -5, -4, -3, -2, -1);
	r1 = kingdomCards(-9, -8, -7, -6, -5, -4, -3, -2, -1, 0);
	r2 = kingdomCards(-5, -4, -3, -2, -1, 0, 1, 2, 3, 4);
	r3 = kingdomCards(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
	r4 = kingdomCards(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

	for(i = 0; i < size; i++){
		if(r0[i] != s0[i]){
			printf("FAIL when passed in ascending negative values\n");
			pass = 0;
		}
		if(r1[i] != s1[i]){
			printf("FAIL when passed in ascending negative and zero values\n");
			pass = 0;
		}
		if(r2[i] != s2[i]){
			printf("FAIL when passed in ascending negative, zero, and positive values\n");
			pass = 0;
		}
		if(r3[i] != s3[i]){
			printf("FAIL when passed in ascending zero and positive values\n");
			pass = 0;
		}
		if(r4[i] != s4[i]){
			printf("FAIL when passed in ascending positive values\n");
			pass = 0;
		}
	}
	if(pass == 1) printf("PASS when passed in 10 ascending values\n");

	int t0[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int t1[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	int t2[] = {5, 4, 3, 2, 1, 0, -1, -2, -3, -4};
	int t3[] = {0, -1, -2, -3, -4, -5, -6, -7, -8, -9};
	int t4[] = {-1, -2, -3, -4, -5, -6, -7, -8, -9, -10};
	r0 = kingdomCards(10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
	r1 = kingdomCards(9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
	r2 = kingdomCards(5, 4, 3, 2, 1, 0, -1, -2, -3, -4);
	r3 = kingdomCards(0, -1, -2, -3, -4, -5, -6, -7, -8, -9);
	r4 = kingdomCards(-1, -2, -3, -4, -5, -6, -7, -8, -9, -10);

	for(i = 0; i < size; i++){
		if(r0[i] != t0[i]){
			printf("FAIL when passed in descending positive values\n");
			pass = 0;
		}
		if(r1[i] != t1[i]){
			printf("FAIL when passed in descending positive and zero values\n");
			pass = 0;
		}
		if(r2[i] != t2[i]){
			printf("FAIL when passed in descending positive, zero, and negative values\n");
			pass = 0;
		}
		if(r3[i] != t3[i]){
			printf("FAIL when passed in descending zero and negative values\n");
			pass = 0;
		}
		if(r4[i] != t4[i]){
			printf("FAIL when passed in descending negative values\n");
			pass = 0;
		}
	}
	if(pass == 1) printf("PASS when passed in 10 descending values\n");
}

int main(int argc, char *argv[]){
	testKingdomCards();
	return 0;
}