#include <iostream>
//#include <string>
#include <algorithm>

using namespace std;

class Polynomial;

class Term {
public:
	friend Polynomial;
	friend istream& operator>>(istream& in, Polynomial& p);//多載cin運算子
	friend ostream& operator<<(ostream& out, const Polynomial& p);//多載cout運算子
private:
	float coef;//係數coefficient
	int exp;//次方數exponent
};

class Polynomial {
private:
	Term* termArray = new Term[8];//多項式儲存陣列
	int capacity;//陣列預設大小
	int terms;//多項式項數
public:
	Polynomial() :capacity(8), terms(0) {};//建構子
	~Polynomial() { delete[] termArray; };//解構子
	Polynomial Add(const Polynomial poly);//加法
	Polynomial Mult(const Polynomial poly);//乘法
	Polynomial NewTerm(const float coef, const int exp);//新增項及擴增

	friend istream& operator>>(istream& in, Polynomial& p);//多載cin運算子
	friend ostream& operator<<(ostream& out, const Polynomial& p);//多載cout運算子
	float Eval(float f);
};

Polynomial Polynomial::Add(const Polynomial poly) {//暫無功能
	return *this;
}

Polynomial Polynomial::Mult(const Polynomial poly) {//暫無功能
	return *this;
}

Polynomial Polynomial::NewTerm(const float coef, const int exp) {
	if (terms == capacity) {
		Term* newtA = new Term[capacity *= 2];
		copy(termArray, termArray + terms, newtA);//複製到新陣列
		delete[] termArray;
		termArray = newtA;
	}
	termArray[terms].coef = coef;
	termArray[terms++].exp = exp;
	return *this;
}

/*istream& operator>>(istream& in, Polynomial& p) {
	float tcoef;
	int texp;
	char a, b, c;
	in >> tcoef >> a >> b >> texp >> c;
	if (tcoef != 0 && a == 'X' && b == '^')  p.NewTerm(tcoef, texp);
	return in;
}

ostream& operator<<(ostream& out, const Polynomial& p) {
	for (int i = 0; i < p.terms; i++) {
		out << p.termArray[i].coef << "X^" << p.termArray[i].exp;
	}
	return out;
}*/


float Polynomial::Eval(const float f) {
	return f;
}

int main(void) {
	Polynomial AP, BP;
	cout << "輸入多項式(降冪排序)：" << endl << "多項式1：";
	cin >> AP;
	cout << endl << "多項式2：";
	cin >> BP;
	cout << endl << "加法運算";
}