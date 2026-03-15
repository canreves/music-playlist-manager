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

    void add(int id, string name, string artist, int dur){
        
        if(findSong(id)){
            cout << "Song already exists."<<endl;
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
        cout << "Song added." << endl;
    }

    void remove(int id){
        if(!head){
            cout << "Playlist is empty." << endl;
            return;
        }

        Node* target = findSong(id);
        if(!target){
            cout << "Not found." << endl;
            return;
        }

        if(size == 1){
            head = tail = currentSong = nullptr;
        } 
        else{
            if(currentSong == target){
                currentSong = currentSong->next;
            }

            target->prev->next = target->next;
            target->next->prev = target->prev;

            if(target == head){
                head = target->next;
            }
            if(target == tail){
                tail = target->prev;
            }
        }

        delete target;
        size--;
        cout << "Song removed." << endl;
    }

    void play(int id){
        if (!head){
            cout << "Playlist is empty." << endl;
            return;
        }
        Node* target = findSong(id);
        if (!target) {
            cout << "Not found." << endl;
            return;
        }
        currentSong = target;
        currentSong->playCount++;
        cout << "Playing: " << currentSong->songName << endl;
    }

    void next() {
        if (!currentSong) {
            cout << "No song is currently playing." << endl;
            return;
        }
        currentSong = currentSong->next;
        currentSong->playCount++;
        cout << "Playing: " << currentSong->songName << endl;
    }

    void prev() {
        if (!currentSong) {
            cout << "No song is currently playing." << endl;
            return;
        }
        currentSong = currentSong->prev;
        currentSong->playCount++;
        cout << "Playing: " << currentSong->songName << endl;
    }

    void moveAfter(int idA, int idB) {
        Node* nodeA = findSong(idA);
        Node* nodeB = findSong(idB);

        if (!nodeA || !nodeB) {
            cout << "Not found." << endl;
            return;
        }

        if (idA == idB || size < 2 || nodeB->next == nodeA) {
            cout << "Move ignored." << endl;
            return;
        }

        nodeA->prev->next = nodeA->next;
        nodeA->next->prev = nodeA->prev;
        
        if (nodeA == head) head = nodeA->next;
        if (nodeA == tail) tail = nodeA->prev;

        Node* nodeC = nodeB->next;
        
        nodeB->next = nodeA;
        nodeA->prev = nodeB;
        
        nodeA->next = nodeC;
        nodeC->prev = nodeA;

        if (nodeB == tail) tail = nodeA;

        cout << "Song moved." << endl;
    }

};

int main(){

    cout<<"?????"<<endl;
    return 0;
}

