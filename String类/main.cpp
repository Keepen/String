#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "String.h"
using namespace std;

//1.���캯��
String::String() {
	_str = '\0';
	_size = 0;
	_capacity = 0;
}

//2.����size
void String::Resize(size_t n,char c) {
	//1.���n<_size,ֱ�Ӹ�ֵ�����油'\0'
	if (n < _size) {
		_size = n;
		_str[n] = '\0';
		return;
	}
	//2.��Ҫ����
	if (n > _capacity) {
		Reserve(n);
	}
	//��_size��ʼ��ֵc
	for (size_t i = _size; i < n; i++) {
		_str[i] = c;
	}
	_str[n] = '\0';
}

//3.����
void String::Reserve(size_t n) {
	//1.���capacityʽ��0���͸���ʼֵ15
	if (_capacity == 0) {
		_str = new char[15];
		_capacity = 15;
	}
	//2.capacity��ֵ��ֻ�ǲ�����,��Ҫ��������
	else {
		String s2;
		s2._str = new char[_capacity * 2];
		s2._capacity = 2 * _capacity;
		//��������
		strcpy(s2._str, _str);
		delete[] _str;
		_str = s2._str;
	}
}

//4.β���ַ�
void String::PushBack(char c) {
	//1.���ж��Ƿ���Ҫ����
	if (_size == _capacity) {
		Reserve(_size);
	}
	//������ϣ�����ѹ������Ҫ����
	_str[_size++] = c;
	_str[_size] = '\0';
}

//5.���
void String::Print() {
	////��Χfor:��Ҫ����ʵ�ֵ�����
	//for (auto e : _str) {
	//	cout << e;
	//}
	//cout << endl;
	for (size_t i = 0; i < _size; i++) {
		cout << _str[i];
	}
	cout << endl;
}

//6.begin�����������ص�һ����Ч�ַ���λ��
Iterator String::begin() {
	if (_str) {
		return _str;
	}
	return nullptr;
}

//7.end��������������Ч�ַ��ĺ�һ���ַ���λ��
Iterator String::end() {
	if (_str) {
		return _str + strlen(_str);
	}
	return nullptr;
}

//8.const begin������
const_Iterator String::begin()const {
	return _str;
}

//9.const end ������
const_Iterator String::end()const {
	return _str + strlen(_str);
}

//10.����+= ������
//		1.β��һ���ַ�
String& String::operator+=(const char c) {
	//�ж��Ƿ�Ҫ����
	if (_size == _capacity) {
		//��������
		Reserve(_size);
	}
	//Ҫô��������ϣ�Ҫô�Ǳ����͹�
	//ֱ�ӽ��и�ֵ��������
	_str[_size++] = c;
	_str[_size] = '\0';
	return *this;
}

//		2.β��һ���ַ���
String& String::operator+=(const char* s) {
	//���ж��Ƿ���Ҫ����
	size_t len = strlen(s);
	if (_size + len >= _capacity) {
		Reserve(_size + len);
	}
	//Ҫô��������ϣ�Ҫô�Ǳ����͹�
	//ֱ�ӽ���β��
	strcpy(_str + _size, s);
	_size += len;		//ע�����_size��ֵ
	return *this;
}

//		3.β��һ������
String& String::operator+=(const String& s) {
	//���ж��Ƿ���Ҫ����
	if (_size + s._size >= _capacity) {
		Reserve(_size + s._size);
	}
	//�������
	strcpy(_str + _size, s._str);
	_size += s._size;
	return *this;
}



//11.��posλ�ô�����
//		1.һ���ַ�
void String::Insert(size_t pos,  const char c) {
	//����Ԫ�أ�����Ҫ��������Ԫ��������һ��
	//�����ȿ�����������
	if (_size == _capacity) {
		Reserve(_size);
	}
	_size++;
	//������ϻ����Ǳ���͹�,�Ӻ���ǰ����
	for (size_t i = _size+1; i > pos; i--) {
		_str[i] = _str[i - 1];
	}
	_str[pos] = c;

}

//		2.����һ���ַ���
void String::Insert(size_t pos, const char* s) {
	//���ж��Ƿ�����
	size_t len = strlen(s);
	if (_size + len >= _capacity) {
		Reserve(_size + len);
	}
	//�������,���߱����͹�
	//��������	
	//int tmp = _size + len;
	for (size_t i = _size + len;i>=pos+len; i--) {
		_str[i] = _str[i - len];
	}
	//��������
	for (size_t i = pos, j = 0; i < pos + len, j < len; i++, j++) {
		_str[i] = s[j];		
	}
	_size += len;
}

//		3.����һ������
void String::Insert(size_t pos, const String& s) {
	//���ж϶��������Ƿ�Ϊ��
	if (s._size == 0) {
		return;
	}

	//�ж��Ƿ�����
	if (_size + s._size >= _capacity) {
		Reserve(_size + s._size);
	}
	//�������
	//��������
	for (size_t i = _size + s._size; i >= pos+s._size; i--) {
		_str[i] = _str[i - s._size];
	}

	//��������
	for (size_t i = pos, j = 0; i < pos + s._size, j < s._size; i++, j++) {
		_str[i] = s._str[j];
	}
	_size += s._size;
	_str[_size] = '\0';
}

//12.ɾ������,����Ԫ�أ����ı�������С
//		1.����posλ�õ�һ���ַ�
void String::Erase(size_t pos) {
	//���ж��Ƿ�Ϸ�
	if (pos > _size || pos < 0) {
		return;
	}
	//����Ϸ�������ɾ������
	//��posλ�õ�Ԫ�ض���ǰ�ƶ�һ��
	while (pos<_size) {
		_str[pos++] = _str[pos + 1];
	}
	_size--;
}

//		2.����posλ�ú��n���ַ�
void String::Erase(size_t pos, size_t n) {
	if (pos >= _size || pos + n >= _size) {
		return;
	}
	//��������
	for (size_t i = pos; i < pos + n; i++) {
		_str[i] = _str[i + n];
	}
	_size -= n;
}

//13.����
//		1.����һ���ַ�
size_t String::Find(const char c) {
	//ѭ������
	for (size_t i = 0; i < _size; i++) {
		if (_str[i] == c) {
			return i;
		}
	}
	//û�ҵ�������npos
	return npos;
}

//		2.�����ַ���
size_t String::Find(const char*s) {
	char* pos = strstr(_str, s);
	if (pos) {
		return pos - _str;
	}
	return npos;
}

//14.����+�����
//		1.��һ���ַ�
String String::operator+(const char c) {
	String tmp = *this;
	tmp += c;
	return tmp;
}
//		2.��һ���ַ���
String String::operator+(const char* s) {
	String tmp = *this;
	tmp += s;
	return tmp;
}
//		3.�Ӷ���
String String::operator+(const String& s) {
	String tmp = *this;
	tmp += s;
	return tmp;
}

//15.������������
ostream& operator<< (ostream& _cout, const String& s) {
	//�õ�����
	const_Iterator it = s.begin();
	while (it != s.end()) {
		_cout << *it;
		it++;
	}
	return _cout;
}


//����
String::~String() {
	//����ַ�����Ϊ�գ����ͷ���ߵ�ֵ
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