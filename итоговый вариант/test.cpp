#include "ln.cpp"

using namespace LongMath;
void test_addition(){
	LongNumber a = "101.10101010100101010"_ln;
	LongNumber b = "101.011011001010010"_ln;
	std::cout << a+b << std::endl;
}

void test_substraction(){
	LongNumber a = "101.10101010100101010"_ln;
	LongNumber b = "101.011011001010010"_ln;
	std::cout << a-b << std::endl;
}

void test_multiplication(){
	LongNumber a = "101.10101010100101010"_ln;
	LongNumber b = "101.011011001010010"_ln;
	std::cout << a*b << std::endl;
}

void test_division(){
	LongNumber a = "101.10101010100101010"_ln;
	LongNumber b = "101.011011001010010"_ln;
	std::cout << a/b << std::endl;
}

void test_comparision(){
	LongNumber a = "101.10101010100101010"_ln;
	LongNumber b = "101.011011001010010"_ln;
	if (a >b and a!=b and b<a) std::cout << "ok" << std::endl;
}

void neg(){
	LongNumber c =	-9_ln, d = "101.1"_ln;
	LongNumber res = c+d;
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
