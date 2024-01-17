template <typename T> 

class Node{
    public:
        T val;
        Node<T>* next;
        Node(T init_val) {
            val = init_val;
            next = NULL;
        }
};

template <typename T> 

class LinkedList {
    public:
        Node<T>* head;
        Node<T>* tail;
        int size;

        LinkedList() {
            head = NULL;
            tail = NULL;
            size = 0;
        }

        void insert(T val) {
            Node<T>* new_node = new Node(val);
            if (this->size != 0) {
                if (this->head == this->tail) {
                    this->head->next = new_node;
                    this->tail = new_node;
                } else {
                    this->tail->next = new_node;
                    this->tail = new_node;
                }
            } else {
                this->head = new_node;
                this->tail = new_node;
            }
            this->size += 1;
        }

        bool search(T val) {
            if (size == 0) {
                return false;
            }
            Node<T>* current_node = this->head;
            if (current_node->val.equals(val)) {
                return true;
            }
            while (current_node->next != NULL) {
                if (current_node->next->val.equals(val)) {
                    return true;
                } else {
                    current_node = current_node->next;
                }
            }
            return false;
        }

        void clear() {
            if (this->size > 1) {
                Node<T>* current_node = this->head;
                Node<T>* next_node = this->head->next;
                while (next_node != this->tail) {
                    delete(current_node);
                    current_node = next_node;
                    next_node = next_node->next;
                }
                delete(current_node);
                delete(next_node);
            }
            this->size = 0;
            this->head = NULL;
            this->tail = NULL;
        }
};
