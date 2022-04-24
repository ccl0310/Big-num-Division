#include <bits/stdc++.h>
using namespace std;

class BigInt {
public:
	string st = "";
	int *array = nullptr;
	int len = 0;
	bool sign = false;
	bool inf = false;
	bool zero = false;
	friend istream& operator >> (istream& in,BigInt& b);
	friend ostream& operator << (ostream& out,BigInt& b);
	void store(string s){
		if (s[0]=='-') {
			sign = true;
			s.erase(s.begin());
		}
		len = s.length()-1;
		if (array!=nullptr){
			delete[] array;
		}
		array = new int[len+1];
		int i = len;
		int j = 0;
		while(i>=0){
			array[j] = s[i]-'0';
			j++; i--;
		}
	}
	int array1[10000];
	int newlen = len;
	void add(int array[],int num){
		int i = 0;
		while (num!=0){
			array[i] += num%10;
			num /= 10;
			i++;
		}
		for (int j=0;j<=i;j++){
			array[j+1] += array[j] / 10;
			array[j] %= 10;
		}
	}
	void sub(int array[],int num){
		int i = 0;
		while (num!=0){
			array[i] -= num%10;
			num /= 10;
			i++;
		}
		for (int j=0;j<=i;j++){
			if (array[j] < 0){
				array[j+1]--;
				array[j] += 10;
			}
		}
	}
	void mul(int array[],int num,int array1[]){
		for (int i=0;i<=len;i++){
			array1[i] = array[i]*num;
			if (array1[i] > 10){
				int cl = array1[i];
				while (cl > 10){
					cl /= 10;
					newlen++;
				}
			}
		}
		for (int i=0;i<newlen;i++){
			array1[i+1] += array1[i] / 10;
			array1[i] %= 10;
		}
	}
	void div(int array[],int num,int array1[]){
		bool dividable = false;
		if (num==0){
			inf = true;
			return;
		}
		int r = 0;
		for (int i=len;i>=0;i--){
			r = r * 10 + array[i];
//			cout << r << endl;
//			cout << r/num << endl;
			if (r/num > 0){
				array1[i] = r / num;
				dividable = true;
			}
			r %= num;
			//cout << array1[i];
		}
		if (!dividable){
			zero = true;
		}
	}
	void clear(){
		st = "";
		sign = false;
		array = nullptr;
		len = 0;
		sign = false;
		inf = false;
		zero = false;
		memset(array1,0,10000);
	}
	BigInt (){
		string st = "";
		array = nullptr;
		len = 0;
		sign = false;
		inf = false;
		zero = false;
	}
	BigInt& operator /= (int num){
		bool op = (num < 0);
		sign = sign ^ op;
		if (num < 0){
			num = -num;
		}
		div(array,num,array1);
	}
};

istream& operator >> (istream& in,BigInt &b){
	cin >> b.st;
	if (b.st == "0") {
		b.zero = true;
	} else b.zero = false;
	b.store(b.st);
	return in;
}

ostream& operator << (ostream& out,BigInt& b){
	bool head_zero = true;
	if (b.zero){
			cout << "0";
			b.clear();
			return out;
		}
	if (b.sign) {
		cout << "-";
	}
	if (b.inf){
		cout << "Inf";
	} else {
	for (int i=b.len;i>=0;i--){
		if (head_zero && b.array1[i]==0){
			continue;
		}
		else {
			head_zero = false;
			cout << b.array1[i];
		}
	}
	}
	b.clear();
	return out;
}


int main(){
	BigInt a;
	int b;
	while(cin >> a >> b){
		a /= b;
		cout << a << endl;
	}
}

