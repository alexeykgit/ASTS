#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <omp.h>

using namespace std;

void create_points(int N) {
    ofstream file("points.txt");

    srand(time(0));

    for (int i = 0; i < N; i++) {
        int x = rand() % 1000;
        int y = rand() % 1000;
        int z = rand() % 1000;

        file << x << " " << y << " " << z << "\n";
    }

    file.close();

    cout << "Created " << N << " points" << endl;
}

int main()
{
    int N, sps, ntr;
    cout << "Введите количество точек: ";
    cin >> N;
    cout << "Введите способ(распаралеливание: 1 | декомпозиция: 2): ";
    cin >> sps;
    //cout << "Введите количество потоков: ";
    //cin >> ntr;
    create_points(N);
    ifstream file("points.txt");

    double sumX = 0, sumY = 0, sumZ = 0;
    double start, end;
    int n = 0;

    int k = N;
    int* x = new int[k];
    int* y = new int[k];
    int* z = new int[k];

    while (file >> x[n] >> y[n] >> z[n]) {
        n++;
    }


    // 1
    if (sps == 1)
    {
    start = omp_get_wtime();
    #pragma omp parallel for reduction(+:sumX,sumY,sumZ)
    for (int i = 0; i < n; i++) {
        sumX += x[i];
        sumY += y[i];
        sumZ += z[i];
    }
    end = omp_get_wtime();

    printf("1: %f, coordinates: %f, %f, %f\n", end - start, sumX / n, sumY / n, sumZ / n);
    }

    // 2
    if (sps == 2)
    {
    sumX = 0, sumY = 0, sumZ = 0;
    start = omp_get_wtime();
    #pragma omp parallel sections
    {
    #pragma omp section
    {
        for (int i = 0; i < n; i++) {
            sumX += x[i];
        }
    }
    #pragma omp section
    {
        for (int i = 0; i < n; i++) {
            sumY += y[i];
        }
    }
    #pragma omp section
    {
        for (int i = 0; i < n; i++) {
            sumZ += z[i];
        }
    }
    }
    end = omp_get_wtime();

    printf("2: %f, coordinates: %f, %f, %f\n", end - start, sumX / n, sumY / n, sumZ / n);
    }


    delete[] x;
    delete[] y;
    delete[] z;

    file.close();

    return 0;
}