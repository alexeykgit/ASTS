#include <iostream>
#include <thread>
#include <chrono>
#include <omp.h>

int main()
{

    int id, ntr, s, nrs;
    std::cout << "Введите количество потоков: ";
    std::cin >> ntr;
    std::cout << "Введите номер решения (от 1 до 5): ";
    std::cin >> nrs;

    if (nrs==1)
    {
    s=ntr;
    //Способ 1
    printf("Способ 1 (через while + if + critical):\n");
    #pragma omp parallel \
    private(id) \
    num_threads(ntr)
    {
        id = omp_get_thread_num();
        while(s>0){
            #pragma omp critical
            {
            if (id==s-1){
                printf("%d, Hello world\n", id);
                s--;
            }
            }
        }
    }
    }

    if (nrs==2)
    {    
    //Способ 2
    printf("Способ 2 (через sleep):\n");
    #pragma omp parallel \
    private(id) \
    num_threads(ntr)
    {
        id = omp_get_thread_num();
        std::this_thread::sleep_for(std::chrono::seconds(8-id));
        printf("%d, Hello world\n", id);
    }
    }

    if (nrs==3)
    {
    //Способ 3
    printf("Способ 3 (через самоупорядочивание в массиве):\n");
    int array[ntr];
    #pragma omp parallel \
    private(id) \
    num_threads(ntr)
    {
        id = omp_get_thread_num();
        array[id] = id;
    }
    for (int i=ntr; i>0; i--){
        printf("%d, Hello world\n", array[i-1]);
    }
    }
   
    if (nrs==4)
    {
    s=ntr;
    //Способ 4
    printf("Способ 4 (через barrier):\n");
    #pragma omp parallel \
    private(id) \
    num_threads(ntr)
    {
    for (int i=0; i<ntr; i++){
        id = omp_get_thread_num();
        if (id==s-1){
            printf("%d, Hello world\n", id);
            #pragma omp critical
            {
            s--;
            }
        }
        #pragma omp barrier
    }
    }
    }

    
    //Способ 5
    /*
    printf("Способ 5:\n");
    #pragma omp parallel for \
    private(id) \
    ordered num_threads(8)
    for (int i = 7; i>=0; i--) {

    #pragma omp ordered
    {
        id = omp_get_thread_num();
        printf("%d, Hello world\n", id);
    }
    }*/
    if (nrs==5)
    {
    //Способ 6
    printf("Способ 5 (через флаги, эстафета):\n");
    int flags[ntr+1];
    for (int i=0; i<ntr+1; i++){
        flags[i] = 0;
    }
    flags[ntr] = 1;
    #pragma omp parallel \
    private(id) \
    num_threads(ntr)
    {
        while(!flags[0]){
            id = omp_get_thread_num();
            if (flags[id+1]){
                printf("%d, Hello world\n", id);
                flags[id]++;
                flags[id+1]--;
            }
        }
    }
    }
    return 0;
}





