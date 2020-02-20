#define _CRT_SECURE_NO_WARNINGS
#include"Expression.h"
#include<stdlib.h>
#include"File.h"

#define THAP_PHAN_MAX 20

//Bieu thuc

void xoaTrang(char* s)
{
	int len = strlen(s);

	for (int i = 0; i < len; i++)
	{
		while (*(s + i) == ' ')
		{
			for (int j = i; j < len - 1; j++)
				*(s + j) = *(s + j + 1);
			len--;
			*(s + len) = '\0';
		}
	}
}

void xoaPhanTuChuoi(char* s, int pos)
{
	int len = strlen(s);

	if (pos < 0 || pos >= len)
		return;

	for (int i = pos; i < len - 1; i++)
		*(s + i) = *(s + i + 1);
	len--;
	*(s + len) = '\0';
}

void chuanHoaBieuThuc(char* s)
{
	xoaTrang(s);

	int len = strlen(s);

	for (int i = 0; i < len - 1; i++)
	{
		if (i == 0)
			if (*(s) == '-'&&*(s + 1) == '(') {
				chenPhanTu(s, '0', 0); len++;
			}
		if (*(s + i) == '-'&&*(s + i + 1) == '('&&*(s + i - 1) == '(') {
			chenPhanTu(s, '0', i); len++;
		}

		if (*(s + i) == '+' || *(s + i) == '-')
		{
			while (*(s + i + 1) == '+' || *(s + i + 1) == '-')
			{
				if (*(s + i) == '+') {
					xoaPhanTuChuoi(s, i);
					len--;
				}
				else {
					if (*(s + i + 1) == '+')
						xoaPhanTuChuoi(s, i + 1);
					else {
						xoaPhanTuChuoi(s, i);
						*(s + i) = '+';
					}
					len--;
				}
			}
		}

		if (*(s + i) == '+')
			if (*(s + i - 1) == '(')
			{
				xoaPhanTuChuoi(s, i);
				len--;
			}
	}
}

bool kiemTraBieuThuc(char *expression)
{
	chuanHoaBieuThuc(expression);

	if (*(expression) == '/' || *(expression) == '*' || *(expression) == '^' || *(expression) == ')' || *(expression) == '.')
		return false;

	int len = strlen(expression);
	int mongoac = 0, dongngoac = 0;
	for (int i = 0; i < len - 1; i++)
	{
		if (strchr("+-*/^().0123456789", *(expression + i)) == NULL)
		{
			//printf("%d\t1",i);
			return false;
		}

		if (*(expression + i) == '/' || *(expression + i) == '*' || *(expression + i) == '.' || *(expression + i) == '(' || *(expression + i) == '^' || *(expression + i) == '+' || *(expression + i) == '-')
		{
			if (*(expression + i + 1) == '*' || *(expression + i + 1) == '^' || *(expression + i + 1) == '.' || *(expression + i + 1) == '/' || *(expression + i + 1) == ')')
			{
				//printf("%d\t2",i);
				return false;
			}
			if (*(expression + i) == '(')
				mongoac++;
		}

		if (*(expression + i) == ')')
		{
			dongngoac++;
			if (strchr("+-*^/", *(expression + i + 1)) == NULL) {
				//printf("%d\t3",i);
				return false;
			}
		}

		//Sau cham khong phai la so
		if (*(expression + i) == '.'&&*(expression + i + 1) < '0'&&*(expression + i + 1) > '9') {
			//	printf("%d\t4",i);
			return false;
		}

		//Sau so la dong ngoac
		if (*(expression + i) >= '0'&&*(expression + i) <= '9')
			if (*(expression + i + 1) == '(') {
				//printf("%d\t5",i);
				return false;
			}

		//Toan hang co hai dau cham
		if (*(expression + i) == '.') {
			int j = i + 1;
			while (strchr("+-*()/^", *(expression + j)) == NULL&&j<len) {
				if (*(expression + j) == '.') return false; j++;
			}
		}
	}

	if (strchr(")0123456789", *(expression + len - 1)) == NULL) {
		//printf("6");
		return false;
	}
	if (*(expression + len - 1) == ')')
		dongngoac++;

	if (dongngoac != mongoac) {
		//printf("7");
		return false;
	}

	return true;
}

//So nguyen khong am
int soSanhSoNguyenKhongDau(char* a, char* b)
{
	int lena = strlen(a), lenb = strlen(b);
	if (lena > lenb)
		return 1;
	if (lena < lenb)
		return -1;

	int result = strcmp(a, b);
	return result;
}

bool soSanhNhoHon(char* number1, char* number2)
{
	if (strlen(number1) < strlen(number2))
		return true;
	else
		if (strlen(number1) == strlen(number2))
		{
			for (int i = strlen(number1) - 1; i >= 0; i--)
				if (*(number1 + i) < *(number2 + i))
					return true;
		}

	return false;
}

void chuanHoaToanHang(char* number)
{
	if (*(number) == '0')
		while (*(number) == '0'&&*(number + 1) != '.'&&strlen(number) > 1)
			xoaPhanTuChuoi(number, 0);

	if (*(number) == '-')
		while (*(number + 1) == '0'&&*(number + 2) != '.'&&strlen(number) > 4)
			xoaPhanTuChuoi(number, 1);

	bool dog = false;
	int len = strlen(number);
	for (int i = 1; i<len; i++)
		if (*(number + i) == '.') {
			dog = true;
			break;
		}
	if (dog == true)
	{
		if (*(number + len - 1) == '0')
			while (*(number + strlen(number) - 1) == '0'&&*(number + strlen(number) - 2) != '.')
				xoaPhanTuChuoi(number, strlen(number) - 1);
	}
}

void layThapPhan(char* number, int soLuong)
{
	bool flag = false;

	int i = 0, dem = 0;
	while (*(number + i))
	{
		if (*(number + i) == '.')
		{
			flag = true;
			break;
		}
		i++;
	}

	if (flag)
	{
		int count = 0;
		while (*(number + i) && count <= soLuong)
		{
			i++;
			count++;
		}
		if (count > soLuong&&*(number + i + 1))
		{
			*(number + i) = '\0';
		}

		while (*(number + strlen(number) - 1) == '0' && *(number + strlen(number) - 2) != '.')
		{
			xoaPhanTuChuoi(number, strlen(number) - 1);
		}
	}
}

char* congHaiSoNguyenKhongAm(char* number1, char* number2)
{
	char* result;
	bool nho = false;

	if (strlen(number1) < strlen(number2))
		swapPointer(&number1, &number2);

	int len1 = strlen(number1), len2 = strlen(number2), lenMax = len1;

	result = (char*)malloc(sizeof(char)*(lenMax + 2));
	memset(result, '0', lenMax);

	for (int i = 0; i < len2; i++)
	{
		int temp = *(number2 + len2 - i - 1) - '0' + *(number1 + len1 - i - 1) - '0';

		if (nho)
			temp++;

		if (temp > 9)
			nho = true;
		else
			nho = false;

		temp = temp % 10;

		*(result + len1 - i) = temp + '0';
	}

	for (int i = 0; i < lenMax - len2; i++)
	{
		int temp = *(number1 + len1 - len2 - i - 1) - '0';

		if (nho)
			temp++;
		if (temp > 9)
			nho = true;
		else
			nho = false;

		temp = temp % 10;

		*(result + len1 - len2 - i) = temp + '0';
	}

	*(result + lenMax + 1) = '\0';

	if (nho)
	{
		*(result) = '1';
	}
	else
	{
		for (int i = 0; i <= lenMax; i++)
			*(result + i) = *(result + i + 1);
	}

	return result;
}

void swapPointer(char** a, char** b)
{
	char* temp = *a;
	*a = *b;
	*b = temp;
}

char* truHaiSoNguyenKhongAm(char* number1, char* number2)
{
	char* result;
	bool sign = false, nho = false;

	if (/*soSanhNhoHon(number1, number2)*/soSanhSoNguyenKhongDau(number1, number2) < 0)
	{
		swapPointer(&number1, &number2);
		sign = true;
	}

	int len1 = strlen(number1), len2 = strlen(number2), lenMax = len1;

	result = (char*)malloc(sizeof(char)*(lenMax + 2));
	memset(result, '0', lenMax + 2);

	for (int i = 0; i < len2; i++)
	{
		int temp = *(number1 + len1 - i - 1) - *(number2 + len2 - i - 1);

		if (nho)
			temp--;

		if (temp < 0)
		{
			temp += 10;
			nho = true;
		}
		else
			nho = false;

		*(result + lenMax - i) = temp + '0';
	}

	for (int i = 0; i < len1 - len2; i++)
	{
		int temp = *(number1 + len1 - len2 - i - 1) - '0';

		if (nho == true)
			temp--;

		if (temp < 0)
		{
			temp += 10;
			nho = true;
		}
		else
			nho = false;

		*(result + len1 - len2 - i) = temp + '0';
	}

	for (int i = 0; i < lenMax; i++)
	{
		*(result + i) = *(result + i + 1);
	}
	*(result + lenMax) = '\0';

	return result;
}

bool soSanhSoBangNhauNhoHon(char* a, char* b) //len(a)=len(b)
{
	int len = strlen(a);
	for (int i = 0; i < len; i++)
	{
		if (*(a + i) > *(b + i))
		{
			return false;
		}
		else
			if (*(a + i) < *(b + i))
			{
				return true;
			}
	}

	return true;
}

char* truNguyen(char* number1, char* number2)
{
	char* result;
	bool sign = false, nho = false;
	int lenMax;
	int len1 = strlen(number1), len2 = strlen(number2);

	if (len1 != len2)
	{
		if (len1 > len2)
		{
			lenMax = len1;
			number2 = (char*)realloc(number2, (lenMax + 1) * sizeof(char));
			for (int i = len2; i < lenMax; i++)
				*(number2 + i) = '0';
			*(number2 + lenMax) = '\0';
		}
		else
		{
			if (len1 < len2) {
				lenMax = len2;
				number1 = (char*)realloc(number1, (lenMax + 1) * sizeof(char));
				for (int i = len1; i < lenMax; i++)
					*(number1 + i) = '0';
				*(number1 + lenMax) = '\0';
			}
			else
				lenMax = len1;
		}
	}

	if (soSanhSoBangNhauNhoHon(number1, number2) == false/*soSanhNhoHon(number1,number2)*/) {
		sign = false;
	}
	else
	{
		swapPointer(&number1, &number2);
		sign = true;
	}

	result = (char*)malloc(sizeof(char)*(lenMax + 2));
	memset(result, '0', lenMax + 2);

	int temp;
	int len = strlen(number1);
	for (int i = 0; i < lenMax; i++)
	{
		temp = *(number1 + len - i - 1) - *(number2 + len - i - 1);

		if (nho)
			temp--;

		if (temp < 0)
		{
			temp += 10;
			nho = true;
		}
		else
			nho = false;

		*(result + lenMax - i + 1) = temp + '0';
	}

	if (*(result + 1) == '0' && sign == true)
	{
		*(result) = '-';
		*(result + lenMax + 1) = '\0';

		return result;
	}

	for (int i = 0; i < lenMax; i++)
	{
		*(result + i) = *(result + i + 1);
	}
	*(result + lenMax + 1) = '\0';
	chuanHoaToanHang(result);

	return result;
}

char* nhanVoiSoDon(char* a, int so)
{
	char* result;
	int nho = 0, len = strlen(a);

	result = (char*)malloc(sizeof(char)*(len + 2));
	memset(result, '0', len);
	if (strcmp(a, "0") == 0 || so == 0) {
		*(result + len) = '\0';
		return result;
	}

	for (int i = 0; i < len; i++)
	{
		int temp = (*(a + len - i - 1) - '0')*so;

		if (nho)
			temp += nho;

		if (temp > 9)
			nho = temp / 10;
		else
			nho = 0;

		temp = temp % 10;

		*(result + len - i) = temp + '0';
	}

	*(result + len + 1) = '\0';

	if (nho)
	{
		*(result) = nho + '0';
	}
	else
	{
		for (int i = 0; i <= len; i++)
			*(result + i) = *(result + i + 1);
	}

	return result;
}

char* nhanHaiSoNguyen(char* number1, char* number2)
{
	char* result = NULL;
	int len1 = strlen(number1), len2 = strlen(number2), temp;
	int len = len1 + len2;
	result = (char*)malloc(sizeof(char)*len + 2);
	memset(result, '0', len);
	*(result + len) = '\0';

	for (int i = 0; i < len2; i++)
	{
		temp = *(number2 + len2 - i - 1) - '0';

		char* nhanDon = nhanVoiSoDon(number1, temp);
		int lenTemp = strlen(nhanDon);
		nhanDon = (char*)realloc(nhanDon, sizeof(char)*(lenTemp + i + 1));
		for (int j = 0; j < i; j++)
			*(nhanDon + lenTemp + j) = '0';
		*(nhanDon + lenTemp + i) = '\0';

		result = congHaiSoNguyenKhongAm(result, nhanDon);
	}

	*(result + len) = '\0';

	return result;
}

//Chuan bi
void tachSoThuc(char* number, char* &nguyen, char *&thuc)
{
	char* t = (char*)malloc(sizeof(char)*(strlen(number) + 1));
	strcpy(t, number);

	char* temp = strtok(t, ".");
	while (temp != NULL)
	{
		if (nguyen == NULL)
		{
			nguyen = (char*)malloc(sizeof(char)*(strlen(temp) + 1));
			strcpy(nguyen, temp);
		}
		else
		{
			thuc = (char*)malloc(sizeof(char)*(strlen(temp) + 1));
			strcpy(thuc, temp);
		}

		temp = strtok(NULL, ".");
	}

	if (thuc == NULL)
	{
		thuc = (char*)malloc(sizeof(char) * 2);
		*(thuc) = '0';
		*(thuc + 1) = '\0';
	}
}

void ghepSoThuc(char* &number, char* nguyen, char* thuc)
{
	int len = strlen(nguyen) + strlen(thuc) + 2;
	number = (char*)malloc(sizeof(char)*(len));
	strcpy(number, nguyen);
	strcat(number, ".");
	strcat(number, thuc);
	*(number + len) = '\0';
}

void chenPhanTu(char* &s, char c, int pos)
{
	int len = strlen(s);

	s = (char*)realloc(s, sizeof(char)*(len + 2));
	for (int i = len; i > pos; i--)
		*(s + i) = *(s + i - 1);
	*(s + pos) = c;

	*(s + len + 1) = '\0';
}

void themChamDong(char* &s, int pos)
{
	int len = strlen(s);

	char* temp = (char*)realloc(s, sizeof(char)*(len + 2));
	for (int i = len; i > len - pos; i--)
		*(temp + i) = *(temp + i - 1);
	*(temp + len - pos) = '.';

	*(temp + len + 1) = '\0';

	if (*(temp) == '-'&&*(temp + 1) == '.')
	{
		chenPhanTu(temp, '0', 1);
	}
	if (*(temp) == '.')
		chenPhanTu(temp, '0', 0);

	s = temp;
}

void ghepSoNguyen(char* &number, char* nguyen, char* thuc)
{
	char* temp;
	int len = strlen(nguyen) + strlen(thuc) + 1;
	temp = (char*)malloc(sizeof(char)*(len));
	strcpy(temp, nguyen);
	strcat(temp, thuc);
	*(temp + len - 1) = '\0';
	number = temp;
}

char* congHaiSoThucKhongDau(char* number1, char* number2)
{
	char* result = NULL, *nguyen1 = NULL, *nguyen2 = NULL, *thuc1 = NULL, *thuc2 = NULL;;
	char* soNguyen1, *soNguyen2;
	int pos;

	tachSoThuc(number1, nguyen1, thuc1);
	tachSoThuc(number2, nguyen2, thuc2);

	if (strlen(thuc1) != strlen(thuc2))
	{
		if (strlen(thuc1) < strlen(thuc2))
		{
			pos = strlen(thuc2);
			swapPointer(&thuc1, &thuc2);
			swapPointer(&nguyen1, &nguyen2);
		}
		else
			pos = strlen(thuc1);
	}
	else
	{
		pos = strlen(thuc1);
	}

	thuc2 = (char*)realloc(thuc2, sizeof(char)*(pos + 1));
	for (int i = strlen(thuc2); i < pos; i++)
		*(thuc2 + i) = '0';
	*(thuc2 + pos) = '\0';


	ghepSoNguyen(soNguyen1, nguyen1, thuc1);
	ghepSoNguyen(soNguyen2, nguyen2, thuc2);
	//printf("%s\n%s\n", soNguyen1, soNguyen2);

	result = congHaiSoNguyenKhongAm(soNguyen1, soNguyen2);
	themChamDong(result, pos);

	return result;
}

bool soThucKhongDauBeHon(char* a, char* b)
{
	char* result, *nguyen1 = NULL, *nguyen2 = NULL, *thuc1 = NULL, *thuc2 = NULL;

	tachSoThuc(a, nguyen1, thuc1);
	tachSoThuc(b, nguyen2, thuc2);

	int lennguyen1 = strlen(nguyen1), lennguyen2 = strlen(nguyen2);

	if (lennguyen1 < lennguyen2)
		return true;
	if (lennguyen1 > lennguyen2)
		return false;
	if (strcmp(nguyen1, nguyen2) < 0)
		return true;
	if (strcmp(nguyen1, nguyen2) > 0)
		return false;
	if (strcmp(thuc1, thuc2) < 0)
		return true;

	return false;
}

char* truHaiSoThucKhongDau(char* number1, char* number2)
{
	char* result, *nguyen1 = NULL, *nguyen2 = NULL, *thuc1 = NULL, *thuc2 = NULL;
	char* soNguyen1, *soNguyen2;
	int pos;
	bool dau = soThucKhongDauBeHon(number1, number2);

	tachSoThuc(number1, nguyen1, thuc1);
	tachSoThuc(number2, nguyen2, thuc2);

	if (strlen(thuc1) >= strlen(thuc2))
	{
		pos = strlen(thuc1);

		thuc2 = (char*)realloc(thuc2, sizeof(char)*(pos + 1));
		for (int i = strlen(thuc2); i < pos; i++)
			*(thuc2 + i) = '0';
		*(thuc2 + pos) = '\0';

		ghepSoNguyen(soNguyen1, nguyen1, thuc1);
		ghepSoNguyen(soNguyen2, nguyen2, thuc2);
	}
	else
	{
		pos = strlen(thuc2);

		thuc1 = (char*)realloc(thuc1, sizeof(char)*(pos + 1));
		for (int i = strlen(thuc1); i < pos; i++)
			*(thuc1 + i) = '0';
		*(thuc1 + pos) = '\0';

		ghepSoNguyen(soNguyen1, nguyen2, thuc2);
		ghepSoNguyen(soNguyen2, nguyen1, thuc1);
	}
	result = truHaiSoNguyenKhongAm(soNguyen1, soNguyen2);
	themChamDong(result, pos);
	chuanHoaToanHang(result);
	if (dau)
		chenPhanTu(result, '-', 0);

	return result;
}

char* nhanHaiSoThucKhongDau(char* number1, char* number2)
{
	char* result = NULL;
	char* nguyen1 = NULL, *nguyen2 = NULL, *thuc1 = NULL, *thuc2 = NULL;
	char* songuyen1, *songuyen2;

	tachSoThuc(number1, nguyen1, thuc1);
	tachSoThuc(number2, nguyen2, thuc2);
	int pos = strlen(thuc1) + strlen(thuc2);

	ghepSoNguyen(songuyen1, nguyen1, thuc1);
	ghepSoNguyen(songuyen2, nguyen2, thuc2);

	result = nhanHaiSoNguyen(songuyen1, songuyen2);
	themChamDong(result, pos);

	chuanHoaToanHang(result);

	return result;
}

char* chiaNguyenBangTru(char* &a, char* &b)
{
	if (strcmp(b, "1") == 0 || strcmp(a, "0") == 0)
		return a;

	char* result = NULL;
	char* resultnguyen = NULL;
	resultnguyen = (char*)malloc(sizeof(char) * 2);
	*(resultnguyen) = '0'; *(resultnguyen + 1) = '\0';

	while (soSanhSoNguyenKhongDau(a, b) >= 0)
	{
		resultnguyen = congHaiSoNguyenKhongAm(resultnguyen, "1");

		a = truHaiSoNguyenKhongAm(a, b);
		chuanHoaToanHang(a);
	}

	result = resultnguyen;
	return result;
}

char* chiaHaiSoNguyenKhongDau(char* number1, char* number2)
{
	if (strcmp(number2, "1") == 0 || strcmp(number1, "0") == 0)
		return number1;

	int count = 0;
	char* result = NULL;
	char* resnguyen = NULL, *respt = NULL;

	resnguyen = chiaNguyen(number1, number2);

	while (count < THAP_PHAN_MAX && strcmp(number1, "0") != 0)
	{
		number1 = (char*)realloc(number1, sizeof(char)*(strlen(number1) + 2));
		strcat(number1, "0");

		if (respt == NULL)
		{
			char*temp = chiaNguyen(number1, number2);
			respt = (char*)malloc(sizeof(char)*(++count + 1));
			strcpy(respt, temp);
			*(respt + 1) = '\0';
		}
		else
		{
			char*temp = chiaNguyen(number1, number2);
			respt = (char*)realloc(respt, sizeof(char)*(++count + 1));
			strcat(respt, temp);
		}
	}
	if (respt == NULL)
	{
		char*temp = chiaNguyen(number1, number2);
		respt = (char*)malloc(sizeof(char) * 2);
		*(respt) = '0';
		*(respt + 1) = '\0';
	}

	ghepSoThuc(result, resnguyen, respt);
	return result;
}

char* chiaHaiSoThucKhongDau(char* number1, char* number2)
{
	char* result = NULL;
	char* nguyen1 = NULL, *nguyen2 = NULL, *thuc1 = NULL, *thuc2 = NULL;
	char* songuyen1, *songuyen2;

	tachSoThuc(number1, nguyen1, thuc1);
	tachSoThuc(number2, nguyen2, thuc2);
	int lenpt1 = strlen(thuc1), lenpt2 = strlen(thuc2);
	int thempt = abs(lenpt1 - lenpt2);

	if (lenpt1 > lenpt2)
	{
		thuc2 = (char*)realloc(thuc2, sizeof(char)*(lenpt2 + thempt + 1));
		for (int i = 0; i < thempt; i++)
			*(thuc2 + lenpt2 + i) = '0';

		*(thuc2 + lenpt2 + thempt) = '\0';
	}
	else {
		if (lenpt1 < lenpt2)
		{
			thuc1 = (char*)realloc(thuc1, sizeof(char)*(lenpt1 + thempt + 1));
			for (int i = 0; i < thempt; i++)
				*(thuc1 + lenpt1 + i) = '0';

			*(thuc1 + lenpt1 + thempt) = '\0';
		}
	}

	ghepSoNguyen(songuyen1, nguyen1, thuc1);
	ghepSoNguyen(songuyen2, nguyen2, thuc2);
	chuanHoaToanHang(songuyen1); chuanHoaToanHang(songuyen2);

	result = chiaHaiSoNguyenKhongDau(songuyen1, songuyen2);

	return result;
}

char* tinhLuyThuaSoThucKhongDau(char* a, char* b)
{
	char* result = (char*)malloc(sizeof(char)*(strlen(a) + 1));
	strcpy(result, a);

	int mu = atoi(b);
	if (mu == 0)
	{
		result = (char*)realloc(result, sizeof(char) * 2);
		*(result) = '1';
		*(result + 1) = '\0';
		return result;
	}
	if (mu == 1)
		return result;

	for (int i = 1; i < mu; i++)
		result = nhanSoThuc(result, a);

	chuanHoaToanHang(result);

	//Xu li so 0 cuoi
	bool flag = false;
	int i = 0, dem = 0;
	while (*(result + i))
	{
		if (*(result + i) == '.')
		{
			flag = true;
			break;
		}
		i++;
	}

	if (flag)
	{
		while (*(result + strlen(result) - 1) == '0' && *(result + strlen(result) - 2) != '.')
		{
			xoaPhanTuChuoi(result, strlen(result) - 1);
		}
	}

	return result;
}

//So thuc
char* congSoThuc(char* a, char* b)
{
	char* result;

	if (*(a) == '-')
	{
		if (*(b) == '-')
		{
			result = congHaiSoThucKhongDau(a + 1, b + 1);
			chenPhanTu(result, '-', 0);
		}
		else
			result = truHaiSoThucKhongDau(b, a + 1);
	}
	else
	{
		if (*(b) == '-')
			result = truHaiSoThucKhongDau(a, b + 1);
		else
			result = congHaiSoThucKhongDau(a, b);
	}

	return result;
}

char* truSoThuc(char* a, char* b)
{
	char* result;

	if (*(a) == '-')
	{
		if (*(b) == '-')
			result = truHaiSoThucKhongDau(b + 1, a + 1);
		else
		{
			result = congHaiSoThucKhongDau(b, a + 1);
			chenPhanTu(result, '-', 0);
		}
	}
	else
	{
		if (*(b) == '-')
			result = congHaiSoThucKhongDau(a, b + 1);
		else
			result = truHaiSoThucKhongDau(a, b);
	}

	return result;
}

char* nhanSoThuc(char* a, char* b)
{
	char* result;

	if (*(a) == '-')
	{
		if (*(b) == '-')
			result = nhanHaiSoThucKhongDau(a + 1, b + 1);
		else
		{
			result = nhanHaiSoThucKhongDau(a + 1, b);
			chenPhanTu(result, '-', 0);
		}
	}
	else
	{
		if (*(b) == '-')
		{
			result = nhanHaiSoThucKhongDau(a, b + 1);
			chenPhanTu(result, '-', 0);
		}
		else
			result = nhanHaiSoThucKhongDau(a, b);
	}

	return result;
}

char* chiaSoThuc(char* a, char* b)
{
	char* result;

	if (*(a) == '-')
	{
		if (*(b) == '-')
			result = chiaHaiSoThucKhongDau(a + 1, b + 1);
		else
		{
			result = chiaHaiSoThucKhongDau(a + 1, b);
			chenPhanTu(result, '-', 0);
		}
	}
	else
	{
		if (*(b) == '-')
		{
			result = chiaHaiSoThucKhongDau(a, b + 1);
			chenPhanTu(result, '-', 0);
		}
		else
			result = chiaHaiSoThucKhongDau(a, b);
	}

	return result;
}

char* tinhLuyThuaSoThuc(char* a, char* mu)
{
	char* result;

	if (*(a) == '-')
	{
		if (atoi(mu) % 2 == 0)
			result = tinhLuyThuaSoThucKhongDau(a + 1, mu);
		else
		{
			result = tinhLuyThuaSoThucKhongDau(a + 1, mu);
			chenPhanTu(result, '-', 0);
		}
	}
	else
		result = tinhLuyThuaSoThucKhongDau(a, mu);

	layThapPhan(result, 20);
	return result;
}

//
char* chiaNguyen(char* &number1, char* number2)
{
	if (strcmp(number2, "1") == 0 || strcmp(number1, "0") == 0)
		return number1;

	char* result = NULL;
	int lenchia = strlen(number2);

	result = (char*)malloc(sizeof(char) * 2);
	*(result) = '0'; *(result + 1) = '\0';
	if (soSanhSoNguyenKhongDau(number1, number2) < 0)
		return result;

	char* chia = (char*)malloc(sizeof(char)*(lenchia + 1));
	for (int i = 0; i < lenchia; i++)
		*(chia + i) = *(number1 + i);
	*(chia + lenchia) = '\0';
	if (soSanhSoNguyenKhongDau(chia, number2) < 0)
	{
		chia = (char*)realloc(chia, sizeof(char)*(lenchia + 2));
		*(chia + lenchia) = *(number1 + lenchia);
		*(chia + lenchia + 1) = '\0';
	}
	char* sochia = (char*)malloc(sizeof(char)*(strlen(number1) + 1));
	strcpy(sochia, number1);
	lenchia = strlen(chia);
	int count = lenchia, len1 = strlen(number1);

	while (soSanhSoNguyenKhongDau(chia, number2) >= 0 || len1 - count >= 0)
	{
		chuanHoaToanHang(chia);

		char *temp = chiaNguyenBangTru(chia, number2);
		result = (char*)realloc(result, sizeof(char)*(strlen(result) + 2));
		strcat(result, temp);

		lenchia = strlen(chia);
		char*tem = (char*)realloc(chia, sizeof(char)*(lenchia + 2));
		*(tem + lenchia) = *(number1 + count);
		*(tem + lenchia + 1) = '\0';
		lenchia++;
		chia = tem;

		count++;
	}

	chuanHoaToanHang(sochia);
	number1 = chia;
	chuanHoaToanHang(result);
	//	printf("result :  %s\n", result);

	return result;
}

//Bieu Thuc
bool khongLaToanTu(char c)
{
	return (strchr("+-*/^()", c) == NULL);
}

bool toanTuUuTienHon(char* t1, char* t2)
{
	char toan1, toan2;
	toan1 = *(t1), toan2 = *(t2);

	if (toan2 == '^'&&toan1 == '^')
		return true;
	if (toan2 == '/' && (toan1 == '/' || toan1 == '^'))
		return true;
	if ((toan2 == '*'&&toan1 == '*' || toan1 == '/' || toan1 == '^'))
		return true;
	if (toan2 == '-' && (toan1 != '+' || toan1 != '('))
		return true;
	if (toan2 == '+' && (toan1 != '('))
		return true;
	return false;
}

int doUuTien(char* t)
{
	char toan;
	toan = *(t);

	if (toan == '(') return 0;
	if (toan == '+' || toan == '-') return 1;
	if (toan == '*' || toan == '/') return 2;
	if (toan == '^') return 3;
}

bool laDauAm(char* expression, int pos)
{
	if (*(expression + pos) != '-')
		return false;

	if (pos == 0)
		if (*(expression + 1) >= '0'&&*(expression + 1) <= '9')
			return true;
	if (*(expression + pos - 1) == '(')
		return true;
	if ((*(expression + pos - 1) >= '0' && *(expression + pos - 1) <= '9') || *(expression + pos - 1) <= ')')
		return false;

	return true;
}

bool khongLaToanTu(char* s)
{
	return (strstr("+-*/^()", s) == NULL);
}

void chuyenVaoQueue(char* expression, Queue& qu)
{
	int len = strlen(expression);
	int i = 0;
	while (i < len)
	{
		if (laDauAm(expression, i))
		{
			char*temp = (char*)malloc(sizeof(char) * 2);
			*(temp) = *(expression + i);
			*(temp + 1) = '\0';
			i++;

			int lenth = 1;
			while (strchr("+-*/^()", *(expression + i)) == NULL)
			{
				temp = (char*)realloc(temp, sizeof(char) * (lenth + 2));
				*(temp + lenth) = *(expression + i);
				*(temp + lenth + 1) = '\0';
				lenth++;
				i++;
			}
			pushQueue(qu, temp);
		}
		else
		{
			if (strchr("+-*/^()", *(expression + i)) != NULL)
			{
				char*temp = (char*)malloc(sizeof(char) * 2);
				*(temp) = *(expression + i);
				*(temp + 1) = '\0';
				i++;
				pushQueue(qu, temp);
			}
			else
			{
				char*temp = (char*)malloc(sizeof(char) * 2);
				*(temp) = *(expression + i);
				*(temp + 1) = '\0';
				i++;

				int lenth = 1;
				while (strchr("+-*/^()", *(expression + i)) == NULL)
				{
					temp = (char*)realloc(temp, sizeof(char) * (lenth + 2));
					*(temp + lenth) = *(expression + i);
					*(temp + lenth + 1) = '\0';
					lenth++;
					i++;
				}
				pushQueue(qu, temp);
			}
		}
	}
}

void chuyenBaLan(Queue quEx, Queue &qu)
{
	Stack stTemp;
	initStack(stTemp);

	while (!queueIsEmpty(quEx))
	{
		char* temp = popQueue(quEx);
		if (khongLaToanTu(temp) == true)
			pushQueue(qu, temp);
		else
		{
			if (strcmp("(", temp) == 0)
				pushStack(stTemp, temp);
			else if (strcmp(")", temp) == 0)
			{
				//	char* toanTuTemp = peekStack(stTemp);
				while (strcmp("(", stTemp.tail->data) != 0)
				{
					char* toanTuTemp = popStack(stTemp);
					pushQueue(qu, toanTuTemp);
				}
				popStack(stTemp);
			}
			else {
				if (strcmp("^", temp) == 0)
					pushStack(stTemp, temp);
				else {
					while (!stackIsEmpty(stTemp) && doUuTien(temp) <= doUuTien(stTemp.tail->data))
					{
						char* toanTuTemp = popStack(stTemp);
						pushQueue(qu, toanTuTemp);
					}
					pushStack(stTemp, temp);
				}
			}
		}
	}

	while (!stackIsEmpty(stTemp))
	{
		char* toanTuTemp = popStack(stTemp);
		pushQueue(qu, toanTuTemp);
	}
}

void tinhBieuThuc(char* fileinput, char* fileoutput)
{
	char* expression = NULL;
	readFile(fileinput, expression);

	if (expression != NULL) {
		if (!kiemTraBieuThuc(expression))
		{
			printf("Bieu thuc khong hop le!\n");
			return;
		}

		char* result = NULL;

		Queue quEx;
		Queue qu;
		Stack st;
		initQueue(quEx);
		initStack(st);
		initQueue(qu);

		chuanHoaBieuThuc(expression);
		chuyenVaoQueue(expression, quEx);
		chuyenBaLan(quEx, qu);

		while (!queueIsEmpty(qu))
		{
			result = popQueue(qu);
			if (khongLaToanTu(result))
			{
				pushStack(st, result);
			}
			else
			{
				char* toanHang1 = popStack(st);
				//chuanHoaToanHang(toanHang1);
				char* toanHang2 = popStack(st);
				chuanHoaToanHang(toanHang2);

				if (strcmp("+", result) == 0)
					result = congSoThuc(toanHang2, toanHang1);
				else
					if (strcmp("-", result) == 0)
						result = truSoThuc(toanHang2, toanHang1);
					else
						if (strcmp("*", result) == 0)
							result = nhanSoThuc(toanHang2, toanHang1);
						else {
							if (strcmp("/", result) == 0) {
								if (strcmp(toanHang1, "0") == 0 || strcmp(toanHang1, "0.0") == 0) {
									printf("Loi phep chia!\n");
									break;
								}
								else
									result = chiaSoThuc(toanHang2, toanHang1);
							}
							else
								result = tinhLuyThuaSoThuc(toanHang2, toanHang1);
						}

						pushStack(st, result);
			}
		}

		chuanHoaToanHang(result);
		writeFile(fileoutput, result);
	}
}