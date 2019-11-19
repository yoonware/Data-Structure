#include <iostream>
using namespace std;

class yString {

// 변수
private:
	char* content;
	int len;

// 생성자
public:
	// 문자
	yString(char c) {
		len = 1;
		content = new char[1];
		content[0] = c;
	}

	// 문자열
	yString(const char* str) {
		len = 0;
		while (str[len] != '\0') len++;
		content = new char[len];
		for (int i = 0; i < len; i++)
			content[i] = str[i];
	}

	// 복사
	yString(const yString& str) {
		len = str.len;
		content = new char[len];
		for (int i = 0; i != len; i++)
			content[i] = str.content[i];
	}

	// 소멸자
	~yString() {
		delete[] content;
	}

// 연산자 오버로딩
public:
	// []
	char& operator[](int i) {
		return content[i];
	}

	// = (문자열)
	void operator=(const char* str) {
		delete[] content;
		len = 0;
		while (str[len] != '\0') len++;
		content = new char[len];
		for (int i = 0; i < len; i++)
			content[i] = str[i];
	}

	// = (복사)
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

// 함수
public:
	// 문자열 길이 반환
	int length() const {
		return len;
	}

	// 문자열 출력
	void println() const {
		for (int i = 0; i != len; i++)
			cout << content[i];
		cout << std::endl;
	}
};

// 사용 예
int main() {

	// 생성자
	yString s1("Y");        s1.println();
	yString s2("Yoonware"); s2.println();
	yString s3(s2);         s3.println();

	// 연산자 오버로딩 [], =, +=
	s1[0] = 'y';            s1.println();
	s2 = "Yoon's";          s2.println();
	s3 = s2;                s3.println();
	s3 += " Software";      s3.println();

	return 0;
}