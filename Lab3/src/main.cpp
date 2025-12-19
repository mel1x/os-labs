#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

int main() {
    srand(time(0));

    const size_t FILE_SIZE = 100 * 1024 * 1024;
    const size_t PAGE_SIZE = 4096;
    const size_t NUM_PAGES = 1000;
    const string filename = "test.bin";

    ofstream file(filename, ios::binary);

    for (size_t i = 0; i < FILE_SIZE; i++) {
        char byte = rand() % 256;
        file.write(&byte, 1);
    }
    file.close();
    cout << "Файл создан" << endl;


    int fd = open(filename.c_str(), O_RDWR);
    char* data = (char*)mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    cout << "Файл отображен" << endl;

    vector<size_t> pages(NUM_PAGES);
    size_t max_page = FILE_SIZE / PAGE_SIZE - 1;

    for (size_t i = 0; i < NUM_PAGES; i++) {
        pages[i] = rand() % max_page;
    }

    char dummy = 0;

    auto startFirst = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < NUM_PAGES; i++) {
        size_t offset = pages[i] * PAGE_SIZE;
        dummy = data[offset];
    }
    auto endFirst = chrono::high_resolution_clock::now();
    double timeFirst = chrono::duration<double, milli>(endFirst - startFirst).count();

    auto startSecond = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < NUM_PAGES; i++) {
        size_t offset = pages[i] * PAGE_SIZE;
        dummy = data[offset];
    }
    auto endSecond = chrono::high_resolution_clock::now();
    double timeSecond = chrono::duration<double, milli>(endSecond - startSecond).count();

    cout << "\n=== РЕЗУЛЬТАТЫ ===" << endl;
    cout << "Время первых обращений:  " << timeFirst << " мс" << endl;
    cout << "Время вторых обращений:  " << timeSecond << " мс" << endl;
    cout << "Ускорение:               " << timeFirst / timeSecond << "x" << endl;


    munmap(data, FILE_SIZE);
    close(fd);
}
