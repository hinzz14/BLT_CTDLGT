#ifndef DNODE_CPP
#define DNODE_CPP
template <class F,class S, class A>
class Node{
    private:
        F cha;
        S con;
        A tuoi;
        Node<F,S,A> *next;
        Node<F,S,A> *pre;
    public:
        Node(){
            next = 0;
            pre = 0;
        }
        Node<F,S,A> *getNext(){return next;}
        Node<F,S,A> *getPre(){return pre;}
        void setNext(Node<F,S,A> *p){next = p;}
        void setPre(Node<F,S,A> *p){pre = p;}
        F getdad(){return cha;}
        void setdad(F ch){cha = ch;}
        S getson(){return con;}
        void setson(S c){con = c;}
        A getage(){return tuoi;}
        void setage(A t){tuoi = t;}
};
#endif