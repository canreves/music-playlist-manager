#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct Node{
    int songId;
    string songName;
    string artistName;
    int duration;
    int playCount;
    Node* next;
    Node* prev;
    Node(int id, string sname, string aname, int dur)
        : songId(id), songName(sname), artistName(aname), duration(dur), 
        playCount(0), next(nullptr), prev(nullptr) {}
};

int main(){

    cout<<"?????"<<endl;
    return 0;
}

