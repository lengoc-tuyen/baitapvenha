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
        size = 1999;
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

vector<vector<int>> findSumK(vector<int> nums, int k) {
    HashTable table1;
    HashTable check;
    vector<vector<int>> ans;
    for (int i : nums) {
        if (table1.find(i)) {
            if (check.find(i) || check.find(k - i)) continue;
            ans.push_back({i, k - i});
            check.insert(i);
        }
        else 
            table1.insert(k - i);
    }
    return ans;
}


int main() {
    vector<int> vec;
    int n;
    int k;
    cout << "Nhap vao so luong phan tu cua mang: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Nhap so nguyen thu " << i + 1 << ": ";
        cin >> k;
        vec.push_back(k);
    }
    cout << "Nhap vao so nguyen k: ";
    cin >> k;
    vector<vector<int>>ans = findSumK(vec, k);
    if (ans.size() == 0) {
        cout << "Khong co cap nao thoa.\n";
        return 0;
    }
    cout << "Cac cap co tong bang k la: ";
    for (int i = 0; i < ans.size(); i++) {
        cout << "{" << ans[i][0] << ", " << ans[i][1] << "}" << "  ";
    }
}
