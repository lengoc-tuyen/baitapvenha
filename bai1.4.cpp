#include<iostream>
#include<vector>
#include <optional>
using namespace std;

class HashTable {
private:
    const int maxSize = 1e6 + 3;
    const int prime = 999983;
    int size;
    vector<optional<int>> table;
    int hash(int key) {
        if (!table[hash1(key)].has_value()) {
            return hash1(key);
        }
        int i = 0;
        while (true) {
            if (!table[(hash1(key) + i * hash2(key)) % maxSize].has_value())
                return (hash1(key) + i * hash2(key)) % maxSize;
            i++;
        }
    }

    int hash1(int key) {
        return (key + maxSize) % maxSize;
    }

    int hash2(int key) {
        return prime - (key % prime);
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
        cout << idx;
        table[idx] = value;
        size++;
        return true;
    }

    bool find(int x) {
        int idx = hash(x);
        
        if (table[idx] == x) return true;
        int i = 0;
        while (i < maxSize - idx){
            if (table[idx + i] == x)
                return true;
            i++;
        }
        return false;
    }

    bool erase(int val) {
        if (!find(val))
            return false;
        int idx = hash(val);
        if (table[idx] == val) {
            table[idx] = nullopt;
            return true;
        }
        int i = 0;
        while (i < maxSize - idx){
            if (table[idx + i] == val) {
                table[idx + i] = nullopt;
                return true;
            }
            i++;
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

 