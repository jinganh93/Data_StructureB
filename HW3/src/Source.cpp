#include <iostream>
#include <algorithm>

using namespace std;

class Polynomial;

class Term {
public:
    float coef; // 係數
    int exp;    // 次方數
    Term* nextTerm;
    Term() : coef(0), exp(0), nextTerm(nullptr) {}
    Term(int incoef, int inexp) : coef(incoef), exp(inexp) { nextTerm = nullptr; }
    Term(int incoef, int inexp, Term* next) : coef(incoef), exp(inexp), nextTerm(next) {}
    ~Term() {};
};

class Polynomial {
private:
    Term* first, * last; // 第一項
    //int capacity;    // 陣列容量
    //int terms;       // 當前項目數量
public:
    Polynomial() : first(nullptr), last(nullptr) {}
    //int getterms() const { return terms; }
    Term* getfirst() { return first; }
    void NewTerm(const float coef, const int exp); // 新增項目

    // 多載運算子
    friend istream& operator>>(istream& in, Polynomial& p);
    friend ostream& operator<<(ostream& out, Polynomial& p);
    Polynomial operator+ (const Polynomial& p) const;
    Polynomial operator- (const Polynomial& p) const;
    Polynomial operator= (const Polynomial& p);
    Polynomial operator* (const Polynomial& p) const;

    //運算函式
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
        cout << "輸入多項式項數：";
        in >> terms;  // 讀取多項式項數

        if (in.fail()) {  // 如果輸入不是有效整數
            in.clear();  // 清除錯誤狀態
            in.ignore(numeric_limits<streamsize>::max(), '\n');  // 忽略錯誤的輸入
            cout << "請輸入一個有效的整數！" << endl;
        }
    } while (terms <= 0);  // 確保項數大於0

    cout << "輸入多項式（格式：係數X^次數）每項以空格隔開：";

    for (int i = 0; i < terms; ++i) {
        float coef;
        int exp;
        char x, caret;  // 用於解析 "X^" 的字符

        in >> coef >> x >> caret >> exp;  // 讀取格式
        if (x != 'X' || caret != '^') {  // 確保格式正確
            cerr << "輸入格式錯誤！預期格式為 係數X^次數。" << endl;
            break;
        }
        p.NewTerm(coef, exp);  // 新增項目到多項式
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
    if (isFirst) out << "0"; // 如果多項式為 0

    return out;
}

Polynomial Polynomial::operator+(const Polynomial& p) const {
    Polynomial result;
    Term* p1 = first; // 第一個多項式的鏈結串列
    Term* p2 = p.first; // 第二個多項式的鏈結串列

    // 合併鏈結串列的項目
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

    // 創建 -other（反號）
    while (p2 != nullptr) {
        result.NewTerm(-p2->coef, p2->exp);
        p2 = p2->nextTerm;
    }

    return *this + result; // 呼叫加法
}

Polynomial Polynomial::operator=(const Polynomial& p) {
    // 自我賦值檢查
    if (this == &p) return *this;

    // 釋放當前物件的記憶體
    Term* current = first;
    while (current != nullptr) {
        Term* toDelete = current;
        current = current->nextTerm;
        delete toDelete;
    }
    first = nullptr;
    last = nullptr;

    // 如果來源多項式是空的，直接返回空多項式
    if (p.first == nullptr) {
        return *this;
    }

    // 深拷貝來源多項式
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
        result = result + temp; // 合併結果
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

    cout << "輸入多項式 A；格式：<係數 次數> 每項用空格分隔，結尾輸入 0 0\n";
    cin >> AP;
    cout << "\n輸入多項式 B；格式同上\n";
    cin >> BP;

    cout << "\n輸入代入的數值 x：";
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