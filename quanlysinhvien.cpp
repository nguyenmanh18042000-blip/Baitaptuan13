#include <iostream>
#include <string.h>

using namespace std;

// --- CÂU 1: KHAI BÁO CẤU TRÚC ---
struct Ngay {
    int ngay, thang, nam;
};

struct SinhVien {
    char maSV[8];
    char hoTen[50];
    int gioiTinh;
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

struct Node {
    SinhVien data;
    Node *link;
};

struct List {
    Node *first;
    Node *last;
};

void Init(List &l) {
    l.first = l.last = NULL;
}

// --- HÀM BỔ TRỢ ---
Node* CreateNode(SinhVien x) {
    Node *p = new Node;
    if (p == NULL) return NULL;
    p->data = x;
    p->link = NULL;
    return p;
}

void NhapSV(SinhVien &sv) {
    cout << "Nhap ma SV (8 ky tu): "; cin >> sv.maSV;
    cin.ignore();
    cout << "Nhap ho ten: "; cin.getline(sv.hoTen, 50);
    cout << "Gioi tinh (0: Nam, 1: Nu): "; cin >> sv.gioiTinh;
    cout << "Ngay sinh (nhap ngay thang nam cach nhau khoang trang): "; 
    cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam;
    cin.ignore();
    cout << "Nhap dia chi: "; cin.getline(sv.diaChi, 100);
    cout << "Nhap lop: "; cin.getline(sv.lop, 12);
    cout << "Nhap khoa: "; cin.getline(sv.khoa, 7);
}

void XuatSV(SinhVien sv) {
    cout << sv.maSV << " | " << sv.hoTen << " | " << sv.ngaySinh.ngay << "/" << sv.ngaySinh.thang << "/" << sv.ngaySinh.nam << " | " << sv.lop << endl;
}

// --- CÂU 2: CHÈN VÀ GIỮ THỨ TỰ TĂNG DẦN ---
void InsertOrder(List &l, SinhVien sv) {
    Node *p = CreateNode(sv);
    if (l.first == NULL || strcmp(p->data.maSV, l.first->data.maSV) < 0) {
        p->link = l.first;
        l.first = p;
        if (l.last == NULL) l.last = p;
    } else {
        Node *ins = l.first;
        while (ins->link != NULL && strcmp(ins->link->data.maSV, p->data.maSV) < 0) {
            ins = ins->link;
        }
        p->link = ins->link;
        ins->link = p;
        if (p->link == NULL) l.last = p;
    }
}

// --- CÂU 3: IN SV CÙNG NGÀY SINH ---
void InSVCungNgaySinh(List l, Ngay d) {
    bool found = false;
    Node *p = l.first;
    while (p != NULL) {
        if (p->data.ngaySinh.ngay == d.ngay && p->data.ngaySinh.thang == d.thang && p->data.ngaySinh.nam == d.nam) {
            XuatSV(p->data);
            found = true;
        }
        p = p->link;
    }
    if (!found) cout << "-> Khong tim thay sinh vien cung ngay sinh" << endl;
}

// --- CÂU 4: LOẠI BỎ SV CÙNG NGÀY SINH ---
void XoaSVCungNgaySinh(List &l, Ngay d) {
    Node *p = l.first;
    Node *prev = NULL;
    while (p != NULL) {
        if (p->data.ngaySinh.ngay == d.ngay && p->data.ngaySinh.thang == d.thang && p->data.ngaySinh.nam == d.nam) {
            Node *tmp = p;
            if (prev == NULL) l.first = p->link;
            else prev->link = p->link;
            p = p->link;
            delete tmp;
        } else {
            prev = p;
            p = p->link;
        }
    }
}

int main() {
    List l;
    Init(l);
    int n;
    cout << "Nhap so luong sinh vien ban dau: "; cin >> n;

    for (int i = 0; i < n; i++) {
        SinhVien sv;
        cout << "\nNhap sinh vien thu " << i + 1 << ":" << endl;
        NhapSV(sv);
        InsertOrder(l, sv);
    }

    cout << "\n--- DANH SACH SINH VIEN (DA SAP XEP TANG DAN) ---" << endl;
    Node *p = l.first;
    while(p != NULL) {
        XuatSV(p->data);
        p = p->link;
    }

    Ngay ngayCheck;
    cout << "\nNhap ngay thang nam sinh de kiem tra (vi du: 18 4 2006): "; 
    cin >> ngayCheck.ngay >> ngayCheck.thang >> ngayCheck.nam;

    cout << "\n--- KET QUA TIM KIEM ---" << endl;
    InSVCungNgaySinh(l, ngayCheck);

    XoaSVCungNgaySinh(l, ngayCheck);
    cout << "\n--- DANH SACH SAU KHI XOA SINH VIEN CUNG NGAY SINH TREN ---" << endl;
    p = l.first;
    if (p == NULL) cout << "(Danh sach trong)" << endl;
    while(p != NULL) {
        XuatSV(p->data);
        p = p->link;
    }

    return 0;
}