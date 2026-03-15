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

    void reverseSegment(int L, int R) {
        if (L < 1 || R > size || L >= R) {
            cout << "Invalid range." << endl;
            return;
        }

        Node* startNode = head;
        for (int i = 1; i < L; ++i) startNode = startNode->next;

        Node* endNode = head;
        for (int i = 1; i < R; ++i) endNode = endNode->next;

        Node* before = startNode->prev;
        Node* after = endNode->next;

        Node* curr = startNode;
        while (true) {
            Node* nextNode = curr->next;
            
            Node* temp = curr->next;
            curr->next = curr->prev;
            curr->prev = temp;
            
            if (curr == endNode) break;
            curr = nextNode;
        }

        if (L == 1 && R == size) {
            Node* temp = head;
            head = tail;
            tail = temp;
        } 
        else {
            before->next = endNode;
            endNode->prev = before;

            after->prev = startNode;
            startNode->next = after;

            if (L == 1) head = endNode;
            if (R == size) tail = startNode;
        }

        cout << "Segment reversed." << endl;
    }

    void jump(int k) {
        if (k < 0) {
            cout << "Invalid jump." << endl;
            return;
        }

        if (!currentSong) {
            cout << "No song is currently playing." << endl;
            return;
        }

        for (int i = 0; i < k; ++i) {
            currentSong = currentSong->next;
        }

        currentSong->playCount++;
        cout << "Playing: " << currentSong->songName << endl;
    }

    void print() {
        cout << "Playlist:";
        if (head) {
            Node* curr = head;
            for (int i = 0; i < size; ++i) {
                cout << " " << curr->songName;
                curr = curr->next;
            }
        }
        cout << "\nCurrent: ";
        if (currentSong) cout << currentSong->songName << endl;
        else cout << "None" << endl;
    }

};

int main(){

    cout<<"?????"<<endl;
    return 0;
}

