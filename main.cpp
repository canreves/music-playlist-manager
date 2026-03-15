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


class PlaylistManager{
private:
    Node* head;
    Node* tail;
    Node* currentSong;
    int size;

    Node* findSong(int id){
        if(!head){
            return nullptr;
        }
        Node* curr = head;
        do {
            if(curr->songId == id){
                return curr;
            }
            curr = curr->next;
        } while (curr != head);
        return nullptr;
    }

public:
    PlaylistManager() : head(nullptr), tail(nullptr), currentSong(nullptr), size(0) {}

    ~PlaylistManager(){
        if(!head){
            return;
        }
        Node* curr = head;
        do {
            Node* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        } while (curr != head);
        
    }

    void add(int id, string name, string artist, int dur) {
        
        if(findSong(id)){
            cout << "Song already exists.\n";
            return;
        }

        Node* newNode = new Node(id, name, artist, dur);

        if(!head){
            head = tail = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        } 
        else {
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
            tail = newNode;
        }
        size++;
        cout << "Song added.\n";
    }

};

int main(){

    cout<<"?????"<<endl;
    return 0;
}

