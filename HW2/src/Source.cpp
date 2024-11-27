#include <iostream>
//#include <string>
#include <algorithm>

using namespace std;

class Polynomial;

class Term {
public:
	friend Polynomial;
	friend istream& operator>>(istream& in, Polynomial& p);//�h��cin�B��l
	friend ostream& operator<<(ostream& out, const Polynomial& p);//�h��cout�B��l
private:
	float coef;//�Y��coefficient
	int exp;//�����exponent
};

class Polynomial {
private:
	Term* termArray = new Term[8];//�h�����x�s�}�C
	int capacity;//�}�C�w�]�j�p
	int terms;//�h��������
public:
	Polynomial() :capacity(8), terms(0) {};//�غc�l
	~Polynomial() { delete[] termArray; };//�Ѻc�l
	Polynomial Add(const Polynomial poly);//�[�k
	Polynomial Mult(const Polynomial poly);//���k
	Polynomial NewTerm(const float coef, const int exp);//�s�W�����X�W

	friend istream& operator>>(istream& in, Polynomial& p);//�h��cin�B��l
	friend ostream& operator<<(ostream& out, const Polynomial& p);//�h��cout�B��l
	float Eval(float f);
};

Polynomial Polynomial::Add(const Polynomial poly) {//�ȵL�\��
	return *this;
}

Polynomial Polynomial::Mult(const Polynomial poly) {//�ȵL�\��
	return *this;
}

Polynomial Polynomial::NewTerm(const float coef, const int exp) {
	if (terms == capacity) {
		Term* newtA = new Term[capacity *= 2];
		copy(termArray, termArray + terms, newtA);//�ƻs��s�}�C
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
	cout << "��J�h����(�����Ƨ�)�G" << endl << "�h����1�G";
	cin >> AP;
	cout << endl << "�h����2�G";
	cin >> BP;
	cout << endl << "�[�k�B��";
}