#include <iostream>
#include <algorithm>
#include <cmath>


using namespace std;

class Polynomial;

class Term {
public:
    friend Polynomial;
private:
    float coef; // �Y��
    int exp;    // �����
};

class Polynomial {
private:
    Term* termArray; // �x�s�h�������ت��}�C
    int capacity;    // �}�C�e�q
    int terms;       // ��e���ؼƶq
public:
    Polynomial() : capacity(8), terms(0) {
        termArray = new Term[capacity];
    }
    int getterms() const { return terms; }
    void Add(const Polynomial& poly);      // �[�k
    Polynomial Mult(const Polynomial poly);      // ���k
    void NewTerm(const float coef, const int exp); // �s�W����
    void print() const;
    float Eval(float x);
    ~Polynomial() {
        delete[] termArray;
    }
};
    
void Polynomial::Add(const Polynomial& poly) {
    Polynomial temp;
    int i = 0, j = 0;

    while (i < terms && j < poly.terms) {
        if (termArray[i].exp > poly.termArray[j].exp) {
            temp.NewTerm(termArray[i].coef, termArray[i].exp);
            i++;
        }
        else if (termArray[i].exp < poly.termArray[j].exp) {
            temp.NewTerm(poly.termArray[j].coef, poly.termArray[j].exp);
            j++;
        }
        else {
            float sumCoef = termArray[i].coef + poly.termArray[j].coef;
            if (sumCoef != 0) temp.NewTerm(sumCoef, termArray[i].exp);
            i++;
            j++;
        }
    }

    // �B�z�Ѿl������
    while (i < terms) {
        temp.NewTerm(termArray[i].coef, termArray[i].exp);
        i++;
    }
    while (j < poly.terms) {
        temp.NewTerm(poly.termArray[j].coef, poly.termArray[j].exp);
        j++;
    }
    temp.print();
}

void Polynomial::NewTerm(const float coef, const int exp) {
    if (terms == capacity) {
        capacity *= 2;
        Term* newTermArray = new Term[capacity];
        for (int i = 0; i < terms; i++) {
            newTermArray[i] = termArray[i];
        }
        delete[] termArray;
        termArray = newTermArray;
    }
    termArray[terms].coef = coef;
    termArray[terms].exp = exp;
    terms++;
}

void Polynomial::print() const {
    for (int i = 0; i < terms; i++) {
        float coef = termArray[i].coef;
        int exp = termArray[i].exp;

        if (coef == 0) continue; // ���L�Y�Ƭ� 0 ������

        if (i != 0 && coef > 0) cout << "+";
        if (i != 0 && coef < 0) cout << "-";

        if (abs(coef) != 1 || exp == 0) cout << abs(coef);
        if (exp != 0) cout << "X";
        if (exp != 0 && exp != 1) cout << "^" << exp;
    }
    cout << endl;
}

float Polynomial::Eval(float x) {
    float result = 0.0;
    for (int i = 0; i < terms; i++) {
        result += (float)(termArray[i].coef * pow(x, termArray[i].exp));
    }
    return result;
}

int main() {
    Polynomial AP, BP;
    int exp;
    float coef;
    char mod;

    // ��J�h����1
    cout << "��J�h����1�]�榡�G�Y�� ����ơA�����п�J����Ƭ�0�^�G" << endl;
    while (cin >> coef >> exp) {
        if (exp == 0) break; // ����Ƭ�0�ɵ���
        if (coef != 0 && exp > 0)  AP.NewTerm(coef, exp);
    }

    // �M�z��J�y
    if (cin.fail()) {
        cin.clear(); // �M�z���~���A
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �����w�İϤ����Ѿl��J

    // ��J�h����2
    cout << "��J�h����2�]�榡�G�Y�� ����ơA�����п�J����Ƭ�0�^�G" << endl;
    while (cin >> coef >> exp) {
        if (exp == 0) break; // ����Ƭ�0�ɵ���
        if (coef != 0 && exp > 0) BP.NewTerm(coef, exp);
    }
    AP.print();

    // ��ܹB��Ҧ��öi��[�k
    cout << "��ܹB��Ҧ�(+):";
    cin >> mod;

    // �I�s Add ��ƨñ����^�Ǫ��h����
    if (mod == '+') {
        cout << "�[�k���G�O�G";
        AP.Add(BP);
    }
    return 0;
}

/*
3 3 5 2 1 1 0 0 
4 3 2 2 1 1 0 0
*/
