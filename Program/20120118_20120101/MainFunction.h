#pragma once
#include "Header.h"
#include "MinorFunction.h"

BigInt Add(BigInt s1, BigInt s2, string he);  //Ham Cong
BigInt Minus(BigInt s1, BigInt s2, string he); //Ham Tru
BigInt Mul10(BigInt s1, BigInt s2);  //Ham Nhan He So 10
BigInt Mul2(BigInt s1, BigInt s2);   //Ham Nhan He So 2
BigInt Div10(BigInt s1, BigInt s2);  //Ham Chia He So 10
BigInt Div2(BigInt s1, BigInt s2);   //Ham Chia He So 2
BigInt Mod10(BigInt s1, BigInt s2);  //Ham Du He So 10
BigInt Mod2(BigInt s1, BigInt s2);   //Ham Du He So 2
BigInt Pow(BigInt s1, BigInt n);     //Ham Mu He So 10
void MinMax(BigInt s1, BigInt s2, string he, string pheptoan);  //Tim Min Max 

BigInt phepand(BigInt s1, BigInt s2);
BigInt phepor(BigInt s1, BigInt s2);
BigInt phepxor(BigInt s1, BigInt s2);
BigInt phepnot(BigInt s1, string he);

string ToBinary(BigInt s, int x);  //Base 10 To Base 2
BigInt ToDecimal(BigInt s);        //Base 2 To Base 10
BigInt ToBase32(BigInt s);		   //Base 10 To Base 32
BigInt ToBase58(BigInt s);		   //Base 10 To Base 58
BigInt ToBase32(BigInt s);	       //Base 10 To Base 64
bool isprime(BigInt n);			   //Kiem tra so nguyen to

int getnum(string s, int n);	   //Lay so luong gia tri INT
BigInt ToString(int n);            //To string
BigInt randomBig(int maxlen); //tao BigInt ngau nhien
void phantich(BigInt a, int& b, BigInt& c);
bool wn(BigInt a, BigInt n);
int digits(BigInt s1);


BigInt Bu2(BigInt s);  //So Bu 2
BigInt MenuAdd(BigInt s1, BigInt s2, string he);  // truong hop phep cong
BigInt MenuMinus(BigInt s1, BigInt s2, string he);  // truong hop phep tru
BigInt MenuDiv10(BigInt s1, BigInt s2);  // truong hop phep chia he 10
BigInt MenuDich(BigInt s1, BigInt s2, string he, string pheptoan);  //Phep Dich >> va <<

void Input(string st, BigInt& s1, BigInt& s2, string& he, string& pheptoan, string& tg);
void Operation(BigInt s1, BigInt s2, string he, string pheptoan, string tg);  //Kiem tra cau lenh
void Output(BigInt s);

BigInt Add(BigInt s1, BigInt s2, string he) {
	int n = he == "2" ? 2 : 10, temp1, temp2, carry = 0;
	int maxlen = max(s1.data.length() + 1, s2.data.length() + 1);
	s1.data = Add0(s1.data, maxlen);
	s2.data = Add0(s2.data, maxlen);
	BigInt s3;
	for (int i = maxlen - 1; i >= 0; i--)
	{
		temp1 = GetDigit(s1, i);
		temp2 = GetDigit(s2, i);
		s3.data = to_string((temp1 + temp2 + carry) % n) + s3.data;
		carry = (temp1 + temp2 + carry) / n;
	}
	return Delete0(s3);
}
BigInt Minus(BigInt s1, BigInt s2, string he) {
	int n = he == "2" ? 2 : 10, temp1, temp2, carry = 0;
	int maxlen = max(s1.data.length() + 1, s2.data.length() + 1);
	char dau = '\0';
	s1.data = Add0(s1.data, maxlen);
	s2.data = Add0(s2.data, maxlen);
	BigInt s3;
	if (s1.data.compare(s2.data) < 0) {
		dau = '-';
		string s = s1.data;
		s1.data = s2.data;
		s2.data = s;
	}
	for (int i = maxlen - 1; i >= 0; i--)
	{
		temp1 = GetDigit(s1, i);
		temp2 = GetDigit(s2, i);
		if (temp1 < temp2)
		{
			s3.data = to_string(temp1 + n - temp2) + s3.data;
			s2.data[i - 1]++;
		}
		else s3.data = to_string(temp1 - temp2) + s3.data;
	}
	if (n == 10 && dau == '-') {
		s3.data = Delete0(s3).data;
		s3.sign = 1;
	}
	if (n == 2 && dau == '-')
		s3.data = Bu2(s3).data;  // bit dau la 1: so am
	return Delete0(s3);
}
BigInt Mul10(BigInt s1, BigInt s2) {
	BigInt Zero, kq;
	Zero.data = "0";
	int len1 = s1.data.length();
	int len2 = s2.data.length();
	if (s1.sign != s2.sign) { kq.sign = 1; }
	if (len1 == 0 || len2 == 0) { return Zero; }
	int dem1 = 0;
	int dem2 = 0;
	kq.data = Add0(kq.data, len1 + len2);
	for (int i = len1 - 1; i >= 0; i--) {
		int nho = 0;
		dem2 = 0;
		for (int j = len2 - 1; j >= 0; j--) {
			kq.data[dem1 + dem2] = int(s1.data[i] - 48) * int(s2.data[j] - 48) + int(kq.data[dem1 + dem2] - 48) + nho;
			nho = kq.data[dem1 + dem2] / 10;
			kq.data[dem1 + dem2] = (kq.data[dem1 + dem2] % 10) + 48;
			dem2++;
		}
		if (nho > 0) { kq.data[dem1 + dem2] = kq.data[dem1 + dem2] + nho; }
		dem1++;
	}
	string temp;
	temp = Add0(temp, kq.data.length());
	for (int i = 0; i < kq.data.length(); i++) {
		temp[i] = kq.data[kq.data.length() - 1 - i];
	}
	kq.data = temp;
	return Delete0(kq);
}
BigInt Mul2(BigInt s1, BigInt s2) {
	int maxlen = s1.data.length() + s2.data.length();
	s2.data = Add0(s2.data, maxlen);
	s1.data = Add0(s1.data, maxlen);
	BigInt kq;
	kq.data = Add0(kq.data, maxlen);
	for (int i = 0; i < s1.data.length(); i++) {
		if (s1.data[maxlen - 1] == '1') { kq = Add(kq, s2, "2"); }
		s1 = dichphai(s1, 1);
		s2 = dichtrai(s2, 1);
	}
	kq = Add(kq, s2, "2");
	return kq;
}

BigInt Div10(BigInt s1, BigInt s2) {
	int  carry = 0, k;
	int maxlen = max(s1.data.length() + 1, s2.data.length() + 1);
	char dau = '\0';
	BigInt hold, s3;
	s1.data = Add0(s1.data, maxlen);
	s2.data = Add0(s2.data, maxlen);
	BigInt kb[11];
	kb[0].data = '0';
	for (int i = 1; i <= 10; i++)
	{
		kb[i] = Add(kb[i - 1], s2, "10");
	}
	hold.data = "";
	s3.data = "";
	for (int i = 0; i < maxlen; i++)
	{
		hold.data = hold.data + s1.data[i];
		k = 1;
		while (Compare(hold, kb[k]) >= 0)
			k++;
		s3.data = s3.data + to_string(k - 1);
		hold = Minus(hold, kb[k - 1], "10");
	}
	return Delete0(s3);
}
BigInt Div2(BigInt s1, BigInt s2) {
	BigInt thuong;
	BigInt temp;
	for (int i = 0; i < s1.data.length(); i++) {
		temp.data = temp.data + s1.data[i];
		if (temp.data.length() > s2.data.length()) { s2.data = Add0(s2.data, temp.data.length()); }
		else { temp.data = Add0(temp.data, s2.data.length()); }
		if (temp.data < s2.data) { thuong.data = thuong.data + "0"; temp = Delete0(temp); }
		else { thuong.data = thuong.data + "1"; temp = Minus(temp, s2, "2"); }
		s2 = Delete0(s2);
	}
	return thuong;
}
BigInt Mod10(BigInt s1, BigInt s2) {
	int carry = 0, k;
	int maxlen = max(s1.data.length() + 1, s2.data.length() + 1);
	char dau = '\0';
	BigInt hold, s3;
	s1.data = Add0(s1.data, maxlen);
	s2.data = Add0(s2.data, maxlen);
	BigInt kb[11];
	kb[0].data = '0';
	for (int i = 1; i <= 10; i++)
	{
		kb[i] = Add(kb[i - 1], s2, "10");
	}
	hold.data = "";
	s3.data = "";
	for (int i = 0; i < maxlen; i++)
	{
		hold.data = hold.data + s1.data[i];
		k = 1;
		while (Compare(hold, kb[k]) >= 0)
			k++;
		s3.data = s3.data + to_string(k - 1);
		hold = Minus(hold, kb[k - 1], "10");
	}
	return Delete0(hold);
}
BigInt Mod2(BigInt s1, BigInt s2) {
	BigInt thuong;
	BigInt temp;
	for (int i = 0; i < s1.data.length(); i++) {
		temp.data = temp.data + s1.data[i];
		if (temp.data.length() > s2.data.length()) { s2.data = Add0(s2.data, temp.data.length()); }
		else { temp.data = Add0(temp.data, s2.data.length()); }
		if (temp.data < s2.data) { thuong.data = thuong.data + "0"; temp = Delete0(temp); }
		else { thuong.data = thuong.data + "1"; temp = Minus(temp, s2, "2"); }
		s2 = Delete0(s2);
	}
	return temp;
}
void MinMax(BigInt s1, BigInt s2, string he, string pheptoan) {
	if (he == "10") {
		if (pheptoan == "max") {
			if (s1.sign == 0 && s2.sign == 1)
				Output(s1); // s1 duong, s2 am
			else if (s1.sign == 1 && s2.sign == 0)
				Output(s2);  // s1 am, s2 duong
			else if (s1.sign == 0 && s2.sign == 0)
			{
				if (Compare(s1, s2) > 0) Output(s1);
				else if (Compare(s1, s2) < 0) Output(s2);
				else fo << "2 so nhap vao bang nhau" << endl;
			}  //so sanh 2 so duong
			else if (s1.sign == 1 && s2.sign == 1)
			{
				if (Compare(s1, s2) > 0) Output(s2);
				else if (Compare(s1, s2) < 0) Output(s1);
				else fo << "2 so nhap vao bang nhau" << endl;
			}  // so sanh 2 so am
		}  // Tim max
		else if (pheptoan == "min") {
			if (s1.sign == 0 && s2.sign == 1)
				Output(s2);  // s1 am, s2 duong
			else if (s1.sign == 1 && s2.sign == 0)
				Output(s1); // s1 am, s2 duong
			else if (s1.sign == 0 && s2.sign == 0)
			{
				if (Compare(s1, s2) > 0) Output(s2);
				else if (Compare(s1, s2) < 0) Output(s1);
				else fo << "2 so nhap vao bang nhau" << endl;
			}  // so sanh 2 so duong
			else if (s1.sign == 1 && s2.sign == 1)
			{
				if (Compare(s1, s2) > 0) Output(s1);
				else if (Compare(s1, s2) < 0) Output(s2);
				else fo << "2 so nhap vao bang nhau" << endl;
			}  // so sanh 2 so am
		}  // Tim min
	}  // Nhung truong hop cua so sanh he 10
	else if (he == "2") {
		if (s1.data[0] == '1') s1.sign = 1;
		else s1.sign = 0;
		s1.data.erase(0, 1);
		if (s2.data[0] == '1') s2.sign = 1;
		else s2.sign = 0;
		s2.data.erase(0, 1);
		if (pheptoan == "max") {
			if (s1.sign == 0 && s2.sign == 1)
			{
				fo << s1.sign;
				s1.sign = 0;
				Output(s1);
			}
			else if (s1.sign == 1 && s2.sign == 0)
			{
				fo << s2.sign;
				s2.sign = 0;
				Output(s2);
			}
			else if (s1.sign == 0 && s2.sign == 0)
			{
				if (Compare(s1, s2) > 0) {
					fo << s1.sign;
					s1.sign = 0;
					Output(s1);
				}
				else if (Compare(s1, s2) < 0) {
					fo << s2.sign;
					s2.sign = 0;
					Output(s2);
				}
				else fo << "2 so nhap vao bang nhau" << endl;
			}  //so sanh 2 so duong
			else if (s1.sign == 1 && s2.sign == 1)
			{
				if (Compare(s1, s2) > 0) {
					fo << s2.sign;
					s2.sign = 0;
					Output(s2);
				}
				else if (Compare(s1, s2) < 0) {
					fo << s1.sign;
					s1.sign = 0;
					Output(s1);
				}
				else fo << "2 so nhap vao bang nhau" << endl;
			}  // so sanh 2 so am
		}  // Tim max
		else if (pheptoan == "min") {
			if (s1.sign == 0 && s2.sign == 1)
			{
				fo << s2.sign;
				s2.sign = 0;
				Output(s2);
			}  // s1 duong, s2 am
			else if (s1.sign == 1 && s2.sign == 0)
			{
				fo << s1.sign;
				s1.sign = 0;
				Output(s1);
			} // s1 am, s2 duong
			else if (s1.sign == 0 && s2.sign == 0)
			{
				if (Compare(s1, s2) > 0) {
					fo << s2.sign;
					s2.sign = 0;
					Output(s2);
				}
				else if (Compare(s1, s2) < 0) {
					fo << s1.sign;
					s1.sign = 0;
					Output(s1);
				}
				else fo << "2 so nhap vao bang nhau" << endl;
			}  // so sanh 2 so duong
			else if (s1.sign == 1 && s2.sign == 1)
			{
				if (Compare(s1, s2) > 0) {
					fo << s1.sign;
					s1.sign = 0;
					Output(s1);
				}
				else if (Compare(s1, s2) < 0) {
					fo << s2.sign;
					s2.sign = 0;
					Output(s2);
				}
				else fo << "2 so nhap vao bang nhau" << endl;
			} // Nhung truong hop cua so sanh he 2
		}
	}
}
BigInt phepand(BigInt s1, BigInt s2) {
	int maxlen = (s1.data.length() > s2.data.length()) ? s1.data.length() : s2.data.length();
	s1.data = Add0(s1.data, maxlen);
	s2.data = Add0(s2.data, maxlen);
	BigInt kq;
	kq.data = Add0(kq.data, maxlen);
	for (int i = 0; i < maxlen; i++) {
		if ((s1.data[i] == '1') && (s2.data[i] == '1')) { kq.data[i] = '1'; }
	}
	return kq;
}
BigInt phepor(BigInt s1, BigInt s2) {
	int maxlen = (s1.data.length() > s2.data.length()) ? s1.data.length() : s2.data.length();
	s1.data = Add0(s1.data, maxlen);
	s2.data = Add0(s2.data, maxlen);
	BigInt kq;
	for (int i = 0; i < maxlen; i++) {
		kq.data = kq.data + "1";
		if ((s1.data[i] == '0') && (s2.data[i] == '0')) { kq.data[i] = '0'; }
	}
	return kq;
}
BigInt phepxor(BigInt s1, BigInt s2) {
	int maxlen = (s1.data.length() > s2.data.length()) ? s1.data.length() : s2.data.length();
	s1.data = Add0(s1.data, maxlen);
	s2.data = Add0(s2.data, maxlen);
	BigInt kq;
	for (int i = 0; i < maxlen; i++) {
		kq.data = kq.data + "1";
		if (s1.data[i] == s2.data[i]) { kq.data[i] = '0'; }
	}
	return kq;
}
BigInt phepnot(BigInt s1,string he) {
	if (he == "10") { BigInt ammot; ammot.sign = 1; ammot.data = "1"; return MenuMinus(ammot, s1, "10"); }
		for (int i = 0; i < s1.data.length(); i++) {
			s1.data[i] = '1' - s1.data[i] + 48;
		}
		return s1;
}
BigInt Pow(BigInt s1, BigInt n) {
	BigInt kq;
	BigInt one, zero;
	one.data = "1";
	kq.data = "1";
	zero.data = "0";
	if (n.sign == 1) {
		if (s1.data == "1") { return one; }
		else { return zero; }
	}
	while (n.sign == 0 && n.data != "0") {
		kq = Mul10(kq, s1);
		n = Minus(n, one, "10");
	}
	if (s1.sign == 1 && GetDigit(n, n.data.length() - 1) % 2 == 1)
		kq.sign == 1;
	return kq;
}
string ToBinary(BigInt s, int x) {
	if (s.data == "0") return "0";
	else {
		int du = 0, thuong = 0, i = 0;
		BigInt s3;
		s3.data = "";
		for (i = 0; i < s.data.length(); i++) {
			du = du * 10 + GetDigit(s, i);
			thuong = du / x;
			du = du - thuong * x;
			s3.data = s3.data + to_string(thuong);
		}
		s3 = Delete0(s3);
		return ToBinary(s3, 2) + to_string(du);
	}
}
BigInt ToDecimal(BigInt s) {
	BigInt temp1, temp2, temp3;
	temp1.data = '2';
	for (int i = 0; i < s.data.length(); i++)
	{
		if (s.data[i] == '1') {
			BigInt temp4;
			temp4.data = to_string(s.data.length() - 1 - i);
			temp2 = Pow(temp1, temp4);
			temp3 = Add(temp3, temp2, "10");
		}
	}
	return temp3;
}
int getnum(string s, int n) {
	int kq = 0;

	for (int i = n - 1; i >= 0; i--) {
		kq = kq + pow(10, (n - i - 1)) * (s[i] - 48);
	}
	return kq;
}
BigInt ToBase58(BigInt s) {
	BigInt st;
	string base58 = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
	while (s.data != "0")
	{
		int du = 0, thuong = 0;
		BigInt s3;
		s3.data = "";
		for (int i = 0; i < s.data.length(); i++) {
			du = du * 10 + GetDigit(s, i);
			thuong = du / 58;
			du = du - thuong * 58;
			s3.data = s3.data + to_string(thuong);
		}
		s3 = Delete0(s3);
		s = s3;
		st.data = base58[du] + st.data;
	}
	return st;
}
BigInt ToString(int n) {
	BigInt kq;
	while (n != 0) {
		int m = n % 10;
		kq.data = kq.data + char(m + 48);
		n = n / 10;
	}
	string temp;
	temp = Add0(temp, kq.data.length());
	for (int i = 0; i < kq.data.length(); i++) {
		temp[i] = kq.data[kq.data.length() - 1 - i];
	}
	kq.data = temp;
	return Delete0(kq);
}
BigInt ToBase32(BigInt s) {
	BigInt bahai;
	BigInt kq;
	BigInt c;
	bahai.data = "32";
	while (s.data != "0") {
		c.data = (Mod10(s, bahai)).data;
		c.data = Add0(c.data, 2);
		if (c.data <= "09") { c = Delete0(c); kq.data = kq.data + c.data; }
		else {
			kq.data = kq.data + char(getnum(c.data, 2) + 55);
		}
		s = Div10(s, bahai);
	}
	string temp;
	temp = Add0(temp, kq.data.length());
	for (int i = 0; i < kq.data.length(); i++) {
		temp[i] = kq.data[kq.data.length() - 1 - i];
	}
	kq.data = temp;
	return kq;
}
BigInt ToBase64(BigInt s) {
	BigInt saubon;
	saubon.data = "64";
	BigInt kq;
	BigInt c;
	while (s.data != "0") {
		c.data = (Mod10(s, saubon)).data;
		c.data = Add0(c.data, 2);
		if (c.data <= "25") { kq.data = kq.data + char(getnum(c.data, 2) + 65); }
		else {
			if (c.data <= "51") { kq.data = kq.data + char(getnum(c.data, 2) + 71); }
			else {
				if (c.data <= "61") kq.data = kq.data + char(getnum(c.data, 2) - 4);
				else {
					if (c.data == "62")  kq.data = kq.data + "+";
					else kq.data = kq.data + "/";
				}
			}
		}
		s = Div10(s, saubon);
	}
	string temp;
	temp = Add0(temp, kq.data.length());
	for (int i = 0; i < kq.data.length(); i++) {
		temp[i] = kq.data[kq.data.length() - 1 - i];
	}
	kq.data = temp;
	return kq;
}
int digits(BigInt s1) {
	return s1.data.length();
}
BigInt Bu2(BigInt s) {
	BigInt ss;
	ss.data = "1";
	int i = 1;
	while (i <= s.data.length())
	{
		ss.data = ss.data + "0";
		i++;
	}
	return Minus(ss, s, "2");
}
BigInt MenuAdd(BigInt s1, BigInt s2, string he) {
	if (!s1.sign && !s2.sign) {
		BigInt s3 = Add(s1, s2, he);
		return s3;
	} // \+ + \+
	else if (s1.sign && s2.sign) {
		BigInt s3 = Add(s1, s2, he);
		s3.sign = 1;
		return s3;
	}  // \- +\-
	else if (!s1.sign && s2.sign) {
		BigInt s3 = Minus(s1, s2, he);
		return s3;
	}  // \+ + \-
	else {
		BigInt s3 = Minus(s2, s1, he);
		return s3;
	}  // \- + \+
}  // Nhung truong hop cua phep cong

BigInt MenuMinus(BigInt s1, BigInt s2, string he) {
	if (!s1.sign && !s2.sign) {
		BigInt s3 = Minus(s1, s2, he);
		return s3;
	}  // \+ - \+
	else if (!s1.sign && s2.sign) {
		BigInt s3 = Add(s1, s2, he);
		return s3;
	}  // \+ - \-
	else if (s1.sign && !s2.sign) {
		BigInt s3 = Add(s1, s2, he);
		s3.sign = 1;
		return s3;
	}  // \- - \+
	else {
		BigInt s3 = Minus(s2, s1, he);
		return s3;
	}  //\- - \-
}  // Nhung truong hop cua phep tru

BigInt MenuDiv10(BigInt s1, BigInt s2) {
	if (s1.sign == s2.sign) {
		BigInt s3 = Div10(s1, s2);
		return s3;
	}  // hai so cung dau
	else if (s1.sign != s2.sign) {
		BigInt s3 = Div10(s1, s2);
		s3.sign = 1;
		return s3;
	}  // hai so trai dau
}  // Nhung truong hop cua phep chia he 10
BigInt MenuDich(BigInt s1, BigInt s2, string he, string pheptoan) {
	if (he == "10") {
		BigInt s3, temp;
		temp.data = "1";
		s3.data = ToBinary(s1, 2);
		if (s1.sign == 1) s3 = Bu2(s3);
		while (s2.data != "0") {
			if (pheptoan == ">>") {
				s3.data.erase(s3.data.length() - 1, 1);
				s2 = Minus(s2, temp, "10");
			}
			if (pheptoan == "<<") {
				s3.data = s3.data + "0";
				s2 = Minus(s2, temp, "10");
			}
		}
		return ToDecimal(s3);
	}
	else if (he == "2") {
		BigInt s3, temp;
		s3.data = s1.data;
		temp.data = "1";
		while (s2.data != "0") {
			if (pheptoan == ">>") {
				s3.data.erase(s3.data.length() - 1, 1);
				s2 = Minus(s2, temp, "10");
			}
			if (pheptoan == "<<") {
				s3.data = s3.data + "0";
				s2 = Minus(s2, temp, "10");
			}
		}
		return s3;
	}
}
BigInt randomBig(int maxlen) {
	BigInt code;
	string box = "0123456789";
	code.data = Add0(code.data, maxlen);
	int len = (rand() % (maxlen)) + 1;
	for (int i = 0; i < len; i++) {
		code.data[i] = box[rand() % box.length()];
	}
	return code;
}
BigInt gcd(BigInt a, BigInt b) {
	BigInt r;
	while (b.data != "0") { r = b; b = Mod10(a, b); a = r; }
	return a;
}
BigInt submod(BigInt a, BigInt b, BigInt c) {
	BigInt two;
	two.data = "2";
	if (b.data == "1") { return Mod10(a, c); }
	else {
		BigInt x = submod(a, Div10(b, two), c);
		if (Mod10(b, two).data == "0") { return Mod10(Mul10(x, x), c); }
		else { return Mod10(Mul10(Mod10(Mul10(x, x), c), a), c); }
	}
}
void phantich(BigInt a, int& b, BigInt& c) {
	b = 0;
	BigInt two;
	two.data = "2";
	while (Mod10(a, two).data == "0") {
		b++;
		a = Div10(a, two);
	}
	c = a;
}
bool wn(BigInt a, BigInt n) {
	int b;
	BigInt c;
	BigInt one;
	one.data = "1";
	phantich(Minus(n, one, "10"), b, c);
	BigInt temp = submod(a, c, n);
	if (temp.data == "1") { return true; }
	else {
		while (b >= 0) {
			BigInt temp1 = Mod10(Mul10(temp, temp), n);
			if (temp1.data == "1") {
				if (temp.data == Minus(n, one, "10").data) { return true; }
				else { return false; }
			}
			temp = temp1;
			b--;
		}
	}
	return false;
}
bool isprime(BigInt n) {
	if (n.data < "1" || n.sign == 1) { return false; }
	if (n.data == "2" || n.data == "3") { return true; }
	BigInt two, three;
	two.data = "2";
	three.data = "3";
	BigInt randnum = Mod10(randomBig(n.data.length()), Minus(n, three, "10"));
	BigInt a = Add(two, randnum, "10");
	if (gcd(a, n).data != "1") { return false; }
	else { return wn(a, n); }
}
void Input(string st, BigInt& s1, BigInt& s2, string& he, string& pheptoan, string& tg) {
	st = st + " ";
	int pos = 0, n = 0;
	int vitri = st.find(' ', pos);
	while (vitri <= st.length()) {
		n++;
		if (he == "") he = st.substr(pos, vitri - pos);
		else if (s1.data == "") s1.data = st.substr(pos, vitri - pos);
		else if (pheptoan == "") pheptoan = st.substr(pos, vitri - pos);
		else if (s2.data == "") s2.data = st.substr(pos, vitri - pos);
		else tg = st.substr(pos, vitri - pos);
		pos = vitri + 1;
		vitri = st.find(' ', pos);
	}
	if (s1.data[0] == '-') {
		s1.sign = 1;
		s1.data.erase(0, 1);
	}
	if (s2.data[0] == '-') {
		s2.sign = 1;
		s2.data.erase(0, 1);
	}
	if (s2.data == "TIME") {
		tg = "TIME";
		s2.data = "";
	}
}
void Operation(BigInt s1, BigInt s2, string he, string pheptoan, string tg) {
	clock_t start, end;
	double duration;
	start = clock();
	if (pheptoan == "+") {
		BigInt s3 = MenuAdd(s1, s2, he);
		Output(s3);
	}
	else if (pheptoan == "-") {
		BigInt s3 = MenuMinus(s1, s2, he);
		Output(s3);
	}
	else if (pheptoan == "*") {
		if (he == "2") Output(Mul2(s1, s2));
		else if (he == "10") {
			BigInt s3 = Mul10(s1, s2);
			Output(s3);
		}
	}
	else if (pheptoan == "/") {
		if (he == "10") {
			BigInt s3 = MenuDiv10(s1, s2);
			Output(s3);
		}
		else if (he == "2") Output(Div2(s1, s2));
	}
	else if (pheptoan == "%") {
		if (he == "10") Output(Mod10(s1, s2));
		else if (he == "2") Output(Mod2(s1, s2));
	}
	else if (pheptoan == "^^") {
		BigInt s3 = Pow(s1, s2);
		Output(s3);
	}
	else if (s1.data == "max" || s1.data == "min") {
		Chance(s1, pheptoan);
		MinMax(s1, s2, he, pheptoan);
	}
	else if (pheptoan == "|") {
		BigInt s3 = phepor(s1, s2);
		Output(s3);
	}
	else if (pheptoan == "&") {
		BigInt s3 = phepand(s1, s2);
		Output(s3);
	}
	else if (pheptoan == "^") {
		BigInt s3 = phepxor(s1, s2);
		Output(s3);
	}
	else if (s1.data == "~") {
		Chance(s1, pheptoan);
		BigInt s3 = phepnot(s1,he);
		Output(s3);
	}
	else if (he == "10" && s1.data == "2") {
		Chance(s1, pheptoan);
		BigInt s3;
		s3.data = ToBinary(s1, 2);
		if (s1.sign == 0) {
			BigInt s4;
			s4.data = '0';
			s3.data = s4.data + Delete0(s3).data;
			Output(s3);
		}
		if (s1.sign == 1) {
			s3 = Bu2(s3);
			Output(Delete0(s3));
		}
	}
	else if (he == "2" && s1.data == "10") {
		Chance(s1, pheptoan);
		if (s1.data[0] == '1') {
			s1 = Bu2(s1);
			s1 = ToDecimal(s1);
			s1.sign = 1;
			Output(s1);
		}
		else if (s1.data[0] = '0') {
			BigInt s3;
			s3 = ToDecimal(s1);
			Output(Delete0(s3));
		}
	}
	else if (pheptoan == ">>" || pheptoan == "<<") {
		BigInt s3 = MenuDich(s1, s2, he, pheptoan);
		Output(s3);
	}
	else if (pheptoan == "To_Base32") {
		BigInt s3;
		if (he == "2")
			s3 = ToBase32(ToDecimal(s1));
		else 
			s3 = ToBase32(s1);
		Output(s3);
	}
	else if (pheptoan == "To_Base58") {
		BigInt s3;
		if (he == "2")
			s3 = ToBase58(ToDecimal(s1));
		else 
			s3 = ToBase58(s1);
		Output(s3);
	}
	else if (pheptoan == "To_Base64") {
		BigInt s3;
		if (he == "2")
			s3 = ToBase64(ToDecimal(s1));
		else 
			s3 = ToBase64(s1);
		Output(s3);
	}
	else if (pheptoan == "abs") {
		BigInt s3 = Abs(s1);
		Output(s3);
	}
	else if (pheptoan == "To_String") {
		BigInt s3 = ToString(getnum(s1.data, s1.data.length()));
		Output(s3);
	}
	else if (pheptoan == "Digits") {
	fo << digits(s1) << endl;
	}
	else if (pheptoan == "Isprime") {
	if (isprime(s1)) { fo << "Day la so nguyen to " << endl; }
	else { fo << "Day khong la so nguyen to " << endl; }
	}
	end = clock();
	if (tg == "TIME") {
		duration = (double)(end - start) / CLOCKS_PER_SEC;
		fo<<"*Time Running: "<<duration<<" s";
	}
}
void Output(BigInt s) {
	if (s.sign == 0)
		fo << s.data << endl;
	else fo << "-" << s.data << endl;
}