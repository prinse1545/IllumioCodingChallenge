//Philipp - CS 271 - Fall 2019
//test_rbtree.cpp
#include <iostream>
#include <string>
#include "rbtree.h"
#include "assert.h"

int main() {
  RBT<int> intTree; //test on the tree we made in class


  int test1 = 11;
  int test2 = 14;
  int test3 = 2;
  int test4 = 1;
  int test5 = 7;
  int test6 = 15;
  int test7 = 5;
  int test8 = 8;
  int test9 = 4;
  intTree.insert(&test1);
  intTree.insert(&test2);
  intTree.insert(&test3);
  intTree.insert(&test4);
  intTree.insert(&test5);
  intTree.insert(&test6);
  intTree.insert(&test7);
  intTree.insert(&test8);
  intTree.insert(&test9);
  try { //check for KeyErrors
    intTree.search(402);
  }catch(KeyError *e) {
    assert(1 == 1);
  }




  assert(*(intTree.search(test1)) == 11);
  assert(*(intTree.search(test2)) == 14);
  assert(*(intTree.search(test3)) == 2);
  assert(*(intTree.search(test6)) == 15);
  assert(*(intTree.search(test4)) == 1);

  RBT<int> smallTree; //insert in a non-tree pattern to check edge cases of insert-fixup
  int small1 = 4;
  int small2 = 5;
  int small3 = 6;
  smallTree.insert(&small1);
  smallTree.insert(&small2);
  smallTree.insert(&small3);
  assert(*(smallTree.search(small1)) == 4);
  assert(*(smallTree.search(small2)) == 5);
  assert(*(smallTree.search(small3)) == 6);

  RBT<double> doubleTree; //not the hotel
  double dtest1 = 11.0;
  double dtest2 = 14.0;
  double dtest3 = 2.0;
  double dtest4 = 1.0;
  double dtest5 = 7.0;
  double dtest6 = 15.0;
  double dtest7 = 5.0;
  double dtest8 = 8.0;
  double dtest9 = 4.0;
  doubleTree.insert(&dtest1);
  doubleTree.insert(&dtest2);
  doubleTree.insert(&dtest3);
  doubleTree.insert(&dtest4);
  doubleTree.insert(&dtest5);
  doubleTree.insert(&dtest6);
  doubleTree.insert(&dtest7);
  doubleTree.insert(&dtest8);
  doubleTree.insert(&dtest9);
  assert(*(doubleTree.search(dtest1)) == 11.0); //tests insert/insertfixup, search, inorder, pre, postorder
  assert(*(doubleTree.search(dtest2)) == 14.0);  //along with rotateleft and rotateright
  assert(*(doubleTree.search(dtest3)) == 2.0);
  assert(*(doubleTree.search(dtest4)) == 1.0);


  try { //check for KeyErrors
    doubleTree.search(402.0);
  }catch(KeyError *e) {
    assert(1 == 1);
  }


  RBT<string> stringTree; //testing on multiple types!
  string string1 = "hello";
  string string2 = "there";
  string string3 = "general";
  stringTree.insert(&string1);
  stringTree.insert(&string2);
  stringTree.insert(&string3);
  assert(*(stringTree.search(string1)) == "hello");
  assert(*(stringTree.search(string2)) == "there");
  assert(*(stringTree.search(string3)) == "general");

  cout << "All tests passed successfully" << endl;
  return 0;
}
