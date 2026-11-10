#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    double tinh_phi() const;
    void hien_thi() const;
};

phuong_tien::phuong_tien() : ma_xe(0), loai_xe(""), gio_vao(0), tg_do(0) {}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg)
    : ma_xe(ma), loai_xe(loai), gio_vao(gio), tg_do(tg) {}

int phuong_tien::lay_ma_xe() const { return ma_xe; }
string phuong_tien::lay_loai_xe() const { return loai_xe; }

double phuong_tien::tinh_phi() const {
    double gia = (loai_xe == "Car") ? 6.0 : (loai_xe == "Motorcycle") ? 4.0 : 2.0;
    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    double tong = 0;
    for (int h = 0; h < tg_do; ++h) {
        if (h < 2) tong += gia * (cao_diem ? 1.30 : 0.95);
        else       tong += gia * 0.90;
    }
    return tong;
}

void phuong_tien::hien_thi() const {
    cout << "  ID: " << ma_xe << " | " << loai_xe
         << " | " << gio_vao << "h | " << tg_do << "h"
         << " | Phi: $" << fixed << setprecision(2) << tinh_phi() << "\n";
}

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    static const int max_phuongtien = 3;
   phuong_tien phuongtien[max_phuongtien];   
    int currentVehicleCount;

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    bool them(phuong_tien v);
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;
    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;
    bool isFull() const {
    	return currentVehicleCount >= max_phuongtien;
	}
	bool addVehicle(const phuong_tien & v){
		if(isFull()){
			return false;
		}
		phuongtien[currentVehicleCount] = v;
		currentVehicleCount++;
		return true;
	}
	int findVehicleIndex(int ma_xe) const{
		for(int i = 0;i < currentVehicleCount;i++){
			if(phuongtien[i].lay_ma_xe() == ma_xe){
				return i ;
			}
		}
		return -1;
	}
	bool removeVehicle(int ma_xe){
		int index = findVehicleIndex(ma_xe);
		if(index == -1){
			return false;
		}
		for(int i = index ;i < currentVehicleCount - 1 ;i++){
			phuongtien[i] = phuongtien[i+1];
		}
		currentVehicleCount--;
		return true;
	}
	void displayLotInfo() const{
		cout<<"[Ma bai xe: "<<ma_bai << " | Kich thuoc: "<< kich_thuoc << " | So xe: "<< currentVehicleCount << "/"<< max_phuongtien << "]" <<endl ;
		if(currentVehicleCount == 0){
			cout<<"Bai xe dang trong"<< endl;
			return;
		}
		for(int i = 0; i <= currentVehicleCount;i++ ){
			cout << "Vi tri "<<(i + 1) << ": ";
			phuongtien[i].hien_thi();
			cout << endl;
		}
	}
};

bai_xe::bai_xe() : ma_bai(0), kich_thuoc('S'), currentVehicleCount(0) {}

bai_xe::bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(kt),currentVehicleCount(0) {}

int bai_xe::lay_ma() const { return ma_bai; }


class SystemInterface {
private:
    static const int max_lots = 10 ;
    bai_xe baixe[max_lots] ;
	int currentLotCount;
public:
    SystemInterface();
    void runMenu();
    bool isParkIDExists(int pID) const {
        for (int i = 0; i < currentLotCount; ++i) {
            if (baixe[i].lay_ma() == pID) {
                return true;
            }
        }
        return false;
    }
    int generateRandomID() const {
        return rand() % 1000 + 1;
    }
bool isVehicleIDExists(int ma_xe) const {
    for (int i = 0; i < currentLotCount; ++i) {
        if (baixe[i].chua(ma_xe)) {
            return true;
        }
    }
    return false;
}
};

void SystemInterface::runMenu() {
    int chon;
    while (true) {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        cout << "Chon: ";
        cin >> chon;
//các e chuyển sang lệnh switch cho thầy
		if(!(cin >> chon)){
			cout << "loi: Vui long nhap mot so nguyen hop le!\n";
			cin.clear();
			return;
		}
		switch(chon){
			case 1 : {
				if(currentLotCount >= max_lots){
					cout << "He thong da dat toi da " << max_lots << " bai do!\n";
					break;
				}
				int ma ; char kt;
				cout << "Ma bai: "; cin >> ma;
				while(isParkIDExists(ma)){
					cout << " Ma bai " << ma << " da ton tai!";
					ma = generateRandomID();
					cout << " He thong tu dong doi thanh ID moi: " << ma << endl;
				}
				cout << "Kich thuoc (S/M/L): "; cin >> kt;
				baixe[currentLotCount] = bai_xe(ma,kt);
				currentLotCount++;
				cout << " Da tao bai " << ma << " thanh cong!\n";
				break;
			}
			case 2 :{
				if(currentLotCount == 0){
					cout << " Chua co bai do nao trong he thong!\n";
					break;
				}
				int ma, gio, tg;
				string loai;
				cout << " Ma bai: "<<ma; 
				while(isVehicleIDExists(ma)){
					cout << " Ma xe " << ma << " da ton tai trong he thong!";
					ma = generateRandomID();
					cout << " He thong tu dong doi thanh ID thanh: " << ma << endl;
				}
				cout << "Loai (Car/Motorcycle/Bicycle): "; cin >> loai;
                cout << "Gio vao (0-23): "; cin >> gio;
                cout << "Thoi luong (1-23): "; cin >> tg;
                phuong_tien v(ma, loai, gio, tg);

                bool ok = false;
                for (int i = 0; i < currentLotCount; ++i) {
                    if (baixe[i].them(v)) {
                        ok = true;
                        break;
                    }
                }
                if (ok) {
                    cout << "-> Da them xe " << ma << " | Phi: $" << fixed << setprecision(2) << v.tinh_phi() << "\n";
                } else {
                    cout << "-> Tat ca cac bai do deu da day!\n";
                } 
				break;
			}
			case 3: {
                int ma;
                cout << "Ma bai can xoa: "; cin >> ma;
                int index = -1;
                for (int i = 0; i < currentLotCount; ++i) {
                    if (baixe[i].lay_ma() == ma) {
                        index = i;
                        break;
                    }
                }

                if (index != -1) {
                    for (int i = index; i < currentLotCount - 1; ++i) {
                        baixe[i] = baixe[i + 1];
                    }
                    currentLotCount--;
                    cout << "-> Da xoa bai " << ma << "\n";
                } else {
                    cout << "-> Khong tim thay bai do co ma " << ma << "\n";
                }
                break;
            }
            case 4: {
                int ma;
                cout << "Ma xe can lay ra: "; cin >> ma;
                bool ok = false;
                for (int i = 0; i < currentLotCount; ++i) {
                    if (baixe[i].xoa(ma)) {
                        ok = true;
                        break;
                    }
                }
                cout << (ok ? "-> Da lay xe ra thanh cong\n" : "-> Khong tim thay xe trong he thong\n");
                break;
            }
            case 5: {
                if (currentLotCount == 0) {
                    cout << "-> He thong chua co bai do nao.\n";
                } else {
                    for (int i = 0; i < currentLotCount; ++i) {
                        baixe[i].hien_thi();
                    }
                }
                break;
            }
            case 6: {
                int ma;
                cout << "Ma bai: "; cin >> ma;
                bool found = false;
                for (int i = 0; i < currentLotCount; ++i) {
                    if (baixe[i].lay_ma() == ma) {
                        baixe[i].hien_thi();
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "-> Khong tim thay bai do co ma " << ma << "\n";
                }
                break;
            }
            case 7: {
                string loai;
                cout << "Loai xe: "; cin >> loai;
                int dem; double tong;
                bool foundAny = false;
                for (int i = 0; i < currentLotCount; ++i) {
                    if (baixe[i].co_loai(loai, dem, tong)) {
                        baixe[i].hien_thi();
                        foundAny = true;
                    }
                }
                if (!foundAny) {
                    cout << "-> Khong co bai nao chua loai xe nay.\n";
                }
                break;
            }
            case 8: {
                string loai_arr[3] = {"Car", "Motorcycle", "Bicycle"};
                for (int t = 0; t < 3; ++t) {
                    int dem = 0; double tong = 0;
                    int d; double s;
                    for (int i = 0; i < currentLotCount; ++i) {
                        if (baixe[i].co_loai(loai_arr[t], d, s)) {
                            dem += d;
                            tong += s;
                        }
                    }
                    cout << loai_arr[t] << ": ";
                    if (dem == 0) cout << "khong co xe\n";
                    else cout << dem << " xe | TB: $" << fixed << setprecision(2) << tong / dem << "\n";
                }
                break;
            }
            case 9:
                cout << "-> Thoat chuong trinh...\n";
                return;
            default:
                cout << "-> Lua chon khong hop le! Vui long chon lai tu 1 den 9.\n";
        }
    }
		}
       


int main() {
    SystemInterface sys;
    sys.runMenu();
    return 0;
}
