
#include <iostream>
#include <algorithm>
using namespace std;

namespace MySTL
{
    template <typename T>
    class bidirectionaliterator
    {
        
    };


	template <typename T>
	class vector
	{
		T* arr;
		T* itr;
		int length;
		int capacity;
	public:
		vector(int n = 1) :arr(new T[n]), itr(NULL), length(0), capacity(1) {};

		T operator[](int n) { return arr[n]; }

		bool is_empty() { return length != 0; }

		int get_length() { return length; }

		T* begin() { return &arr[0]; }

		T* end() { return &arr[length]; }

		void push_back(T data)
		{
			if (length + 1 >= capacity)
			{
				T* temp = new T[capacity * 2];
				capacity *= 2;
				for (int i = 0;i < length;i++)
					temp[i] = arr[i];
				delete[] arr;
				arr = temp;
			}
			arr[length++] = data;
		}

		T pop_back()
		{
			return arr[--length];
		}

		void print()
		{
			for (int i = 0;i < length;i++)
				cout << arr[i] << " ";
			cout << endl;
		}
	};


	template <typename T>
	struct Node
	{
		T data;
		Node* prev;
		Node* next;
		Node(T newdata) :data(newdata), prev(NULL), next(NULL) {};
	};


	template <typename T>
	class list
	{
		Node<T>* head, * tail;
		Node<T>* itr;
		int length;
	public:
		list() :head(NULL), tail(NULL), itr(NULL), length(0) {};

		// 순서 맞추기
		void append(T data)
		{
			Node<T>* newnode = new Node<T>(data);
			if (head == NULL)
			{
				head = newnode;
				tail = newnode;
			}
			else
			{
				tail->next = newnode;
				newnode->prev = tail;
				tail = newnode;
			}
			length++;
		}

		void remove(Node<T>* target)
		{
			if (target == head)
			{
				target->next->prev = NULL;
				head = target->next;
				delete target;
			}
			else if (target == tail)
			{
				target->prev->next = NULL;
				tail = target->prev;
				delete target;
			}
			else
			{
				target->prev->next = target->next;
				target->next->prev = target->prev;
				delete target;
			}
			length--;
		}

		Node<T>* find(T target)
		{
			for (itr = head;itr != NULL;itr = itr->next)
			{
				if (itr->data == target) return itr;
			}
			return NULL;
		}

		void erase(T target)
		{
			while ((itr = find(target)) != NULL)
			{
				remove(itr);
			}
		}

		void print()
		{
			for (itr = head;itr != NULL;itr = itr->next)
			{
				cout << itr->data << " ";
			}
			cout << endl;
		}
	};

	template <typename T>
	class stack
	{
		Node<T>* head;
		Node<T>* itr;
		int length;
	public:
		stack() :head(NULL), itr(NULL), length(0) {};

		int get_length() { return length; }

		bool is_empty() { return head == NULL; }

		void push(T data)
		{
			Node<T>* newnode = new Node<T>(data);
			if (head == NULL)
			{
				head = newnode;
			}
			else
			{
				newnode->next = head;
				head = newnode;
			}
			length++;
		}

		T pop()
		{
			if (head == NULL)
			{
				cout << "Empty stack" << endl;
				exit(-1);
			}
			T temp = head->data;
			Node<T>* newhead = head->next;
			delete head;
			head = newhead;
			return temp;
			length--;
		}

		void print()
		{
			for (itr = head;itr != NULL;itr = itr->next)
			{
				cout << itr->data << " ";
			}
			cout << endl;
		}
	};

	template <typename T>
	class dequeue
	{
		Node<T>* head, tail;
		Node<T>* itr;
		int length;
	public:
		dequeue() :head(NULL), tail(NULL), itr(NULL), length(0) {};

		void push_front(T data)
		{
			Node<T>* newnode = new Node<T>(data);
			if (head == NULL)
			{
				head = newnode;
				tail = newnode;
			}
			else
			{
				newnode->next = head;
				head->prev = newnode;
				head = newnode;
			}
		}

		void push_back(T data)
		{
			Node<T>* newnode = new Node<T>(data);
			if (tail == NULL)
			{
				head = newnode;
				tail = newnode;
			}
			else
			{
				tail->next = newnode;
				newnode->prev = tail;
				tail = newnode;
			}
		}

		T pop_front()
		{
			if (head == NULL)
			{
				cout << "Empty dequeue" << endl;
				return;
			}
			if (head == tail)
			{
				T deldata = head->data;
				delete head;
				head = tail = NULL;
				return deldata;
			}
			else
			{
				T deldata = head->data;
				Node<T>* temp = head;
				head->next->prev = NULL;
				head = head->next;
				delete temp;
				return deldata;
			}
		}

		T pop_back()
		{
			if (tail == NULL)
			{
				cout << "Empty dequeue" << endl;
				return;
			}
			if (head == tail)
			{
				T deldata = head->data;
				delete head;
				head = tail = NULL;
				return deldata;
			}
			else
			{
				T deldata = tail->data;
				Node<T>* temp = tail;
				tail->prev->next = NULL;
				tail = tail->prev;
				delete temp;
				return deldata;
			}
		}
	};

	// maximum heap
	class priority_queue
	{
		int numofdata;
		int* heap;

		void swap(int& a, int& b)
		{
			int temp = a;
			a = b;
			b = temp;
		}

	public:
		priority_queue(int n) :numofdata(0), heap(new int[n]) 
		{
			memset(heap, 0, sizeof(int) * n);
		};

		bool is_empty() { return !numofdata; }

		void insert(int data)
		{
			heap[++numofdata] = data;
			int idx = numofdata;
			while (idx > 1 && heap[idx] > heap[idx / 2])
			{
				swap(heap[idx], heap[idx / 2]);
				idx /= 2;
			}
		}
		int pop()
		{
			int deldata = heap[1];
			heap[1] = heap[numofdata];
			heap[numofdata--] = 0;
			int idx = 1;
			while (idx < numofdata && heap[idx] < max(heap[idx * 2], heap[idx * 2 + 1]))
			{
				if (heap[idx * 2] > heap[idx * 2 + 1])
				{
					swap(heap[idx], heap[idx * 2]);
					idx = idx * 2;
				}
				else
				{
					swap(heap[idx], heap[idx * 2 + 1]);
					idx = idx * 2 + 1;
				}
			}
			return deldata;
		}
	};

}

int main()
{
	auto pqueue = MySTL::priority_queue(100);
	pqueue.insert(5);
	pqueue.insert(2);
	pqueue.insert(9);
	pqueue.insert(6);
	pqueue.insert(12);
	for (int i = 1;i <= 3;i++)
	{
		cout << pqueue.pop() << " ";
	}
	pqueue.insert(10);
	for (int i = 1;i <= 3;i++)
	{
		cout << pqueue.pop() << " ";
	}
}
