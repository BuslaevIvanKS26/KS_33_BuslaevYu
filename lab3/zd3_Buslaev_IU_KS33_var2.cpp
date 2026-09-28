
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <windows.h>

using namespace std;

const int MAX_COURSES = 100;
const int MIN_DURATION = 1;
const int MAX_DURATION = 120;
const double MIN_RATING = 0.0;
const double MAX_RATING = 5.0;
const double MIN_PRICE = 100.0;
const double MAX_PRICE = 10000.0;

struct Course {
    string title;
    string instructor;
    int duration;
    double rating;
    double price;
    bool is_advanced;
};

int readCourseCount();
string generateRandomTitle();
string generateRandomInstructor();
int generateRandomDuration();
double generateRandomRating();
double generateRandomPrice();
bool generateRandomIsAdvanced();
Course generateRandomCourse();
Course* createCourseArray(int size);
void fillCourseArrayRandom(Course* p_courses, int size);
void printCourse(const Course& course);
void printCourseArray(const Course* p_courses, int size);
void recommendCourses(const Course* p_courses, int size, double min_rating, double max_price);
void compareByDuration(const Course* p_courses, int size);
void groupByAdvanced(const Course* p_courses, int size);
void sortCourses(Course* p_courses, int size);
void sortCoursesByEfficiency(Course* p_courses, int size);
void buyCourses(const Course* p_courses, int size, double budget, int max_total_duration);
void deleteCourseArray(Course* p_courses);

/**
 * Считывает количество курсов N от пользователя с проверкой.
 *
 * @return корректное количество курсов (от 1 до MAX_COURSES).
 */
int readCourseCount() {
    int size = 0;

    while (true) {
        cout << "Введите количество курсов N (1.." << MAX_COURSES << "): ";
        cin >> size;

        if (cin.fail() || size < 1 || size > MAX_COURSES) {
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
 * Генерирует случайное название курса.
 *
 * @return строка — название курса.
 */
string generateRandomTitle() {
    const string TITLES[] = {
        "C++ Basics", "Python Pro", "Web Dev", "Data Science",
        "ML Intro", "Java Core", "SQL Master", "Linux Admin",
        "Git Basics", "Algorithms", "OOP Deep", "Rust Start"
    };

    const int index = rand() % 12;

    return TITLES[index];
}

/**
 * Генерирует случайное имя преподавателя.
 *
 * @return строка — имя преподавателя.
 */
string generateRandomInstructor() {
    const string INSTRUCTORS[] = {
        "Ivanov", "Petrov", "Sidorov", "Kuznetsov",
        "Smirnov", "Popov", "Lebedev", "Kozlov"
    };

    const int index = rand() % 8;

    return INSTRUCTORS[index];
}

/**
 * Генерирует случайную длительность курса в часах.
 *
 * @return целое число от MIN_DURATION до MAX_DURATION.
 */
int generateRandomDuration() {
    const int duration = MIN_DURATION + rand() % (MAX_DURATION - MIN_DURATION + 1);

    return duration;
}

/**
 * Генерирует случайный рейтинг курса.
 *
 * @return число с плавающей точкой от 0.0 до 5.0.
 */
double generateRandomRating() {
    const double rating = MIN_RATING + (double)rand() / RAND_MAX * (MAX_RATING - MIN_RATING);

    return rating;
}

/**
 * Генерирует случайную стоимость курса.
 *
 * @return число с плавающей точкой от MIN_PRICE до MAX_PRICE.
 */
double generateRandomPrice() {
    const double price = MIN_PRICE + (double)rand() / RAND_MAX * (MAX_PRICE - MIN_PRICE);

    return price;
}

/**
 * Генерирует случайный флаг «продвинутый курс».
 *
 * @return true или false.
 */
bool generateRandomIsAdvanced() {
    const bool is_advanced = (rand() % 2 == 1);

    return is_advanced;
}

/**
 * Генерирует один случайный курс со всеми полями.
 *
 * @return структура Course со случайными значениями.
 */
Course generateRandomCourse() {
    Course course;

    course.title = generateRandomTitle();
    course.instructor = generateRandomInstructor();
    course.duration = generateRandomDuration();
    course.rating = generateRandomRating();
    course.price = generateRandomPrice();
    course.is_advanced = generateRandomIsAdvanced();

    return course;
}

/**
 * Выделяет память под массив курсов в куче.
 *
 * @param size количество курсов.
 * @return указатель на массив курсов.
 */
Course* createCourseArray(int size) {
    Course* p_courses = new Course[size];

    return p_courses;
}

/**
 * Заполняет массив курсов случайными данными.
 *
 * @param p_courses указатель на массив курсов.
 * @param size количество курсов.
 */
void fillCourseArrayRandom(Course* p_courses, int size) {
    for (int i = 0; i < size; i++) {
        p_courses[i] = generateRandomCourse();
    }
}

/**
 * Выводит один курс на экран.
 *
 * @param course ссылка на курс.
 */
void printCourse(const Course& course) {
    cout << "| " << course.title;
    cout << " | " << course.instructor;
    cout << " | " << course.duration << " ч";
    cout << " | " << course.rating;
    cout << " | " << course.price;
    cout << " | " << (course.is_advanced ? "advanced" : "basic");
    cout << " |" << endl;
}

/**
 * Выводит весь массив курсов на экран.
 *
 * @param p_courses указатель на массив курсов.
 * @param size количество курсов.
 */
void printCourseArray(const Course* p_courses, int size) {
    for (int i = 0; i < size; i++) {
        printCourse(p_courses[i]);
    }
}

/**
 * Находит и выводит курсы с рейтингом выше заданного и ценой ниже заданной.
 *
 * @param p_courses указатель на массив курсов.
 * @param size количество курсов.
 * @param min_rating минимальный рейтинг.
 * @param max_price максимальная цена.
 */
void recommendCourses(const Course* p_courses, int size, double min_rating, double max_price) {
    cout << endl << "Рекомендации (рейтинг > " << min_rating
         << ", цена < " << max_price << "):" << endl;

    bool found = false;

    for (int i = 0; i < size; i++) {
        if (p_courses[i].rating > min_rating && p_courses[i].price < max_price) {
            printCourse(p_courses[i]);
            found = true;
        }
    }

    if (!found) {
        cout << "Подходящих курсов не найдено." << endl;
    }
}

/**
 * Находит и выводит самый короткий и самый длинный курсы.
 *
 * @param p_courses указатель на массив курсов.
 * @param size количество курсов.
 */
void compareByDuration(const Course* p_courses, int size) {
    int min_index = 0;
    int max_index = 0;

    for (int i = 1; i < size; i++) {
        if (p_courses[i].duration < p_courses[min_index].duration) {
            min_index = i;
        }

        if (p_courses[i].duration > p_courses[max_index].duration) {
            max_index = i;
        }
    }

    cout << endl << "Самый короткий курс:" << endl;
    printCourse(p_courses[min_index]);

    cout << "Самый длинный курс:" << endl;
    printCourse(p_courses[max_index]);
}

/**
 * Считает и выводит средний рейтинг базовых и продвинутых курсов.
 *
 * @param p_courses указатель на массив курсов.
 * @param size количество курсов.
 */
void groupByAdvanced(const Course* p_courses, int size) {
    double basic_sum = 0.0;
    double advanced_sum = 0.0;
    int basic_count = 0;
    int advanced_count = 0;

    for (int i = 0; i < size; i++) {
        if (p_courses[i].is_advanced) {
            advanced_sum += p_courses[i].rating;
            advanced_count++;
        } else {
            basic_sum += p_courses[i].rating;
            basic_count++;
        }
    }

    cout << endl << "Средний рейтинг:" << endl;

    if (basic_count > 0) {
        cout << "Базовые: " << basic_sum / basic_count << endl;
    } else {
        cout << "Базовые: нет курсов" << endl;
    }

    if (advanced_count > 0) {
        cout << "Продвинутые: " << advanced_sum / advanced_count << endl;
    } else {
        cout << "Продвинутые: нет курсов" << endl;
    }
}

/**
 * Сортирует массив курсов по рейтингу (убывание),
 * при равенстве рейтинга — по цене (возрастание).
 *
 * @param p_courses указатель на массив курсов.
 * @param size количество курсов.
 */
void sortCourses(Course* p_courses, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            bool need_swap = false;

            if (p_courses[j].rating < p_courses[j + 1].rating) {
                need_swap = true;
            } else if (p_courses[j].rating == p_courses[j + 1].rating) {
                if (p_courses[j].price > p_courses[j + 1].price) {
                    need_swap = true;
                }
            }

            if (need_swap) {
                Course temp = p_courses[j];
                p_courses[j] = p_courses[j + 1];
                p_courses[j + 1] = temp;
            }
        }
    }
}

/**
 * Сортирует массив курсов по соотношению рейтинга к цене (убывание).
 * При равенстве эффективности курс с меньшей ценой ставится раньше.
 *
 * @param p_courses указатель на массив курсов.
 * @param size количество курсов.
 */
void sortCoursesByEfficiency(Course* p_courses, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            bool need_swap = false;

            const double first_efficiency =
                p_courses[j].rating / p_courses[j].price;

            const double second_efficiency =
                p_courses[j + 1].rating / p_courses[j + 1].price;

            if (first_efficiency < second_efficiency) {
                need_swap = true;
            } else if (first_efficiency == second_efficiency) {
                if (p_courses[j].price > p_courses[j + 1].price) {
                    need_swap = true;
                }
            }

            if (need_swap) {
                Course temp = p_courses[j];
                p_courses[j] = p_courses[j + 1];
                p_courses[j + 1] = temp;
            }
        }
    }
}

/**
 * «Покупает» курсы, выбирая их по наилучшему соотношению рейтинга и цены,
 * пока они помещаются в бюджет и ограничение суммарной длительности.
 *
 * @param p_courses указатель на массив курсов.
 * @param size количество курсов.
 * @param budget максимальный бюджет.
 * @param max_total_duration максимальная суммарная длительность.
 */
void buyCourses(const Course* p_courses, int size, double budget, int max_total_duration) {
    double total_price = 0.0;
    int total_duration = 0;

    Course* p_sorted_courses = new Course[size];

    for (int i = 0; i < size; i++) {
        p_sorted_courses[i] = p_courses[i];
    }

    sortCoursesByEfficiency(p_sorted_courses, size);

    cout << endl << "Купленные курсы (бюджет " << budget
         << ", макс. длительность " << max_total_duration << "):" << endl;

    
    for (int i = 0; i < size; i++) {
        if (p_sorted_courses[i].price + total_price <= budget &&
            p_sorted_courses[i].duration + total_duration <= max_total_duration) {

            printCourse(p_sorted_courses[i]);

            total_price += p_sorted_courses[i].price;
            total_duration += p_sorted_courses[i].duration;
        }
    }

    cout << "Итого: " << total_price << " у.е., "
         << total_duration << " ч" << endl;

    
    delete[] p_sorted_courses;
}

/**
 * Освобождает память, выделенную под массив курсов.
 *
 * @param p_courses указатель на массив курсов.
 */
void deleteCourseArray(Course* p_courses) {
    delete[] p_courses;
}

/**
 * Выполняет основную последовательность работы программы.
 *
 * @return 0 при успешном завершении.
 */
int main() {
    srand((unsigned int)time(0));
    SetConsoleOutputCP(65001);

    const int size = readCourseCount();

    Course* p_courses = createCourseArray(size);
    fillCourseArrayRandom(p_courses, size);

    cout << endl << "Исходный массив курсов:" << endl;
    printCourseArray(p_courses, size);

    // Ввод критериев для рекомендаций
    double min_rating;
    double max_price;

    cout << endl << "Введите минимальный рейтинг: ";
    cin >> min_rating;

    cout << "Введите максимальную стоимость: ";
    cin >> max_price;

    cout << endl << " РЕКОМЕНДАЦИИ " << endl;
    recommendCourses(p_courses, size, min_rating, max_price);

    cout << endl << " СРАВНЕНИЕ ПО ДЛИТЕЛЬНОСТИ " << endl;
    compareByDuration(p_courses, size);

    cout << endl << " ГРУППИРОВКА " << endl;
    groupByAdvanced(p_courses, size);

    cout << endl << "СОРТИРОВКА " << endl;
    sortCourses(p_courses, size);
    printCourseArray(p_courses, size);

    cout << endl << " ПОКУПКА КУРСОВ " << endl;
    buyCourses(p_courses, size, 15000.0, 200);

    deleteCourseArray(p_courses);

    return 0;
}
