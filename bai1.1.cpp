#include<iostream>
#include<vector>
using namespace std;


class HashTable {
private:
    struct Node {
        int val;
        Node* next;
        Node(int x) : val(x), next(nullptr) {}
    };
    int size;
    Node** table;
public:
    HashTable() {
        size = 1e6 + 3;
        table = new Node*[size];
    }

    void insert(int x) {
        if (!table[abs(x) % size])
            table[abs(x) % size] = new Node(x);
        else {
            Node* ptr = table[abs(x) % size];
            while (ptr->next) {
                ptr = ptr->next;
            }
            ptr->next = new Node(x);
        }
    }


    bool find(int x) {
        if (!table[abs(x) % size])
            return false;
        Node* ptr = table[abs(x) % size];
        while (ptr) {
            if (ptr->val == x)
                return true;
            ptr = ptr->next;
        }
        return false;
    }

    bool erase(int x) {
        if (!find(x))
            return false;
        Node* ptr = table[abs(x) % size];
        if (ptr->val == x) {
            table[abs(x) % size] = ptr->next;
            delete ptr;
            return true;
        }

        while (ptr) {
            if (ptr->next && ptr->next->val == x) {
                Node* temp = ptr->next;
                ptr->next = temp->next;
                delete temp;
            }
            else 
                ptr = ptr->next;
        }
        return true;
    }


    int countElement() {
        int ans = 0;
        for (int i = 0; i < size; i++) {
            Node* ptr = table[i];
            while (ptr) {
                ans++;
                ptr = ptr->next;
            }
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

