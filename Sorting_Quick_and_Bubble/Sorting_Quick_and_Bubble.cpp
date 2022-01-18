/*
* Сортировать по возрастанию, алгоритмы: простой обмен (улучшенная), Быстрая (первый, рекурсивно)
* В файле:
* период брони (дата, кол-во дней)
* тип номера
* телефон
* Сортировать сначала по периоду брони, потом по типу номера
* Устойчивая сортировка не меняет изначальный порядок одинаковых элементов
* Пример сортировка по фамилии:
* Иванов Иван         Абрамов Олег
* Иванов Сергей  ->   Иванов Иван
* Абрамов Олег        Иванов Сергей
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Date
{
	int day;
	int mounth;
	int year;
};

struct Info // элементы содержат информацию из файла
{
	Date date;
	int countOfDay;
	string typeOfRoom;
	string phoneNumber;
};

// ----------------------------------------------- Методы вычленения данных из файла -----------------------------------------------

// Считает количество непустых строк в файле
int getCountOfLines(ifstream &in)
{
	int count = 0; string str = "";
	while (!in.eof())
	{
		getline(in, str);
		if (str != "")
			count++;
	}
	return count;
}

// Возвращает дату из брони
Date getDate(string str)
{
	Date date;
	string s = "";
	int i = 0;

	while (str[i] != '.')
	{
		s += str[i];
		i++;
	}
	date.day = stoi(s);
	i++;

	s = "";
	while (str[i] != '.')
	{
		s += str[i];
		i++;
	}
	date.mounth = stoi(s);
	i++;

	s = "";
	while (str[i] != ' ')
	{
		s += str[i];
		i++;
	}
	date.year = stoi(s);

	return date;
}

// Возращает число (количество дней) из брони
int getCountOfDay(string str)
{
	// Доходим до дня из брони
	int i = 0;
	while (str[i] != ' ')
		i++;
	i++;

	// Вычлением дни из брони
	string s = "";
	while (str[i] != ' ')
	{
		s += str[i];
		i++;
	}

	return stoi(s); // stoi() преобразует строку в int
}

// Возвращает тип номера из брони
string getTypeOfRoom(string str)
{
	int i = 0;
	for (int j = 0; j < 2; j++)
	{
		while (str[i] != ' ')
			i++;
		i++;
	}

	string s = "";
	while (str[i] != ' ')
	{
		s += str[i];
		i++;
	}

	return s;
}

// Возвращает тип комнаты из файла
int getPriorityTypeOfRoom(string type)
{
	if (type == "Single")
		return 1;
	else if (type == "Double")
		return 2;
	else if (type == "Triple")
		return 3;
	else
		return 0;
}

// Возвращает номер телефона из файла
string getPhoneNumber(string str)
{
	int l = str.length();
	string s = "";

	int i = l - 1;
	while (str[i] != ' ')
	{
		i--;
	}
	i++;

	while (i < l - 1)
	{
		s += str[i];
		i++;
	}

	return s;
}

// ----------------------------------------------- Операторы перегрузки -----------------------------------------------

// Перегрузка оператора "<" для сравнения дат
bool operator < (Date d1, Date dPivot)
{
	if (d1.year < dPivot.year)
	{
		return true;
	}
	else if (d1.mounth < dPivot.mounth)
	{
		return true;
	}
	else if (d1.mounth > dPivot.mounth)
	{
		return false;
	}
	else if (d1.day < dPivot.day)
	{
		return true;
	}
	else
		return false;
}

// Перегрузка оператора ">" для сравнения дат
bool operator > (Date d1, Date dPivot)
{
	if (d1.year > dPivot.year)
	{
		return true;
	}
	else if (d1.year < dPivot.year)
	{
		return false;
	}
	else if (d1.mounth > dPivot.mounth)
	{
		return true;
	}
	else if (d1.mounth < dPivot.mounth)
	{
		return false;
	}
	else if (d1.day > dPivot.day)
	{
		return true;
	}
	else
		return false;
}

// Перегрузка оператора "==" для сравнения дат
bool operator == (Date d1, Date dPivot)
{
	if (d1.year == dPivot.year &&
		d1.mounth == dPivot.mounth
		&& d1.day == dPivot.day)
	{
		return true;
	}
	else
		return false;
}

// Перегрузка оператора "<<" для вывода информации: период брони, тип комнаты, номер телефона
ostream &operator << (ostream &out, Info info)
{
	if (info.date.day < 10 && info.date.day > 0)
		out << "0"
			<< info.date.day
			<< "."
			<< info.date.mounth
			<< "."
			<< info.date.year
			<< " "
			<< info.countOfDay
			<< " " 
			<< info.typeOfRoom
			<< " "
			<< info.phoneNumber;
	else
		out << info.date.day
			<< "."
			<< info.date.mounth
			<< "."
			<< info.date.year
			<< " "
			<< info.countOfDay
			<< " "
			<< info.typeOfRoom
			<< " "
			<< info.phoneNumber;

	return out;
}

// ----------------------------------------------- Быстрая сортировка, по Хоара -----------------------------------------------

void quickSortByDate(Info *arrayOfInfo, int left, int right)
{
	int i = left, j = right;
	Date pivot = arrayOfInfo[left].date; // Опорный - первый элемент
	int k = arrayOfInfo[left].countOfDay;

	do
	{
		// Сравниваем по дате и по количеству дней(второстепенно)
		while ((arrayOfInfo[i].date < pivot) || (arrayOfInfo[i].date == pivot && arrayOfInfo[i].countOfDay < k))
			i++;

		// Сравниваем по дате по количеству дней(второстепенно)
		while ((arrayOfInfo[j].date > pivot) || (arrayOfInfo[j].date == pivot && arrayOfInfo[j].countOfDay > k))
			j--;

		if (i <= j)
		{
			if ((arrayOfInfo[i].date > arrayOfInfo[j].date) || 
				(arrayOfInfo[i].date == arrayOfInfo[j].date &&
				 arrayOfInfo[i].countOfDay > arrayOfInfo[j].countOfDay))
			{
				Info s = arrayOfInfo[i];
				arrayOfInfo[i] = arrayOfInfo[j];
				arrayOfInfo[j] = s;
			}
			i++;
			j--;
		}
	}
	while (i <= j);

	if (i < right)
		quickSortByDate(arrayOfInfo, i, right);
	if (left < j)
		quickSortByDate(arrayOfInfo, left, j);
}

void quickSortByTypeOfRoom(Info *arrayOfInfo, int left, int right)
{
	int i = left, j = right;
	string pivot = arrayOfInfo[left].typeOfRoom; // Опорный - первый элемент

	do
	{
		// Сравниваем по типу номера
		while (getPriorityTypeOfRoom(arrayOfInfo[i].typeOfRoom) < getPriorityTypeOfRoom(pivot)) i++;

		// Сравниваем по типу номера
		while (getPriorityTypeOfRoom(arrayOfInfo[j].typeOfRoom) > getPriorityTypeOfRoom(pivot)) j--;

		if (i <= j)
		{
			if (getPriorityTypeOfRoom(arrayOfInfo[i].typeOfRoom) > getPriorityTypeOfRoom(arrayOfInfo[j].typeOfRoom))
			{
				Info s = arrayOfInfo[i];
				arrayOfInfo[i] = arrayOfInfo[j];
				arrayOfInfo[j] = s;
			}
			i++;
			j--;
		}
	}
	while (i <= j);

	if (i < right)
		quickSortByTypeOfRoom(arrayOfInfo, i, right);
	if (left < j)
		quickSortByTypeOfRoom(arrayOfInfo, left, j);
}

// ----------------------------------------------- Сортировка простыми обменами (улучшенная) -----------------------------------------------

/*Можно заметить, что после i-ой итерации внешнего цикла i последних элементов уже находятся на своих местах в отсортированном порядке,
поэтому нет необходимости производить их сравнения друг с другом.
Следовательно, внутренний цикл можно выполнять не до n−2, а до n−i−2.
Также заметим, что если после выполнения внутреннего цикла не произошло ни одного обмена, то массив уже отсортирован,
и продолжать что-то делать бессмысленно. Поэтому внутренний цикл можно выполнять не n−1 раз, а до тех пор,
пока во внутреннем цикле происходят обмены.*/

void BubbleSortByDate(Info *arrayOfInfo, int N)
{
	int i = 0;
	bool isChanged = true;

	while (isChanged)
	{
		isChanged = false;

		for (int j = 0; j < N - i - 1; j++)
		{
			if (arrayOfInfo[j].date > arrayOfInfo[j + 1].date ||
				(arrayOfInfo[j].date == arrayOfInfo[j + 1].date &&
					arrayOfInfo[j].countOfDay > arrayOfInfo[j + 1].countOfDay))
			{
				//Меняем местами элемент массива с индексом i и следующий за ним
				Info s = arrayOfInfo[j];
				arrayOfInfo[j] = arrayOfInfo[j + 1];
				arrayOfInfo[j + 1] = s;

				isChanged = true;
			}
		}
		i += 1;
	}
}

void BubbleSortByTypeOfRoom(Info *arrayOfInfo, int N)
{
	int i = 0;
	bool isChanged = true;

	while (isChanged)
	{
		isChanged = false;

		for (int j = 0; j < N - i - 1; j++)
		{
			if (getPriorityTypeOfRoom(arrayOfInfo[j].typeOfRoom) > getPriorityTypeOfRoom(arrayOfInfo[j + 1].typeOfRoom))
			{
				//Меняем местами элемент массива с индексом j и следующий за ним
				Info s = arrayOfInfo[j];
				arrayOfInfo[j] = arrayOfInfo[j + 1];
				arrayOfInfo[j + 1] = s;

				//Раз поменяли местами, зафиксируем этот факт
				isChanged = true;
			}
		}
		i += 1;
	}
}


// ----------------------------------------------- Main -----------------------------------------------
int main()
{
	setlocale(LC_ALL, "rus");

	string input = "Input.txt"; // Путь к входному файлу
	string output = "Output.txt";// Путь к файлу для записи

	ifstream in(input);
	ofstream out(output);

	unsigned int start; // Начало и конец выполнения программы по времени

	int count = 0; // Количество строк в файле
	if (in.is_open())
		count = getCountOfLines(in);

	Info *arrayOfInfo = new Info[count];
	string str = "";
	int j = 0;

	in.seekg(0); // Возвращает курсор в начало файла
	while (!in.eof())
	{
		getline(in, str);

		Info arr;
		arr.date = getDate(str);
		arr.countOfDay = getCountOfDay(str);
		arr.typeOfRoom = getTypeOfRoom(str);
		arr.phoneNumber = getPhoneNumber(str);

		arrayOfInfo[j] = arr;
		j++;
	}
	in.close();

	int v; // Для switch
	cout << "1: Быстрая сортировка по периоду брони\n" << "2: Быстрая сортировка по типу номера\n";
	cout << "3: Простыми обменами (улучшенная) по периоду брони\n" << "4: Простыми обменами (улучшенная) по типу номера\n";
	cout << "Выберите сортировку: ";
	cin >> v;

	switch (v)
	{
	case 1: 
		cout << "Сортируем быстрая сортировка по периоду брони..." << endl;
		start = clock();
		quickSortByDate(arrayOfInfo, 0, count - 1);
		start = clock() - start;
		cout << "Быстрая сортировка по периоду брони: " << "выполнена (смотреть файл)" << endl;

		out << "======================= Быстрая сортировка по периоду брони =======================" << endl;
		for (int i = 0; i < count; i++)
			out << arrayOfInfo[i] << endl;
		out << "Время сортировки в секундах: " << (double)start / CLOCKS_PER_SEC << endl;
		out << endl;
		break;

	case 2: 
		cout << "Сортируем быстрая сортировка по типу номера..." << endl;
		start = clock();
		quickSortByTypeOfRoom(arrayOfInfo, 0, count - 1);
		start = clock() - start;
		cout << "Быстрая сортировка по типу номера: " << "выполнена (смотреть файл)" << endl;

		out << "======================= Быстрая сортировка по типу номера =======================" << endl;
		for (int i = 0; i < count; i++)
			out << arrayOfInfo[i] << endl;
		out << "Время сортировки в секундах: " << (double)start / CLOCKS_PER_SEC << endl;
		out << endl;
		break;

	case 3:
		cout << "Сортируем простыми обменами (улучшенная) по периоду брони..." << endl;
		start = clock();
		BubbleSortByDate(arrayOfInfo, count);
		start = clock() - start;
		cout << "Сортировка простыми обменами (улучшенная) по периоду брони: " << "выполнена (смотреть файл)" << endl;

		out << "======================= Сортировка простыми обменами (улучшенная) по периоду брони =======================" << endl;
		for (int i = 0; i < count; i++)
			out << arrayOfInfo[i] << endl;
		out << "Время сортировки в секундах: " << (double)start / CLOCKS_PER_SEC << endl;
		out << endl;
		break;

	case 4:
		cout << "Сортируем простыми обменами (улучшенная) по типу номера..." << endl;
		start = clock();
		BubbleSortByTypeOfRoom(arrayOfInfo, count);
		start = clock() - start;
		cout << "Сортировка простыми обменами (улучшенная) по типу номера: " << "выполнена (смотреть файл)" << endl;

		out << "======================= Сортировка простыми обменами (улучшенная) по типу номера =======================" << endl;
		for (int i = 0; i < count; i++)
			out << arrayOfInfo[i] << endl;
		out << "Время сортировки в секундах: " << (double)start / CLOCKS_PER_SEC << endl;
		out << endl;
		break;

	default:
		cout << "Неверно введен номер сортировки";
		break;
	}

	/*
	Время для 1000 элементов:
	* 1: Время 0,165 сек
	* 2: Время 0,196 сек
	* 3: Время 8,538 сек
	* 4: Время 8,358
	*/
	
	delete[] arrayOfInfo;
	return 0;
}