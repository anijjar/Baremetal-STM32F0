#include <stdio.h> //printf
#include "..\..\core\system\inc\uart.h"
#include "..\cutest-1.5\CuTest.h"

/**
 * Test Methods 
*/
void Test_UART_INIT(CuTest* tc){
}

CuSuite* CircularBufferGetSuite(){
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, Test_UART_INIT);
    // Add more test cases bellow
}

/**
 * main 
*/
void RunAllTests() {
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();

	CuSuiteAddSuite(suite, CircularBufferGetSuite());
    // Add more suites below

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}

int main(){
    RunAllTests();
}