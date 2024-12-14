#include <iostream>
#include <algorithm>
#include <cmath>


using namespace std;

class Polynomial;

class Term {
public:
    friend Polynomial;
private:
    float coef; // 係數
    int exp;    // 次方數
};

class Polynomial {
private:
    Term* termArray; // 儲存多項式項目的陣列
    int capacity;    // 陣列容量
    int terms;       // 當前項目數量
public:
    Polynomial() : capacity(8), terms(0) {
        termArray = new Term[capacity];
    }
    int getterms() const { return terms; }
    void Add(const Polynomial& poly);      // 加法
    Polynomial Mult(const Polynomial poly);      // 乘法
    void NewTerm(const float coef, const int exp); // 新增項目
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

    // 處理剩餘的項目
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

        if (coef == 0) continue; // 跳過係數為 0 的項目

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

    // 輸入多項式1
    cout << "輸入多項式1（格式：係數 次方數，結束請輸入次方數為0）：" << endl;
    while (cin >> coef >> exp) {
        if (exp == 0) break; // 次方數為0時結束
        if (coef != 0 && exp > 0)  AP.NewTerm(coef, exp);
    }

    // 清理輸入流
    if (cin.fail()) {
        cin.clear(); // 清理錯誤狀態
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略緩衝區中的剩餘輸入

    // 輸入多項式2
    cout << "輸入多項式2（格式：係數 次方數，結束請輸入次方數為0）：" << endl;
    while (cin >> coef >> exp) {
        if (exp == 0) break; // 次方數為0時結束
        if (coef != 0 && exp > 0) BP.NewTerm(coef, exp);
    }
    AP.print();

    // 顯示運算模式並進行加法
    cout << "選擇運算模式(+):";
    cin >> mod;

    // 呼叫 Add 函數並接收回傳的多項式
    if (mod == '+') {
        cout << "加法結果是：";
        AP.Add(BP);
    }
    return 0;
}

/*
3 3 5 2 1 1 0 0 
4 3 2 2 1 1 0 0
*/
