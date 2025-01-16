#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Функция умножения двух длинных чисел (строки)
string multiply(const string& num1, const string& num2) {
	int n = num1.size(); // Длина первого числа
	int m = num2.size(); // Длина второго числа
	string result(n + m, '0'); // Результат умножения, инициализирован нулями

	// Перемножаем числа поразрядно
	for (int i = n - 1; i >= 0; i--) {
		int carry = 0; // Перенос в старший разряд
		for (int j = m - 1; j >= 0; j--) {
			int temp = (result[i + j + 1] - '0') + // Текущий разряд результата
				(num1[i] - '0') * (num2[j] - '0') + carry; // Умножение разрядов двух чисел
			result[i + j + 1] = temp % 10 + '0'; // Обновляем младший разряд результата
			carry = temp / 10; // Переносим остаток
		}
		result[i] += carry; // Добавляем перенос
	}

	// Удаляем ведущие нули из результата, если они есть
	size_t startpos = result.find_first_not_of("0");
	if (startpos != string::npos) {
		return result.substr(startpos); // Возвращаем строку без ведущих нулей
	}
	return "0"; // Если результат — ноль, возвращается "0"
}

// Функция возведения числа (в строковом формате) в степень
string power(const string& base, int exponent) {
	string result = "1"; // Начальное значение результата (единица)
	string current = base; // Текущее основание — начинается с base

	while (exponent > 0) {
		if (exponent % 2 == 1) {
			result = multiply(result, current); // Умножаем результат на текущее основание
		}
		current = multiply(current, current); // Увеличиваем текущее основание до квадрата
		exponent /= 2; // Делим степень на два
	}

	return result;
}

// Функция вычитания длинных чисел (строк). подобие столбиком вычитание
string subtract(const string& num1, const string& num2) {
	string result; // Результат
	int n = num1.size(); // Длина уменьшаемого
	int m = num2.size(); // Длина вычитаемого
	int carry = 0; // Переменная для учета займа

	// Вычитаем числа поразрядно, начиная с младших разрядов
	for (int i = 0; i < n; i++) {
		int a = num1[n - 1 - i] - '0'; // Текущий разряд уменьшаемого
		int b = (i < m) ? num2[m - 1 - i] - '0' : 0; // Текущий разряд вычитаемого (или 0)
		int current = a - b - carry; // Вычитаем с учетом возможного займа
		if (current < 0) { // Если результат меньше нуля
			current += 10; // Делаем заимствование
			carry = 1; // Устанавливаем перенос
		}
		else {
			carry = 0; // Займа нет
		}
		result.push_back(current + '0'); // Добавляем разряд к результату
	}

	// Удаляем ведущие нули с конца строки
	while (result.size() > 1 && result.back() == '0') {
		result.pop_back(); // Удаляем последний символ, если он равен '0'
	}
	reverse(result.begin(), result.end()); // Разворачиваем строку, так как результат формировался с конца
	return result; 
}

// Функция сравнения двух длинных чисел:
// Возвращает:
// 1 — если num1 > num2
// -1 — если num1 < num2
// 0 — если числа равны
int compare(const string& num1, const string& num2) {
	if (num1.size() > num2.size()) return 1; // 
	if (num1.size() < num2.size()) return -1; //
	for (size_t i = 0; i < num1.size(); i++) { // Сравниваем посимвольно
		if (num1[i] > num2[i]) return 1;
		if (num1[i] < num2[i]) return -1;
	}
	return 0; // Числа равны
}


int main() {
	int a, b, m, n;
	cout << "Дана задача : Выяснить, какое из чисел a^m, b^n больше и на сколько (0 < a, b <= 40000; 0 <  m, n <= 10)." << endl;
	cout << "Введите значения a, m, b, n: "; 
	cin >> a >> m >> b >> n;
	if (a > 40000 or b > 40000 or m > 10 or n > 10 or a < 0 or b < 0 or m < 0 or n < 0) {
		cout << "Ошибка ввода! Читайте внимательно." << endl; //Если числа не подходят к задаче
		return 1;
	}


	// Преобразуем числа a и b в строки для работы с длинными числами
	string str_a = to_string(a);
	string str_b = to_string(b);

	// Вычисляем степени a^m и b^n с использованием функции pow
	string a_pow_m = power(str_a, m);
	string b_pow_n = power(str_b, n);

	// Сравниваем результаты a^m и b^n
	int cmp = compare(a_pow_m, b_pow_n);

	if (cmp == 1) {
		string difference = subtract(a_pow_m, b_pow_n);
		cout << "Число a^m больше числа b^n на: " << difference << "\n";
	}
	else if (cmp == -1) {
		string difference = subtract(b_pow_n, a_pow_m);
		cout << "Число b^n больше числа a^m на: " << difference << "\n";
	}
	else {
		cout << "Число a^m и Число b^n равны." << "\n";
	}

	return 0;
}