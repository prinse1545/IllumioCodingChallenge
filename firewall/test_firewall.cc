// Philipp Moura Srivastava
// 06.02.2020
// Illumio Coding Challenge
// Filename: test_firewall.cc
// Description: This file tests the firewall class

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "firewall.h"

using namespace std;


int main() {

  Firewall fire("./firewall/sample.csv");

  cout << fire.accept_packet("inbound",  "tcp",  81,  "192.168.1.2") << endl;


  return 0;
}
