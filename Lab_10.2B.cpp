#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <Windows.h>
using namespace std;

enum Spetsialnist { KOMPYUTERNI_NAUKY, INFORMATYKA, MATEMATYKA_TA_EKONOMIKA, FIZYKA_TA_INFORMATYKA, TRUDOVE_NAVCHANNYA };
enum Riven { NIZHCH��, SEREDN��, VISHCH�� };  // ������ ����� ��������

struct Student {
    string prizv;
    int kurs;
    Spetsialnist spetsialnist;
    Riven riven;  // ������ ���� ��� ���� ��������
    int ozenka_fizyka;
    int ozenka_matematyka;
    int ozenka_informatyka;
};

void Create(Student* s, const int N);
void Print(const Student* s, const int N);
void SortStudents(Student* s, const int N);
int BinarySearch(Student* s, int N, const string& prizv);

int main() {
    SetConsoleCP(1251);  // ������������ ������� ��� �����
    SetConsoleOutputCP(1251);  // ������������ ������� ��� ������

    int N;
    cout << "������ ������� ��������: ";
    cin >> N;

    Student* students = new Student[N];

    int menuItem;
    do {
        cout << "\n����:\n";
        cout << " [1] - �������� �����\n";
        cout << " [2] - ��������� �����\n";
        cout << " [3] - ���������� ��������\n";
        cout << " [4] - ����� �������� �� �������� (������� �����)\n";
        cout << " [0] - �����\n";
        cout << "������ ��� ����: ";
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
            cout << "������ ������� �������� ��� ������: ";
            cin.ignore();
            getline(cin, prizv);
            int index = BinarySearch(students, N, prizv);
            if (index != -1) {
                cout << "������� ���������:\n";
                Print(&students[index], 1);
            }
            else {
                cout << "�������� �� ��������.\n";
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "�������! ��� ������� ��������� �����.\n";
        }
    } while (menuItem != 0);

    delete[] students;  // ������� ���'��
    return 0;
}

void Create(Student* s, const int N) {
    for (int i = 0; i < N; i++) {
        cout << "������� �" << i + 1 << ":\n";
        cin.ignore();
        cout << "�������: ";
        getline(cin, s[i].prizv);
        cout << "����: ";
        cin >> s[i].kurs;
        cout << "������������ (0 - ����'����� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): ";
        int sp;
        cin >> sp;
        s[i].spetsialnist = static_cast<Spetsialnist>(sp);
        cout << "г���� �������� (0 - ������, 1 - �������, 2 - �����): ";
        int r;
        cin >> r;
        s[i].riven = static_cast<Riven>(r);  // �������� ���� ��������
        cout << "������ � ������: ";
        cin >> s[i].ozenka_fizyka;
        cout << "������ � ����������: ";
        cin >> s[i].ozenka_matematyka;
        cout << "������ � �����������: ";
        cin >> s[i].ozenka_informatyka;
        cout << endl;
    }
}



void Print(const Student* s, const int N) {
    cout << "=================================================================================================\n";
    cout << "| � | �������    | ���� | ������������          | г����  | Գ���� | ���������� | ����������� |\n";
    cout << "-------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < N; i++) {
        cout << left << "| " << setw(1) << i + 1 << " ";
        cout << "| " << setw(12) << left << s[i].prizv;
        cout << "| " << setw(4) << s[i].kurs << " ";
        string spets;
        switch (s[i].spetsialnist) {
        case KOMPYUTERNI_NAUKY: spets = "����'����� �����"; break;
        case INFORMATYKA: spets = "�����������"; break;
        case MATEMATYKA_TA_EKONOMIKA: spets = "���������� �� ��������"; break;
        case FIZYKA_TA_INFORMATYKA: spets = "Գ���� �� �����������"; break;
        case TRUDOVE_NAVCHANNYA: spets = "������� ��������"; break;
        }
        cout << "| " << setw(23) << left << spets;

        string riven_str;
        switch (s[i].riven) {  // ��������� ���� ��������
        case NIZHCH��: riven_str = "������"; break;
        case SEREDN��: riven_str = "�������"; break;
        case VISHCH��: riven_str = "�����"; break;
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
    cout << "������ �������� ����������� �� ��������.\n";
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
    return -1;  // ������� �� ���������
}
