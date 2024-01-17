#include "linkedlist.h"

template <typename T>
class HashMap {
    public:
        int size;
        LinkedList<T>* map;
        HashMap(int init_size = 0) {
            size = init_size;
            map = new LinkedList[init_size];
        }

        int hash(T point) {
            return abs((31*(point.x)+17*(point.y)) % this->size);
        }

        void insert(T point) {
            int table = hash(point);
            this->map[table].insert(point);
        }

        bool search(T point) {
            int table = hash(point);
            return this->map[table].search(point);
        }
        
        void clear() {
            for (int i = 0; i < this->size;i++) {
                map[i].clear();
            }
        }
};