#pragma once
#include <iostream>

template<typename Key, typename Info>
class BiRing {  ///ALLOW DUPLICATES
        struct Node;
    public:
        class const_iterator;
        class iterator;

        BiRing();
        BiRing(const BiRing&);
        ~BiRing();
        BiRing& operator=(const BiRing&);
        void clear(); //doesnt clear sentinel
        iterator begin() const;
        iterator end() const;
        const_iterator cbegin() const;
        const_iterator cend() const;
        void push_front(Key, Info);
        void push_back(Key, Info);
        void pop_front();
        void pop_back();
        iterator find_key(Info info, int pos = 1) const;
        iterator find_info(Key key, int pos = 1) const;
        iterator add(Key key, Info info, const iterator& after); //what we add and after what in arguments
        iterator add(Key key, Info info, Key after, int pos = 1);
        iterator remove(Key key, int pos = 1); //returns iterator to next element after removed one , do nothing when invalid value
        iterator remove(const iterator&);
        template<typename K, typename I>
        friend std::ostream& operator<<(std::ostream&, const BiRing<K, I>&);

        class iterator { ///when 0 arguments, begin() and end() points to themselves with both iterators next and previous
            ///after .end()++; goes to next first elem
            friend class BiRing;
            Node* node;
            iterator(Node* node) { this->node = node; };
            public:
                iterator() { node = nullptr; };
                iterator& operator=(const iterator& s) { node = s.node; return *this; };
                iterator& operator++()       { node = node->next; return *this; };
                iterator& operator++(int)    { node = node->next; return *this; };
                iterator& operator--()       { node = node->prev; return *this; };
                iterator& operator--(int)    { node = node->prev; return *this; }
                iterator& operator+=(unsigned int n) { while(n--) {++(*this);} };
                iterator& operator-=(unsigned int n) { while(n--) {--(*this);} };
                bool operator==(const iterator& x) const { return node == x.node; };
                bool operator!=(const iterator& x) const { return node != x.node; };
                const Key& key() const { return node->key; };
                Info& info() const { return node->info; };
        };
        class const_iterator {
            friend class BiRing;
            Node* node;
            const_iterator(Node* node) { this->node = node; };
            public:
                const_iterator() { node = nullptr; };
                const_iterator& operator=(const const_iterator& s) { node = s.node; return *this; };
                const_iterator& operator++() { node = node->next; return *this; };
                const_iterator& operator++(int) { node = node->next; return *this; };
                const_iterator& operator--() { node = node->prev; return *this; };
                const_iterator& operator--(int) { node = node->prev; return *this; }
                const_iterator& operator+=(unsigned int n) { for(;n--;) {++(*this);} };
                const_iterator& operator-=(unsigned int n) { for(;n--;) {--(*this);} };
                bool operator==(const const_iterator& x) const { return node == x.node; };
                bool operator!=(const const_iterator& x) const { return node != x.node; };
                const Key& key() const { return node->key; };
                const Info& info() const { return node->info; };
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
std::ostream& operator<<(std::ostream& os, const BiRing<Key, Info>& x) {
    for(typename BiRing<Key, Info>::iterator i = x.begin(); i != x.end(); ++i) {
        os << "Key: " << i.key() << " Info: " << i.info() << std::endl;
    }
    return os;
}
