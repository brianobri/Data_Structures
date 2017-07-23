#ifndef AVL_HPP
#define AVL_HPP
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <cmath>
#include <string>

template <class T>
class AVL {
private:
    struct AVL_node
    {
        T data;
        AVL_node* left;
        AVL_node* right;
        ~AVL_node() {
            delete left;
            delete right;
        }
    };
    AVL_node* root;
    // put your private functions here (you will probably have quite a few)
    void balence_tree(AVL_node *, AVL_node *);
    void insert_into_tree(AVL_node *, AVL_node *,AVL_node *);
    void pre_order_for_serialize(AVL_node *,  std::vector<std::string> &);
    void find_and_remove(T, AVL_node*, AVL_node **);
    int height(AVL_node *);
    void balence_rightrotate(AVL_node *, AVL_node *);
    void balence_leftrotate(AVL_node *, AVL_node *);
    void balence_Double_rightrotate(AVL_node *, AVL_node *);
    void balence_Double_leftrotate(AVL_node *, AVL_node *);
    T iop(AVL_node *, AVL_node ** );


public:
    AVL()
    {
        root = NULL;
    }

    ~AVL()
    {
      delete root;
      // need post order deletion
      //create a method called clear
    }

    // Insert a node into the AVL with a given data value
    // The tree must be balanced after every insert
    void insert(const T& value)
    {
        if(!root){
            root = new AVL_node();
            root->data = value;
            root->left = NULL;
            root->right = NULL;
        }
        else{
            AVL_node *newnode = NULL;
            newnode = new AVL_node();
            newnode->data = value;
            newnode->left = NULL;
            newnode->right = NULL;
            insert_into_tree(NULL,root, newnode);
        }
    }

    // remove a node from the AVL with a specific data value
    // you MUST use the in order predecessor to replace the removed node
    void remove(const T& t){
        find_and_remove(t, NULL, &root);
    }

    // return a std::vector<std::string> of the serialized AVL tree
    // you WILL need to have template specialization for AVL<int> and AVL<std::string>
    // std::to_string(int) can be used to convert an integer to a string
    std::vector<std::string> serialize()
    {
        std::vector<std::string> new_string_vector_list;
        pre_order_for_serialize(root, new_string_vector_list);
        return new_string_vector_list;
    }
};

template <class T>
void AVL<T>::insert_into_tree(AVL_node * prev, AVL_node * nodeptr, AVL_node * newnode)
{
    // inserting in order then balancing
    if (newnode->data  < nodeptr->data){
        if(nodeptr->left != NULL) {
            insert_into_tree(nodeptr,nodeptr->left, newnode);
        }
        else {
            nodeptr->left = newnode;
        }
    }
    else if (newnode->data > nodeptr->data){
        if(nodeptr->right != NULL) {
            insert_into_tree(nodeptr,nodeptr->right, newnode);
        }
        else {
            nodeptr->right = newnode;
        }
    }
    balence_tree(prev,nodeptr);
}

template <class T>
void AVL<T>::pre_order_for_serialize(AVL_node* nodeptr, std::vector<std::string>& vector_list)
{
    //serialize pre order
    std::string temp;
    std::stringstream d;
    d << nodeptr->data;
    d >> temp;
    vector_list.push_back(temp);

    if (nodeptr->left == NULL){
        vector_list.push_back("/");
    }
    else{
        pre_order_for_serialize(nodeptr->left, vector_list);
    }
    if (nodeptr->right == NULL){
            vector_list.push_back("/");
    }
    else{
        pre_order_for_serialize(nodeptr->right, vector_list);
    }

}

template <class T>
int AVL<T>::height(AVL_node * n)
{
    // return height negitive means left heavy positive means right heavy
    if (n == NULL)
        return -1;
    else
        return 1 + std::max(height(n->left),height(n->right));
}

template <class T>
void AVL<T>::balence_tree(AVL_node * parent, AVL_node *piv){
    //figures out what rotation to do with the heights
    int lh = height(piv->left);
    int rh = height(piv->right);
    int d = rh-lh;
    if (d == -2)
    {
        if(height(piv->left->left) >= height(piv->left->right)){
            balence_rightrotate(parent, piv);
        }
        else {
          balence_Double_rightrotate(parent, piv);
        }
    }
    else if (d == 2)
    {
        if(height(piv->right->right) >= height(piv->right->left)){
            balence_leftrotate(parent, piv);
        }
        else{
          balence_Double_leftrotate(parent, piv);
        }
    }
}

template <class T>
void AVL<T>::balence_rightrotate(AVL_node * parent, AVL_node *piv)
{
    //right rotation
    if(!parent){
        //at root
         AVL_node* old = root;
         root = root->left;
         AVL_node* m = root->right;
         root->right = old;
         old->left = m;
         return;
    }
    if (parent->left == piv) {
        parent->left = piv->left;
    }
    else {
        parent->right = piv->left;
    }
    AVL_node *temp = piv->left->right;
    piv->left->right = piv;
    piv->left = temp;
}

template <class T>
void AVL<T>::balence_leftrotate(AVL_node * parent, AVL_node *piv)
{
    //left rotation
    if(!parent){
        root = piv->right;
    }
    else if (parent->left == piv) {
        parent->left = piv->right;
    }
    else {
        parent->right = piv->right;
    }
    AVL_node *temp = piv->right->left;
    piv->right->left = piv;
    piv->right = temp;
}

template <class T>
void AVL<T>::balence_Double_rightrotate(AVL_node * parent, AVL_node *piv)
{
    //double right rotate
    balence_leftrotate(piv, piv->left);
    balence_rightrotate(parent,piv);
}

template <class T>
void AVL<T>::balence_Double_leftrotate(AVL_node * parent, AVL_node *piv)
{
    // double left rotate
    balence_rightrotate(piv, piv->right);
    balence_leftrotate(parent,piv);
}


template <class T>
void AVL<T>::find_and_remove(T value, AVL_node * parent, AVL_node ** doubleNode)
{
    //finds the data to remove by pre order then deletes and replace with in order predecessor if needed then rebalance tree
    AVL_node* node = *doubleNode;
    if (value == node->data){
       if (node->left == NULL && node->right == NULL) {
            //no children delete
            delete *doubleNode;
            *doubleNode = NULL;
       }
       else if (node->left != NULL && node->right == NULL) {
            //one child  delete
            AVL_node* copy_ = node;
            *doubleNode = node->left;
            copy_->left = NULL;
            delete copy_;
       }
       else if (node->left == NULL && node->right != NULL) {
            //two children  delete
            AVL_node* copy_ = node;
            *doubleNode = node->right;
            copy_->right = NULL;
            delete copy_;
       } else {
            // root delete
            T value = iop(node, &(node->left));
            node->data = value;
       }
   }
   else if(value < node->data){
       find_and_remove(value, node, &(node->left));
       balence_tree(parent, node);
   }
   else if (value > node->data){
       find_and_remove(value, node, &(node->right));
       balence_tree(parent, node);
   }
}


template <class T>
T AVL<T>::iop(AVL_node * parent, AVL_node ** doublenode)
{
    AVL_node * node = *doublenode;
    if (node->right != NULL)
    {
        T val = iop(node, &(node->right));
        balence_tree(parent, node);
        return val;
    }

    T value = node->data;
    AVL_node * C = node;
    *doublenode = node->left;
    delete C;
    return value;
}



#endif
