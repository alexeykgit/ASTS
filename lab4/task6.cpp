#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
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
    //cout << "Введите способ(Способ через сложение сразу: 1 | Способ через сложение сумм: 2): ";
    //cin >> sps;
    //cout << "Введите количество потоков: "
    //cin >> ntr;
    create_points(N);
    ifstream file("points.txt");

    //double sumX = 0, sumY = 0, sumZ = 0;
    double sumALL=0;
    double start, end;
    int n = 0;

    int k = N;
    int* x = new int[k];
    int* y = new int[k];
    int* z = new int[k];

    while (file >> x[n] >> y[n] >> z[n]) {
        n++;
    }

    //1
    /*
    if (sps == 1)
    {
    //sumX = 0, sumY = 0, sumZ = 0;
    start = omp_get_wtime();
    #pragma omp parallel sections
    {
    #pragma omp section
    {
        for (int i = 0; i < n; i++) {
            #pragma omp critical
            {
                sumALL += x[i];
            }
        }
    }
    #pragma omp section
    {
        for (int i = 0; i < n; i++) {
            #pragma omp critical
            {
                sumALL += y[i];
            }
        }
    }
    #pragma omp section
    {
        for (int i = 0; i < n; i++) {
            #pragma omp critical
            {
                sumALL += z[i];
            }
        }
    }
    }
    end = omp_get_wtime();

    printf("time: %f, result: %f\n", end - start, sumALL / 3 / n);
    }
    */

    //if (sps==2){
    //sumALL = 0;
    start = omp_get_wtime();
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            double sumX = 0;
            
            #pragma omp parallel for reduction(+:sumX)
            for (int i = 0; i < n; i++) {
                sumX += x[i];
            }

            #pragma omp critical
            {
                sumALL += sumX;
            }
        }

        #pragma omp section
        {
            double sumY = 0;

            #pragma omp parallel for reduction(+:sumY)
            for (int i = 0; i < n; i++) {
                sumY += y[i];
            }

            #pragma omp critical
            {
                sumALL += sumY;
            }
        }

        #pragma omp section
        {
            double sumZ = 0;

            #pragma omp parallel for reduction(+:sumZ)
            for (int i = 0; i < n; i++) {
                sumZ += z[i];
            }

            #pragma omp critical
            {
                sumALL += sumZ;
            }
        }
    }
    end = omp_get_wtime();

    printf("time: %f, result: %f\n", end - start, sumALL / 3 / n);
    //}

    delete[] x;
    delete[] y;
    delete[] z;

    file.close();

    return 0;
}