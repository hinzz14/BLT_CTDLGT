#ifndef DOUBLELIST_CPP
#define DOUBLELIST_CPP
#include"dnode.cpp"
#include<bits/stdc++.h>
using namespace std;
template <class F,class S, class A>
class Doublelist {
    private:
        Node<F,S,A> *header;
        Node<F,S,A> *trailer;
        
    public:
        Doublelist(){
            header = NULL;
            trailer = NULL;
        }
        Node<F,S,A> *pushback(F ch, S c, A t){
            Node<F,S,A> *q;
            q = new Node<F,S,A>;
            q->setdad(ch);
            q->setson(c);
            q->setage(t);
            q->setNext(nullptr);
            if(header == NULL){
                header = q;
                trailer = q;
            }
           else{
                trailer ->setNext(q);
                q->setPre(trailer);
                trailer = q;
            }
            return q;
        }
        Node<F,S,A> *pushfront(F ch, S c, A t){
            Node<F,S,A> *q;
            q = new Node<F,S,A>;
            q->setdad(ch);
            q->setson(c);
            q->setage(t);
            q->setPre(nullptr);
            if(header == NULL){
                header = q;
                trailer = q;
            }
           else{
                header ->setPre(q);
                q->setNext(header);
                header = q;
            }
            return q;
        }
        void push(int n){
            for (int i = 0; i < n; ++i) {
                string father, child;
                int age;
                cin >> father >> child >> age;
                if(father == "Ted") pushfront(father,child,age);
                else pushback(father, child, age);
            }
        }
        void remove(Node<F, S, A>* node) {
            if (node) {
                if (node == header) {
                    header = node->getNext();
                }
                if (node == trailer) {
                    trailer = node->getPre();
                }
                if (node->getPre()) {
                    node->getPre()->setNext(node->getNext());
                }
                if (node->getNext()) {
                    node->getNext()->setPre(node->getPre());
                }
                delete node; 
            }
        }
        void insert(Node<F,S,A> *node1, Node<F,S,A> *node2){
            Node<F,S,A> *q = new Node<F,S,A>;
            q->setdad(node2->getdad());
            q->setson(node2->getson());
            q->setage(node2->getage());

            q->setNext(node1->getNext());
            node1->getNext()->setPre(q);
            node1->setNext(q);
            q->setPre(node1);

            remove(node2);
        }
        void sortdad(){
            for(Node<F,S,A> *i=header;i!=nullptr;i=i->getNext()){
                for(Node<F,S,A> *j=i->getNext();j!=nullptr;j=j->getNext()){
                    if(j->getdad() == i->getson())
                        insert(i,j);                       
                }
            }
        }
        void calcul(){
            Node<F,S,A> *current = header;
            while (current != nullptr) {
                if (current->getdad() == "Ted") {
                    current->setage(100 - current->getage());
                } else {
                // Tìm tuổi của cha của người con
                Node<string, string, int> *father = header;
                while (father != nullptr) {
                    if (father->getson() == current->getdad()) {
                        current->setage(father->getage() - current->getage());
                        break;
                    }
                    father = father->getNext();
                }
            }
            current = current->getNext();
            }
        }
        void swapNodes(Node<F, S, A>* node1, Node<F, S, A>* node2) {
            if (node1 == node2) return;  
            A tempAge = node1->getage();
            S tempSon = node1->getson();
            F tempDad = node1->getdad();

            node1->setage(node2->getage());
            node1->setson(node2->getson());
            node1->setdad(node2->getdad());

            node2->setage(tempAge);
            node2->setson(tempSon);
            node2->setdad(tempDad);
        }
        void quicksort(Node<F, S, A>* low, Node<F, S, A>* high) {
        if (low != nullptr && high != nullptr && low != high && low->getPre() != high) {
            Node<F, S, A>* pivot = partition(low, high);

            quicksort(low, pivot->getPre());
            quicksort(pivot->getNext(), high);
            }
        }

        Node<F, S, A>* partition(Node<F, S, A>* low, Node<F, S, A>* high) {
            A pivotAge = high->getage();
            Node<F, S, A>* i = low->getPre();

            for (Node<F, S, A>* j = low; j != high; j = j->getNext()) {
                if (j->getage() > pivotAge || (j->getage() == pivotAge && j->getson() < high->getson())) {
                    i = (i == nullptr) ? low : i->getNext();
                    swapNodes(i, j);
                }
            }

            i = (i == nullptr) ? low : i->getNext();
            swapNodes(i, high);
            return i;
        }
        void sort(){
            quicksort(header, trailer);
        //    for (Node<F, S, A>* i = header; i != nullptr; i = i->getNext()) {
        //        for (Node<F, S, A>* j = i->getNext(); j != nullptr; j = j->getNext()) {
        //            if (i->getage() < j->getage() || (i->getage() == j->getage() && i->getson() > j->getson())) {
        //            swapNodes(i, j);
        //            }
        //        }
        //    }
        }
        void printf(){
            Node<F,S,A> *current = header;
            while (current != nullptr) {
            
                cout << current->getson() << " " << current->getage() << endl;
            
            current = current->getNext();
        }
        }
};
#endif
