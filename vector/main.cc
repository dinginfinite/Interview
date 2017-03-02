#include <cassert>
#include <stdlib.h>
#include <ctime>
#include <cstdio>
#include <vector>
#include "qh_vector.h"

/**
 * Test constructors
 */
void test1() {

	// default constructor
	qh::vector<int> a;
	assert(a.size() == 0);
	assert(a.empty());

	qh::vector<int> b(10, 1);
	assert(b.size() == 10);
	for (size_t i = 0; i < b.size(); ++i)
		assert(b[i]==1);

	// copy constructor
	qh::vector<int> c(b);
	for (size_t i = 0; i < c.size(); ++i)
		assert(c[i] == b[i]);
}

/**
 * Test operator=
 */
void test2() {
	qh::	vector<int> a(10, 1);
	qh::vector<int> b(3, 2);

	b = a;
	for (size_t i = 0; i < b.size(); ++i)
		assert(b[i] == a[i]);

	qh::vector<int> c(10, 1);

	// self assign
	c = c;
	for (size_t i = 0; i < c.size(); ++i)
		assert(c[i] == 1);
}


/**
 * Test <code>push_back</code> and <code>pop_back</code>
 */
void test3() {
	size_t sz = 100;
	qh::vector<int> a;
	for (size_t i = 0; i < sz; ++i)
		a.push_back(i);
	assert(a.size() == sz);
	for (size_t i = 0; i < a.size(); ++i)
		assert(a[i] == i);
	for (size_t i = 0; i < sz / 2; ++i)
		a.pop_back();
	assert(a.size() == sz / 2);
	for (size_t i = 0; i < a.size(); ++i)
		assert(a[i] == i);
}

/**
 * Test other function
 */
void test4() {
	qh::vector<int> a;
	a.resize(10);
	assert(a.size() == 10);

	a.resize(3);
	assert(a.size() == 3);

	a.clear();
	assert(a.empty());
}

/**
 * Test nested vector
 */

void test5() {
	qh::vector<qh::vector<int> > a;

	int cnt = 0;
	for (size_t i = 0; i < 3; ++i) {
		qh::vector<int> tmp;
		for (size_t j = 0; j < 4; ++j) {
			tmp.push_back(cnt++);
		}
		a.push_back(tmp);
	}

	cnt = 0;
	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 4; ++j) {
			assert(a[i][j] == cnt++);
		}
	}
}

/**
 * Test profile
 */
void test6() {
	qh::vector<int> a;
	std::vector<int> b;

	time_t st = clock();
	for (size_t i = 0; i < 10000000; ++i)
		a.push_back(i);
	printf("qh::vecotr %.3fs\n", (double)(clock() - st) / CLOCKS_PER_SEC);
	st = clock();
	for (size_t i = 0; i < 10000000; ++i)
		b.push_back(i);
    printf("std::vecotr %.3fs\n", (double)(clock() - st) / CLOCKS_PER_SEC);
}

int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    //TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断。
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();

#ifdef WIN32
    system("pause");
#endif

	return 0;
}
