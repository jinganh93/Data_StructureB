#include <iostream>
#include <algorithm>

using namespace std;

class Polynomial;

class Term {
public:
    float coef; // �Y��
    int exp;    // �����
    Term* nextTerm;
    Term() : coef(0), exp(0), nextTerm(nullptr) {}
    Term(int incoef, int inexp) : coef(incoef), exp(inexp) { nextTerm = nullptr; }
    Term(int incoef, int inexp, Term* next) : coef(incoef), exp(inexp), nextTerm(next) {}
    ~Term() {};
};

class Polynomial {
private:
    Term* first, * last; // �Ĥ@��
    //int capacity;    // �}�C�e�q
    //int terms;       // ��e���ؼƶq
public:
    Polynomial() : first(nullptr), last(nullptr) {}
    //int getterms() const { return terms; }
    Term* getfirst() { return first; }
    void NewTerm(const float coef, const int exp); // �s�W����

    // �h���B��l
    friend istream& operator>>(istream& in, Polynomial& p);
    friend ostream& operator<<(ostream& out, Polynomial& p);
    Polynomial operator+ (const Polynomial& p) const;
    Polynomial operator- (const Polynomial& p) const;
    Polynomial operator= (const Polynomial& p);
    Polynomial operator* (const Polynomial& p) const;

    //�B��禡
    float Eval(float x);

    ~Polynomial() {
        Term* current = first;
        while (current != nullptr) {
            Term* toDelete = current;
            current = current->nextTerm;
            delete toDelete;
        }
    }
};

void Polynomial::NewTerm(const float coef, const int exp) {
    if (first == nullptr) {
        first = new Term(coef, exp);
        last = first;
    }
    else {
        last->nextTerm = new Term(coef, exp);
        last = last->nextTerm;
    }
}

istream& operator>>(istream& in, Polynomial& p) {
    int terms;
    do {
        cout << "��J�h�������ơG";
        in >> terms;  // Ū���h��������

        if (in.fail()) {  // �p�G��J���O���ľ��
            in.clear();  // �M�����~���A
            in.ignore(numeric_limits<streamsize>::max(), '\n');  // �������~����J
            cout << "�п�J�@�Ӧ��Ī���ơI" << endl;
        }
    } while (terms <= 0);  // �T�O���Ƥj��0

    cout << "��J�h�����]�榡�G�Y��X^���ơ^�C���H�Ů�j�}�G";

    for (int i = 0; i < terms; ++i) {
        float coef;
        int exp;
        char x, caret;  // �Ω�ѪR "X^" ���r��

        in >> coef >> x >> caret >> exp;  // Ū���榡
        if (x != 'X' || caret != '^') {  // �T�O�榡���T
            cerr << "��J�榡���~�I�w���榡�� �Y��X^���ơC" << endl;
            break;
        }
        p.NewTerm(coef, exp);  // �s�W���ب�h����
    }
    return in;
}

ostream& operator<<(ostream& out, Polynomial& p) {
    Term* a = p.getfirst();
    bool isFirst = true;

    while (a != nullptr) {
        if (a->coef != 0) {
            if (!isFirst) {
                out << (a->coef > 0 ? "+" : "-");
            }
            else if (a->coef < 0) {
                out << "-";
            }
            if (std::abs(a->coef) != 1 || a->exp == 0)
                out << std::abs(a->coef);
            if (a->exp > 0) out << "X";
            if (a->exp > 1) out << "^" << a->exp;

            isFirst = false;
        }
        a = a->nextTerm;
    }
    if (isFirst) out << "0"; // �p�G�h������ 0

    return out;
}

Polynomial Polynomial::operator+(const Polynomial& p) const {
    Polynomial result;
    Term* p1 = first; // �Ĥ@�Ӧh�������쵲��C
    Term* p2 = p.first; // �ĤG�Ӧh�������쵲��C

    // �X���쵲��C������
    while (p1 != nullptr || p2 != nullptr) {
        if (p1 != nullptr && (p2 == nullptr || p1->exp > p2->exp)) {
            result.NewTerm(p1->coef, p1->exp);
            p1 = p1->nextTerm;
        }
        else if (p2 != nullptr && (p1 == nullptr || p1->exp < p2->exp)) {
            result.NewTerm(p2->coef, p2->exp);
            p2 = p2->nextTerm;
        }
        else { // p1->exp == p2->exp
            float newCoef = p1->coef + p2->coef;
            if (newCoef != 0) {
                result.NewTerm(newCoef, p1->exp);
            }
            p1 = p1->nextTerm;
            p2 = p2->nextTerm;
        }
    }
    return result;
}

Polynomial Polynomial::operator-(const Polynomial& p) const {
    Polynomial result;
    Term* p2 = p.first;

    // �Ы� -other�]�ϸ��^
    while (p2 != nullptr) {
        result.NewTerm(-p2->coef, p2->exp);
        p2 = p2->nextTerm;
    }

    return *this + result; // �I�s�[�k
}

Polynomial Polynomial::operator=(const Polynomial& p) {
    // �ۧڽ���ˬd
    if (this == &p) return *this;

    // �����e���󪺰O����
    Term* current = first;
    while (current != nullptr) {
        Term* toDelete = current;
        current = current->nextTerm;
        delete toDelete;
    }
    first = nullptr;
    last = nullptr;

    // �p�G�ӷ��h�����O�Ū��A������^�Ŧh����
    if (p.first == nullptr) {
        return *this;
    }

    // �`�����ӷ��h����
    Term* temp = p.first;
    while (temp != nullptr) {
        this->NewTerm(temp->coef, temp->exp);
        temp = temp->nextTerm;
    }

    return *this;
}



Polynomial Polynomial::operator*(const Polynomial& other) const {
    Polynomial result;

    for (Term* p1 = first; p1 != nullptr; p1 = p1->nextTerm) {
        Polynomial temp;
        for (Term* p2 = other.first; p2 != nullptr; p2 = p2->nextTerm) {
            float newCoef = p1->coef * p2->coef;
            int newExp = p1->exp + p2->exp;
            temp.NewTerm(newCoef, newExp);
        }
        result = result + temp; // �X�ֵ��G
    }

    return result;
}

float Polynomial::Eval(float x) {
    float result = 0.0;
    Term* current = first;
    while (current != nullptr) {
        result += current->coef * pow(x, current->exp);
        current = current->nextTerm;
    }
    return result;
}

int main() {
    Polynomial AP, BP, CP;
    float x;

    cout << "��J�h���� A�F�榡�G<�Y�� ����> �C���ΪŮ���j�A������J 0 0\n";
    cin >> AP;
    cout << "\n��J�h���� B�F�榡�P�W\n";
    cin >> BP;

    cout << "\n��J�N�J���ƭ� x�G";
    cin >> x;

    cout << "\nA(x) = " << AP << "\nB(x) = " << BP;

    CP = AP + BP;
    cout << "\nA(x) + B(x) = " << CP;
    /*
        CP = AP - BP;
        cout << "\nA(x) - B(x) = " << CP;

        cout << "\nA(" << x << ") = " << AP.Eval(x);
        cout << "\nB(" << x << ") = " << BP.Eval(x);
    */
    return 0;
}

/*
2
2X^2 1X^0
1
3X^1
3
*/