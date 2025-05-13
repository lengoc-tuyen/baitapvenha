#include<iostream>
#include<vector>
#include <optional>
using namespace std;


class HashTable {
private:
    const int size = 1e6 + 3;
    vector<optional<int>> table;
public:
    HashTable() : table(size) {}

    void insert(int x) {
        if (!table[abs(x) % size].has_value())
            table[abs(x) % size] = x;
        else {
            int i = 0;
            int temp = (abs(x) % size + i * i) % size;
            while (i < size && table[temp].has_value()) {
                i++;
                temp = (abs(x) % size + i * i ) % size;
            }

            if (i < size) 
                table[temp] = x;
            else {
                cout << "Bang da day.\n";
            }
        }
    }


    bool find(int x) {
        for (int i = 0; i < size; i++) {
            if (table[i] == x)
                return true;
        }
        return false;
    }

    bool erase(int x) {
        if (!find(x))
            return false;
        for (int i = 0; i < size; i++) {
            if (table[i] == x) {
                table[i] = nullopt;
                return true;
            }
        }
        return false;
    }


    int countElement() {
        int ans = 0;
        for (int i = 0; i < size; i++) {
            if (table[i].has_value())
                ans++;
        }
        return ans;
    }


    double loadFactor() {
        return (double) countElement() / size;
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
                table.insert(x);
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

