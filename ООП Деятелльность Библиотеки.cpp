//Данные в файле представленны след. образом
//Пушкин_А.С Сказки 1990 2
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<iomanip>

using namespace std;

//класс Книга
class Book
{
public:
	char author[255];//фамилия + инициалы автора
	char name[255];//название
	int year;//год издания
	int number;//кол-во экземпляров

public:
	Book() { }
	//заполнение информации о книге с клавиатуры
	Book initKL()
	{
		char str_author[255];
		cout << "Введите фамилию и иницыалы автора" << endl;
		cin >> str_author;
		strcpy(author,str_author);

		char str_name[255];
		cout << "Введите название книги" << endl;
		cin >> str_name;
		strcpy(name, str_name);

		cout << "Введите год издания" << endl;
		cin >> year;

		cout << "Введите кол-во экземпляров" << endl;
		cin >> number;
		return *this;
	}
	//добавление информации о книге
	Book init(char* _Author, char* _name, int _year, int _number)
	{
		strcpy(author,_Author);
		strcpy(name, _name);
		year = _year;
		number = _number;
		return *this;
	}
	//печать книги
	void PrintBook()
	{
		cout << "______________________________________________" << endl;
		cout << "|"<<setw(15) << left<< author << "|" << setw(15) << left << name << "|" << setw(5) << left << year << "|" << setw(6) << left << number <<"|"<< endl;
		cout << "______________________________________________" << endl;
	}

};

//класс Библиотека
class Bibliotek
{
	vector <Book> Books;//массив - база всех книг в библиотеке
	int size=0;//размер библиотеки

public:

	//чтение сведений о книгах из файла
	int CreateBaz( const char* f_name)//создание и заполнение базы
	{
		FILE* f;

		if ((f = fopen(f_name, "r")) == NULL)
		{
			cout << "Cann't open";
			return -1;
		}
		else
		{
			while (!feof(f))
			{
				char a[255];
				char n[255];
				int year;
				int num;
				
				fscanf(f, "%s", a);
				fscanf(f, "%s",n);
				fscanf(f, "%d", &year);
				fscanf(f, "%d", &num);
				Book ekz;
				ekz.init(a, n, year, num);
				Books.push_back(ekz);
				size++;
			}
			fclose(f);
			return 1;
		}
	}

	//запись сведений о книгах в файл
	int FileOutput(const char* f_name)
	{
		FILE* f;

		if ((f = fopen(f_name, "w")) == NULL)
		{
			cout << "Cann't open";
			return -1;
		}
		else
		{
			for (auto it=Books.begin(); it!= Books.end(); it++)
			{
				fputs(it->author, f);
				fputs(" ", f);
				fputs(it->name, f);
				fputs(" ", f);
				fprintf(f, "%d",it->year);
				fputs(" ", f);
				fprintf(f, "%d", it->number);
				fputs("\n", f);
			}
			fclose(f);
			return 1;
		}
	}

	//вывод всех книг одного автора
	void PrintBooksOneA(string autor)
	{

		cout << "______________________________________________" << endl;
		cout << "|     АВТОР     |   НАЗВАНИЕ    | ГОД |КОЛ-ВО|" << endl;
		for (auto it = Books.begin(); it!= Books.end(); it++)//печатаем
		{
			if (it->author == autor)
			{
				it->PrintBook();
			}
		}
	}
	
	//удаление всех книг с одинаковым автором
	void DeleteBookOneA(string autor)
	{
		int s = 0;
		string names;
		for (auto it = Books.begin(); it != Books.end(); it++)
		{
			if (it->author == autor)
			{
				names = it->name;
				s++;
			}

		}
		while (s > 0)
		{
			(*this).DeleteBook(autor, names);
			s--;
		}
	}
	
	//Сортировка книг по году издательства методом прямого выбора
	void sortBooksYear(vector<Book>& Books, int size)
	{

		for (int i = 0; i < size; i++)
		{
			int j_min = i;
			for (int j = i; j < size; j++)
			{
				if (Books[j_min].year > Books[j].year)
				{
					j_min = j;
				}
			}
			Book temp;
			temp = Books[i];
			Books[i] = Books[j_min];
			Books[j_min] = temp;
		}
	}

	//списать книгу(удалить из библиотеки по ключу - ФИО автора и название книги)
	void DeleteBook(string key, string key_name)
	{
		//удаление книги по ключу - фио автора и назанию
		auto  it = Books.begin();
		for (it; it->author != key && it->name != key_name; it++) {}
		Books.erase(it);
		size--;

	}

	//вывести информацию о книге заданной ее названием
	void InfoBook(string key)
	{
		//удаление книги по ключу - фио автора и назанию
		auto  it = Books.begin();
		cout << "______________________________________________" << endl;
		cout << "|     АВТОР     |   НАЗВАНИЕ    | ГОД |КОЛ-ВО|" << endl;
		for (it;  it->name != key; it++) {}
		it->PrintBook();
		size--;

	}

	//изменение полей книги по заданнаому ключу  
	void Set(string key, string key_name)
	{
		//изменение данных о книге по ключу - фио автора и назанию
		int n;
		cout << "Какое поле вы хотите изменить?" << endl;
		cout << "1. Автор" << endl;
		cout << "2. Название" << endl;
		cout << "3. Год" << endl;
		cout << "4. Кол-во" << endl;
		cin >> n;
		auto it = Books.begin();
		for (it; it->author != key && it->name != key_name; it++) {}
		switch (n)
		{
		case 1:
		{
			char key_a[255];
			cin >> key_a;
			strcpy(it->author, key_a);
			break;
		}
		case 2:
		{
			char key_n[255];
			cin >> key_n;
			strcpy(it->name, key_n);
			break;
		}
		case 3:
		{
			int key_y;
			cin >> key_y;
			it->year=key_y;
			break;
		}
		case 4:
		{
			int key_n;
			cin >> key_n;
			it->number= key_n;
			break;
		}
		default:
			break;
		}
		
	
	}

	//заполнение библиотеки книгами с клавиатуры
	void ZapolnBibliotek()
	{
		cout << "Введите кол-во книг которые нужно добавить в библиотеку" << endl;
		int n;
		cin >> n;
		Book B; //книгa
		for (int i = 0; i < n; i++)//добавляем книги
		{
			size++;
			B.initKL();
			Books.push_back(B);
		}
	}

	//печать всех книг упорядоченных по году издания 
	void PrintBooksYear()
	{
	
		sortBooksYear(Books, size);//сортируем 
		cout << "______________________________________________" << endl;
		cout << "|     АВТОР     |   НАЗВАНИЕ    | ГОД |КОЛ-ВО|" << endl;
		for (int i = 0; i < size; i++)//печатаем
		{
			Books[i].PrintBook();
		}
	}

	//меню
	void Menu()
	{
		bool f = 0;
		while (f != 1)
		{
			cout << "1. Добавить книги в библиотеку\n";
			cout << "2. Записать книги в файл\n";
			cout << "3. Считать книги из файла\n";
			cout << "4. Списать несколько книг\n";
			cout << "5. Выдать список книг, упорядоченный по годам издания\n";
			cout << "6. Изменить информацию о книге по ее ключу\n";
			cout << "7. Списать все книги заданного автора\n";
			cout << "8. Вывести все книги заданного автора\n";
			cout << "9. Вывести информацию о книге по ее названию\n"; 
			cout << "10. Выход\n";
			int c;
			cin >> c;
			switch (c)
			{
			case 1:
			{
				(*this).ZapolnBibliotek();
				cout << endl;
				break;
			}
			case 2://запись в файл
			{
				char filename[255];
				int r;
				cout << "Введите имя файла: " << endl;
				cin >> filename;
				r = FileOutput(filename);
				if (r == 1) cout << "Успешно записано" << endl;
				else cout << "Ошибка" << endl;

				break;
			}
			case 3://считывание из файла
			{
				char filename[255];
				int r;
				cout << "Введите имя файла: " << endl;
				scanf("%s",filename);
				r = CreateBaz(filename);
				if (r == 1) cout << "Успешно считано" << endl;
				else cout << "Ошибка" << endl;
				break;
			}
			case 4:
			{
				string autor;
				string namebook;
				int k;
				cout << "Сколько книг нужно удалить?" << endl;
				cin >> k;
			while( k>0 )
				{
					cout << "Введите фамилию и иницыалы автора:" << endl;
					cin >> autor;
					cout << "Введите название книги:" << endl;
					cin >> namebook;
					(*this).DeleteBook(autor, namebook);
					cout << "true" << endl;
					k--;
				}
				cout << endl;
				break;
			}
			case 5:
			{
				if (size != 0)
				{
					cout << endl << "Список книг упорядоченный по году издания:" << endl;
					(*this).PrintBooksYear();
				}
				else cout << "Библиотека пуста!" << endl;
				cout << endl;
				break;
			}
			case 6:
			{
				string a_key, n_key;
				cout << "Введите фамилию и иницыалы автора" << endl;
				cin >> a_key;
				cout << "Введите название книги" << endl;
				cin >> n_key;
				(*this).Set(a_key, n_key);
				cout << endl;
				break;
			}
			case 7:
			{	string autor;
				cout << "Введите фамилию и иницыалы автора:" << endl;
				cin >> autor;
				DeleteBookOneA(autor);
				cout << endl;
			break;
			}
			case 8:
			{
				string autor;
				cout << "Введите фамилию и иницыалы автора:" << endl;
				cin >> autor;
				if (size != 0)
				{
					cout << endl << "Книги " <<autor<<":"<< endl;
					(*this).PrintBooksOneA(autor);
				}
				else cout << endl << "Книг " << autor << " нет в библиотеке !" << endl;
				cout << endl;
				break;
			}
			case 9:
			{
				string name_book;
				cout << "Введите название книги:" << endl;
				cin >> name_book;
				InfoBook(name_book);
				cout << endl;
				break;
			}
			case 10:
			{
				f = 1;
				break;
			}
			default:cout << "Не верный ввод! Попробуйте еще раз.\n";
			}
		}
		cin.sync();
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Bibliotek Bibl;
	Bibl.Menu();
	
}