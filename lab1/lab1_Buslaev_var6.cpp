#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MIN_GRADE = 1;
const int MAX_GRADE = 10;
const int N_SMALL = 10;
const int N_MEDIUM = 50;
const int N_LARGE = 100;
const int MAX_ARRAY_SIZE = 100;

/**
 * Генерирует случайную оценку в диапазоне от MIN_GRADE до MAX_GRADE.
 *
 * @return случайное целое число от 1 до 10 включительно.
 */
int generateGrade() {
    int grade = MIN_GRADE + rand() % (MAX_GRADE - MIN_GRADE + 1);
    return grade;
}

/**
 * Заполняет массив оценок случайными значениями.
 *
 * @param p_array указатель на массив оценок.
 * @param size количество элементов в массиве.
 */
void fillGrades(int* p_array, int size) {
    for (int i = 0; i < size; i++) {
        p_array[i] = generateGrade();
    }
}

/**
 * Выводит массив оценок в одну строку через пробел.
 *
 * @param p_array указатель на массив оценок.
 * @param size количество элементов в массиве.
 */
void printGrades(const int* p_array, int size) {
    for (int i = 0; i < size; i++) {
        cout << p_array[i] << " ";
    }
    cout << endl;
}

/**
 * Сортирует массив оценок по возрастанию методом выбора.
 *
 * @param p_array указатель на массив оценок.
 * @param size количество элементов в массиве.
 */
void sortGradesSelection(int* p_array, int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < size; j++) {
            if (p_array[j] < p_array[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            int temp = p_array[i];
            p_array[i] = p_array[min_index];
            p_array[min_index] = temp;
        }
    }
}

/**
 * Считает средний балл по массиву оценок.
 *
 * @param p_array указатель на массив оценок.
 * @param size количество элементов в массиве.
 * @return средний балл как число с плавающей точкой.
 */
double calculateAverage(const int* p_array, int size) {
    long long sum = 0;
    for (int i = 0; i < size; i++) {
        sum += p_array[i];
    }
    double average = (double)sum / size;
    return average;
}

/**
 * Выводит отсортированный массив в виде аккуратной таблицы.
 *
 * @param p_array указатель на массив оценок.
 * @param size количество элементов в массиве.
 */
void printGradesTable(const int* p_array, int size) {
    cout << "----------------" << endl;
    cout << "|  #  | Grade  |" << endl;
    cout << "----------------" << endl;

    for (int i = 0; i < size; i++) {
        cout << "|";
        if (i + 1 < 10) {
            cout << "  " << i + 1 << "  ";
        } else if (i + 1 < 100) {
            cout << "  " << i + 1 << " ";
        } else {
            cout << " " << i + 1 << " ";
        }
        cout << "|";

        if (p_array[i] < 10) {
            cout << "   " << p_array[i] << "    ";
        } else {
            cout << "   " << p_array[i] << "   ";
        }
        cout << "|" << endl;
    }

    cout << "----------------" << endl;
}

/**
 * Выполняет полный сценарий обработки массива оценок:
 * генерацию, сортировку, подсчёт среднего и вывод таблицы.
 *
 * @param size количество оценок.
 */
void processGrades(int size) {
    if (size > MAX_ARRAY_SIZE) {
        cout << "Error: size " << size
             << " exceeds MAX_ARRAY_SIZE = " << MAX_ARRAY_SIZE << endl;
        return;
    }

    int grades[MAX_ARRAY_SIZE];

    fillGrades(grades, size);

    cout << "Initial grades array:" << endl;
    printGrades(grades, size);
    cout << endl;

    sortGradesSelection(grades, size);

    double average = calculateAverage(grades, size);

    cout << "Sorted grades:" << endl;
    printGradesTable(grades, size);

    cout << "Average grade: " << average << endl;
    
}

int main() {
    srand((unsigned int)time(0));

    cout << "Test 1: N = " << N_SMALL << endl;
    cout << "-------------------------" << endl;
    processGrades(N_SMALL);

    cout << "Test 2: N = " << N_MEDIUM << endl;
    cout << "-------------------------" << endl;
    processGrades(N_MEDIUM);

    cout << "Test 3: N = " << N_LARGE << endl;
    cout << "-------------------------" << endl;
    processGrades(N_LARGE);

    return 0;
}