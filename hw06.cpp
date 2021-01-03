// Grant Norton
// HW 06
// Due 7/24/2019

#include<iostream>
#include<string>
#include<array>
using namespace std;



class ERHeap {
	private:
		struct Node {
			int priority;
			string name;
			string description;
		};
		Node* heap;
		int capacity;
		int bottom;

		void ReHeapUp();
		void ReHeapDown();

	public:
		ERHeap(int s);
		~ERHeap();
		void enqueue(string name, string desc, int pri);
		void dequeue(string& name);
};


ERHeap::ERHeap(int s) {
	capacity = s;
	bottom = -1;
	cout << "bottom before node: " << bottom << endl;
	heap = new Node[capacity];
	cout << "bottom: " << bottom << endl;
}

ERHeap::~ERHeap() {
	delete[] heap;
}

void ERHeap::enqueue(string name, string desc, int pri) {
	if (bottom == capacity - 1) {
		int oldCap = capacity;
		capacity = capacity * 2;
		Node* temp = new Node[capacity];
		for (int i = 0; i < oldCap; i++) {
			temp[i] = heap[i];
		}
		delete[] heap;
		heap = temp;
	}
	bottom++;
	heap[bottom].name = name;
	heap[bottom].description = desc;
	heap[bottom].priority = pri;
	ReHeapUp();
	cout << "capacity: " << capacity << endl;
	cout << "bottom: " << bottom << endl;
}

void ERHeap::dequeue(string& name) {
	if(bottom >= 0){
		name = heap[0].name;
		int j = 0;
		while (j < bottom) {
			heap[j] = heap[j + 1];
			j++;
		}
		bottom--;
		ReHeapDown();
	}
}

void ERHeap::ReHeapUp() {
	int i = bottom;
	while (i != 0) {
		int p = (i - 1) / 2;
		if (heap[i].priority > heap[p].priority) {
			Node temp = heap[i];
			heap[i] = heap[p];
			heap[p] = temp;
		}
		i = p;
	}
}

void ERHeap::ReHeapDown() {
	int i = 0;
	int bc;
	while (i < bottom)
	{
		int lc = 2 * i + 1;
		int rc = 2 * i + 2;
		if (lc <= bottom) {
			if (lc == bottom)
				bc = lc;
			else {
				if (heap[lc].priority > heap[rc].priority)
					bc = lc;
				else
					bc = rc;
			}
		}
		else {
			return;
		}
		if (heap[i].priority < heap[bc].priority) {
			swap(heap[i], heap[bc]);
			i = bc;
		}
		else
			return;
	}
}



int main() {

	ERHeap heap(2);

	char choice;
	

	do
	{
		cout << "(A)dd patient" << endl;
		cout << "(N)ext patient" << endl;
		cout << "(Q)uit" << endl << ":]";
		cin >> choice;
		cin.ignore();
		choice = tolower(choice);
		cout << endl;

		if (choice == 'a') {
			string name;
			string desc;
			int pri;

			cout << "Enter patient's name: ";
			getline(cin, name);
			cout << "Enter compaint: ";
			getline(cin, desc);
			cout << "Enter priority: ";
			cin >> pri;
			heap.enqueue(name, desc, pri);
			cout << endl;
		}

		else if (choice == 'n') {
			string name;
			cout << "Next patient: ";
			heap.dequeue(name);
			cout << name;
			cout << endl << endl;
		}

	} while (choice != 'q');


	return 0;
}