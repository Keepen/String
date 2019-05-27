#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "String.h"
using namespace std;

//1.构造函数
String::String() {
	_str = '\0';
	_size = 0;
	_capacity = 0;
}

//2.重置size
void String::Resize(size_t n,char c) {
	//1.如果n<_size,直接赋值，后面补'\0'
	if (n < _size) {
		_size = n;
		_str[n] = '\0';
		return;
	}
	//2.需要扩容
	if (n > _capacity) {
		Reserve(n);
	}
	//从_size开始赋值c
	for (size_t i = _size; i < n; i++) {
		_str[i] = c;
	}
	_str[n] = '\0';
}

//3.扩容
void String::Reserve(size_t n) {
	//1.如果capacity式是0，就给初始值15
	if (_capacity == 0) {
		_str = new char[15];
		_capacity = 15;
	}
	//2.capacity有值，只是不够了,需要搬运数据
	else {
		String s2;
		s2._str = new char[_capacity * 2];
		s2._capacity = 2 * _capacity;
		//搬运数据
		strcpy(s2._str, _str);
		delete[] _str;
		_str = s2._str;
	}
}

//4.尾插字符
void String::PushBack(char c) {
	//1.先判断是否需要扩容
	if (_size == _capacity) {
		Reserve(_size);
	}
	//扩容完毕，或者压根不需要扩容
	_str[_size++] = c;
	_str[_size] = '\0';
}

//5.输出
void String::Print() {
	////范围for:需要自行实现迭代器
	//for (auto e : _str) {
	//	cout << e;
	//}
	//cout << endl;
	for (size_t i = 0; i < _size; i++) {
		cout << _str[i];
	}
	cout << endl;
}

//6.begin迭代器：返回第一个有效字符的位置
Iterator String::begin() {
	if (_str) {
		return _str;
	}
	return nullptr;
}

//7.end迭代器：返回有效字符的后一个字符的位置
Iterator String::end() {
	if (_str) {
		return _str + strlen(_str);
	}
	return nullptr;
}

//8.const begin迭代器
const_Iterator String::begin()const {
	return _str;
}

//9.const end 迭代器
const_Iterator String::end()const {
	return _str + strlen(_str);
}

//10.重载+= 操作符
//		1.尾插一个字符
String& String::operator+=(const char c) {
	//判断是否要增容
	if (_size == _capacity) {
		//进行增容
		Reserve(_size);
	}
	//要么是增容完毕，要么是本来就够
	//直接进行赋值操作即可
	_str[_size++] = c;
	_str[_size] = '\0';
	return *this;
}

//		2.尾插一个字符串
String& String::operator+=(const char* s) {
	//先判断是否需要扩容
	size_t len = strlen(s);
	if (_size + len >= _capacity) {
		Reserve(_size + len);
	}
	//要么是扩容完毕，要么是本来就够
	//直接进行尾插
	strcpy(_str + _size, s);
	_size += len;		//注意更新_size的值
	return *this;
}

//		3.尾插一个对象
String& String::operator+=(const String& s) {
	//先判断是否需要增容
	if (_size + s._size >= _capacity) {
		Reserve(_size + s._size);
	}
	//增容完毕
	strcpy(_str + _size, s._str);
	_size += s._size;
	return *this;
}



//11.在pos位置处插入
//		1.一个字符
void String::Insert(size_t pos,  const char c) {
	//插入元素，就需要将其后面的元素向后搬运一格
	//还是先考虑增容问题
	if (_size == _capacity) {
		Reserve(_size);
	}
	_size++;
	//增容完毕或者是本身就够,从后向前搬运
	for (size_t i = _size+1; i > pos; i--) {
		_str[i] = _str[i - 1];
	}
	_str[pos] = c;

}

//		2.插入一个字符串
void String::Insert(size_t pos, const char* s) {
	//先判断是否增容
	size_t len = strlen(s);
	if (_size + len >= _capacity) {
		Reserve(_size + len);
	}
	//增容完毕,或者本来就够
	//搬运数据	
	//int tmp = _size + len;
	for (size_t i = _size + len;i>=pos+len; i--) {
		_str[i] = _str[i - len];
	}
	//插入数据
	for (size_t i = pos, j = 0; i < pos + len, j < len; i++, j++) {
		_str[i] = s[j];		
	}
	_size += len;
}

//		3.插入一个对象
void String::Insert(size_t pos, const String& s) {
	//先判断对象内容是否为空
	if (s._size == 0) {
		return;
	}

	//判断是否增容
	if (_size + s._size >= _capacity) {
		Reserve(_size + s._size);
	}
	//增容完毕
	//搬运数据
	for (size_t i = _size + s._size; i >= pos+s._size; i--) {
		_str[i] = _str[i - s._size];
	}

	//插入数据
	for (size_t i = pos, j = 0; i < pos + s._size, j < s._size; i++, j++) {
		_str[i] = s._str[j];
	}
	_size += s._size;
	_str[_size] = '\0';
}

//12.删除操作,擦除元素，不改变容量大小
//		1.擦除pos位置的一个字符
void String::Erase(size_t pos) {
	//先判断是否合法
	if (pos > _size || pos < 0) {
		return;
	}
	//输入合法，进行删除操作
	//将pos位置的元素都向前移动一格
	while (pos<_size) {
		_str[pos++] = _str[pos + 1];
	}
	_size--;
}

//		2.擦除pos位置后的n个字符
void String::Erase(size_t pos, size_t n) {
	if (pos >= _size || pos + n >= _size) {
		return;
	}
	//搬运数据
	for (size_t i = pos; i < pos + n; i++) {
		_str[i] = _str[i + n];
	}
	_size -= n;
}

//13.查找
//		1.查找一个字符
size_t String::Find(const char c) {
	//循环遍历
	for (size_t i = 0; i < _size; i++) {
		if (_str[i] == c) {
			return i;
		}
	}
	//没找到，返回npos
	return npos;
}

//		2.查找字符串
size_t String::Find(const char*s) {
	char* pos = strstr(_str, s);
	if (pos) {
		return pos - _str;
	}
	return npos;
}

//14.重载+运算符
//		1.加一个字符
String String::operator+(const char c) {
	String tmp = *this;
	tmp += c;
	return tmp;
}
//		2.加一个字符串
String String::operator+(const char* s) {
	String tmp = *this;
	tmp += s;
	return tmp;
}
//		3.加对象
String String::operator+(const String& s) {
	String tmp = *this;
	tmp += s;
	return tmp;
}

//15.重载输出运算符
ostream& operator<< (ostream& _cout, const String& s) {
	//用迭代器
	const_Iterator it = s.begin();
	while (it != s.end()) {
		_cout << *it;
		it++;
	}
	return _cout;
}


//析构
String::~String() {
	//如果字符串不为空，就释放里边的值
	if (_str) {
		delete[] _str;
		_str = nullptr;
	}
}



void test1() {
	String s;
	//s.PushBack('a');
	//s.PushBack('b');
	//s.PushBack('c');
	//s.PushBack('d');
	
	//s.Print();

	String s2;
	s2 += "adfghj";
	s2.Print();
	cout << endl;

	//s2 += s;
	//s2.Print();
	//s2.Insert(1,'k');
	//s2.Print();
	//cout << endl;

	//s2.Insert(0, "1234");
	//s2.Print();
	//cout << endl;

	//String s3;
	//s3 += "!hello!";
	//s3.Print();
	//cout << endl;
	//s2.Insert(3, s3);
	//s2.Print();
	//
	//s2.Erase(0);
	//s2.Print();

	//s2.Erase(0, 2);
	//s2.Print();

	//cout << s2.Find('g') << endl;

	//cout << s2.Find("!h!kk");

	cout << s2;
}




int main() {
	test1();

	system("pause");
	return 0;
}