#include <iostream>

using namespace std;

template<typename Key, typename Info>
class BiRing {  ///ALLOW DUPLICATES
    public:
        BiRing();
        BiRing(const BiRing&);
        ~BiRing();
        class const_iterator;
        class iterator;
        BiRing& operator=(const BiRing&);
        void clear(); //doesnt clear sentinel
        iterator begin() const;
        iterator end() const;
        void push_front(Key, Info);
        void push_back(Key, Info);
        void pop_front();
        void pop_back();
        iterator find_key() const;
        iterator find_info() const;
        iterator add(); //what we add and after what in arguments
        iterator remove(); //returns iterator to next element after removed one , do nothing when invalid value
        const_iterator cbegin() const; //const iterator returned
        const_iterator cend() const;
        friend ostream& operator<<(ostream&, const BiRing<Key, Info>&);

        class iterator{ ///when 0 arguments, begin() and end() points to themselves with both iterators next and previous
            ///after .end()++; goes to next first elem
            Node* node;
            public:
                const_iterator& operator++();
                const_iterator& operator++(int);
                const_iterator& operator--();
                const_iterator& operator+=(unsigned int);
                const_iterator& operator-=(unsigned int);
                bool operator==(const const_iterator&) const;
                bool operator!=(const const_iterator&) const;
                const Key& key() const;
                Info& info() const;
        };
        class const_iterator{
            Node* node;
            public:
                const_iterator& operator++();
                const_iterator& operator++(int);
                const_iterator& operator--();
                const_iterator& operator+=(unsigned int);
                const_iterator& operator-=(unsigned int);
                bool operator==(const const_iterator&) const;
                bool operator!=(const const_iterator&) const;
                const Key& key() const;  //returns const reference
                const Info& info() const;
        };
    private:
        iterator sentinel;
        struct Node {
            Key key;
            Info info;
            Node* next;
            Node* prev;
            Node() : next(this), prev(this) {};
        };
};

template<typename Key, typename Info>
BiRing<Key, Info>::BiRing() {
    sentinel = new Node();
    sentinel.node->next = this;
    sentinel.node->prev = this;
}

template<typename Key, typename Info>
BiRing<Key, Info>::BiRing(const BiRing& toCopy) {
    sentinel = new Node();
    for(BiRing<Key, Info>::iterator i = toCopy.begin(); i != toCopy.end(); ++i) {
        push_back(i.key(), i.info());
    }
}

template<typename Key, typename Info>
BiRing<Key, Info>& BiRing<Key, Info>::operator=(const BiRing<Key, Info>& toCopy) {
    if(this == &toCopy) return *this;
    clear();
    for(BiRing<Key, Info>::iterator i = toCopy.begin(); i != toCopy.end(); ++i) {
        push_back(i.key(), i.info());
    }
    return *this;
}

template<typename Key, typename Info>
void BiRing<Key, Info>::push_back(Key key, Info info) {
    Node* temp = new Node();
    temp->next = begin().node;
    begin().node->prev = temp;
    temp->prev = end().node;
    end().node->next = temp;

}


template<typename Key, typename Info>
ostream& operator<<(ostream&, const BiRing<Key, Info>& x) {

}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
