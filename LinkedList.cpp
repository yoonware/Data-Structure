#include <stdio.h>
#include <algorithm>
#include <list>
#include "Windows.h"
using namespace std;

// Size
const int NODE_SIZE = 30000;

// Test Command
const int PUSH_BACK     = 0;
const int PUSH_FRONT    = 1;
const int INSERT        = 2;
const int POP_BACK      = 3;
const int POP_FRONT     = 4;
const int ERASE         = 5;

struct NODE {
	int val;
	int prev;
	int next;
};

struct yList {
	int pos;
	int head = NODE_SIZE;
	int tail = NODE_SIZE + 1;
	NODE node[NODE_SIZE + 2];

	yList() {
		pos = 0;
		node[head].next = tail;
		node[tail].prev = head;
	}

	void push_back(int data) {
		node[pos].val = data;
		int prev = node[tail].prev;
		int next = node[prev].next;
		node[pos].prev = prev;
		node[prev].next = pos;
		node[pos].next = next;
		node[next].prev = pos;
		++pos;
	}

	void push_front(int data) {
		node[pos].val = data;
		int next = node[head].next;
		int prev = node[next].prev;
		node[pos].prev = prev;
		node[prev].next = pos;
		node[pos].next = next;
		node[next].prev = pos;
		++pos;
	}

	void insert(int p, int data) {
		node[pos].val = data;
		int next = node[head].next;
		for (int i = 0; i < p; ++i) {
			next = node[next].next;
		}
		int prev = node[next].prev;
		node[pos].prev = prev;
		node[prev].next = pos;
		node[pos].next = next;
		node[next].prev = pos;
		++pos;
	}

	void pop_back() {
		int target = node[tail].prev;
		int prev = node[target].prev;
		int next = node[target].next;
		node[prev].next = next;
		node[next].prev = prev;
	}

	void pop_front() {
		int target = node[head].next;
		int prev = node[target].prev;
		int next = node[target].next;
		node[prev].next = next;
		node[next].prev = prev;
	}

	void erase(int p) {
		int target = node[head].next;
		for (int i = 0; i < p; ++i) {
			target = node[target].next;
		}
		int prev = node[target].prev;
		int next = node[target].next;
		node[prev].next = next;
		node[next].prev = prev;
	}
};

yList y_list;
list<int> stl_list;
int test_cmd[NODE_SIZE][3];

int main()
{
	// Initialize test_cmd
	int cur_size = 0;
	for (int i = 0; i < NODE_SIZE; ++i) {
		if (i < NODE_SIZE / 3) {
			test_cmd[i][0] = rand() % 2;
		}
		else {
			test_cmd[i][0] = rand() % 6;
		}
		switch (test_cmd[i][0]) {
		case PUSH_BACK:
		case PUSH_FRONT: {
			test_cmd[i][1] = rand();
			++cur_size;
			break;
		}
		case INSERT: {
			test_cmd[i][1] = rand() % cur_size;
			test_cmd[i][2] = rand();
			++cur_size;
			break;
		}
		case POP_BACK:
		case POP_FRONT: {
			--cur_size;
			break;
		}
		case ERASE: {
			test_cmd[i][1] = rand() % cur_size;
			--cur_size;
			break;
		}
		}
	}

	// Operate y_list
	int y_list_begin = GetTickCount64();
	for (int i = 0; i < NODE_SIZE; ++i) {
		switch (test_cmd[i][0]) {
		case PUSH_BACK: {
			y_list.push_back(test_cmd[i][1]);
			break;
		}
		case PUSH_FRONT: {
			y_list.push_front(test_cmd[i][1]);
			break;
		}
		case INSERT: {
			y_list.insert(test_cmd[i][1], test_cmd[i][2]);
			break;
		}
		case POP_BACK: {
			y_list.pop_back();
			break;
		}
		case POP_FRONT: {
			y_list.pop_front();
			break;
		}
		case ERASE: {
			y_list.erase(test_cmd[i][1]);
			break;
		}
		}
	}
	int y_list_end = GetTickCount64();

	// Operate stl_list
	int stl_list_begin = GetTickCount64();
	for (int i = 0; i < NODE_SIZE; ++i) {
		switch (test_cmd[i][0]) {
		case PUSH_BACK: {
			stl_list.push_back(test_cmd[i][1]);
			break;
		}
		case PUSH_FRONT: {
			stl_list.push_front(test_cmd[i][1]);
			break;
		}
		case INSERT: {
			list<int>::iterator it = stl_list.begin();
			for (int k = 0; k < test_cmd[i][1]; ++k) {
				++it;
			}
			stl_list.insert(it, test_cmd[i][2]);
			break;
		}
		case POP_BACK: {
			stl_list.pop_back();
			break;
		}
		case POP_FRONT: {
			stl_list.pop_front();
			break;
		}
		case ERASE: {
			list<int>::iterator it = stl_list.begin();
			for (int k = 0; k < test_cmd[i][1]; ++k) {
				++it;
			}
			stl_list.erase(it);
			break;
		}
		}
	}
	int stl_list_end = GetTickCount64();

	// Check Speed
	printf("y_list : %d\n", y_list_end - y_list_begin);
	printf("stl_list : %d\n", stl_list_end - stl_list_begin);

	// Check Accuracy
	list<int>::iterator it = stl_list.begin();
	int cur = y_list.node[y_list.head].next;
	while (it != stl_list.end()) {
		if (*it != y_list.node[cur].val) {
			printf("Error\n");
		}
		++it;
		cur = y_list.node[cur].next;
	}

	return 0;
}