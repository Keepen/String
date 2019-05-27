#pragma once
#include <iostream>
using namespace std;
typedef char* Iterator;
typedef const char* const_Iterator;
size_t npos = -1;		//��ʾ�Ƿ����±�
class String {
private:
	char* _str;
	size_t _size;
	size_t _capacity;

public:
	//1.��ʼ��
	String();
	//2.����_size
	void Resize(size_t n, char c = '\0');

	//3.����
	void Reserve(size_t n);

	//4.β���ַ�
	void PushBack(char c);

	//5.����ַ���
	void Print();

	//6.begin������
	Iterator begin();

	//7.end������
	Iterator end();

	//8.const begin������
	const_Iterator begin() const;

	//9.const end ������
	const_Iterator end() const;

	//10.����+=�ٲ�����,
	//   1.β��һ���ַ�
	String& operator+=(const char c);

	//   2.β��һ���ַ���
	String& operator+=(const char* s);

	//	3.β��һ������
	String& operator+=(const String& s);


	//11.��posλ�ô�����Ԫ��
	//		1.�����ַ�
	void Insert(size_t pos, const char c);

	//		2.�����ַ���
	void Insert(size_t pos, const char* s);

	//		3.����һ������
	void Insert(size_t pos, const String& s);

	//12.����Ԫ��
	//		1.����posλ�ô���һ���ַ�
	void Erase(size_t pos);

	//		2.����posλ�ú�n���ַ�
	void Erase(size_t pos, size_t n);

	//13.����
	//		1.����һ���ַ�
	size_t Find(const char c);
	//		2.�����ַ���
	size_t Find(const char* s);

	//14.����+������
	//		1.��һ���ַ�
	String operator+(const char c);
	//		2.���ַ���
	String operator+(const char* s);
	//		3.�Ӷ���
	String operator+(const String& s);


	//15.������������
;	friend ostream& operator<<(ostream& _cout, const String& s);

	//����
	~String();
};
