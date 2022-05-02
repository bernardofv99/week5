#ifndef BSTREE_H
#define BSTREE_H

#include "iterator.h"

using namespace std;

template <typename T>
class BSTree {
    public:
        typedef BSTIterator<T> iterator;  

    private:
        NodeBT<T>* root; 
        void travel(Node<T>**& pointer, int key); 
        void killNode(Node<T>*& pointer);  

    public:
        BSTree(): root(nullptr) {}

		template<typename T>
        bool BSTree<T>::insert(int key, T data) {
            if(!root){ // Tree is empty
                root = new Node<T>(key, data);
                this->nodes++;
                return true; // Element inserted successfully
            } else{ // Tree has elements
                Node<T>** temp;
                travel(temp, key);
                // Insert data
                if(key == (*temp)->key){
                    (*temp)->data = data;
                    return false; // Element was not inserted, but data was changed
                }else if(key > (*temp)->key){
                    (*temp)->right = new Node<T>(key, data);
                    this->nodes++;
                    return true; // Element inserted successfully
                } else{
                    (*temp)->left = new Node<T>(key, data);
                    this->nodes++;
                    return true; // Element inserted successfully
                }
            }
        }

		bool find(T value);		

        template <typename T>
        void BSTree<T>::displayInOrder(NodeBT<T>* node){
            if (node == nullptr)
                return;

            displayInOrder(node->left);

            cout << node->data << "\n";

            displayInOrder(node->right);
        }
        
        template <typename T>
        void BSTree<T>::displayPreOrder(NodeBT<T>* node){
            if (node == nullptr)
                return;

            cout << node->data << "\n";

            displayPreOrder(node->left);

            displayPreOrder(node->right);
        }

        template <typename T>
        void BSTree<T>::displayPostOrder(NodeBT<T>* node){
            if (node == nullptr)
                return;

            displayPostOrder(node->left);

            displayPostOrder(node->right);

            cout << node->data << "\n";
        }

        template<typename T>
        int BSTree<T>::height(Node<T>* pointer) {
            if(pointer){
                int leftHeight = height(pointer->left);
                int rightHeight = height(pointer->right);
                int max = (leftHeight > rightHeight) ? leftHeight : rightHeight;
                return max+1;
            } else{
                return false;
            }
        }

        template<typename T>
        T BSTree<T>::minValue(NodeBT<T> *node) {
            if(node == nullptr) {
                return -1;
            }

            if (node->left == nullptr){
                return node->data;
            }

            return minValue(node->left);
        }

        template<typename T>
        T BSTree<T>::maxValue(NodeBT<T> *node) {
            if(node == nullptr) {
                return -1;
            }

            if(node->right == nullptr){
                return node->data;
            }

            return maxValue(node->right);
        }

        template<typename T>
        bool BSTree<T>::remove(int key) {
            if(this->root){
                Node<T>** temp;
                travel(temp, key);
                Node<T>* swap = *temp;
                if(swap->key != key){
                    return false; // Key was not found, could not remove element
                } else{
                    if (!swap->right && !swap->left){ // Delete if node is a leaf node
                        *temp = nullptr;
                    } else if(!swap->right && swap->left){ // Swap with the "previous" element
                        swapPrev(temp, swap);
                    } else{ // Swap with the "next" element
                        swapNext(temp, swap);
                    }
                    delete swap;
                    this->nodes--;
                    return true; // Element successfully removed
                }
            } else{
                return false; // Empty tree, failed to remove element
            }
        }   

        template<typename T>
        bool BSTree<T>::isBalanced(NodeBT<T> *node) {
            if(node == nullptr) return true;
            else abs(height(node->left) - height(node->right)) <= 1
                    && isBalanced(node->left) && isBalanced(node->right);
        }

        template<typename T>
        int BSTree<T>::size() {
            return this->nodes;
        }

        bool isFull(); //es aquel en el que todos los nodos tienen 0 o 2 hijos        
        T successor(T value); // Retornar el valor siguiente de "value" en el arbol
        T predecessor(T value); // Retornar el valor anterior de "value" en el arbol
        void clear(); // Liberar todos los nodos (usar root->KillSelf)
        void buildFromOrderedArray(T *array, int n); //dado un array ordenado construir un arbol binario balanceado
        string displayBFS();// Recorrido en anchura (BreadthFirstSearch)
        string displayDFS();// Recorrido en profundidad (DepthFirstSearch)

        Iterator<T> begin() {
            // TODO
            if(this->root){
                Iterator<T> itBegin(this->root);
                return itBegin;
            } else{
                Iterator<T> itBegin;
                return itBegin;
            }
        }// Retorna el inicio del iterador   

        Iterator<T> end() { 
            // TODO
            Iterator<T> itEnd;
            return itEnd;
        }// Retorna el final del iterador

        template<typename T>
        void BSTree<T>::killNode(Node<T>*& pointer){
            if(pointer){
                killNode(pointer->left);
                killNode(pointer->right);
                delete pointer;
            }
        }

        template<typename T>
        BSTree<T>::~BSTree() {
            if(this->root){
                killNode(this->root);
            }
        } //Destructor del arbol

}; 


#endif


