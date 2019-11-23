const int SIZE = 10000;

int parent[SIZE];
int nodeCnt[SIZE];

void init() {
	for (int i = 0; i < SIZE; i++) {
		parent[i] = i;
		nodeCnt[i] = 1;
	}
}

int find(int idx) {
	if (parent[idx] == idx) {
		return idx;
	}
	return parent[idx] = find(parent[idx]);
}

void merge(int c, int p) {
	c = find(c);
	p = find(p);
	parent[c] = p;
	nodeCnt[p] += nodeCnt[c];
}