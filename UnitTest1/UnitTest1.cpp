#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_10.2B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StudentTests
{
    TEST_CLASS(StudentTests)
    {
    public:

        TEST_METHOD(TestCreateAndPrint)
        {
            const int N = 1;
            Student students[N];

            students[0].prizv = "Ivanenko";
            students[0].kurs = 2;
            students[0].spetsialnist = KOMPYUTERNI_NAUKY;
            students[0].riven = SEREDN²É;
            students[0].ozenka_fizyka = 80;
            students[0].ozenka_matematyka = 90;
            students[0].ozenka_informatyka = 85;

            Assert::AreEqual(std::string("Ivanenko"), students[0].prizv);
            Assert::AreEqual(2, students[0].kurs);
            Assert::AreEqual(static_cast<int>(KOMPYUTERNI_NAUKY), static_cast<int>(students[0].spetsialnist));
            Assert::AreEqual(static_cast<int>(SEREDN²É), static_cast<int>(students[0].riven));
            Assert::AreEqual(80, students[0].ozenka_fizyka);
            Assert::AreEqual(90, students[0].ozenka_matematyka);
            Assert::AreEqual(85, students[0].ozenka_informatyka);
        }

        TEST_METHOD(TestSortStudents)
        {
            const int N = 2;
            Student students[N];

            students[0].prizv = "Petrenko";
            students[1].prizv = "Ivanenko";

            SortStudents(students, N);

            Assert::AreEqual(std::string("Ivanenko"), students[0].prizv);
            Assert::AreEqual(std::string("Petrenko"), students[1].prizv);
        }

        TEST_METHOD(TestBinarySearch)
        {
            const int N = 3;
            Student students[N];

            students[0].prizv = "Ivanenko";
            students[1].prizv = "Petrenko";
            students[2].prizv = "Shevchenko";

            SortStudents(students, N);

            int index = BinarySearch(students, N, "Petrenko");
            Assert::AreEqual(1, index);

            index = BinarySearch(students, N, "Shevchenko");
            Assert::AreEqual(2, index);

            index = BinarySearch(students, N, "Ivanenko");
            Assert::AreEqual(0, index);

            index = BinarySearch(students, N, "Unknown");
            Assert::AreEqual(-1, index);
        }
    };
}
