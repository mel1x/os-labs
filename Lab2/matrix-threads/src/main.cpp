#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <chrono>

using namespace std;

int matrixSize;
int numThreads;
int** A;
int** B;
int** C;

struct Data {
    int startRow;
    int endRow;
};

void* multiply(void* arg) {
    Data* data = (Data*)arg;

    for (int i = data->startRow; i < data->endRow; i++) {
        for (int j = 0; j < matrixSize; j++) {
            C[i][j] = 0;
            for (int k = 0; k < matrixSize; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc == 3) {
        matrixSize = atoi(argv[1]);
        numThreads = atoi(argv[2]);
    } else {
        cout << "Введите размер матрицы: ";
        cin >> matrixSize;
        cout << "Введите количество потоков: ";
        cin >> numThreads;
    }

    A = new int*[matrixSize];
    B = new int*[matrixSize];
    C = new int*[matrixSize];
    for (int i = 0; i < matrixSize; i++) {
        A[i] = new int[matrixSize];
        B[i] = new int[matrixSize];
        C[i] = new int[matrixSize];
    }

    srand(time(NULL));
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            A[i][j] = rand() % 10 + 1;
            B[i][j] = rand() % 10 + 1;
        }
    }

    auto start = chrono::high_resolution_clock::now();


    pthread_t* threads = new pthread_t[numThreads];
    Data* threadData = new Data[numThreads];

    int rowsPerThread = matrixSize / numThreads;
    int extraRows = matrixSize % numThreads;
    int curRow = 0;

    for (int i = 0; i < numThreads; i++) {
        threadData[i].startRow = curRow;
        threadData[i].endRow = curRow + rowsPerThread;

        if (i < extraRows) {
            threadData[i].endRow++;
        }

        curRow = threadData[i].endRow;

        pthread_create(&threads[i], NULL, multiply, &threadData[i]);
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::duration<double, milli>>(end - start);

    cout << "Размер матрицы: " << matrixSize << "x" << matrixSize << endl;
    cout << "Количество потоков: " << numThreads << endl;
    cout << "Время выполнения: " << duration.count() / 1000.0 << " секунд" << endl;

    if (matrixSize <= 5) {
        cout << "\nРезультат:" << endl;
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                cout << C[i][j] << " ";
            }
            cout << endl;
        }
    }

    for (int i = 0; i < matrixSize; i++) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;
    delete[] threads;
    delete[] threadData;
}
