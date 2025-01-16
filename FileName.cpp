#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;
void massiv(vector <long int>& a, string s, int len, int part)
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
string to_str(long int m)
{
	string s = to_string(m);
	s.insert(0, 9 - s.length(), '0');
	return s;
}
string factorial(string s1, string s2) //ymnojenie stolbikom
{
	string s;
	int dlina;
	if (s1.length() >= s2.length()) {
		s.insert(0, s1.length() * 2, '0');
		dlina = s1.length() * 2 - 1;
	}
	else {
		s.insert(0, s2.length() * 2, '0');
		dlina = s2.length() * 2 - 1;
	}
	int ost = 0; int ost1 = 0;
	int l1, l2, l;
	string c, c1, c2;
	for (int i = s1.length() - 1; i >= 0; i--) {
		int d = dlina;
		for (int j = s2.length() - 1; j >= 0; j--) {
			c = s[d]; c1 = s1[i]; c2 = s2[j];
			l = atoi(c.c_str()); l1 = atoi(c1.c_str()); l2 = atoi(c2.c_str());
			ost = (l + (l1 * l2) + ost1) / 10;
			l = (l + (l1 * l2) + ost1) % 10;
			ost1 = ost;
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
	SetConsoleOutputCP(1251);
	int n;
	cout << "Для подсчёта суммы 1! + 2! + 3! + ... + n!" << endl;
	int pr = 0;
	while (pr == 0) {
		while (true) // proverka na vvod n
		{
			cout << "Введите n: ";
			cin >> n;
			if (!cin)
			{
				cout << "Не верно введено число, введите заново: \n";
				cin.clear();
				while (cin.get() != '\n');
			}
			else break;
		}
		while (cin.get() != '\n')
			cin.clear();
		cout << "Вы хотите подсчитать сумма для n = " << n << "? (Если нет введите 0, иначе введите 1)" << endl;
		while (true) { //proverka na pravilnost vvoda
			cin >> pr;
			if (!cin) {
				cout << "Введите корректный ответ (Если не хотите считать введите 0б иначе - 1): ";
				cin.clear();
				while (cin.get() != '\n');
			}
			else break;
		}
	}
	int j = 1;
	string s2 = to_string(1), f2 = to_string(1);
	string s = to_string(0);
	string fact;
	for (int i = 1; i <= n; i++) {
		string s1;
		s1 = s;
		s.clear();
		f2 = to_string(i);
		fact = factorial(s2, f2);
		s2 = fact;
		int len1 = s1.length();
		int len2 = s2.length();
		if (len1 < len2)
		{
			s1.insert(0, len2 - len1, '0');
		}
		else
			if (len1 > len2)
				s2.insert(0, len1 - len2, '0');
		int len = s1.length();
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
		j++;
	}
	cout << "Сумма факториалов равна: " << s;	
}