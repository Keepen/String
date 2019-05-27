#pragma once
#include <iostream>
using namespace std;
typedef char* Iterator;
typedef const char* const_Iterator;
size_t npos = -1;		//表示非法的下标
class String {
private:
	char* _str;
	size_t _size;
	size_t _capacity;

public:
	//1.初始化
	String();
	//2.重置_size
	void Resize(size_t n, char c = '\0');

	//3.扩容
	void Reserve(size_t n);

	//4.尾插字符
	void PushBack(char c);

	//5.输出字符串
	void Print();

	//6.begin迭代器
	Iterator begin();

	//7.end迭代器
	Iterator end();

	//8.const begin迭代器
	const_Iterator begin() const;

	//9.const end 迭代器
	const_Iterator end() const;

	//10.重载+=操操作符,
	//   1.尾插一个字符
	String& operator+=(const char c);

	//   2.尾插一个字符串
	String& operator+=(const char* s);

	//	3.尾插一个对象
	String& operator+=(const String& s);


	//11.在pos位置处插入元素
	//		1.插入字符
	void Insert(size_t pos, const char c);

	//		2.插入字符串
	void Insert(size_t pos, const char* s);

	//		3.插入一个对象
	void Insert(size_t pos, const String& s);

	//12.擦除元素
	//		1.擦除pos位置处的一个字符
	void Erase(size_t pos);

	//		2.擦除pos位置后n个字符
	void Erase(size_t pos, size_t n);

	//13.查找
	//		1.查找一个字符
	size_t Find(const char c);
	//		2.查找字符串
	size_t Find(const char* s);

	//14.重载+操作符
	//		1.加一个字符
	String operator+(const char c);
	//		2.加字符串
	String operator+(const char* s);
	//		3.加对象
	String operator+(const String& s);


	//15.重载输出运算符
;	friend ostream& operator<<(ostream& _cout, const String& s);

	//析构
	~String();
};
