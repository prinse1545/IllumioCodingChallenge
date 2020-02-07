// Philipp Moura Srivastava
// 05.02.2020
// Illumio Coding Challenge
// Filename: firewall.h
// Description: This is the header file for the firewall class
// as described by the Illumio Coding Challenge

#ifndef _firewall_h
#define _firewall_h

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <exception>
#include "../rbtree/rbtree.h"

using namespace std;

class Firewall{
public:

  Firewall(string filename);

  bool accept_packet(string direction, string protocol, int host, string ip);

private:

  RBT<string> tcpOutbound;
  RBT<string> tcpInbound;
  RBT<string> udpOutbound;
  RBT<string> udpInbound;

  vector<string> split(string item, char splitChar);

  void insert(string port, string ip, string rbtree);

  void insertHelper(string toInsert, string rbtree);

  bool accept_packet_helper(string packet, string rbtree);

  unsigned int ipToInt(vector<int> ip);

  vector<int> ipToVector(string ip);

};

class FileError : public exception {
public:
  string what() {
    return "The file could not be opened!";
  }
};

#endif
