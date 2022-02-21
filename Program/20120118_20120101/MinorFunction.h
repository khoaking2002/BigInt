#pragma once
#include "Header.h"
#include "MainFunction.h"

void Chance(BigInt& s, string& st);        //Chuyen doi dau vao cho hop ly
string Add0(string s, int n);			   //Them so 0 o dau
int GetDigit(BigInt x, int pos);           //Lay gia tri kieu int
BigInt Delete0(BigInt& s);                 //Xoa so 0 o dau 
int Compare(BigInt x, BigInt y);           //so sanh hai xau
BigInt dichtrai(BigInt s, int soLuong);
BigInt dichphai(BigInt s, int soLuong);
BigInt Abs(BigInt s1);                     //Chi can doi sign


void Chance(BigInt& s, string& st) {
	if (st[0] == '-') {
		s.sign = 1;
		st.erase(0, 1);
	}
	string temp = st;
	st = s.data;
	s.data = temp;
}
string Add0(string s, int n) {
	int temp = s.length();
	for (int i = 0; i < n - temp; i++)
		s = "0" + s;
	return s;
}  //chen them so 0 o dau
int GetDigit(BigInt x, int pos) {
	return x.data[pos] - 48;
}  //lay gia tri INT
BigInt Delete0(BigInt& s) {
	while (s.data[0] == '0' && s.data.length() > 1)
	{
		s.data.erase(0, 1);
	}
	return s;
}  //xoa ki tu 0 o dau 
int Compare(BigInt x, BigInt y) {
	int temp = max(x.data.length(), y.data.length());
	(temp == x.data.length()) ? y.data = Add0(y.data, temp) : x.data = Add0(x.data, temp);
	return x.data.compare(y.data);
} // Cho do dai 2 xau bang nhau va so sanh compare
BigInt dichphai(BigInt s, int soLuong) {

	for (int i = 0; i < soLuong; i++) {
		for (int j = s.data.length() - 2; j >= 0; j--) {
			s.data[j + 1] = s.data[j];
		}
		s.data[i] = '0';
	}
	return s;
}
BigInt dichtrai(BigInt s, int soLuong) {

	for (int i = 0; i < soLuong; i++) {
		for (int j = 0; j < s.data.length() - 1; j++) {
			s.data[j] = s.data[j + 1];
		}
		s.data[s.data.length() - i - 1] = '0';
	}
	return s;
}
BigInt Abs(BigInt s1) {
	if (s1.sign == true) { s1.sign = false; }
	return s1;
}
