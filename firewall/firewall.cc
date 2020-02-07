// Philipp Moura Srivastava
// 05.02.2020
// Illumio Coding Challenge
// Filename: firewall.cc
// Description: This file implements the firewall class

#include "firewall.h"

Firewall::Firewall(string filename) {

  ifstream f;
  f.open(filename, ios::in);
  string line;

  if(f.is_open()) {
    getline(f, line); //Getting Column lines

    while(!f.eof()) {

      getline(f, line);
      vector<string> contents = split(line, ',');
      if(line != "") {
        if(contents[0] == "outbound") {

          if(contents[1] == "tcp") {
            insert(contents[2], contents[3], "tcpOutbound");
          }
          else {
            insert(contents[2], contents[3], "udpOutbound");
          }
        }
        else {

          if(contents[1] == "tcp") {
            insert(contents[2], contents[3], "tcpInbound");
          }
          else {
            insert(contents[2], contents[3], "udpInbound");

          }
        }
      }
    }
  }
  else {
    throw new FileError;
  }


  f.close();
}

bool Firewall::accept_packet(string direction, string protocol, int port, string ip) {

  string packetString = to_string(ipToInt(ipToVector(ip))) + ":" + to_string(port);

  if(direction == "outbound") {

    if(protocol == "tcp") {
      return accept_packet_helper(packetString, "tcpOutbound");
    }
    else if(protocol == "udp") {
      return accept_packet_helper(packetString, "udpOutbound");

    }
    else {
      return false;
    }
  }
  else if(direction == "inbound") {

    if(protocol == "tcp") {
      return accept_packet_helper(packetString, "tcpInbound");
    }
    else if(protocol == "udp") {
      return accept_packet_helper(packetString, "udpInbound");
    }
    else {
      return false;
    }
  }
  else {
    return false;
  }
}

bool Firewall::accept_packet_helper(string packet, string rbtree) {

  if(rbtree == "tcpOutbound") {
    try {
      tcpOutbound.search(packet);
      return true;
    }
    catch(KeyError *e) {
      return false;
    }
  }
  else if(rbtree == "tcpInbound") {
    try {
      tcpInbound.search(packet);
      return true;
    }
    catch(KeyError *e) {
      return false;
    }
  }
  else if(rbtree == "udpOutbound") {
    try {
      udpOutbound.search(packet);
      return true;
    }
    catch(KeyError *e) {
      return false;
    }
  }
  else if(rbtree == "udpInbound") {
    try {
      udpInbound.search(packet);
      return true;
    }
    catch(KeyError *e) {
      return false;
    }
  }
  else {
    return false;
  }

}


void Firewall::insert(string port, string ip, string rbtree) {

  vector<string> portContents = split(port, '-');
  vector<string> ipContents = split(ip, '-');

  if(portContents.size() == 1 && ipContents.size() == 1) {

    unsigned int intIP = ipToInt(ipToVector(ipContents[0]));

    string toInsert = to_string(intIP) + ":" + portContents[0];

    insertHelper(toInsert, rbtree);
  }
  else if(portContents.size() == 2 && ipContents.size() == 1) {

    unsigned int low, high;

    stringstream ss(portContents[0]);
    stringstream sss(portContents[1]);

    ss >> low;

    sss.str(sss.str().erase(0, 2));

    sss >> high;



    string ipIntAsString = to_string(ipToInt(ipToVector(ipContents[0])));

    for(int i = low; i <= high; i++) {

      string toInsert = ipIntAsString + ":" + to_string(i);

      insertHelper(toInsert, rbtree);
    }
  }
  else if(portContents.size() == 1 && ipContents.size() == 2) {

    unsigned int lowIP = ipToInt(ipToVector(ipContents[0]));
    unsigned int highIP = ipToInt(ipToVector(ipContents[1]));


    for(unsigned int i = lowIP; i <= highIP; i++) {
      string toInsert = to_string(i) + ":" + portContents[0];

      insertHelper(toInsert, rbtree);
    }


  }
  else if(portContents.size() == 2 && ipContents.size() == 2) {
    stringstream ss1(portContents[0]);
    stringstream ss2(portContents[1]);
    unsigned int lowIP = ipToInt(ipToVector(ipContents[0]));
    unsigned int highIP = ipToInt(ipToVector(ipContents[1]));

    int low, high;

    ss2.str(ss2.str().erase(0, 2));

    ss1 >> low;
    ss2 >> high;


    for(int i = low; i <= high; i++) {

      for(unsigned int j = lowIP; j <= highIP; j++) {

        string toInsert = to_string(j) + ":" + to_string(i);
        insertHelper(toInsert, rbtree);
      }
    }
  }

}

void Firewall::insertHelper(string toInsert, string rbtree) {

  if(rbtree == "tcpOutbound") {
    tcpOutbound.insert(&toInsert);
  }
  else if(rbtree == "tcpInbound") {
    tcpInbound.insert(&toInsert);
  }
  else if(rbtree == "udpOutbound") {
    udpOutbound.insert(&toInsert);
  }
  else if(rbtree == "udpInbound") {
    udpInbound.insert(&toInsert);
  }

}


unsigned int Firewall::ipToInt(vector<int> ip) {

  unsigned int ret = 0;
  int exp = 24;

  for(int i = 0; i < ip.size(); i++) {

    ret += ip[i] * pow(2, exp);
    exp = exp - 8;
  }
  return ret;
}

vector<int> Firewall::ipToVector(string ip) {

  vector<string> ipContents = split(ip, '.');
  vector<int> ipAsIntVec;

  for(int i = 0; i < ipContents.size(); i++) {


    ipAsIntVec.push_back(stoi(ipContents[i]));
  }

  return ipAsIntVec;
}

vector<string> Firewall::split(string item, char splitChar) {
  string s = "";
  vector<string> ret;

  for(int i = 0; i < item.length(); i++) {

    if(item[i] != splitChar) {
      s += item[i];
    }
    else {
      ret.push_back(s);
      s = "";
    }
  }

  if(s != "") {
    ret.push_back(s);
  }

  return ret;
}
