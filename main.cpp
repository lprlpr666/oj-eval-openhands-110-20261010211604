// Solution for ACMOJ 1073

#include <iostream>
#include <cstdlib>

using namespace std;

class Date {
    int y, m, d;
    static bool isLeap(int year) {
        return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    }
    static int monthDays(int year, int month) {
        static const int mdays[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
        if (month == 2 && isLeap(year)) return 29;
        return mdays[month];
    }
    // days since 1900-01-01 (0 based)
    long toOrdinal() const {
        long days = 0;
        for (int yr = 1900; yr < y; ++yr) days += isLeap(yr) ? 366 : 365;
        for (int mo = 1; mo < m; ++mo) days += monthDays(y, mo);
        days += d - 1; // current day offset
        return days;
    }
    void fromOrdinal(long ord) {
        int yr = 1900;
        while (true) {
            int yearDays = isLeap(yr) ? 366 : 365;
            if (ord >= yearDays) { ord -= yearDays; ++yr; }
            else break;
        }
        int mo = 1;
        while (true) {
            int md = monthDays(yr, mo);
            if (ord >= md) { ord -= md; ++mo; }
            else break;
        }
        y = yr; m = mo; d = (int)ord + 1;
    }
public:
    Date(): y(1900), m(1), d(1) {}
    Date(int yy, int mm, int dd) {
        bool ok = true;
        if (yy < 1900 || yy > 2030) ok = false;
        if (mm < 1 || mm > 12) ok = false;
        if (dd < 1 || dd > monthDays(yy, mm)) ok = false;
        if (ok) { y = yy; m = mm; d = dd; }
        else { y = 1900; m = 1; d = 1; }
    }
    // prefix ++
    Date& operator++() {
        *this = *this + 1;
        return *this;
    }
    // postfix ++
    Date operator++(int) {
        Date tmp = *this;
        ++(*this);
        return tmp;
    }
    // prefix --
    Date& operator--() {
        *this = *this - 1;
        return *this;
    }
    // postfix --
    Date operator--(int) {
        Date tmp = *this;
        --(*this);
        return tmp;
    }
    Date operator+(int days) const {
        Date res = *this;
        long ord = toOrdinal() + days;
        res.fromOrdinal(ord);
        return res;
    }
    Date operator-(int days) const {
        Date res = *this;
        long ord = toOrdinal() - days;
        res.fromOrdinal(ord);
        return res;
    }
    // date - date => absolute days difference
    long operator-(const Date& other) const {
        long diff = toOrdinal() - other.toOrdinal();
        if (diff < 0) diff = -diff;
        return diff;
    }
    bool operator<(const Date& other) const {
        return toOrdinal() < other.toOrdinal();
    }
    friend ostream& operator<<(ostream& os, const Date& dt) {
        os << dt.y << '-' << dt.m << '-' << dt.d;
        return os;
    }
    // optional out() for safety
    void out() const { cout << y << '-' << m << '-' << d << '\n'; }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int op; if(!(cin>>op)) return 0;
    int yy,mm,dd;
    if(op==1||op==0){
        Date d0; Date d1(2000,2,29); Date d2(1900,2,29);
        cout<<d0<<'\n'<<d1<<'\n'<<d2<<'\n';
    }
    if(op==2||op==0){
        cin>>yy>>mm>>dd; Date d0(yy,mm,dd);
        for(int i=0;i<5;++i) cout<<++d0<<'\n';
        for(int i=0;i<5;++i) cout<<d0++<<'\n';
        for(int i=0;i<5;++i) cout<<d0--<<'\n';
        for(int i=0;i<2;++i) cout<<--d0<<'\n';
        cout<<d0<<'\n';
    }
    if(op==3||op==0){
        cin>>yy>>mm>>dd; Date d0(yy,mm,dd);
        cout<<d0+100<<'\n';
        cout<<d0-1000<<'\n';
    }
    if(op==4||op==0){
        cin>>yy>>mm>>dd; Date d0(yy,mm,dd);
        Date d1(2020,12,21);
        cout<<(d0<d1?1:0)<<'\n';
    }
    if(op==5||op==0){
        cin>>yy>>mm>>dd; Date d0(yy,mm,dd);
        Date d1(1912,6,23);
        cout<<d0-d1<<'\n';
    }
// End of solution
    return 0;
}
