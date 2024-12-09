#include <bits/stdc++.h>
#define ll long long
using namespace std;
const string itemFilename = "item.txt";
const string memberFilename = "member.txt";

struct item {
    int id;
    string name;
    float price;
    ll amount;
};

struct member {
    string name;
};

void saveItemsToFile(const vector<item>& produk, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& p : produk) {
            file << p.id << " " << p.name << " " << p.price << " " << p.amount << "\n";
        }
        file.close();
        cout << "Data barang berhasil disimpan ke file.\n";
    } else {
        cout << "Gagal membuka file untuk menyimpan data barang.\n";
    }
}

void loadItemsFromFile(vector<item>& produk, int& nextId, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        produk.clear();
        item temp;
        while (file >> temp.id >> temp.name >> temp.price >> temp.amount) {
            produk.push_back(temp);
            nextId = max(nextId, temp.id + 1); 
        }
        file.close();
        sort(produk.begin(), produk.end(), [](const item& a, const item& b) {
            return a.name < b.name;
        });
        saveItemsToFile(produk, filename);
        cout << "Data barang berhasil dimuat dan diurutkan dari file.\n";
    } else {
        cout << "File tidak ditemukan, memulai dengan data kosong.\n";
    }
}

void saveMembersToFile(const vector<member>& members, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& m : members) {
            file << m.name << "\n";
        }
        file.close();
        cout << "Data member berhasil disimpan ke file.\n";
    } else {
        cout << "Gagal membuka file untuk menyimpan data member.\n";
    }
}

void loadMembersFromFile(vector<member>& members, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        members.clear();
        member temp;
        while (file >> temp.name) {
            members.push_back(temp);
        }
        file.close();
        sort(members.begin(), members.end(), [](const member& a, const member& b) {
            return a.name < b.name;
        });
        saveMembersToFile(members, filename);
        cout << "Data member berhasil dimuat dan diurutkan dari file.\n";
    } else {
        cout << "File tidak ditemukan, memulai dengan data member kosong.\n";
    }
}

void addItem(vector<item>& produk, int& nextId) {
    item newItem;
    newItem.id = nextId++;
    cout << "Masukkan nama barang: ";
    cin.ignore();
    getline(cin, newItem.name);
    cout << "Masukkan harga barang: ";
    cin >> newItem.price;
    cout << "Masukkan jumlah barang: ";
    cin >> newItem.amount;
    produk.push_back(newItem);
    cout << "Barang berhasil ditambahkan! ID Barang: " << newItem.id << "\n";
}

void removeItem(vector<item>& produk) {
    string name;
    cout << "Masukkan nama barang yang ingin dihapus: ";
    cin.ignore();
    getline(cin, name);
    auto it = remove_if(produk.begin(), produk.end(), [&name](const item& p) { return p.name == name; });
    if (it != produk.end()) {
        produk.erase(it, produk.end());
        cout << "Barang berhasil dihapus.\n";
    } else {
        cout << "Barang tidak ditemukan.\n";
    }
}

void editPrice(vector<item>& produk) {
    string name;
    cout << "Masukkan nama barang yang ingin diedit harganya: ";
    cin.ignore();
    getline(cin, name);
    auto it = find_if(produk.begin(), produk.end(), [&name](const item& p) { return p.name == name; });
    if (it != produk.end()) {
        cout << "Masukkan harga baru: ";
        cin >> it->price;
        cout << "Harga berhasil diubah.\n";
    } else {
        cout << "Barang tidak ditemukan.\n";
    }
}

void editStock(vector<item>& produk) {
    string name;
    cout << "Masukkan nama barang yang ingin diedit stocknya: ";
    cin.ignore();
    getline(cin, name);
    auto it = find_if(produk.begin(), produk.end(), [&name](const item& p) { return p.name == name; });
    if (it != produk.end()) {
        cout << "Masukkan jumlah stock yang ditambah: ";
        int at;
        cin>>at;
        it->amount += at;
        cout << "Stock diubah.\n";
    } else {
        cout << "Barang tidak ditemukan.\n";
    }
}

void searchItemByName(const vector<item>& produk) {
    string name;
    cout << "Masukkan nama barang yang ingin dicari: ";
    cin.ignore();
    getline(cin, name);
    auto it = find_if(produk.begin(), produk.end(), [&name](const item& p) { return p.name == name; });
    if (it != produk.end()) {
        cout << "Barang ditemukan:\n";
        cout << "ID: " << it->id << "\nNama: " << it->name << "\nHarga: " << it->price << "\nJumlah: " << it->amount << endl;
    } else {
        cout << "Barang tidak ditemukan.\n";
    }
}

void Stock(vector<item>& produk, int& nextId) {
    int stockpilih;
    do {
        cout << "Selamat datang di menu \"Manajemen Stock\"\nApa yang bisa saya bantu?\n";
        cout << "1. Menambah Barang\n";
        cout << "2. Menghapus Barang\n";
        cout << "3. Mengedit Harga\n";
        cout << "4. Mengedit Stock\n";
        cout << "5. Mencari Barang via Nama\n";
        cout << "6. Kembali\n";
        cout << "(Ketikan angka saja)\nInput : ";
        cin >> stockpilih;
        switch (stockpilih) {
            case 1: addItem(produk, nextId); break;
            case 2: removeItem(produk); break;
            case 3: editPrice(produk); break;
            case 4: editStock(produk); break;
            case 5: searchItemByName(produk); break;
            case 6: cout << "\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (stockpilih != 6);
}

bool isMember(const vector<member>& members, const string& name) {
    return any_of(members.begin(), members.end(), [&name](const member& m) { return m.name == name; });
}

void penjualan(vector<item>& produk, double& totalProfit, const vector<member>& members) {
    string itemName, buyerName;
    ll jumlah;
    cout << "Masukkan nama pembeli: ";
    cin.ignore();
    getline(cin, buyerName);
    cout << "Masukkan nama barang yang ingin dibeli: ";
    getline(cin, itemName);
    cout << "Masukkan jumlah barang yang ingin dibeli: ";
    cin >> jumlah;
    auto it = find_if(produk.begin(), produk.end(), [&itemName](const item& p) { return p.name == itemName; });
    if (it != produk.end() && it->amount >= jumlah) {
        double discount = isMember(members, buyerName) ? 0.95 : 1.0;
        double profit = jumlah * it->price * discount;
        totalProfit += profit;
        it->amount -= jumlah;
        cout << "Penjualan berhasil! " << (discount < 1.0 ? "Member discount applied.\n" : "");
        cout << "Total keuntungan: " << profit << endl;
    } else {
        cout << "Barang tidak ditemukan atau jumlah stok tidak cukup.\n";
    }
}

void manageMembers(vector<member>& members) {
    int memberChoice;
    do {
        cout << "Selamat datang di menu \"Manajemen Member\"\nApa yang bisa saya bantu?\n";
        cout << "1. Tambah Member\n";
        cout << "2. Hapus Member\n";
        cout << "3. Kembali\n";
        cout << "(Ketikan angka saja)\nInput : ";
        cin >> memberChoice;
        switch (memberChoice) {
            case 1: {
                member newMember;
                cout << "Masukkan nama member baru: ";
                cin.ignore();
                getline(cin, newMember.name);
                members.push_back(newMember);
                sort(members.begin(), members.end(), [](const member& a, const member& b) {
                    return a.name < b.name;
                });
                cout << "Member berhasil ditambahkan.\n";
                break;
            }
            case 2: {
                string name;
                cout << "Masukkan nama member yang ingin dihapus: ";
                cin.ignore();
                getline(cin, name);
                auto it = remove_if(members.begin(), members.end(), [&name](const member& m) { return m.name == name; });
                if (it != members.end()) {
                    members.erase(it, members.end());
                    cout << "Member berhasil dihapus.\n";
                } else {
                    cout << "Member tidak ditemukan.\n";
                }
                break;
            }
            case 3: cout << "\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (memberChoice != 3);
}

signed main() {
    vector<item> produk(100);
    vector<member> members;
    int jumlahProduk = 0, pilihan; 
    int nextId = 1;
    double totalProfit = 0;

    loadItemsFromFile(produk, nextId, itemFilename);
    loadMembersFromFile(members, memberFilename);

    do {
        cout << "Selamat datang di program \"Manajemen Toko\"\nApa yang bisa saya bantu?\n";
        cout << "1. Penjualan\n";
        cout << "2. Manajemen Stock\n";
        cout << "3. Manajemen Member\n";
        cout << "4. Keluar\n";
        cout << "(Ketikan angka saja)\nInput : ";
        cin >> pilihan;
        switch (pilihan) {
            case 1: penjualan(produk, totalProfit, members); break;
            case 2: Stock(produk,nextId); break;
            case 3: manageMembers(members); break;
            case 4: cout << "Sampai jumpa kembali!\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 4);

    saveItemsToFile(produk, itemFilename);
    saveMembersToFile(members, memberFilename);

    return 0;
}
