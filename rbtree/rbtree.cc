// Philipp Moura Srivastava
// 05.02.2020
// Illumio Coding Challenge
// Filename: rbtree.cc
// Description: This file implements the red black tree
// as described through the header file in rbtree.h

template <class T>
RBT<T>::RBT() {
  root = NULL;
}

template <class T>
RBT<T>::~RBT() {
  destroy(root);
}

template <class T>
T* RBT<T>::search(const T &value) const {
  Node* x = root;
  if (x == NULL) {
    throw new KeyError;
  }

  while(x != NULL && x->value != value) {

    if(value < x->value) { //test code changed from key and x->value
      x = x->left;
    }
    else {
      x = x->right;
    }
  }

  if(x == NULL || x->value != value) {
    throw new KeyError;
  }
  return &x->value;

}

template <class T>
void RBT<T>::insert(T* item) {
  Node* x = root; //set x to root
  Node* y = NULL; //set y to null

  while(x != NULL) { //in this case, we create the node inside of insert, but in the dictionary, we are inserting pairs
    y = x;    //for the dictionary implementation, x->getKey() produces a NODE with key/value pairs.
    if(*item < x->value) { //if our current node's key is larger, go left of the tree
      x = x->left; //set x to left child
    }
    else {
      x = x->right; //set x to right child
    }
  }
  Node* z = new Node; //create new node with the desired key
  z->value = *item;
  z->parent = y;

  if(y == NULL) {//the case that the tree is empty
    root = z; //make z the new root
  }
  else if(z->value < y->value) {
    y->left = z; //if y's key is bigger, z is the left child
  }
  else {
    y->right = z; //otherwise make z the right child
  }

  z->left = NULL;
  z->right = NULL;
  z->isBlack = false; // false for red, true for black
  fixInsert(z); //run fix insert on node z
}

template <class T>
void RBT<T>::fixInsert(Node * z) {
  while(z->parent != NULL && z->parent->isBlack == false) { //while z.p.color == RED
    if(z->parent == z->parent->parent->left) { //if z.p = z.p.p.left
      Node* y = z->parent->parent->right; //set y to z.p.p.right
      if(y != NULL && y->isBlack == false) { //if y.color == red and it's not null (which is black by default)
        z->parent->isBlack = true; //set z.p.color to black
        y->isBlack = true; //set y.color to black
        z->parent->parent->isBlack = false; //set z.p.p.color to red
        z = z->parent->parent; //z = z.p.p
      }

      else {

        if(z == z->parent->right) { //z is the right child (case 2)
          z = z->parent; //z = z.p
          rotateLeft(z);
        }
        z->parent->isBlack = true; //z.p.color = black //case 3
        z->parent->parent->isBlack = false; //set grandparent color to red // case 3
        rotateRight(z->parent->parent); //rotate grandparent right //case 3
      }
    }
    else { //same as then clause with right and left unchanged
      Node* y = z->parent->parent->left; //set y to z.p.p.left
      if(y != NULL && y->isBlack == false) { //if y.color == red - and it's not null which is black by default
        z->parent->isBlack = true; //set z.p.color to black
        y->isBlack = true; //set y.color to black
        z->parent->parent->isBlack = false; //set z.p.p.color to red
        z = z->parent->parent; //z = z.p.p
      }
      else { //changed to this from else if

        if(z == z->parent->left) { //z is the right child (case 2)
            z = z->parent;
            rotateRight(z); //do we swapped left and right rotate
        }
        z->parent->isBlack = true; //z.p.color = black
        z->parent->parent->isBlack = false; //set grandparent color to red
        rotateLeft(z->parent->parent); //rotate grandparent right
      }
    }
  }
  root->isBlack = true; //set root color to black
}

template <class T>
void RBT<T>::rotateRight(Node* item) {
  Node* y = item->left; //set y
  item->left = y->right; //turn y's right subtree into item's left subtree
  if(y->right != NULL) {
    y->right->parent = item;
  }
  y->parent = item->parent; //link item's parent to y
  if(item->parent == NULL) {
    root = y;
  }
  else if(item == item->parent->right) {
    item->parent->right = y;
  }
  else {
    item->parent = y;
  }
  y->right = item; //put item on y's right
  item->parent = y; //make y item's parent
}

template <class T>
void RBT<T>::rotateLeft(Node* item) {
  Node* y = item->right; //set y
  item->right = y->left = y->left; //turn y's left subtree into item's right subtree
  if(y->left != NULL) {
    y->left->parent = item;
  }
  y->parent = item->parent; //link item's parent to y
  if(item->parent == NULL) {
    root = y;
  }
  else if(item == item->parent->left) {
    item->parent->left = y;
  }
  else {
    item->parent->right = y;
  }
  y->left = item; //put item on y's left
  item->parent = y; //make y item's parent
}

template <class T>
void RBT<T>::transplant(Node* u, Node* v) {
  if (u->parent == NULL) {//only the root
    root = v;
  }
  else if (u == u->parent->left) {
    u->parent->left = v;
  }
  else {  //u != u.parent.left
    u->parent->right = v;
  }
  v->parent = u->parent;
}

template <class T>
void RBT<T>::destroy(Node* item) {
  if(item != NULL) {
    destroy(item->left);
    destroy(item->right);
    delete item;
  }
}
