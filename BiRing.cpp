#include "BiRing.h"

template<typename Key, typename Info>
BiRing<Key, Info>::BiRing() {
    sentinel.node = new Node();
    sentinel.node->next = sentinel.node;
    sentinel.node->prev = sentinel.node;
}

template<typename Key, typename Info>
BiRing<Key, Info>::BiRing(const BiRing& toCopy) {
    sentinel = new Node();
    for(BiRing<Key, Info>::iterator i = toCopy.begin(); i != toCopy.end(); ++i) {
        push_back(i.key(), i.info());
    }
}

template<typename Key, typename Info>
BiRing<Key, Info>::~BiRing() {
    clear();
    delete sentinel.node;
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
void BiRing<Key, Info>::clear() {
    BiRing<Key, Info>::iterator i = begin();
    while(i != end()) {
        i = remove(i);
    }
}

template<typename Key, typename Info>
typename BiRing<Key,Info>::iterator BiRing<Key, Info>::begin() const {
    return iterator(sentinel.node->next);
}

template<typename Key, typename Info>
typename BiRing<Key,Info>::iterator BiRing<Key, Info>::end() const {
    return sentinel;
}

template<typename Key, typename Info>
typename BiRing<Key,Info>::const_iterator BiRing<Key, Info>::cbegin() const {
    return const_iterator(sentinel.node->next);
}

template<typename Key, typename Info>
typename BiRing<Key,Info>::const_iterator BiRing<Key, Info>::cend() const {
    return const_iterator(sentinel.node);
}

template<typename Key, typename Info>
void BiRing<Key, Info>::push_front(Key key, Info info) {
    add(key, info, --end());
}

template<typename Key, typename Info>
void BiRing<Key, Info>::push_back(Key key, Info info) {
    add(key, info, begin());
}

template<typename Key, typename Info>
void BiRing<Key, Info>::pop_front() {
    remove(--end());
}

template<typename Key, typename Info>
void BiRing<Key, Info>::pop_back() {
    remove(begin());
}

template<typename Key, typename Info>
typename BiRing<Key, Info>::iterator BiRing<Key, Info>::find_key(Info info, int pos) const {
    for(BiRing<Key, Info>::iterator i = begin(); i != end(); ++i) {
        if(i.info() == info && !--pos) {
            return i;
        }
    }
    return end();
}

template<typename Key, typename Info>
typename BiRing<Key,Info>::iterator BiRing<Key, Info>::find_info(Key key, int pos) const {
    for(BiRing<Key, Info>::iterator i = begin(); i != end(); ++i) {
        if(i.key() == key && !--pos) {
            return i;
        }
    }
    return end();
}

template<typename Key, typename Info>
typename BiRing<Key,Info>::iterator BiRing<Key, Info>::add(Key key, Info info, const BiRing<Key, Info>::iterator& after) {
    Node* tmp = new Node();
    tmp->info = info;
    tmp->key = key;
    tmp->next = after.node->next;
    tmp->prev = after.node;
    after.node->next->prev = tmp;
    after.node->next = tmp;
    return iterator(tmp);
}

template<typename Key, typename Info>
typename BiRing<Key,Info>::iterator BiRing<Key, Info>::add(Key key, Info info, Key after, int pos) {
    for(BiRing<Key, Info>::iterator i = begin(); i != end(); ++i) {
        if(i.key() == after && !--pos) {
            return add(key, info, i);
        }
    }
    return end();
}

template<typename Key, typename Info>
typename BiRing<Key,Info>::iterator BiRing<Key, Info>::remove(Key key, int pos) {
    for(BiRing<Key, Info>::iterator i = begin(); i != end(); ++i) {
        if(i.key() == key && !--pos)  {
            return remove(i);
        }
    }
    return end();
}

template<typename Key, typename Info>
typename BiRing<Key,Info>::iterator BiRing<Key, Info>::remove(const iterator& x) {
    if(x != end()) {
        x.node->next->prev = x.node->prev;
        x.node->prev->next = x.node->next;
        iterator ret;
        ret.node = x.node->next;
        delete x.node;
        return ret;
    }
    return end();
}

