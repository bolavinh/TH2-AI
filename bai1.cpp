#include <iostream>
#include <string>
#include <unordered_map>
#include <cctype>
#include <stack>

using namespace std;

bool PhuDinh(bool giaTri) {
    return !giaTri;
}

bool Va(bool a, bool b) {
    return a && b;
}

bool Hoac(bool a, bool b) {
    return a || b;
}
bool Tuyen(bool a, bool b) {
    return !(a && b);
}
bool SaiLech(bool a, bool b) {
    return !a || b;
}
bool KiemTraHopLe(const string& bieuThuc) {
    int ngoacMo = 0;

    
    for (size_t i = 0; i < bieuThuc.size(); i++) {
        char kyTu = bieuThuc[i];

        
        if (kyTu == '(') {
            ngoacMo++;
        } else if (kyTu == ')') {
            if (ngoacMo == 0) return false; 
            ngoacMo--;
        }

        
        if (kyTu == '&' || kyTu == '|' || kyTu == '>' || kyTu == '~') {
            if (i == 0 || i == bieuThuc.size() - 1) {
                return false; 
            }
            if (bieuThuc[i - 1] == '(' || bieuThuc[i + 1] == ')') {
                return false; 
            }
        }
    }

                        
    return ngoacMo == 0;
}


bool TinhGiaTriBieuThuc(const string& bieuThuc, const unordered_map<char, bool>& giaTriBien) {
    stack<bool> nganXepToanHang; 
    stack<char> nganXepToanTu; 

    for (size_t i = 0; i < bieuThuc.size(); i++) {
        char kyTu = bieuThuc[i];

        
        if (isalpha(kyTu)) {
            nganXepToanHang.push(giaTriBien.at(kyTu));
        }
        
        else if (kyTu == '~') {
            bool toanHang = nganXepToanHang.top();
            nganXepToanHang.pop();
            nganXepToanHang.push(PhuDinh(toanHang));
        }
        
        else if (kyTu == '&') {
            nganXepToanTu.push(kyTu);
        }
        
        else if (kyTu == '|') {
            nganXepToanTu.push(kyTu);
        }
        
        else if (kyTu == '>') {
            nganXepToanTu.push(kyTu);
        }
        
        else if (kyTu == '(') {
            nganXepToanTu.push(kyTu);
        }
        
        else if (kyTu == ')') {
            while (nganXepToanTu.top() != '(') {
                char toanTu = nganXepToanTu.top();
                nganXepToanTu.pop();
                bool toanHangPhai = nganXepToanHang.top();
                nganXepToanHang.pop();
                bool toanHangTrai = nganXepToanHang.top();
                nganXepToanHang.pop();

                // Thuc hien phep toan logic tuong ung
                if (toanTu == '&') {
                    nganXepToanHang.push(Va(toanHangTrai, toanHangPhai));
                } else if (toanTu == '|') {
                    nganXepToanHang.push(Hoac(toanHangTrai, toanHangPhai));
                } else if (toanTu == '>') {
                    nganXepToanHang.push(SaiLech(toanHangTrai, toanHangPhai));
                }
            }
            nganXepToanTu.pop(); // Xoa dau ngoac mo
        }
    }

    // Xu ly cac phep toan con lai trong ngan xep toan tu
    while (!nganXepToanTu.empty()) {
        char toanTu = nganXepToanTu.top();
        nganXepToanTu.pop();
        bool toanHangPhai = nganXepToanHang.top();
        nganXepToanHang.pop();
        bool toanHangTrai = nganXepToanHang.top();
        nganXepToanHang.pop();

        if (toanTu == '&') {
            nganXepToanHang.push(Va(toanHangTrai, toanHangPhai));
        } else if (toanTu == '|') {
            nganXepToanHang.push(Hoac(toanHangTrai, toanHangPhai));
        } else if (toanTu == '>') {
            nganXepToanHang.push(SaiLech(toanHangTrai, toanHangPhai));
        }
    }

    return nganXepToanHang.top(); // Tro ve gia tri cuoi cung
}

int main() {
    string bieuThuc;
    cout << "Nhap bieu thuc logic: ";
    getline(cin, bieuThuc);

    // Kiem tra tinh hop le cua bieu thuc
    if (!KiemTraHopLe(bieuThuc)) {
        cout << "Bieu thuc khong hop le: " << endl;
        return 1;
    }

    // Nhap gia tri cua cac bien logic
    unordered_map<char, bool> giaTriBien;
    cout << "Nhap gia tri cho cac bien (vi du: A: true, B: false):" << endl;

    for (size_t i = 0; i < bieuThuc.size(); i++) {
        if (isalpha(bieuThuc[i])) {
            char bien = bieuThuc[i];
            if (giaTriBien.find(bien) == giaTriBien.end()) {
                bool giaTri;
                cout << "Nhap gia tri cho " << bien << " (true hoac false): ";
                cin >> boolalpha >> giaTri;
                giaTriBien[bien] = giaTri;
            }
        }
    }

    // Tinh toan gia tri cua bieu thuc
    bool ketQua = TinhGiaTriBieuThuc(bieuThuc, giaTriBien);
    cout << "Ket qua cua bieu thuc loi: " << (ketQua ? "True" : "False") << endl;

    return 0;
}
