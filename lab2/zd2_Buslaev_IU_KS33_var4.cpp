
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

const int MIN_BRIGHTNESS = 0;
const int MAX_BRIGHTNESS = 255;
const int DEFAULT_THRESHOLD = 128;
const int MAX_MATRIX_SIZE = 100;

int readMatrixSize();
int generateBrightness();
int* createMatrix(int size);
void fillMatrixRandom(int* p_matrix, int size);
void fillMatrixManually(int* p_matrix, int size);
void printMatrix(const int* p_matrix, int size);
void invertMatrix(int* p_matrix, int size);
void binarizeMatrix(int* p_matrix, int size, int threshold);
int findBrightestRow(const int* p_matrix, int size);
void printMatrixViaVoid(void* p_void_matrix, int size);
void deleteMatrix(int* p_matrix);
int readOperationChoice();
int readFillMode();
int readThreshold();

/**
 * Считывает размер матрицы N от пользователя с проверкой корректности.
 *
 * @return корректный размер матрицы (от 1 до MAX_MATRIX_SIZE).
 */
int readMatrixSize() {
    int size = 0;

    while (true) {
        cout << "Введите размер матрицы N (1.." << MAX_MATRIX_SIZE << "): ";
        cin >> size;

        if (cin.fail() || size < 1 || size > MAX_MATRIX_SIZE) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Некорректный ввод. Попробуйте ещё раз." << endl;
        } else {
            cin.ignore(10000, '\n');
            break;
        }
    }

    return size;
}

/**
 * Генерирует случайную яркость от MIN_BRIGHTNESS до MAX_BRIGHTNESS.
 *
 * @return случайное целое число от 0 до 255.
 */
int generateBrightness() {
    int value = MIN_BRIGHTNESS + rand() % (MAX_BRIGHTNESS - MIN_BRIGHTNESS + 1);

    return value;
}

/**
 * Выделяет память под двумерный массив N x N в куче.
 * Элементы хранятся в одном непрерывном массиве.
 *
 * @param size размер матрицы.
 * @return указатель на массив целых чисел.
 */
int* createMatrix(int size) {
    int* p_matrix = new int[size * size];

    return p_matrix;
}

/**
 * Заполняет матрицу случайными значениями яркости.
 *
 * @param p_matrix указатель на матрицу.
 * @param size размер матрицы.
 */
void fillMatrixRandom(int* p_matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            p_matrix[i * size + j] = generateBrightness();
        }
    }
}

/**
 * Заполняет матрицу значениями, введёнными пользователем вручную.
 * Проверяет, что каждое значение находится в диапазоне от 0 до 255.
 *
 * @param p_matrix указатель на матрицу.
 * @param size размер матрицы.
 */
void fillMatrixManually(int* p_matrix, int size) {
    cout << "Введите " << size * size << " чисел (от 0 до 255):" << endl;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int value = 0;

            while (true) {
                cin >> value;

                if (cin.fail() || value < MIN_BRIGHTNESS || value > MAX_BRIGHTNESS) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Ошибка: число должно быть от 0 до 255. Повторите: ";
                } else {
                    p_matrix[i * size + j] = value;
                    break;
                }
            }
        }
    }

    cin.ignore(10000, '\n');
}

/**
 * Выводит матрицу на экран.
 *
 * @param p_matrix указатель на матрицу.
 * @param size размер матрицы.
 */
void printMatrix(const int* p_matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << p_matrix[i * size + j] << "\t";
        }

        cout << endl;
    }
}

/**
 * Выполняет инверсию изображения: каждый пиксель x заменяется на 255 - x.
 *
 * @param p_matrix указатель на матрицу.
 * @param size размер матрицы.
 */
void invertMatrix(int* p_matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            p_matrix[i * size + j] = MAX_BRIGHTNESS - p_matrix[i * size + j];
        }
    }
}

/**
 * Преобразует изображение в бинарное по заданному порогу.
 * Пиксель > threshold становится 1, иначе 0.
 *
 * @param p_matrix указатель на матрицу.
 * @param size размер матрицы.
 * @param threshold порог бинаризации.
 */
void binarizeMatrix(int* p_matrix, int size, int threshold) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (p_matrix[i * size + j] > threshold) {
                p_matrix[i * size + j] = 1;
            } else {
                p_matrix[i * size + j] = 0;
            }
        }
    }
}

/**
 * Находит индекс строки с максимальной суммой значений.
 *
 * @param p_matrix указатель на матрицу.
 * @param size размер матрицы.
 * @return индекс самой яркой строки (от 0 до size - 1).
 */
int findBrightestRow(const int* p_matrix, int size) {
    int brightest_index = 0;
    int max_sum = 0;

    for (int i = 0; i < size; i++) {
        int current_sum = 0;

        for (int j = 0; j < size; j++) {
            current_sum += p_matrix[i * size + j];
        }

        if (i == 0 || current_sum > max_sum) {
            max_sum = current_sum;
            brightest_index = i;
        }
    }

    return brightest_index;
}

/**
 * Выводит матрицу, переданную через void*,
 * приводя указатель к int* внутри функции.
 *
 * @param p_void_matrix указатель на матрицу как void*.
 * @param size размер матрицы.
 */
void printMatrixViaVoid(void* p_void_matrix, int size) {
    int* p_matrix = (int*)p_void_matrix;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << p_matrix[i * size + j] << "\t";
        }

        cout << endl;
    }
}

/**
 * Освобождает память, выделенную под матрицу.
 *
 * @param p_matrix указатель на матрицу.
 */
void deleteMatrix(int* p_matrix) {
    delete[] p_matrix;
}

/**
 * Выводит меню действий и считывает выбор пользователя с проверкой.
 *
 * @return номер выбранного действия (1..4).
 */
int readOperationChoice() {
    int choice = 0;

    while (true) {
        cout << endl;
        cout << "Выберите действие:" << endl;
        cout << "1 - Инвертировать изображение (255 - x)" << endl;
        cout << "2 - Бинаризовать изображение по порогу" << endl;
        cout << "3 - Найти самую яркую строку" << endl;
        cout << "4 - Вывести матрицу через void*" << endl;
        cout << "Ваш выбор: ";

        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 4) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Некорректный выбор. Введите число от 1 до 4." << endl;
        } else {
            cin.ignore(10000, '\n');
            break;
        }
    }

    return choice;
}

/**
 * Считывает способ заполнения матрицы с проверкой.
 *
 * @return 1 — случайное заполнение, 2 — ручной ввод.
 */
int readFillMode() {
    int fill_mode = 0;

    while (true) {
        cout << "Заполнить матрицу случайно (1) или ввести вручную (2)? ";
        cin >> fill_mode;

        if (cin.fail() || (fill_mode != 1 && fill_mode != 2)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Некорректный выбор. Введите 1 или 2." << endl;
        } else {
            cin.ignore(10000, '\n');
            break;
        }
    }

    return fill_mode;
}

/**
 * Считывает порог бинаризации с проверкой диапазона.
 *
 * @return корректный порог (от 0 до 255).
 */
int readThreshold() {
    int threshold = 0;

    while (true) {
        cout << "Введите порог (0..255): ";
        cin >> threshold;

        if (cin.fail() || threshold < MIN_BRIGHTNESS || threshold > MAX_BRIGHTNESS) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Некорректный порог. Попробуйте ещё раз." << endl;
        } else {
            cin.ignore(10000, '\n');
            break;
        }
    }

    return threshold;
}

/**
 * Выполняет основную последовательность работы программы.
 *
 * @return 0 при успешном завершении.
 */
int main() {
    srand((unsigned int)time(0));

    SetConsoleOutputCP(65001);

    int size = readMatrixSize();

    int* p_matrix = createMatrix(size);

    int fill_mode = readFillMode();

    if (fill_mode == 1) {
        fillMatrixRandom(p_matrix, size);
    } else {
        fillMatrixManually(p_matrix, size);
    }

    cout << endl << "Исходная матрица:" << endl;
    printMatrix(p_matrix, size);

    int choice = readOperationChoice();

    if (choice == 1) {
        invertMatrix(p_matrix, size);

        cout << endl << "Инвертированная матрица:" << endl;
        printMatrix(p_matrix, size);
    } else if (choice == 2) {
        int threshold = readThreshold();

        binarizeMatrix(p_matrix, size, threshold);

        cout << endl << "Бинаризованная матрица:" << endl;
        printMatrix(p_matrix, size);
    } else if (choice == 3) {
        int brightest_index = findBrightestRow(p_matrix, size);

        cout << endl << "Индекс самой яркой строки: "
             << brightest_index << endl;

        cout << "Значения строки: ";

        for (int j = 0; j < size; j++) {
            cout << p_matrix[brightest_index * size + j] << " ";
        }

        cout << endl;
    } else if (choice == 4) {
        cout << endl << "Матрица через void*:" << endl;
        printMatrixViaVoid((void*)p_matrix, size);
    }

    deleteMatrix(p_matrix);

    return 0;
}
