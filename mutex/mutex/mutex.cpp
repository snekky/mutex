// mutex.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <mutex>
#include <thread>
#include <iostream>
#include <Windows.h>

void foo(int& num, std::mutex& mtx) {
	while (1) {
		mtx.lock();
		num += 10;
		std::cout << "foo  " << num << std::endl;
		mtx.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}


void bar(int& num, std::mutex& mtx) {
	while (1) {
		mtx.lock();
		num -= 10;
		std::cout << "bar  " << num << std::endl;
		mtx.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}


int main()
{
	int number = 10;
	std::mutex mutant;

	std::thread thr1(foo, std::ref(number), std::ref(mutant));
	std::thread thr2(bar, std::ref(number), std::ref(mutant));
	thr1.join();
	thr2.join();
    return 0;
}

