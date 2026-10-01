#include <iostream>
#include <cstdlib>
#include <omp.h>

using namespace std;

void randarr(int* arr, int N, int M, int randnum) {

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            arr[i * M + j] = rand() % randnum;
        }
    }
}

void printarr(int* arr, int N, int M, std::string name) {
    printf("Массив %s\n", name.c_str());

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", arr[i * M + j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    int N = 400, M = 500, L = 600, sps, ntr;
    cout << "Введите размер матриц для а(N*M) и b(M*L)\n";
    cout << "Введите N: ";
    cin >> N;
    cout << "Введите M: ";
    cin >> M;
    cout << "Введите L: ";
    cin >> L;
    cout << "Введите способ выполнения (последовательный: 1 | параллельный: 2): ";
    cin >> sps;
    if (sps==2){
        cout << "Введите количество потоков: ";
        cin >> ntr;
    }
    double start, end, sum;
    int* a = new int[N * M];
    int* b = new int[M * L];
    int* c = new int[N * L];

    randarr(a, N, M, 10);
    randarr(b, M, L, 10);

    if (sps == 1)
    {
    // posledovatel
    start = omp_get_wtime();
    for(int i = 0; i < N; i++){
        for(int j = 0; j < L; j++){
            c[i*L + j] = 0;

            for(int k = 0; k < M; k++){
                c[i*L + j] += a[i * M + k] * b[k*L+j];
            }
        }
    }
    end = omp_get_wtime();
    printf("Время для последовательного: %f\n", end-start);
    }

    if (sps == 2)
    {
    start = omp_get_wtime();
    #pragma omp parallel for num_threads(ntr) //reduction(+:sum)
    for(int i = 0; i < N; i++){
        for(int j = 0; j < L; j++){
            c[i*L + j] = 0;
            for(int k = 0; k < M; k++){
                c[i*L + j] += a[i * M + k] * b[k*L+j];
            }
        }
    }
    end = omp_get_wtime();
    printf("Время для параллельного с %dмя потоками: %f\n", ntr, end-start);
    }
    //printarr(a, N, M, "a");
    //printarr(b, M, L, "b");
    //printarr(c, N, L, "c");
    delete[] a;
    delete[] b;
    delete[] c;

    return 0;
}