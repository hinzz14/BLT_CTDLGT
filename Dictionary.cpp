#include <iostream>
#include <fstream>
#include <string>
#include "hashtbl.cpp" 
using namespace std;

class Dictionary {
private:
    Hashtable<string, string> hashtable;

public:
    Dictionary(int size) : hashtable(size) {}

    void LoadFromFile(const string &filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                size_t pos = line.find(" ");
                if (pos != string::npos) {
                    string word = line.substr(0, pos);
                    string meaning = line.substr(pos + 1);
                    hashtable.Add(word, meaning, Hash);
                }
            }
            file.close();
        }
    }

    void SaveToFile(const string &filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < hashtable.getSize(); i++) {
                Node<string, string> *node = hashtable.getTable()[i].getHead();
                while (node != nullptr) {
                    file << node->getKey() << "  " << node->getElem() << endl;
                    node = node->getNext();
                }
            }
            file.close();
        }
    }

    string Lookup(const string &word) {
        Node<string, string> *node = hashtable.Find(word, Hash);
        if (node != nullptr) {
            return node->getElem();
        }
        return "Word not found in the dictionary.";
    }

    void Modify(const string &word, const string &meaning) {
        hashtable.Remove(word, Hash);
        hashtable.Add(word, meaning, Hash);
    }

    void AddWord(const string &word, const string &meaning) {
        hashtable.Add(word, meaning, Hash);
    }

    void RemoveWord(const string &word) {
        hashtable.Remove(word, Hash);
    }

    void Display() {
        cout << "-----Dictionary-----" << endl;
        for (int i = 0; i < hashtable.getSize(); i++) {
            Node<string, string> *node = hashtable.getTable()[i].getHead();
            while (node != nullptr) {
                cout << node->getKey() << " -" << node->getElem() << endl;
                node = node->getNext();
            }
        }
        cout << "--------------------" << endl;
    }

    static int Hash(string key, int size) {
        unsigned long hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + c; // djb2 algorithm
        }
        return hash % size;
    }


};
int main() {
    Dictionary dictionary(100); 

    dictionary.LoadFromFile("dictionary.txt");

    while (true) {
        cout << "--------------Menu---------------\n";
        cout << "a. Lookup word\n";
        cout << "b. Modify word\n";
        cout << "c. Add word\n";
        cout << "d. Remove word\n";
        cout << "e. Display dictionary\n";
        cout << "f. Save dictionary to file\n";
        cout << "h. Exit\n";
        cout << "---------------------------------\n";
        cout << "Choose an option: ";

        char choice;
        cin >> choice;

        if (choice == 'a') {
            cout << "Enter a word to lookup: ";
            string word;
            cin >> word;
            cout <<"Meaning of "<<word<<": "<< dictionary.Lookup(word) << endl;
        } else if (choice == 'b') {
            cout << "Enter a word to modify: ";
            string word;
            cin >> word;
            cout << "Enter the new meaning: ";
            string meaning;
            cin.ignore();
            getline(cin, meaning);
            dictionary.Modify(word, meaning);
        } else if (choice == 'c') {
            cout << "Enter a new word: ";
            string word;
            cin >> word;
            cout << "Enter the meaning: ";
            string meaning;
            cin.ignore();
            getline(cin, meaning);
            dictionary.AddWord(word, meaning);
        } else if (choice == 'd') {
            cout << "Enter a word to remove: ";
            string word;
            cin >> word;
            dictionary.RemoveWord(word);
        } else if (choice == 'e') {
            dictionary.Display();
        } else if (choice == 'f') {
            dictionary.SaveToFile("dictionary.txt");
            cout << "Dictionary saved to file." << endl;
        } else if (choice == 'h') {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}











