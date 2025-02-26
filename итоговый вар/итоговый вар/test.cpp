#include "ln.h"

using namespace LongMath;
void test_addition(){
	LongNumber a = "101.10101010100101010"_ln; //5,6663360595703125
	LongNumber b = "101.011011001010010"_ln; //5,42437744140625
	if((a+b).toStr() == "11.0907135009765625") std::cout << "test_addition: OK" << std::endl;
	else std::cout << "test_addition: FAIL"<< std::endl;
	std::cout << a+b << std::endl;
}

void test_substraction(){
	LongNumber a = "101.10101010100101010"_ln;
	LongNumber b = "101.011011001010010"_ln;
	if((a-b).toStr() == "0.2419586181640625") std::cout << "test_substraction: OK" << std::endl;
	else std::cout << "test_substraction: FAIL"<< std::endl;
	std::cout << a-b << std::endl;
}

void test_multiplication(){
	LongNumber a = "101.10101010100101010"_ln;
	LongNumber b = "101.011011001010010"_ln;
	if((a*b).toStr() == "30.736345496959984302520751953125") std::cout << "test_multiplication: OK" << std::endl;
	else std::cout << "test_multiplication: FAIL"<< std::endl;
	std::cout << a*b << std::endl;
}

void test_division(){
	LongNumber a = "101.11"_ln; //5,75
	LongNumber b = "110.01"_ln; // 6,25
	if((a/b).toStr() == "0.92") std::cout << "test_division: OK" << std::endl;
	else std::cout << "test_division: FAIL"<< std::endl;
	std::cout << a/b << std::endl;
}

void test_comparision(){
	LongNumber a = "101.10101010100101010"_ln;
	LongNumber b = "101.011011001010010"_ln;
	
	if (a >b and a!=b and b<a) std::cout << "test_comparision: OK" << std::endl;
	else std::cout << "test_comparision: FAIL" << std::endl;
}

void neg(){
	LongNumber c =	-9_ln, d = "101.1"_ln;
	LongNumber res = c+d;
	if (res.toStr() == "-3.5") std::cout << "neg: OK"<< std::endl;
	else std::cout << "neg: FAIL"<< std::endl;
	std::cout << res;
}
int main(){
	LongNumber a = "101.10101010100101010"_ln;
	LongNumber b = "101.011011001010010"_ln;
	std::cout << "a ="<< a << " "<< "b =" << b << std::endl;
	test_addition();
	test_substraction();
	test_multiplication();
	test_division();
	test_comparision();
	neg();	
}
