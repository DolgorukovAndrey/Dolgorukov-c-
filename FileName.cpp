#include <iostream>
#include <vector>
#include <string>
using namespace std;
void massiv(vector <long int>& a, string s, int len, int part) //razdelenie po 9 elementov i zanesenie v massiv
{
	string sub; 
	int k = 1, i = len - 9, j = 0;
	while (k <= part)
	{
		sub = i >= 0 ? s.substr(i, 9) : s.substr(0, 9 + i);
		a[j] = atoi(sub.c_str());	
		j++; k++;
		i -= 9;
	}
}
string to_str(long int m) //preobrazovanie chisla v stroky s dobavleniem 0
{
	string s = to_string(m);
	s.insert(0, 9 - s.length(), '0');
	return s;
}
string factorial(string s1, string s2) //ymnojenie stolbikom
{
	string s;
	int dlina;
	if (s1.length() >= s2.length()) { //vichislenie max dlina chisel i vichislenie max vozmojnoi dlini
		s.insert(0, s1.length() * 2, '0');
		dlina = s1.length() * 2 - 1;
	}
	else {
		s.insert(0, s2.length() * 2, '0');
		dlina = s2.length() * 2 - 1;
	}
	int ost = 0; int ost1 = 0; //ostatki
	int l1, l2, l;
	string c, c1, c2;
	for (int i = s1.length() - 1; i >= 0; i--) { //ymnojenie stolbikom
		int d = dlina;
		for (int j = s2.length() - 1; j >= 0; j--) {
			c = s[d]; c1 = s1[i]; c2 = s2[j]; //videlenie nyznih elementov
			l = atoi(c.c_str()); l1 = atoi(c1.c_str()); l2 = atoi(c2.c_str()); //perevod strok v chisla
			ost = (l + (l1 * l2) + ost1) / 10; //ostatok
			l = (l + (l1 * l2) + ost1) % 10; //vichislenie elementa
			ost1 = ost; //peredacha novogo ostatka
			s[d] = char(48 + l);
			d--;

		}
		s[d] += ost;
		ost = 0;
		ost1 = 0;
		dlina--;
	}
	s.erase(0, s.find_first_not_of('0'));
	return s;
}
int main()
{
	int n;
	cout << "To calculate the amount 1! + 2! + 3! + ... + n!" << endl;
	int pr = 0;
	while (pr == 0) { //vvod n
		while (true) // proverka na vvod n
		{
			cout << "Enter n: ";
			cin >> n;
			if (!cin)
			{
				cout << "The number is incorrect, please enter it again: \n";
				cin.clear();
				while (cin.get() != '\n');
			}
			else break;
		}
		while (cin.get() != '\n')
			cin.clear();
		cout << "You want to calculate the amount for n = " << n << "? (If not, enter 0, else 1)" << endl;
		while (true) { //proverka na pravilnost vvoda
			cin >> pr;
			if (!cin) {
				cout << "Enter the correct answer (If not, enter 0, else 1): ";
				cin.clear();
				while (cin.get() != '\n');
			}
			else break;
		}
	}
	string s2 = to_string(1), f2 = to_string(1);
	string s = to_string(0);
	string fact;
	for (int i = 1; i <= n; i++) {
		string s1;
		s1 = s; // peredaetsa summa
		s.clear();
		f2 = to_string(i);
		fact = factorial(s2, f2);
		s2 = fact; // peredaetsa factorial
		int len1 = s1.length();
		int len2 = s2.length();
		if (len1 < len2)
		{
			s1.insert(0, len2 - len1, '0');
		}
		else
			if (len1 > len2)
				s2.insert(0, len1 - len2, '0');
		int len = s1.length(); //dlina
		// delim stroki po 9
		int part = len % 9 == 0 ? len / 9 : len / 9 + 1;
		vector <long int> a(part + 1, 0);
		vector <long int> b(part + 1, 0);
		// zanesenie strok v vectori
		massiv(a, s1, len, part);
		massiv(b, s2, len, part);
		// perenos razrada
		int ost = 0;
		int ost1 = 0;
		for (int i = 0; i <= part; i++)
		{
			ost = (a[i] + b[i]) / 1000000000; // perenos
			a[i] = (a[i] + b[i]) % 1000000000 + ost1; // summa chisel
			ost1 = ost; // perenos
		}
		for (int i = part; i >= 0; i--)
			s += to_str(a[i]);// vivod s konca
		s.erase(0, s.find_first_not_of('0'));
	}
	cout << "The sum of the factorials is: " << s;	
}