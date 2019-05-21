#include <iostream>
#include <fstream>
#include <io.h>
#include <fcntl.h>
#include <limits>
#include <codecvt>
#include <windows.h>
#include <vector>
#include <sstream>
#undef max
#pragma execution_character_set( "utf-8" )
using namespace std;

//struct ngay sinh
struct ngaySinh {
	wstring ngay, thang, nam;
};
struct tenNhanVien {
	wstring ho, tenDem, ten;
};
struct chucVu {
	wstring tenChucVu;
	int priority = 4;
};
wstring to_vnLowerCase(wstring str);
bool soSanhString(wstring one, wstring two);
bool soSanhDate(wstring one, wstring two);

// nhan vien
class NhanVien
{
public:
	struct tenNhanVien ten;
	wstring luong;
	struct chucVu chucvu;
	struct ngaySinh ntn;
	wstring tenToString() {
		if (this->ten.tenDem==L"")
		{
			return ten.ho +L" "+ ten.ten;
		}
		return ten.ho + L" " + ten.tenDem + L" " + ten.ten;
	}
	wstring chucVuToString() {
		return chucvu.tenChucVu;
	}
	wstring ntnToString() {
		return ntn.ngay + L"/" + ntn.thang + L"/" + ntn.nam;
	}
	wstring hienThi() {
		return  L" Tên : " +tenToString() +L"   Chức vụ : " + chucVuToString() + L"	Ngày sinh : " + ntnToString() + L"	Hệ số lương : " + this->luong ;

	}
	bool timKiem(wstring str) {
		return false;
	}
	void capDo() {
		if (soSanhString(to_vnLowerCase(chucvu.tenChucVu),to_vnLowerCase(L"Tổng giám đốc")))
		{
			chucvu.priority = 1;
		}
		else if (soSanhString(to_vnLowerCase(chucvu.tenChucVu),to_vnLowerCase(L"Giám đốc")))
		{
			chucvu.priority = 2;
		}
		else if (soSanhString(to_vnLowerCase(chucvu.tenChucVu),to_vnLowerCase(L"Trưởng phòng")))
		{
			chucvu.priority = 3;
		}else if(soSanhString(to_vnLowerCase(chucvu.tenChucVu), to_vnLowerCase(L"Phó phòng")))
		{
			chucvu.priority = 4;
		}
		else {
			chucvu.priority = 5;
		}
	}
	wstring toString() {
		return tenToString() + L"," + chucVuToString() + L"," + ntnToString() + L"," + this->luong;
	}
	bool timTen(wstring wt) {
		if (soSanhString(this->tenToString(),wt)||
			soSanhString(this->ten.ten, wt)|| 
			soSanhString(this->ten.ho, wt)) {
			return true;
		}
		return false;
	}
	bool timChucVu(wstring wt) {
		if (soSanhString(this->chucvu.tenChucVu, wt))
		{
			return true;
		}
		return false;
	}
	bool timNtn(wstring wt) {
		if (soSanhDate(ntnToString(),wt)||
			soSanhDate(ntn.nam,wt)||
			soSanhDate(ntn.thang,wt)||
			soSanhDate(ntn.ngay,wt)
			) {
			return true;
		}
		return false;
	}
	bool timLuong(wstring dau,wstring wt) {
		if (dau == L"="&& stod(this->luong) == stod(wt)) {
				return true;
		}
		else if (dau == L"<" && stod(this->luong) < stod(wt))
		{
			return true;
		}
		else if (dau == L">" && stod(this->luong) > stod(wt))
		{
			return true;
		} 
		return false;
	}
};

//các hàm hiển thị giao diện
void clrscr()
{
	system("cls");
}
void canhBao() {
	clrscr();
	wcout << L"??? Giá trị bạn nhập vào không đúng ???";
	wcout << L"Vui lòng nhập lại" << endl;
	wcin.clear();
	wcin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void form(wstring str) {
	wcout <<endl<< L"----------------------------" << endl;
	wcout << L"|	" << str << endl;
	wcout << L"----------------------------" << endl;
}
void smallForm(wstring str) {
	wcout << endl << L"-----	" <<str<< L"		-----" << endl;
	
}
void tbTrong() {
	wcout <<endl << L"??? Bạn chưa nhập file vào ???" << endl;
	wcout << L"Vui lòng nhập phím 1 để nhập file nhân viên >>>>>>>>" << endl;
	wcout << endl;
}
wstring formInput() {
	wstring input;
	wstring infos;
	wcin.ignore();
	wcout << endl << L"Nhập họ và tên : ";
	getline(wcin, input);
	infos += input + L",";
	wcout << endl << L"Nhập chức vụ : ";
	getline(wcin, input);
	infos+= input + L",";
	wcout << endl << L"Nhập ngày tháng năm sinh : ";
	getline(wcin, input);
	infos += input + L",";
	wcout << endl << L"Nhập hệ số lương : ";
	getline(wcin, input);
	infos += input;
	return infos;
}
wstring to_vnLowerCase(wstring str) {
	for (wchar_t &c : str) {
		c = tolower(c);
		if (c == L'Đ')c = L'đ';
		if (c == L'Ă')c = L'ă';if (c == L'Ắ')c = L'ắ';if (c == L'Ằ')c = L'ằ';
		if (c == L'Ẳ')c = L'ẳ';if (c == L'Ẵ')c = L'ẵ';if (c == L'Ặ')c = L'ặ';
		if (c == L'Â')c = L'â'; if (c == L'Ấ')c = L'ấ'; if (c == L'Ầ')c = L'ầ';
		if (c == L'Ậ')c = L'ẩ'; if (c == L'Ậ')c = L'ậ'; if (c == L'Ậ')c = L'ậ';
		if (c == L'Ê')c = L'ê'; if (c == L'Ế')c = L'ế'; if (c == L'Ề')c = L'ề';
		if (c == L'Ể')c = L'ể'; if (c == L'Ễ')c = L'ễ'; if (c == L'Ệ')c = L'ệ';
		if (c == L'Ô')c = L'ô'; if (c == L'Ố')c = L'ố'; if (c == L'Ồ')c = L'ồ';
		if (c == L'Ổ')c = L'ổ'; if (c == L'Ổ')c = L'ổ'; if (c == L'Ộ')c = L'ộ';
		if (c == L'Ơ')c = L'ơ'; if (c == L'Ớ')c = L'ớ'; if (c == L'Ờ')c = L'ờ';
		if (c == L'Ở')c = L'ở'; if (c == L'Ỡ')c = L'ỡ'; if (c == L'Ợ')c = L'ợ';
		if (c == L'Ư')c = L'ư'; if (c == L'Ứ')c = L'ứ'; if (c == L'Ừ')c = L'ừ';
		if (c == L'Ử')c = L'ử'; if (c == L'ữ')c = L'ữ'; if (c == L'Ự')c = L'ự';

	}
	return str;
}
bool soSanhString(wstring one, wstring two) {
	vector <wstring> tokens1;
	wstring str1;
	wstringstream lineStr1(one);
	while (getline(lineStr1,str1,L' ')){
		tokens1.push_back(str1);
	}
	vector <wstring> tokens2;
	wstring str2;
	wstringstream lineStr2(two);
	while (getline(lineStr2, str2,L' ')) {
		tokens2.push_back(str2);
	}
	if (tokens2.size()==1)
	{
		if (to_vnLowerCase(one)==to_vnLowerCase(two))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else 
	{
		if (tokens1.size() == tokens2.size()) {
			for (int i = 0; i < tokens2.size(); i++)
			{
				if (to_vnLowerCase(tokens1[i])!=to_vnLowerCase(tokens2[i]))
				{
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}
	
}
bool soSanhDate(wstring one, wstring two) {
	vector <wstring> tokens1;
	wstring str1;
	wstringstream lineStr1(one);
	while (getline(lineStr1, str1, L'/')) {
		tokens1.push_back(str1);
	}
	vector <wstring> tokens2;
	wstring str2;
	wstringstream lineStr2(two);
	while (getline(lineStr2, str2, L'/')) {
		tokens2.push_back(str2);
	}

	if (tokens2.size() == 1)
	{

		if (stod(one) == stod(two))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else {
		if (tokens1.size() == tokens2.size()) {
			for (int i = 0; i < tokens2.size(); i++)
			{
				
				if (stod(tokens1[i])!=stod(tokens2[i]))
				{
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}

}
//struct node
struct node {
	NhanVien nhanVien;
	node* next = NULL;
};
NhanVien taoNhanVien(wstring line);
// danh sach nhan vien

class List {
private:
	node* first, * last;
public:
	int status = 0;
	List()
	{
		first = NULL;
		last = NULL;
	}
	node* getFirst() {
		return this->first;
	}
	// them nhan vien vao list
	void themNhanVien(NhanVien nv) {
		node* temp = new node;
		temp->nhanVien =nv;
		temp->next = NULL;
		//neu chua co nhan vien nao trong list
		if (first==NULL)
		{
			first = temp;
			last = temp;
		}
		else
			//neu co roi thi chuyen last sang node vua duoc them
		{
			//linked next cua last vao node vua them
			last->next = temp;
			last = last->next;
		}
	}	
	
	// hien thi nhan vien
	void hienThi() {
		node* current;
		current = first;
		while (current != NULL)
		{
			wcout << current->nhanVien.hienThi() << endl;
			current = current->next;
		}
	}
	
	//sắp xếp
	
	void swap(node* i, node* j) {
		NhanVien nv = i->nhanVien;
		i->nhanVien = j->nhanVien;
		j->nhanVien = nv;
	}
	void sapXepTheoLuong() {
		this->status = 4;
		node* i;
		node* j = NULL;
		int swapped;
		if (first == NULL)
		{
			return;
		}

		//bubble sort
		do
		{
			swapped = 0;
			i = first;

			while (i->next != j)
			{
				//so sanh i va i+1
				if (stod(i->nhanVien.luong) < stod(i->next->nhanVien.luong))
				{
					swap(i, i->next);
					swapped = 1;
				}
				i = i->next;
			}
			//thu hep chuoi so sanh
			j = i;
		} while (swapped);
		
	}
	void sapXepTen() {
		this->status = 1;
		node* i;
		node* j = NULL;
		int swapped;
		if (first == NULL)
		{
			return;
		}

		//bubble sort
		do
		{
			swapped = 0;
			i = first;

			while (i->next != j)
			{
				//so sanh i va i+1
				if (i->nhanVien.ten.ten > i->next->nhanVien.ten.ten)
				{
					swap(i, i->next);
					swapped = 1;
				}
				i = i->next;
			}
			//thu hep chuoi so sanh
			j = i;
		} while (swapped);
		
	}
	void sapXepTheoNtn() {
		this->status = 2;

		node* i;
		node* j = NULL;
		int swapped;
		if (first == NULL)
		{
			return;
		}

		//bubble sort
		do
		{
			swapped = 0;
			i = first;

			while (i->next != j)
			{
				//so sanh i va i+1
				if (stoi(i->nhanVien.ntn.nam) > stoi(i->next->nhanVien.ntn.nam))
				{
					swap(i, i->next);
					swapped = 1;
				}
				else if (stoi(i->nhanVien.ntn.nam) == stoi(i->next->nhanVien.ntn.nam)) {
					if (stoi(i->nhanVien.ntn.thang) > stoi(i->next->nhanVien.ntn.thang))
					{
						swap(i, i->next);
						swapped = 1;
					}
					else if (stoi(i->nhanVien.ntn.thang) == stoi(i->next->nhanVien.ntn.thang))
					{
						if (stoi(i->nhanVien.ntn.thang) > stoi(i->next->nhanVien.ntn.thang)) {
							swap(i, i->next);
							swapped = 1;
						}
					}
				}
				i = i->next;
			}
			//thu hep chuoi so sanh
			j = i;
		} while (swapped);
		
	}
	void sapXepChucVu() {
		this->status = 3;

		node* i;
		node* j = NULL;
		int swapped;
		if (first == NULL)
		{
			return;
		}

		//bubble sort
		do
		{
			swapped = 0;
			i = first;

			while (i->next != j)
			{
				//so sanh i va i+1
				if (i->nhanVien.chucvu.priority > i->next->nhanVien.chucvu.priority)
				{
					swap(i, i->next);
					swapped = 1;
				}
				i = i->next;
			}
			//thu hep chuoi so sanh
			j = i;
		} while (swapped);
		
	}
	void chenNhanVien() {
		form(L"Thêm nhân viên");
		wstring nv = formInput();
		this->themNhanVien(taoNhanVien(nv));
		wcout <<endl<<L"Thêm nhân viên thành công !";
		switch (this->status)
		{
		case 1:
			this->sapXepTen();
			break;
		case 2:
			this->sapXepTheoNtn();
			break;
		case 3:
			this->sapXepChucVu();
			break;
		case 4:
			this->sapXepTheoLuong();
			break;
		default:
			break;
		}
	}
	void writeFile(wstring filename) {
		wofstream outfile;
		outfile.imbue(locale(locale::empty(), new codecvt_utf8_utf16<wchar_t,65001>));
		outfile.open(filename, ios::out|ios::app );
		node* current;
		current = first;
		outfile << L"Họ và tên,Chức vụ,Ngày tháng năm sinh,Hệ số lương"<<endl;
		while (current != NULL)
		{
			outfile << current->nhanVien.toString()<<endl;
			current = current->next;
		}
		clrscr();
		wcout <<endl<< L"Xuất file thành công" << endl;
	}
	void timKiemTen(bool isXoa=false) {
		wstring ten;
		int pos = 0;
		if (!isXoa)
		{
			smallForm(L"Tìm kiếm theo họ tên");
			wcout << L"Nhập họ hoặc tên >>>>>> ";
		}
		else {
			smallForm(L"Xóa theo họ tên");
			wcout << L"Nhập họ và tên >>>>>> ";
		}
		wcin.ignore();
		getline(wcin, ten);
		node* current;
		vector <NhanVien> ds;vector <int> poss;
		current = first;
		while (current != NULL)
		{
			if (current->nhanVien.timTen(ten)) {
				ds.push_back(current->nhanVien);
				poss.push_back(pos);

			}
			pos++;
			current = current->next;
		}
		if (!isXoa) {
			if (ds.size()) {
				wcout << L"Danh sách tìm thấy :" << endl;
				for (int i = 0; i < ds.size(); i++)
				{
					wcout << ds[i].hienThi() << L"	tại vị trí: " << poss[i] << endl;
				}
			}
			else {
				wcout << L" ??? Không tìm thấy thông tin nhân viên" << endl;
			}
		}
		else {
			xoaNhanVien(poss,ds);
		}
	}
	void timKiemLuong(bool isXoa=false) {
		wstring luong;
		wstring dau;

		int pos = 0;
		if (!isXoa)
		{
			smallForm(L"Tìm kiếm theo hệ số lương");
			wcout << L"Nhập hệ số lương ( nhập <n , >n để định giới hạn) >>>>>> ";
		}
		else {
			smallForm(L"Xóa theo hệ số lương");
			wcout << L"Nhập hệ số lương ( nhập <n , >n để định giới hạn)  >>>>>> ";
		}
		wcin.ignore();
		getline(wcin, luong);
		if (luong.substr(0,1) == L"<"|| luong.substr(0, 1) == L">") {
			dau = luong.at(0);
			luong = luong.erase(0, 1);
		}
		else {
			dau = L"=";
		}
		node* current;
		vector <NhanVien> ds;vector <int> poss;
		current = first;
		while (current != NULL)
		{
			if (current->nhanVien.timLuong(dau,luong)) {
				ds.push_back(current->nhanVien);
				poss.push_back(pos);

			}
			pos++;
			current = current->next;
		}
		if (!isXoa) {
			if (ds.size()) {
				wcout << L"Danh sách tìm thấy :" << endl;
				for (int i = 0; i < ds.size(); i++)
				{
					wcout << ds[i].hienThi() << L"	tại vị trí: " << poss[i] << endl;
				}
			}
			else {
				wcout << L" ??? Không tìm thấy thông tin nhân viên" << endl;
			}
		}
		else {
			xoaNhanVien(poss, ds);
		}
	}
	void timKiemNtn(bool isXoa=false) {
		wstring str;
		int pos = 0;
		if (!isXoa) {
			smallForm(L"Tìm kiếm theo ngày tháng năm sinh");
			wcout << L"Nhập ngày tháng năm sinh (có thể nhập ngày hoặc tháng hoặc năm) >>>>> ";
		}
		else {
			smallForm(L"Xóa theo ngày tháng năm sinh");
			wcout << L"Nhập ngày tháng năm sinh (có thể nhập ngày hoặc tháng hoặc năm) >>>>> ";
		}
		wcin.ignore();
		getline(wcin,str);
		node* current;
		vector <NhanVien> ds;vector <int> poss;
		current = first;
		while (current != NULL)
		{
			if (current->nhanVien.timNtn(str)) {
				ds.push_back(current->nhanVien);
				poss.push_back(pos);

			}
			pos++;
			current = current->next;
		}
		if (!isXoa) {
			if (ds.size()) {
				wcout << L"Danh sách tìm thấy :" << endl;
				for (int i = 0; i < ds.size(); i++)
				{
					wcout << ds[i].hienThi() << L"	tại vị trí: " << poss[i] << endl;
				}
			}
			else {
				wcout << L" ??? Không tìm thấy thông tin nhân viên" << endl;
			}
		}
		else {
			xoaNhanVien(poss, ds);
		}
	}
	void timKiemChucVu(bool isXoa=false) {
		wstring str;
		int pos = 0;
		if (!isXoa) {
			smallForm(L"Tìm kiếm theo chức vụ");
			wcout << L"Nhập tên chức vụ >>>>> ";
		}
		else {
			smallForm(L"Xóa theo chức vụ");
			wcout << L"Nhập tên chức vụ >>>>> ";
		}
		wcin.ignore();
		getline(wcin, str);
		node* current;
		vector <NhanVien> ds; vector <int> poss;
		current = first;
		while (current != NULL)
		{
			if (current->nhanVien.timChucVu(str)) {
				ds.push_back(current->nhanVien);
				poss.push_back(pos);

			}
			pos++;
			current = current->next;
		}
		if (!isXoa) {
			if (ds.size()) {
				wcout << L"Danh sách tìm thấy :" << endl;
				for (int i = 0; i < ds.size(); i++)
				{
					wcout << ds[i].hienThi() << L"	tại vị trí: " << poss[i] << endl;
				}
			}
			else {
				wcout << L" ??? Không tìm thấy thông tin nhân viên" << endl;
			}
		}
	}
	void xoaNhanVien(vector <int> tokens,vector <NhanVien> ds) {
		int pos;
		node* current;
	
		for (int i = 0; i < tokens.size(); i++)
		{
			pos = 0;
			current = first;
			while (current != NULL)
			{
				if (pos == tokens[i]) {
					current->nhanVien.chucvu.priority=0;
				}
				pos++;
				current = current->next;
			}
		}
		node* tmp, * prev = NULL;
		tmp = first;
		while (tmp!=NULL)
		{
			if (tmp == first && tmp->nhanVien.chucvu.priority == 0) {
				first = tmp->next;
				free(tmp);
				tmp = first;
			}
			else if (tmp!=first&&tmp->nhanVien.chucvu.priority == 0) {
				prev->next = tmp->next;
				free(tmp);
				tmp = prev->next;
			}
			else {
				prev = tmp;
				tmp = tmp->next;
			}
		}
		wcout << L"Đã xóa thành công các nhân viên sau"<<endl;
			for (int i = 0; i < ds.size(); i++)
			{
				wcout<<endl<<ds[i].hienThi()<<endl;
			}

	}
};

//tạo list 
List list;
void readFile(wstring filename);
void menu_1();
void menu_2();
void menu_3();
void menu_4();
void menu_5();
void menu_6();
void menu_7();
// menu
void hienThiMeNu() {
	int input;
	wcout << endl;
	form(L"Menu");
	wcout << endl;
	wcout << L"1. Đọc file danh sách nhân viên " << endl;
	wcout << L"2. Sắp xếp nhân viên " << endl;
	wcout << L"3. Thêm nhân viên " << endl;
	wcout << L"4. Xóa nhân viên " << endl;
	wcout << L"5. Tìm kiếm nhân viên " << endl;
	wcout << L"6. Xuất file danh sách nhân viên " << endl;
	wcout << L"7. Hiển thị danh sách nhân viên  " << endl;
	wcout << L"8. Thoát chương trình " << endl;
	wcout << L">>>>>>>>>>"; wcin >> input;

	if (!wcin)
	{
		canhBao();
	}
	else {
		clrscr();
		switch (input)
		{
		case 1:
			menu_1();
			break;
		case 2:
			menu_2();
			break;
		case 3:
			menu_3();
			break;
		case 4:
			menu_4();
			break;
		case 5:
			menu_5();
			break;
		case 6:
			menu_6();
			break;
		case 7:
			menu_7();
			break;
		case 8:
			exit(0);
			break;
		default:
			canhBao();
			break;
		}
	}
	hienThiMeNu();
}
//menu 1
NhanVien taoNhanVien(wstring line){
	vector <wstring>  arr;
	
	// tach cac phan tu ra khoi chuoi
	wstringstream strLine(line);
	wstring section;
	int i = 0;
	while (getline(strLine, section, L',')) {
		arr.push_back(section);
		i++;
	}
	//tach ten
	NhanVien nhanVien;
	wstringstream strName(arr[0]);
	vector <wstring> tokens;
	while (getline(strName, section, L' ')) {
		tokens.push_back(section);
	}
	//chuyen thanh doi tuong nhan vien
	//ho ten
	if(tokens.size()<=1){
		nhanVien.ten.ho = L"";nhanVien.ten.tenDem = L"";
	}
	else if (tokens.size() == 2) {
		nhanVien.ten.ho = tokens[0];
		nhanVien.ten.tenDem = L"";

	}
	else {
		for (int j = 1; j < tokens.size() - 1; j++)
		{
			nhanVien.ten.tenDem += L" " + tokens[j];
		}
		nhanVien.ten.tenDem.erase(0, 1);
		nhanVien.ten.ho = tokens[0];
	}
	
	
	nhanVien.ten.ten = tokens[tokens.size()-1];
	//chuc vu
	nhanVien.chucvu.tenChucVu = arr[1];
	nhanVien.capDo();
	//ngay thang nam sinh
	wstringstream strNtn(arr[2]);
	vector <wstring> dates ;
	while (getline(strNtn, section, L'/')) {
		dates.push_back(section);
	}
	nhanVien.ntn.ngay = dates[0];
	nhanVien.ntn.thang = dates[1];
	nhanVien.ntn.nam = dates[2];
	//luong
	nhanVien.luong = arr[3];
	return nhanVien;
}
void readFile(wstring filename) {
	//đọc file từ file .csv
	wstring input;
	wfstream file;
	file.imbue(locale(locale::empty(), new codecvt_utf8_utf16<wchar_t>));
	file.open(filename,ios::in);
	wstring line;
	//đọc file theo từng hàng
	// hàng đầu tiên 
	getline(file, line);
	if (!file.good())
	{
		wcout <<endl<< L"??? file lỗi hoặc không tìm thấy ???"<< endl;
		wcout << L"Vui lòng nhập lại tên file (hoặc bấm 0 thể quay lại) : >>>>>>>>>";
		wcin >> input ;
		if (input == L"0") {
			clrscr();
			hienThiMeNu();
		}
		wcout << endl;
		readFile(input);

	}
	else {
		while (!file.eof() && file.good())
		{
			getline(file, line);


			list.themNhanVien(taoNhanVien(line));
		}
		clrscr();
		smallForm(L"Thêm dữ liệu thành công");
	}
	
	
	//đóng file sau khi đọc xong
	file.close();
	list.hienThi();
}

void menu_1() {
	wstring input;
	form(L" Nhập file ");
	wcout << L"Nhập tên file (hoặc bấm 0 để quay lại)>>>>>>"; wcin >> input;
	if (input == L"0") {
		hienThiMeNu();
	}
	readFile(input);
}
//hết menu 1

//menu 2
void menu_2() {
	if (list.getFirst() == NULL)
	{
		tbTrong();
		hienThiMeNu();
	}
	else {
		int input;
		form(L"Sắp xếp nhân viên");
		wcout << L"	1. Theo họ và tên " << endl;
		wcout << L"	2. Theo ngày tháng năm sinh " << endl;
		wcout << L"	3. Theo chức vụ " << endl;
		wcout << L"	4. Theo hệ số lương " << endl;
		wcout << L"	5. Quay lại menu" << endl;
		wcout << L">>>>>>>>>>"; wcin >> input;
		if (!wcin) {
			canhBao();
		}
		else {
			clrscr();
			switch (input)
			{
			case 1:
				list.sapXepTen();
				clrscr();
				wcout << endl << L"Danh sách được sắp xếp theo họ tên" << endl;
				list.hienThi();
				break;
			case 2:
				list.sapXepTheoNtn();
				clrscr();
				wcout << endl << L"Danh sách được sắp xếp theo ngày tháng năm sinh" << endl;
				list.hienThi();
				break;
			case 3:
				list.sapXepChucVu();
				clrscr();
				wcout << endl << L"Danh sách được sắp xếp theo chức vụ" << endl;
				list.hienThi();
				break;
			case 4:
				list.sapXepTheoLuong();
				clrscr();
				wcout << endl << L"Danh sách được sắp xếp theo hệ số lương" << endl;
				list.hienThi();
				break;
			case 5:
				clrscr();
				hienThiMeNu();
				break;
			default:
				canhBao();
				break;
			}
		}
		menu_2();
	}
}
// hết menu 2

//menu 3
void menu_3() {
	if (list.getFirst() == NULL)
	{
		tbTrong();
		hienThiMeNu();
	}
	else {
		list.chenNhanVien();
	}
}
//hết menu 3

//menu 4
void menu_4() {
	if (list.getFirst() == NULL)
	{
		tbTrong();
		hienThiMeNu();
	}
	else {
		int input;
		form(L"Xóa nhân viên");
		wcout << L"	1. Theo họ và tên " << endl;
		wcout << L"	2. Theo ngày tháng năm sinh " << endl;
		wcout << L"	3. Theo chức vụ " << endl;
		wcout << L"	4. Theo hệ số lương " << endl;
		wcout << L"	5. Quay lại menu" << endl;
		wcout << L">>>>>>>>>>"; wcin >> input;
		if (!wcin) {
			canhBao();
		}
		else {
			clrscr();
			switch (input)
			{
			case 1:

				list.timKiemTen(true);
				break;
			case 2:
				list.timKiemNtn(true);
				break;
			case 3:
				list.timKiemChucVu(true);
				break;
			case 4:
				list.timKiemLuong(true);
				break;
			case 5:
				clrscr();
				hienThiMeNu();
				break;
			default:
				canhBao();
				break;
			}
		}
		menu_4();
	}
}
//hết menu 4

//menu 5
void menu_5() {
	if (list.getFirst() == NULL)
	{
		tbTrong();
		hienThiMeNu();
	}
	else {
		int input;
		form(L"Tìm kiếm nhân viên");
		wcout << L"	1. Theo họ và tên " << endl;
		wcout << L"	2. Theo ngày tháng năm sinh " << endl;
		wcout << L"	3. Theo Chức vụ " << endl;
		wcout << L"	4. Theo Hệ số lương " << endl;
		wcout << L"	5. Quay lại menu" << endl;
		wcout << L">>>>>>>>>>"; wcin >> input;
		if (!wcin) {
			canhBao();
		}else{
			clrscr();
			
			switch(input)
			{
			case 1:
				
				list.timKiemTen();
				break;
			case 2:
				list.timKiemNtn();
				break;
			case 3:
				list.timKiemChucVu();
				break;
			case 4:
				list.timKiemLuong();
				break;
			case 5:
				clrscr();
				hienThiMeNu();
				break;
			default:
				canhBao();
				break;
			}
		}
		menu_5();
	}
}
//hết menu 5

//menu 6
void menu_6() {
	if (list.getFirst() == NULL)
	{
		tbTrong();
		hienThiMeNu();
	}
	else {
		wstring input;
		form(L" Xuất file ");
		wcout << L"Nhập tên file (hoặc bấm 0 để quay lại)>>>>>>"; wcin >> input;
		if (input == L"0") {
			hienThiMeNu();
		}
		list.writeFile(input);
	}
}
//hết menu 6
//menu 7
void menu_7(){
	if (list.getFirst() == NULL)
	{
		tbTrong();
		hienThiMeNu();
	}
	else { 
		form( L"Danh sách nhân viên");
		list.hienThi(); }
}
// hết menu 8

// main
int main()
{
	
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	int resultin=_setmode(_fileno(stdin), _O_U16TEXT);
	int resultout=_setmode(_fileno(stdout), _O_U16TEXT);
	hienThiMeNu();
	
}




