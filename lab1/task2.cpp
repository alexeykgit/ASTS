#include <iostream>
#include <omp.h>

int main()
{
    int id, N, ntr, sdg;
    std::cout << "Введите количество элементов массива: ";
    std::cin >> N;
    std::cout << "Введите количество потоков: ";
    std::cin >> ntr;
    std::cout << "Введите номер способа (static: 1 | dynamic: 2 | guided: 3): ";
    std::cin >> sdg;
    int a[N];
    double start, end;
    double b[N-2];
    for(int i=0; i<N; i++){
        a[i] = i;
    }

    if (sdg == 1)
    {
    // static
    start = omp_get_wtime();
    #pragma omp parallel for \
    num_threads(ntr) \
    schedule(static)
    for(int i=1; i<N-1; i++){
        b[i] = (a[i-1] + a[i] + a[i+1])/3.0;
    }
    end = omp_get_wtime();
    printf("Time for Static: %f seconds\n", end - start);
    }

    if (sdg == 2)
    {
    // dynamic
    start = omp_get_wtime();
    #pragma omp parallel for \
    num_threads(ntr) \
    schedule(dynamic)
    for(int i=1; i<N-1; i++){
        b[i] = (a[i-1] + a[i] + a[i+1])/3.0;
    }
    end = omp_get_wtime();
    printf("Time for Dynamic: %f seconds\n", end - start);
    }

    if (sdg == 3)
    {
    // guided
    start = omp_get_wtime();
    #pragma omp parallel for \
    num_threads(ntr) \
    schedule(guided)
    for(int i=1; i<N-1; i++){
        b[i] = (a[i-1] + a[i] + a[i+1])/3.0;
    }
    end = omp_get_wtime();
    printf("Time for Guided: %f seconds\n", end - start);
    }

    return 0;
}





