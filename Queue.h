template<class T>
class Node
{
	public:
		
		T Data;
		Node* next;
};

template<class T>
struct Queue
{
	Node<T>* head;
	Node<T>* last;

	public:

		Queue()
		{
			head = NULL;
			last = NULL;
		}

		~Queue()
		{
			Node<T>* temp = new Node<T>;
			temp = head;

			while (head != NULL)
			{
				temp = head;
				head = head->next;;
				delete temp;
			}

			last = NULL;
		}

		bool IsEmpty() const
		{
			if (head == NULL)
				return true;

			return false;
		}

		void enqueue(const T& d)
		{
			if (head == NULL)
			{
				head = new Node<T>;
				head->Data = d;
				head->next = NULL;
				last = head;
			}

			else
			{
				last->next = new Node<T>;
				last = last->next;
				last->Data = d;
				last->next = NULL;
			}
		}
		
		T dequeue()
		{
			Node<T> *temp = new Node<T>;
			T d = head->Data;

			temp = head;
			head = head->next;

			delete temp;

			return d;
		}

		void clear()
		{
			Node<T>* temp = new Node<T>;
			temp = head;

			while (head != NULL)
			{
				temp = head;
				head = head->next;;
				delete temp;
			}

			last = NULL;
		}
};