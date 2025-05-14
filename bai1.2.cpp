#include<iostream>
#include<vector>
#include <optional>
using namespace std;


class HashTable {
private:
    const int maxSize = 2017;
    int size;
    vector<optional<int>> table;
public:
    HashTable() : table(maxSize), size(0) {}

    bool insert(int x) {
        if (find(x)) {
            return false;
        }
        if (!table[abs(x) % maxSize].has_value()) {
            table[abs(x) % maxSize] = x;
            size++;
        }
        else {
            int i = 0;
            int temp = (abs(x) % maxSize + i) % maxSize;
            while (i < maxSize && table[temp].has_value()) {
                i++;
                temp = (abs(x) % maxSize + i) % maxSize;
            }

            if (i < maxSize) {
                table[temp] = x;
                size++;
            }
            else {
                cout << "Bang da day.\n";
                return false;
            }
        }
        return true;
    }


    int findPosition(int key) {
        int index = abs(key) % maxSize;

        if (table[index].has_value() && table[index] == key)
            return index;
        int i = 1;
        while (i < maxSize) {
            if (table[(index + i) % maxSize].has_value() && table[(index + i) % maxSize] == key)
                return (index + i) % maxSize;
            i++;
        }
        return -1;
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
                    cout << x << " Da them thanh cong.\n";
                else
                    cout << x << " Khong the them.\n";
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

