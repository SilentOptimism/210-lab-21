// COMSC-210 | Lab 21 | Goat Doubly Linked list
#include <iostream>
#include <random>

using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

const int NAME_COUNT = 15, COLOR_COUNT = 15;

class Goat {
    private:
        int age;
        string name;
        string color;
        string names[NAME_COUNT] = {
            "Nanny McGoat",
            "Billy the Kid",
            "Butterscotch",
            "Clover",
            "Scruffy",
            "Luna",
            "Pippin",
            "Marzipan",
            "Tofu",
            "Biscuit",
            "Fig",
            "Buckaroo",
            "Willow",
            "Peaches",
            "Ziggy"
        };
        string colors[COLOR_COUNT] = {
            "Snow White",
            "Midnight Black",
            "Chestnut Brown",
            "Sandy Beige",
            "Slate Gray",
            "Honey Gold",
            "Spotted Black and White",
            "Rusty Red",
            "Cloudy Gray",
            "Cream",
            "Hazel",
            "Smoky Silver",
            "Chocolate Brown",
            "Ivory",
            "Sandy Cream",
        };

    public:
        Goat(){
            int nameIndex = rand() % NAME_COUNT;
            int colorIndex = rand() % COLOR_COUNT;

            name = names[nameIndex]; // random name from names list
            color = colors[colorIndex]; // random color from colors list

            age = rand() % 20 + 1;

        }

        Goat(int a, string n, string c){
            age = a;
            name = n;
            color = c;
        }

        string getName() {return name;}
        string getColor() {return color;}
        int getAge() {return age;}

};

class DoublyLinkedList {
private:
    struct Node {
        Goat Animal;
        Node* prev;
        Node* next;
        Node(Goat g, Node* p = nullptr, Node* n = nullptr) {
            Animal = g; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(Goat goat) {
        Node* newNode = new Node(goat);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(Goat goat) {
        Node* newNode = new Node(goat);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(Goat goat, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(goat);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

/*
    void delete_node(Goat value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }
*/
    void print() {
        Node* current = head;
        if (!current){
            cout << "Empty List" << endl;
        } 

        cout << "Backward:" << endl;

        while (current) {
            cout << "\t";
            cout << current->Animal.getName() << " (";
            cout << current->Animal.getColor() << ", ";
            cout << current->Animal.getAge() << ")";
            cout << endl;
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current){
            cout << "Empty List" << endl;
        } 

        cout << "Forward:" << endl;

        while (current) {
            cout << "\t";
            cout << current->Animal.getName() << " (";
            cout << current->Animal.getColor() << ", ";
            cout << current->Animal.getAge() << ")";
            cout << endl;
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};



// Driver program
int main() {
    srand(0);
    DoublyLinkedList list;

    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i){
        Goat newGoat;
        list.push_back(newGoat);
    }
    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();
    return 0;
}
