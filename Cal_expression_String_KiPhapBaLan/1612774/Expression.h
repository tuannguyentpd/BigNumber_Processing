#pragma once

#include"LinkList.h"
#include"Stack.h"
#include"Queue.h"
#include<string.h>

void xoaTrang(char*);
void xoaPhanTuChuoi(char*, int);
void chuanHoaBieuThuc(char*);

int soSanhSoNguyenKhongDau(char*, char*);
bool kiemTraBieuThuc(char *);
void swapPointer(char**, char**);
bool soSanhNhoHon(char*, char*);
void chuanHoaToanHang(char*);
void layThapPhan(char*, int);
char* congHaiSoNguyenKhongAm(char*, char*);
char* truHaiSoNguyenKhongAm(char*, char*);
char* chiaNguyenBangTru(char* &, char* &);
char* chiaNguyen(char*&, char*);
char* nhanVoiSoDon(char*, int);
char* nhanHaiSoNguyen(char*, char*);
char* truNguyen(char*, char*);

//chuan bi...
void tachSoThuc(char*, char* &, char *&);
void ghepSoThuc(char*&, char*, char*);
char* congHaiSoThucKhongDau(char*, char*);
void themChamDong(char*&, int);
void ghepSoNguyen(char*&, char*, char*);
bool soThucKhongDauBeHon(char*, char*);
void chenPhanTu(char*&, char, int);
char* truHaiSoThucKhongDau(char*, char*);
char* nhanHaiSoThucKhongDau(char*, char*);
char* chiaHaiSoNguyenKhongDau(char*, char*);
char* chiaHaiSoThucKhongDau(char*, char*);
char* tinhLuyThuaSoThucKhongDau(char*, char*);

//So thuc
char* congSoThuc(char*, char*);
char* truSoThuc(char*, char*);
char* nhanSoThuc(char*, char*);
char* chiaSoThuc(char*, char*);
char* tinhLuyThuaSoThuc(char*, char*);

//Tinh toan
bool laDauAm(char*, int);
bool khongLaToanTu(char);
void chuyenBaLan(Stack, Queue &);
void tinhBieuThuc(char*, char*);
void chuyenVaoQueue(char*, Queue &);