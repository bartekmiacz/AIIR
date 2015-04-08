#include <iostream>
#include <mpi.h>
#include <ciso646>
#include <master.hpp>
#include <slave.hpp>

int main(int argc, char **argv)
{
    unsigned long long primeCandidate = atoi(argv[1]);
    unsigned int numberOfTests = atoi(argv[2]);
    int my_rank;
    // MPI initializations
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    if (not(primeCandidate & 1))
    {
        if (0 == my_rank)
        {
            std::cout << "NIE" << std::endl; //Jezeli liczba jest parzysta odrazu mozna skonczyc
        }
        MPI_Finalize();
        return 0;
    }
    if (primeCandidate <= 2)
    {
        if (0 == my_rank)
        {
            std::cout << "TAK" << std::endl; //Szybkie skonczenie dla warunkow brzegowych
        }
        MPI_Finalize();
        return 0;
    }

    if (0 == my_rank)
    {
        master(primeCandidate, numberOfTests);
    }
    else
    {
        slave();
    }

    // End MPI
    MPI_Finalize();
    return 0;
}