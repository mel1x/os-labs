#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <chrono>

using namespace std;

int main(int argc, char* argv[]) {
    int matrixSize;
    int numProcs;

    if (argc == 3) {
        matrixSize = atoi(argv[1]);
        numProcs = atoi(argv[2]);
    } else {
        cout << "Введите размер матрицы: ";
        cin >> matrixSize;
        cout << "Введите количество процессов: ";
        cin >> numProcs;
    }


    int size = matrixSize * matrixSize * sizeof(int);

    int* A = (int*)mmap(NULL, size, PROT_READ | PROT_WRITE,
                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int* B = (int*)mmap(NULL, size, PROT_READ | PROT_WRITE,
                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int* C = (int*)mmap(NULL, size, PROT_READ | PROT_WRITE,
                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);


    srand(time(NULL));
    for (int i = 0; i < matrixSize * matrixSize; i++) {
        A[i] = rand() % 10 + 1;
        B[i] = rand() % 10 + 1;
        C[i] = 0;
    }

    auto start = chrono::high_resolution_clock::now();

    int rowsPerProc = matrixSize / numProcs;
    int extraRows = matrixSize % numProcs;
    int curRow = 0;

    for (int p = 0; p < numProcs; p++) {
        int startRow = curRow;
        int endRow = curRow + rowsPerProc;

        if (p < extraRows) {
            endRow++;
        }

        curRow = endRow;
        pid_t pid = fork();

        if (pid == 0) {
            for (int i = startRow; i < endRow; i++) {
                for (int j = 0; j < matrixSize; j++) {
                    C[i * matrixSize + j] = 0;
                    for (int k = 0; k < matrixSize; k++) {
                        C[i * matrixSize + j] += A[i * matrixSize + k] * B[k * matrixSize + j];
                    }
                }
            }
            exit(0);
        }
    }

    for (int i = 0; i < numProcs; i++) {
        wait(NULL);
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::duration<double, milli>>(end - start);

    cout << "Размер матрицы: " << matrixSize << "x" << matrixSize << endl;
    cout << "Количество процессов: " << numProcs << endl;
    cout << "Время выполнения: " << duration.count() / 1000.0 << " секунд" << endl;

    if (matrixSize <= 5) {
        cout << "\nРезультат:" << endl;
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                cout << C[i * matrixSize + j] << " ";
            }
            cout << endl;
        }
    }

    munmap(A, size);
    munmap(B, size);
    munmap(C, size);
}
