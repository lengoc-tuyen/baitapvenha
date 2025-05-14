#include<iostream>
#include<vector>
#include <optional>
using namespace std;

class HashTable {
private:
    const int maxSize = 2017;
    const int prime = 1117;
    int size;
    vector<optional<int>> table;
    int hash(int key) {
        if (!table[hash1(key)].has_value()) {
            return hash1(key);
        }
        int i = 0;
        while (i < maxSize) {
            if (!table[(hash1(key) + i * hash2(key)) % maxSize].has_value())
                return (hash1(key) + i * hash2(key)) % maxSize;
            i++;
        }
        return -1;
    }

    int findPosition(int key) {
        int index = hash1(key);
        if (table[index].has_value() && table[index] == key)
            return index;
        int i = 0;
        while (i < maxSize) {
            if (table[(hash1(key) + i * hash2(key)) % maxSize].has_value() && table[(hash1(key) + i * hash2(key)) % maxSize] == key)
                return (hash1(key) + i * hash2(key)) % maxSize;
            i++;
        }
        return -1;
    }

    int hash1(int key) {
        return (key + maxSize) % maxSize;
    }

    int hash2(int key) {
        int value = (prime - (key % prime)) % maxSize;
        return (value == 0) ? 1 : value;  
    }

public:
    HashTable() : table(maxSize), size(0) {}

    bool insert(int value) {
        if (size == maxSize) {
            cout << "Bang da day.\n";
            return false;
        }
        if (find(value)) {
            cout << "Phan tu da ton tai trong bang.\n";
            return false;
        }
        
        int idx = hash(value);
        if (idx == -1)
            return false;
        table[idx] = value;
        size++;
        return true;
    }

    bool find(int x) {
        int idx = findPosition(x);
        return idx != -1;
    }

    bool erase(int val) {
        int idx = findPosition(val);
        if (idx != -1) {
            table[idx] = nullopt;
            size--;
            return true;
        }
        return false;
    }

    double loadFactor() {
        return (double) size / maxSize;
    }
};

int main() {
    HashTable table;
    int choose;
    do {
        cout << "-------------MENU-------------\n";
        cout << "1. Them phan tu vao bang bam.\n";
        cout << "2. Tim kiem phan tu.\n";
        cout << "3. Xoa phan tu.\n";
        cout << "4. In he so tai.\n";
        cout << "5. Thoat.\n";
        cout << "Nhap yeu cau (1-5): \n";
        cin >> choose;
        switch (choose) {
            case 1: 
            {   
                system("clear");
                int x;
                cout << "Nhap phan tu can them: ";
                cin >> x;
                if (table.insert(x))
                    cout << "Da them thanh cong.\n";
                break;
            }

            case 2:
            {
                system("clear");
                int x;
                cout << "Nhap phan tu can tim kiem.\n";
                cin >> x;
                if (table.find(x)) 
                    cout << x << " co ton tai.\n";
                else
                    cout << x << " khong ton tai.\n";
                break;
            }

            case 3:
            {
                system("clear");
                int x;
                cout << "Nhap phan tu muon xoa: ";
                cin >> x;
                if (table.erase(x))
                    cout << "Da xoa x thanh cong.\n";
                else 
                    cout << "Khong tim thay phan tu.\n";
                break;
            }

            case 4:
            {
                system("clear");
                cout << "He so tai la: " << table.loadFactor() << endl;
                break;
            }
            case 5:
            {
                cout << "Cam on ban da su dung. Tam biet!\n";
                return 0;
            }
            default: {
                cout << "Vui long nhap tu 1 den 5.\n";
                break;
            }
        }

    } while (choose != 5);

}