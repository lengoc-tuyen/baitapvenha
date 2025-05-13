#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// check coi hieu cua 2 moc tgian co <= 1p ko (trong vong 1p la tron 60s nha) (1 la sau 2 la truoc)
bool isOneMinute(string t1, string t2) {
    long tempHour = (stoi(t1.substr(0, 2)) - stoi(t2.substr(0, 2))) * 3600;
    long tempMinute = (stoi(t1.substr(3, 2)) - stoi(t2.substr(3, 2))) * 60;
    long tempSecond = stoi(t1.substr(6, 2)) - stoi(t2.substr(6, 2));
    if ((tempHour + tempMinute + tempSecond) <= 60)
        return true;
    return false;
}


// class hashtable
template <typename T>
class HashTable {
private:
    const int maxSize = 1e6 + 3;
    const int prime = 999983;
    int size;
    vector<vector<T>> table;
    int hash(int key) {
        if (table[hash1(key)].empty()) {
            return hash1(key);
        }
        int i = 0;
        while (true) {
            if (table[(hash1(key) + i * hash2(key)) % maxSize].empty())
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

    bool insert(int user, T value) {
        if (size == maxSize) return false;

        int idx = hash(user);
        table[idx].push_back(value);
        size++;
        return true;
    }

    int getSize() {
        return maxSize;
    }

    vector<T> operator[](int user) {
        int idx = hash(user);
        return table[idx];
    }

    void getAllTransactions(vector<vector<T>>& result) {
        for (int i = 0; i < maxSize; i++) {
            if (!table[i].empty()) {
                result.push_back(table[i]);
            }
        }
    }
};


class Transaction {
private:
    int fromID;
    int toID;
    double money;
    string time;
public:
    Transaction(int fromID, int toID, double money, string time)
        : fromID(fromID), toID(toID), money(money), time(time) {}

    bool operator==(Transaction &other) {
        return fromID == other.fromID && toID == other.toID && money == other.money && time == other.time; 
    }

    void str() {
        cout << setw(10) << fromID
                     << setw(10) << toID
                     << setw(15) << fixed << setprecision(2) << money
                     << setw(15) << time << "\n";
    } 

    int getFromID() const { return fromID; }
    int getToID()const { return toID; }
    double getMoney() const { return money; }
    string getTime() const { return time; }

};

class DetectFraudSystem {
private:
    const int maxMoney = 10000;
    HashTable<Transaction> user;

public:
    DetectFraudSystem() {}

    bool addTransaction(int fromID, int toID, double money, string time) {
        Transaction trans(fromID, toID, money, time);
        if (detectFraud(trans))  {
            cout << "Giao dich bat thuong.\n";
            return false;
        }
        else 
            return user.insert(fromID, trans);
    }

    bool detectFraud(Transaction& trans) {
        // check tien > 10000
        if (trans.getMoney() > 10000) {
            return true;
        }

        int userID = trans.getFromID();
        vector<Transaction> transList = user[userID];
        int toID = trans.getToID();
        string time = trans.getTime();

        // check 5 giao dich 
        if (transList.size() >= 4)  {
            string t = transList[transList.size() - 4].getTime();
            if (isOneMinute(time, t)) {
                return true;
            }
        }

        //check 3 lan cung 1 tai khoan trong 1p
        int count  = 0;
        for (int i = transList.size() - 1; i >= 0; i--) {
            string t = transList[i].getTime();
            if (!isOneMinute(time, t)) 
                break;
            if (transList[i].getToID() == toID) count++;
            if (count == 3) break;
        }
        if (count == 3) {
            return true;
        }

        return false;

    }

    void showTransaction() {
        vector<vector<Transaction>> transactions;
        user.getAllTransactions(transactions);
        if (transactions.empty()) {
            cout << "No transactions found.\n";
            return;
        }

        cout << "\n===================== TRANSACTION HISTORY ======================\n";
        cout << setw(10) << "From ID" << setw(10) << "To ID" << setw(15) << "Money" << setw(15) << "Time" <<  "\n";
        cout << string(65, '-') << "\n";
        for (auto& transList : transactions) {
            int userID = transList[0].getFromID();
            cout << "User " << userID << ":\n";
            for (auto& trans : transList) {
                trans.str();
            }
            cout << "\n";
        }
        cout << "===========================================================\n\n\n\n\n\n";
    }
};

int main() {
    int n;
    DetectFraudSystem *System = new DetectFraudSystem;
    do {
        cout << "==============================MENU==============================\n";
        cout << "1. Them giao dich.\n";
        cout << "2. Hien cac giao dich trong he thong.\n";
        cout << "3. Thoat.\n";
        cout << "Nhap vao 1 gia tri tu 1 den 3.\n";
        cin >> n;
        switch (n) {
            case 1: {
                system("clear");
                int fromID, toID;
                double money;
                string time;
                cout << "Nhap ID nguoi gui: ";
                cin >> fromID;
                cout << "Nhap ID nguoi nhan: ";
                cin >> toID;
                cout << "Nhap so tien can gui: ";
                cin >> money;
                cout << "Nhap thoi gian thuc hien giao dich (hh:mm:ss): ";
                cin.ignore();
                getline(cin, time);
                cout << "\n\n\n";

                
                if (System->addTransaction(fromID, toID, money, time))
                    cout << "Them giao dich thanh cong.\n";
                else 
                    cout << "Them giao dich khong thanh cong.\n";
                break;
            }
            case 2: {
                system("clear");
                System->showTransaction();
                break;
            }
            default: {}
        }

    } while (n != 3);
    delete System;
    return 0;
}