
#include <stdio.h> //printf
#include "circularBuffer.h"
#include "../../cutest-1.5/cuTest.h"

/**
 * Test Methods 
*/

void TestNew_8BitCircularBuffer(CuTest* tc){
    int length = 8;
    sCircBuff8bit_t * tBuf = New_8BitCircularBuffer(length);
    CuAssertIntEquals(tc, length, tBuf->maxLen);
    CuAssertIntEquals(tc, 0, tBuf->writeIndx);
    CuAssertIntEquals(tc, 0, tBuf->readIndx);
    CuAssertIntEquals(tc, 0x04, tBuf->flags);
}

void TestDelete_8BitCircularBuffer(CuTest* tc){
    int length = 8;
    sCircBuff8bit_t * tBuf = New_8BitCircularBuffer(length);
    CuAssertTrue(tc, !Delete_8BitCircularBuffer(tBuf));
}

void TestInit_8BitCircularBuffer(CuTest* tc){
// See TestNew_8BitCircularBuffer
}

void TestReset_8BitCircularBuffer(CuTest* tc){
    int length = 8;
    sCircBuff8bit_t * tBuf = New_8BitCircularBuffer(length);
    CuAssertTrue(tc, !Reset_8BitCircularBuffer(tBuf));
}

void TestFull_8BitCircularBuffer(CuTest* tc){
    int length = 8;
    sCircBuff8bit_t * tBuf = New_8BitCircularBuffer(length);
    uint8_t flag = Full_8BitCircularBuffer(tBuf);
    CuAssertIntEquals(tc, 0, flag); // Pass if empty

    // Push Data into it and see if the full flag is raised
    for(int i = 0; i < length; i++){
        Push_8BitCircularBuffer(tBuf, i);
    }
    flag = Full_8BitCircularBuffer(tBuf);
    CuAssertIntEquals(tc, 1, flag); // Pass if not empty
}

void TestOverflow_8BitCircularBuffer(CuTest* tc){
    int length = 8;
    sCircBuff8bit_t * tBuf = New_8BitCircularBuffer(length);
    uint8_t flag = Overflow_8BitCircularBuffer(tBuf);
    CuAssertIntEquals(tc, 0, flag); // Pass if no overflow

    // Push a lot of data into the buffer
    for(int i = 0; i < length*3; i++){
        Push_8BitCircularBuffer(tBuf, i);
    }
    flag = Overflow_8BitCircularBuffer(tBuf);
    CuAssertIntEquals(tc, 1, flag); // Pass if overflowed

    // Reset the buffer and check initials
    if(Overflow_8BitCircularBuffer(tBuf)){
        Reset_8BitCircularBuffer(tBuf);
    }
    CuAssertIntEquals(tc, length, tBuf->maxLen);
    CuAssertIntEquals(tc, 0, tBuf->writeIndx);
    CuAssertIntEquals(tc, 0, tBuf->readIndx);
    CuAssertIntEquals(tc, 0x04, tBuf->flags);
}

void TestEmpty_8BitCircularBuffer(CuTest* tc){
    int length = 8;
    sCircBuff8bit_t * tBuf = New_8BitCircularBuffer(length);
    uint8_t flag = Empty_8BitCircularBuffer(tBuf);
    CuAssertIntEquals(tc, 1, flag); // Pass if it is empty

    // Push something
    Push_8BitCircularBuffer(tBuf, 2);

    flag = Empty_8BitCircularBuffer(tBuf);
    CuAssertIntEquals(tc, 0, flag); // Pass if it is not empty
    
}

void TestCapacity_8BitCircularBuffer(CuTest* tc){
    int length = 8;
    sCircBuff8bit_t * tBuf = New_8BitCircularBuffer(length);
    CuAssertIntEquals(tc, length, Capacity_8BitCircularBuffer(tBuf)); // Capacity should be = length

}

void TestSize_8BitCircularBuffer(CuTest* tc){
    int length = 8;
    sCircBuff8bit_t * tBuf = New_8BitCircularBuffer(length);
    CuAssertIntEquals(tc, 0, Size_8BitCircularBuffer(tBuf)); // size should be 0

    // Push some stuff
    Push_8BitCircularBuffer(tBuf, 2);
    Push_8BitCircularBuffer(tBuf, 2);
    Push_8BitCircularBuffer(tBuf, 2);
    CuAssertIntEquals(tc, 3, Size_8BitCircularBuffer(tBuf)); // size should be 3
    
    // Pop some stuff
    uint8_t container = 0;
    Pop_8BitCircularBuffer(tBuf, &container);
    CuAssertIntEquals(tc, 2, Size_8BitCircularBuffer(tBuf)); // size should be 2 

    // make writer be behind reader
    Push_8BitCircularBuffer(tBuf, 2);
    Push_8BitCircularBuffer(tBuf, 2);
    Push_8BitCircularBuffer(tBuf, 2);
    Push_8BitCircularBuffer(tBuf, 2);
    Push_8BitCircularBuffer(tBuf, 2);
    CuAssertIntEquals(tc, -1, Size_8BitCircularBuffer(tBuf)); // size should be -1 because reader is at index 1 and writer is at index 0

    // Make Writer equal reader
    Push_8BitCircularBuffer(tBuf, 2);
    CuAssertIntEquals(tc, 0, Size_8BitCircularBuffer(tBuf)); // size should be 0

    // Make writer go ahead of reader.
    Push_8BitCircularBuffer(tBuf, 2);
    CuAssertIntEquals(tc, 0, Size_8BitCircularBuffer(tBuf)); // size should be 0 because the buffer will not overwrite the unread data. The overflow flag is raised, waiting for the program to reset the buffer.
}

void TestPush_8BitCircularBuffer(CuTest* tc){
    // Code coverage done in previous tests
    
}

void TestPop_8BitCircularBuffer(CuTest* tc){
    // Code coverage done in previous tests
}

CuSuite* CircularBufferGetSuite(){
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, TestNew_8BitCircularBuffer);
    SUITE_ADD_TEST(suite, TestDelete_8BitCircularBuffer);
    SUITE_ADD_TEST(suite, TestInit_8BitCircularBuffer);
    SUITE_ADD_TEST(suite, TestReset_8BitCircularBuffer);
    SUITE_ADD_TEST(suite, TestFull_8BitCircularBuffer);
    SUITE_ADD_TEST(suite, TestOverflow_8BitCircularBuffer);
    SUITE_ADD_TEST(suite, TestEmpty_8BitCircularBuffer);
    SUITE_ADD_TEST(suite, TestCapacity_8BitCircularBuffer);
    SUITE_ADD_TEST(suite, TestSize_8BitCircularBuffer);
    SUITE_ADD_TEST(suite, TestPush_8BitCircularBuffer);
    SUITE_ADD_TEST(suite, TestPop_8BitCircularBuffer);
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