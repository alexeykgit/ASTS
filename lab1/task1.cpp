#include <iostream>
#include <omp.h>

int main()
{
    int id, ntr;
    std::cout << "Введите количество потоков: ";
    std::cin >> ntr;
    #pragma omp parallel \
    private(id) \
    num_threads(ntr)
    {
    id = omp_get_thread_num();
    printf("%d, Hello world\n", id);
    }
    return 0;
}