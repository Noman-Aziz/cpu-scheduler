template<class T>
class Node1
{
	public:
		
		T Data;
		Node1* next;
};

template<class T>
struct MinHeap
{
	Node1<T>* head;
	Node1<T>* last;

	public:

		MinHeap()
		{
			head = NULL;
			last = NULL;
		}

		~MinHeap()
		{
			Node1<T>* temp = new Node1<T>;
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

		void insert(T& d)
		{
			if (head == NULL)
			{
				head = new Node1<T>;
				head->Data = d;
				head->next = NULL;
				last = head;
			}

			else
			{
                if(d < head->Data)
                {
                    T swap = head->Data ;
                    head->Data = d;

       				last->next = new Node1<T>;
	            	last = last->next;
	            	last->Data = swap;
		            last->next = NULL;
                }

                else
                {
    				last->next = new Node1<T>;
	    			last = last->next;
		    		last->Data = d;
			    	last->next = NULL;                    
                }
                
			}
		}
		
		T remove()
		{
			Node1<T> *temp = new Node1<T> ;
			T d = head->Data;

			temp = head;
			head = head->next;

			delete temp;

			if(head==NULL)
				return d ;

            T swap;

            for( temp = head->next ; temp != NULL ; temp = temp->next )
            {
                if(temp->Data < head->Data)
                {
                    swap = head->Data;
                    head->Data = temp->Data;
                    temp->Data = swap;
                }
            }

			return d;
		}

		void clear()
		{
			Node1<T>* temp = new Node1<T>;
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