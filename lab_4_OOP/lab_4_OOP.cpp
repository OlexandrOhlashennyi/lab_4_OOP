#include <iostream>
#include <string>
#define NAME 30

using namespace std;

enum currency {
	DOLLAR = 2772,
	EURO = 3301,
	POUND = 3843,
};

class pass {
protected:
	string destination;
	int duration;
public:
	pass() {
		destination = "";
		duration = 0;
	}
	pass(string str, int dur) : destination(str), duration(dur) {}
	~pass() {}
	string get_destination() { return destination; }
	int get_duration() { return duration; }
	virtual double total() { return 0; }
	bool operator<(pass& p) {
		return this->total() < p.total();
	}
	bool operator>(pass& p) {
		return this->total() > p.total();
	}

};

class vacation : public pass {
private:
	double day_price;
	double journey_price; 
	currency cur;
public:
	vacation() : pass(), day_price(0), journey_price(0), cur(DOLLAR) {}
	vacation(string str, int dur, double d_price, double j_price, currency c) : pass(str, dur), day_price(d_price), journey_price(j_price), cur(c) {}
	~vacation() {}
	double get_day_p() { return day_price; }
	double get_journey_p() { return journey_price; }
	void set_day_p(double p) { day_price = p; }
	void set_journey_p(double p) { journey_price = p; }
	double total() { return (day_price * duration + journey_price * 2)*cur/100; }
	currency get_currency() { return cur; }
};

ostream& operator<<(ostream& o, pass p) {
	o << "Destination: " << p.get_destination() << "\t\tduration: " << p.get_duration() << endl;
	return o;
}

ostream& operator<<(ostream& o, vacation v) {
	char c[5];
	switch (v.get_currency())
	{
	case DOLLAR:
		strcpy_s(c, " USD");
		break;
	case EURO:
		strcpy_s(c, " EUR");
		break;
	case POUND:
		strcpy_s(c, " GBP");
		break;
	default:
		break;
	}
	o << "Destination: " << v.get_destination() << "\tduration: " << v.get_duration() << "\n\tprice per day: " << v.get_day_p() << c << "\tjourney price: " << v.get_journey_p() << c << "\n\t\t\ttotal price: " << v.total() << " UAH" << endl;	
	return o;
}

void input_pass(pass **p, int n) {
	cout << "\n\tEnter pass:\n";
	for (int i = 0; i < n; i++) {
		char s[NAME];
		int l, d_p, j_p, c;
		currency cur;
		cout << "Destination: "; cin >> s;
		cout << "Duration: "; cin >> l;
		cout << "day price: "; cin >> d_p;
		cout << "journey price: "; cin >> j_p;
		cout << "currency(dollar -- 1, euro -- 2, pound -- 3): "; cin >> c;
		cout << "\n\n";
		switch (c) {
		case 1:
			cur = DOLLAR;
			break;
		case 2:
			cur = EURO;
			break;
		case 3:
			cur = POUND;
		default:
			break;
		}
		p[i] = new vacation(s, l, d_p, j_p, cur);
	}
}

void print_pass(pass** p, int n) {
	cout << "\n\t***pass***\n";
	for (int i = 0; i < n; i++) {
		cout << i+1 << ". " << *static_cast<vacation*>(p[i]) << endl;
	}
}

void sort(pass **p, int n) {
	pass** ptrpass;
	vacation temp;
	int i;
	for (i = 1; i < n; i++) {
		if (p[i] < p[i-1])
			continue;
		temp = *static_cast<vacation*>(p[i]);
		ptrpass = p + i - 1;
		while (temp < **ptrpass) {
			*static_cast<vacation*>(*(ptrpass + 1)) = *static_cast<vacation*>(*ptrpass);
			if (--ptrpass < p) break;
		}
		*static_cast<vacation*>(*(ptrpass + 1)) = (temp);
	}
}

double average(pass** p, int n) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += p[i]->total();
	}
	return sum/n;
}

int main() {
	pass *(*p);
	int n;
	cout << "Enter number of pass: ";
	cin >> n;
	p = new pass*[n];
	input_pass(p, n);
	print_pass(p, n);
	sort(p, n);
	cout << "\n\tAfter sort:\n";
	print_pass(p, n);
	cout << "\n\tAverage price: " << average(p, n);
	return 0;
}

/*5
Lviv
3
11
10
2
Kyiv
2
15
10
1
Antananarivo
7
35
25
3
Krakow
3
25
15
2
Kahovka
4
2
53
3*/