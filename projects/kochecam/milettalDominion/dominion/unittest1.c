#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

void testCompare(){
	const int size = 7;
	const int A[] = {INT_MIN, -5, -1, 0, 1, 5, INT_MAX};
	const int B[] = {INT_MIN, -5, -1, 0, 1, 5, INT_MAX};
	int i, j;

	/*printf("Testing for equality...\n");
	for(i = 0; i < size; i++){
		if(compare(&A[i], &B[i]) == 0)
			printf("PASS: equality is correctly detected with A = %d and B = %d.\n", A[i], B[i]);
		else
			printf("FAIL: equality is NOT correctly detected with A = %d and B = %d.\n", A[i], B[i]);
	}*/

	printf("=============================================\n");
	printf("Testing COMPARE function from dominion.c\n");
	printf("=============================================\n");
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			if(compare(&A[i], &B[j]) == 1 && A[i] > B[j]){
				printf("PASS: A > B is correctly detected when A = %d and B = %d.\n", A[i], B[j]);
			}
			else if(compare(&A[i], &B[j]) == 0 && A[i] == B[j]){
				printf("PASS: equality is correctly detected when A = %d and B = %d.\n", A[i], B[j]);
			}
			else if(compare(&A[i], &B[j]) == -1 && A[i] < B[j]){
				printf("PASS: A < B is correctly detected when A = %d and B = %d.\n", A[i], B[j]);
			}
			else{
				if(compare(&A[i], &B[j]) != -1 && compare(&A[i], &B[j]) != 0 && compare(&A[i], &B[j]) != 1)
					printf("FAIL: Nonsense value returned when A = %d and B = %d.\n", A[i], B[j]);
				else if(compare(&A[i], &B[j]) == 1)
					printf("FAIL: 1 returned when A !> B, A = %d and B = %d", A[i], B[j]);
				else if(compare(&A[i], &B[j]) == 0)
					printf("FAIL: 0 returned when A != B, A = %d and B = %d", A[i], B[j]);
				else if(compare(&A[i], &B[j]) == -1)
					printf("FAIL: -1 returned when A !< B, A = %d and B = %d", A[i], B[j]);
			}
		}
	}
}


int main(int argc, char *argv[]){
	testCompare();
	return 0;
}