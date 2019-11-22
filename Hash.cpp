#include <stdio.h>
#include <map>
#include "Windows.h"
using namespace std;

char input[30000][100];			// �Է�
const int PN = 23;				// �Ҽ�

const int HASH_SIZE = 10000;	// �ؽ� ���̺� ũ�� (�ε���)
int hash_table[HASH_SIZE][30];	// �ؽ� ���̺� (�ε���)

int hash_size = 0;				// ���� ���̺� ��ġ
char hash_raw[30000][100];		// ���� ���̺�

// �񱳱� (STL)
map<char*, int> test;

// ���ڿ� ��
int y_strcmp(char a[], char b[]) {
	int i = 0, j = 0;
	while (a[i]) {
		if (a[i++] != b[j++]) {
			--i, --j;
			break;
		}
	}
	return (a[i] - b[j]);
}

// Ű ����
unsigned int get_key(char str[]) {
	unsigned int key = 0, p = 1;
	for (int i = 0; str[i] != 0; ++i) {
		key += (str[i] * p);
		p *= PN;
	}
	return (key % HASH_SIZE);
}

// �߰�
void add(char str[]) {
	int len;
	for (len = 0; str[len] != 0; ++len) {
		hash_raw[hash_size][len] = str[len];
	}
	hash_raw[hash_size][len] = 0;

	unsigned int key = get_key(str);
	int& size = hash_table[key][0];
	hash_table[key][++size] = hash_size;
	++hash_size;
}

// ���翩�� Ȯ��
int contain(char str[]) {
	unsigned int key = get_key(str);
	int size = hash_table[key][0];
	for (int i = 1; i <= size; i++) {
		int pos = hash_table[key][i];
		if (y_strcmp(hash_raw[pos], str) == 0) {
			return pos;
		}
	}
	return -1;
}

// ����
bool remove(char str[]) {
	unsigned int key = get_key(str);
	int& size = hash_table[key][0];
	for (int i = 1; i <= size; i++) {
		int pos = hash_table[key][i];
		if (y_strcmp(hash_raw[pos], str) == 0) {
			hash_table[key][i] = hash_table[key][size--];
			return true;
		}
	}
	return false;
}

int make_int(int min, int max) {
	return (rand() % (max - min)) + min;
}

char make_char() {
	int val = rand() % 52;
	if (val < 26) {
		return static_cast<char>('a' + val);
	}
	return static_cast<char>('A' + val - 26);
}

int main()
{
	int y_hash_time = 0;
	int stl_hash_time = 0;

	for (int i = 0; i < 30000; ++i) {
		int len = make_int(10, 100);
		for (int j = 0; j < len; ++j) {
			input[i][j] = make_char();
		}
		input[i][len] = 0;

		// ���� (y_hash)
		int y_add_begin = GetTickCount64();
		if (contain(input[i]) == -1) {
			add(input[i]);
		}
		int y_add_end = GetTickCount64();
		y_hash_time += (y_add_end - y_add_begin);

		// ���� (stl_hash)
		int stl_add_begin = GetTickCount64();
		test[input[i]] = i;
		int stl_add_end = GetTickCount64();
		stl_hash_time += (stl_add_end - stl_add_begin);

		if (i > 20000) {
			int cmd = make_int(0, 5);
			int index = make_int(0, i);
			if (cmd == 0) {
				// ���� (y_hash)
				int y_remove_begin = GetTickCount64();
				if (contain(input[index]) != -1) {
					remove(input[index]);
				}
				int y_remove_end = GetTickCount64();
				y_hash_time += (y_add_end - y_add_begin);

				// ���� (stl_hash)
				int stl_remove_begin = GetTickCount64();
				test.erase(input[index]);
				int stl_remove_end = GetTickCount64();
				stl_hash_time += (stl_remove_end - stl_remove_begin);
			}
			if (cmd == 1) {
				// Ž�� (y_hash)
				int y_contain_begin = GetTickCount64();
				int my_pos = contain(input[index]);
				int y_contain_end = GetTickCount64();
				y_hash_time += (y_contain_end - y_contain_begin);

				// Ž�� (stl_hash)
				int stl_contain_begin = GetTickCount64();
				map<char*, int>::iterator iter = test.find(input[index]);
				int stl_pos = -1;
				if (iter != test.end()) {
					stl_pos = iter->second;
				}
				int stl_contain_end = GetTickCount64();
				stl_hash_time += (stl_contain_end - stl_contain_begin);

				// ���� üũ
				if (my_pos != stl_pos) {
					printf("find error\n");
				}
			}
		}
	}

	int y_hash_size = 0;
	for (int i = 0; i < HASH_SIZE; ++i) {
		y_hash_size += hash_table[i][0];
	}
	if (y_hash_size != test.size()) {
		printf("remove error\n");
	}

	printf("y_hash : %d\n", y_hash_time);
	printf("stl_hash : %d\n", stl_hash_time);

	return 0;
}