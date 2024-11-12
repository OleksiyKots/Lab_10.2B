#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <Windows.h>
using namespace std;

enum Spetsialnist { KOMPYUTERNI_NAUKY, INFORMATYKA, MATEMATYKA_TA_EKONOMIKA, FIZYKA_TA_INFORMATYKA, TRUDOVE_NAVCHANNYA };
enum Riven { NIZHCHИЙ, SEREDNІЙ, VISHCHИЙ };  // Додано рівень студента

struct Student {
    string prizv;
    int kurs;
    Spetsialnist spetsialnist;
    Riven riven;  // Додано поле для рівня студента
    int ozenka_fizyka;
    int ozenka_matematyka;
    int ozenka_informatyka;
};

void Create(Student* s, const int N);
void Print(const Student* s, const int N);
void SortStudents(Student* s, const int N);
int BinarySearch(Student* s, int N, const string& prizv);

int main() {
    SetConsoleCP(1251);  // Встановлення сторінки для вводу
    SetConsoleOutputCP(1251);  // Встановлення сторінки для виводу

    int N;
    cout << "Введіть кількість студентів: ";
    cin >> N;

    Student* students = new Student[N];

    int menuItem;
    do {
        cout << "\nМеню:\n";
        cout << " [1] - введення даних\n";
        cout << " [2] - виведення даних\n";
        cout << " [3] - сортування студентів\n";
        cout << " [4] - пошук студента за прізвищем (бінарний пошук)\n";
        cout << " [0] - вихід\n";
        cout << "Введіть ваш вибір: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            Create(students, N);
            break;
        case 2:
            Print(students, N);
            break;
        case 3:
            SortStudents(students, N);
            break;
        case 4: {
            string prizv;
            cout << "Введіть прізвище студента для пошуку: ";
            cin.ignore();
            getline(cin, prizv);
            int index = BinarySearch(students, N, prizv);
            if (index != -1) {
                cout << "Студент знайдений:\n";
                Print(&students[index], 1);
            }
            else {
                cout << "Студента не знайдено.\n";
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "Помилка! Слід вибрати коректний номер.\n";
        }
    } while (menuItem != 0);

    delete[] students;  // Очистка пам'яті
    return 0;
}

void Create(Student* s, const int N) {
    for (int i = 0; i < N; i++) {
        cout << "Студент №" << i + 1 << ":\n";
        cin.ignore();
        cout << "Прізвище: ";
        getline(cin, s[i].prizv);
        cout << "Курс: ";
        cin >> s[i].kurs;
        cout << "Спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
        int sp;
        cin >> sp;
        s[i].spetsialnist = static_cast<Spetsialnist>(sp);
        cout << "Рівень студента (0 - Нижчий, 1 - Середній, 2 - Вищий): ";
        int r;
        cin >> r;
        s[i].riven = static_cast<Riven>(r);  // Введення рівня студента
        cout << "Оцінка з фізики: ";
        cin >> s[i].ozenka_fizyka;
        cout << "Оцінка з математики: ";
        cin >> s[i].ozenka_matematyka;
        cout << "Оцінка з інформатики: ";
        cin >> s[i].ozenka_informatyka;
        cout << endl;
    }
}



void Print(const Student* s, const int N) {
    cout << "=================================================================================================\n";
    cout << "| № | Прізвище    | Курс | Спеціальність          | Рівень  | Фізика | Математика | Інформатика |\n";
    cout << "-------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < N; i++) {
        cout << left << "| " << setw(1) << i + 1 << " ";
        cout << "| " << setw(12) << left << s[i].prizv;
        cout << "| " << setw(4) << s[i].kurs << " ";
        string spets;
        switch (s[i].spetsialnist) {
        case KOMPYUTERNI_NAUKY: spets = "Комп'ютерні науки"; break;
        case INFORMATYKA: spets = "Інформатика"; break;
        case MATEMATYKA_TA_EKONOMIKA: spets = "Математика та економіка"; break;
        case FIZYKA_TA_INFORMATYKA: spets = "Фізика та інформатика"; break;
        case TRUDOVE_NAVCHANNYA: spets = "Трудове навчання"; break;
        }
        cout << "| " << setw(23) << left << spets;

        string riven_str;
        switch (s[i].riven) {  // Виведення рівня студента
        case NIZHCHИЙ: riven_str = "Нижчий"; break;
        case SEREDNІЙ: riven_str = "Середній"; break;
        case VISHCHИЙ: riven_str = "Вищий"; break;
        }
        cout << "| " << setw(8) << left << riven_str;

        cout << "| " << setw(7) << s[i].ozenka_fizyka;
        cout << "| " << setw(11) << s[i].ozenka_matematyka;
        cout << "| " << setw(11) << s[i].ozenka_informatyka;
        cout << " |\n";
    }
    cout << "=================================================================================================\n";
}

void SortStudents(Student* s, const int N) {
    sort(s, s + N, [](const Student& a, const Student& b) {
        return a.prizv < b.prizv;
        });
    cout << "Список студентів відсортовано за прізвищем.\n";
}

int BinarySearch(Student* s, int N, const string& prizv) {
    int left = 0;
    int right = N - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (s[mid].prizv == prizv) {
            return mid;
        }
        if (s[mid].prizv < prizv) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;  // Студент не знайдений
}
