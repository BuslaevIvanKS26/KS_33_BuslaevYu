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
int** createMatrix(int size);
void fillMatrixRandom(int** p_matrix, int size);
void fillMatrixManually(int** p_matrix, int size);
void printMatrix(int** p_matrix, int size);
void invertMatrix(int** p_matrix, int size);
void binarizeMatrix(int** p_matrix, int size, int threshold);
int findBrightestRow(int** p_matrix, int size);
void printMatrixViaVoid(void* p_void_matrix, int size);
void deleteMatrix(int** p_matrix, int size);
int readOperationChoice();
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
 *
 * @param size размер матрицы.
 * @return указатель на массив указателей (int**).
 */
int** createMatrix(int size) {
    int** p_matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        p_matrix[i] = new int[size];
    }
    return p_matrix;
}

/**
 * Заполняет матрицу случайными значениями яркости.
 *
 * @param p_matrix указатель на матрицу.
 * @param size размер матрицы.
 */
void fillMatrixRandom(int** p_matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            p_matrix[i][j] = generateBrightness();
        }
    }
}

/**
 * Заполняет матрицу значениями, введёнными пользователем вручную.
 * Проверяет, что каждое значение в диапазоне от 0 до 255.
 * После ввода очищает буфер, чтобы лишние числа не попали в следующие команды.
 *
 * @param p_matrix указатель на матрицу.
 * @param size размер матрицы.
 */
void fillMatrixManually(int** p_matrix, int size) {
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
                    p_matrix[i][j] = value;
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
void printMatrix(int** p_matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << p_matrix[i][j] << "\t";
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
void invertMatrix(int** p_matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            p_matrix[i][j] = MAX_BRIGHTNESS - p_matrix[i][j];
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
void binarizeMatrix(int** p_matrix, int size, int threshold) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (p_matrix[i][j] > threshold) {
                p_matrix[i][j] = 1;
            } else {
                p_matrix[i][j] = 0;
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
int findBrightestRow(int** p_matrix, int size) {
    int brightest_index = 0;
    long long max_sum = 0;

    for (int i = 0; i < size; i++) {
        long long current_sum = 0;
        for (int j = 0; j < size; j++) {
            current_sum += p_matrix[i][j];
        }
        if (i == 0 || current_sum > max_sum) {
            max_sum = current_sum;
            brightest_index = i;
        }
    }

    return brightest_index;
}

/**
 * Выводит матрицу, переданную через void*, приведя её к int** внутри.
 * Демонстрирует работу с void-указателем.
 *
 * @param p_void_matrix указатель на матрицу как void*.
 * @param size размер матрицы.
 */
void printMatrixViaVoid(void* p_void_matrix, int size) {
    int** p_matrix = (int**)p_void_matrix;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << p_matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

/**
 * Освобождает память, выделенную под двумерный массив.
 *
 * @param p_matrix указатель на матрицу.
 * @param size размер матрицы.
 */
void deleteMatrix(int** p_matrix, int size) {
    for (int i = 0; i < size; i++) {
        delete[] p_matrix[i];
    }
    delete[] p_matrix;
}

/**
 * Выводит меню действий и считывает выбор пользователя.
 *
 * @return номер выбранного действия (1..4).
 */
int readOperationChoice() {
    cout << endl;
    cout << "Выберите действие:" << endl;
    cout << "1 - Инвертировать изображение (255 - x)" << endl;
    cout << "2 - Бинаризовать изображение по порогу" << endl;
    cout << "3 - Найти самую яркую строку" << endl;
    cout << "4 - Вывести матрицу через void*" << endl;
    cout << "Ваш выбор: ";

    int choice = 0;
    cin >> choice;
    cin.ignore(10000, '\n');
    return choice;
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

int main() {
    srand((unsigned int)time(0));

    SetConsoleOutputCP(65001);

    int size = readMatrixSize();

    int** matrix = createMatrix(size);

    cout << "Заполнить матрицу случайно (1) или ввести вручную (2)? ";
    int fill_mode = 0;
    cin >> fill_mode;
    cin.ignore(10000, '\n');

    if (fill_mode == 1) {
        fillMatrixRandom(matrix, size);
    } else {
        fillMatrixManually(matrix, size);
    }

    cout << endl << "Исходная матрица:" << endl;
    printMatrix(matrix, size);

    int choice = readOperationChoice();

    if (choice == 1) {
        invertMatrix(matrix, size);
        cout << endl << "Инвертированная матрица:" << endl;
        printMatrix(matrix, size);
    } else if (choice == 2) {
        int threshold = readThreshold();
        binarizeMatrix(matrix, size, threshold);
        cout << endl << "Бинаризованная матрица:" << endl;
        printMatrix(matrix, size);
    } else if (choice == 3) {
        int brightest_index = findBrightestRow(matrix, size);
        cout << endl << "Индекс самой яркой строки: " << brightest_index << endl;
        cout << "Значения строки: ";
        for (int j = 0; j < size; j++) {
            cout << matrix[brightest_index][j] << " ";
        }
        cout << endl;
    } else if (choice == 4) {
        cout << endl << "Матрица через void*:" << endl;
        printMatrixViaVoid(matrix, size);
    } else {
        cout << endl << "Неизвестная операция. Выход." << endl;
    }

    deleteMatrix(matrix, size);

    return 0;
}