#include <iostream>
using namespace std;

class yString {

// ����
private:
	char* content;
	int len;

// ������
public:
	// ����
	yString(char c) {
		len = 1;
		content = new char[1];
		content[0] = c;
	}

	// ���ڿ�
	yString(const char* str) {
		len = 0;
		while (str[len] != '\0') len++;
		content = new char[len];
		for (int i = 0; i < len; i++)
			content[i] = str[i];
	}

	// ����
	yString(const yString& str) {
		len = str.len;
		content = new char[len];
		for (int i = 0; i != len; i++)
			content[i] = str.content[i];
	}

	// �Ҹ���
	~yString() {
		delete[] content;
	}

// ������ �����ε�
public:
	// []
	char& operator[](int i) {
		return content[i];
	}

	// = (���ڿ�)
	void operator=(const char* str) {
		delete[] content;
		len = 0;
		while (str[len] != '\0') len++;
		content = new char[len];
		for (int i = 0; i < len; i++)
			content[i] = str[i];
	}

	// = (����)
	void operator=(const yString& str) {
		delete[] content;
		len = str.len;
		content = new char[len];
		for (int i = 0; i != len; i++)
			content[i] = str.content[i];
	}

	// +=
	void operator+=(const char* str2) {
		int len2 = 0;
		while (str2[len2] != '\0') len2++;

		int lenAll = len + len2;
		char* temp = new char[lenAll];
		for (int i = 0; i < len; i++)
			temp[i] = content[i];
		for (int i = len, j = 0; i < lenAll; i++, j++)
			temp[i] = str2[j];

		delete[] content;
		len = lenAll;
		content = new char[len];

		for (int i = 0; i < len; i++)
			content[i] = temp[i];
		delete[] temp;
	}

// �Լ�
public:
	// ���ڿ� ���� ��ȯ
	int length() const {
		return len;
	}

	// ���ڿ� ���
	void println() const {
		for (int i = 0; i != len; i++)
			cout << content[i];
		cout << std::endl;
	}
};

// ��� ��
int main() {

	// ������
	yString s1("Y");        s1.println();
	yString s2("Yoonware"); s2.println();
	yString s3(s2);         s3.println();

	// ������ �����ε� [], =, +=
	s1[0] = 'y';            s1.println();
	s2 = "Yoon's";          s2.println();
	s3 = s2;                s3.println();
	s3 += " Software";      s3.println();

	return 0;
}