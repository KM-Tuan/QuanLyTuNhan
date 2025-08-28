// Thực hiện tạo chương trình quản lý các tù nhân trên sao hỏa. Thông tin các tù nhân được lưu trong cây nhị phân tìm kím dựa theo mã tù nhân.
// Cấu trúc thông tin của các tù nhân:
                // Struct TuNhan {
                // String maTuNhan;
                // String hoTen;
                // String ngayVaoTu;
                // dd/mm/yyyy
                // Int Concac; (thời gian trong tù của tù nhân – tính bằng ngày)
                // };
// Phát triển những tính năng sau:
// a) Nhập họ tên và ngày vào tù và của tù nhân được nhập từ bàn phím. Hệ thống sẽ tự động cấp ngẫu nhiên mã tù nhân cho tù nhân.
// Lưu ý: maTuNhan có 6 kí tự nằm trong phạm vi 26 chữ cái tiếng anh và số.
// b) Tìm kím 1 tù nhân qua mã tù nhân. Xác nhận CÓ hoặc KHÔNG về sự tồn tại của mã tù nhân này. Xuất danh sách tù nhân theo mã tù nhân (alpha bê).
// c) Tạo 1 danh sách liên kết chứa mã tù nhân và ngày ra tù của tù nhân. Nếu (ngày vào tù + thời gian trong tù = ngày ra tù),
// thả về chuồng và xóa mọi thông tin của người này trong cây và danh sách liên kết. Nếu (ngày vào tù + thời gian trong tù > ngày ra tù), 
// đền bù cho người này bằng số tiền 1đ ứng với mỗi ngày tù nhân ở quá hạn. Thông tin tù nhân được xóa sẽ ghi vào file riêng (bao gồm tiền đền bù).

#include <iostream>
#include <conio.h>
#include <string>
#include <cstring>
#include <fstream>
#include <ctime>
#define CONST 10
using namespace std;

struct TuNhan
{
    string maTN;
    string hoTen;
    string ngayVaoTu, ngayRaTu;
    int thoiGianVaoTu;
};
struct Node
{
    TuNhan info;
    Node *left, *right;
};
Node *root;
void init();
string creat_maTN();
void creat_Node(TuNhan &tn);
int insert(Node *&p, TuNhan tn);
Node *search(Node *p, TuNhan tn);
void process_list(Node *p, int start);
void delete_list(Node *p);


struct NodeList
{
    TuNhan info;
    NodeList *link;
};
NodeList *first;
void init_Linklist();
void insert_list(Node *p);
void processLNR(Node *p);
void process_Linklist();
void delete_Linklist();





int main()
{
    TuNhan tn;
    int choose;
    bool in = false;
    srand(time(0));
    do
    {
        system("cls");
        cout << "================= MENU =================" << endl
            << "1. Khoi tao nha tu: " << endl
            << "2. Them tu nhan: " << endl
            << "3. Tim kiem tu nhan: " << endl
            << "4. Xuat nha tu: " << endl
            << "5. Khoi tao danh sach: " << endl
            << "6. Xuat danh sach: " << endl
            << "7. Thoat: " << endl
            << "Chon: "; cin >> choose;
        switch (choose)
        {
            case 1: 
                init();
                in = true;
                cout << "Khoi tao nha tu thanh cong!" << endl;
                break;
            case 2:
                if (in)
                {
                    creat_Node(tn);
                    if (insert(root, tn))
                        cout << "Them thanh cong!" << endl;
                    else
                        cout << "Khong the them!" << endl;
                }
                else
                    cout << "Vui long khoi tao nha tu!" << endl;
                break;
            case 3:
                if (in)
                {
                    cout << "Nhap ma tu nhan: "; 
                    cin.ignore();
                    getline(cin, tn.maTN);
                    if (search(root, tn) != NULL)
                    {
                        cout << endl;
                        cout << "Tu nhan " << tn.maTN << " co ton tai!" << endl;
                        cout << "=========================================" << endl;
                        cout << "Ho va ten: " << tn.hoTen << endl;
                        cout << "Ngay vao tu: " << tn.ngayVaoTu << endl;
                        cout << "Ngay ra tu: " << tn.ngayRaTu << endl;
                        cout << "Thoi gian: " << tn.thoiGianVaoTu << " ngay" << endl;
                    }
                    else
                        cout << "Tu nhan " << tn.maTN << " khong ton tai!" << endl;
                }
                else
                    cout << "Vui long khoi tao nha tu!" << endl;
                break;
            case 4:
                if (in)
                {
                    int start(0);
                    cout << endl;
                    cout << "================= NHA TU =================" << endl;
                    process_list(root, start);
                }
                else
                    cout << "Vui long khoi tao nha tu!" << endl;
                break;
            case 5:
                if (in)
                {
                    init_Linklist();
                    processLNR(root);
                    cout << "Khoi tao danh sach thanh cong!" << endl;
                }
                else
                    cout << "Vui long khoi tao nha tu!" << endl;
                break;
            case 6:
                if (in)
                {
                    cout << endl;
                    cout << "Danh sach dang luu tru: ";
                    process_Linklist();
                }
                else
                    cout << "Vui long khoi tao nha tu!" << endl;
                break;
            default:
                cout << endl;
                cout << "Ban da chon thoat!" << endl;
                delete_list(root);
                delete_Linklist();
                _getch();
                return 0;
        }
        _getch();
    } while (choose >= 1 && choose <= 6);
}

void init()
{
    root = NULL;
}
string creat_maTN() {
    string maTuNhan = "";
    static const char arr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for (int i = 0; i < 6; ++i) {
        maTuNhan += arr[rand() % (sizeof(arr) - 1)];
    }
    return maTuNhan;
}
void creat_Node(TuNhan &tn)
{
    tn.maTN = creat_maTN();
    cin.ignore();
    cout << "Ho va ten: "; getline(cin, tn.hoTen);
    cout << "Ngay vao tu: "; getline(cin, tn.ngayVaoTu);
    cout << "Ngay ra tu: "; getline(cin, tn.ngayRaTu);
    cout << "Thoi gian vao tu: "; cin >> tn.thoiGianVaoTu;
}
int insert(Node *&p, TuNhan tn)
{
    if (p == NULL)
    {
        p = new Node;
        p->info = tn;
        p->left = NULL;
        p->right = NULL;
    }
    else
    {
        if (p->info.maTN == tn.maTN)
            return 0;
        else if (tn.maTN > p->info.maTN)
            return insert(p->right, tn);
        else
            return insert(p->left, tn);
    }
    return 1;
}
Node *search(Node *p, TuNhan tn)
{
    if (p == NULL) return NULL;
    if (p->info.maTN == tn.maTN) return p;
    else if (tn.maTN > p->info.maTN)
        return search(p->right, tn);
    else
        return search(p->left, tn);
}
void process_list(Node *p, int start)
{
    if (p == NULL) return;
    start += CONST;
    process_list(p->right, start);
    cout << endl;
    for (int i = CONST; i < start; i++)
        cout << " ";
    cout << p->info.maTN << endl;
    process_list(p->left, start);
}
void delete_list(Node *p)
{
    if (p == NULL) return;
    delete_list(p->left);
    delete_list(p->right);
    cout << "Da xoa tu nhan " << p->info.hoTen << " thanh cong!" << endl;
    delete p;   
}


void init_Linklist()
{
    first = NULL;
}
void insert_list(Node *p)
{
    NodeList *q = new NodeList;
    q->info.maTN = p->info.maTN;
    q->info.ngayRaTu = p->info.ngayRaTu;
    q->link = NULL;
    if (first != NULL)
    {
        NodeList *m = first;
        while (m->link != NULL)
            m = m->link;
        m->link = q;
    }
    else
    {
        q->link = first;
        first = q;
    }
}
void processLNR(Node *p)
{
    if (p == NULL) return;
    processLNR(p->left);
    insert_list(p);
    processLNR(p->right);
}
void process_Linklist()
{
    NodeList *p = first;
    while (p != NULL)
    {
        cout << p->info.maTN << "#" << p->info.ngayRaTu << "  ";
        p = p->link;
    }
}
void delete_Linklist()
{
    while (first != NULL)
    {
        NodeList *p = first;
        first = first->link;
        cout << "Da xoa tu nhan " << p->info.maTN << " thanh cong!" << endl;
        delete p;
    }
}
