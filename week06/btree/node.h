#ifndef NODE_H
#define NODE_H

using namespace std;

template <typename TK>
struct Node {
    //array de keys
    TK* keys;    
    //array de punteros a hijos
    Node** children;
    //cantidad de keys
    int count;
    //indicador de nodo hoja
    bool leaf;

    Node(): keys(nullptr), children(nullptr), count(0), leaf(true) {}

    Node(int M, bool _leaf = true){
        keys = new TK[M-1];
        children = new Node<Tk>*[M];
        count = 0;
        leaf = _leaf;
    }    

    void killSelf(){
        //TODO
    }    
};

#endif