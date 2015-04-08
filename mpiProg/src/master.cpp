#include <master.hpp>
#include <random>
#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
#include <ciso646>
#include <mpi.h>

void master(unsigned long long primeCandidate, int numberOfTries)
{
    std::vector<unsigned long long> randBase(primeCandidate - 3LL);
    std::random_device rd;
    std::mt19937 g(rd());
    int limit;
    int numprocs;
    int rank;
    int work;
    int randIter = 0;
    double probability = 1;
    char partialResult;
    MPI_Status status;
    bool result = true;

    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    work = std::min(numberOfTries, static_cast<int>(randBase.size()));
    limit = std::min({ numprocs, static_cast<int>(randBase.size()+1), numberOfTries+1 });

    std::iota(randBase.begin(), randBase.end(), 2); // Wypelnienie wektora liczbami rosnacymi zaczynajacymi sie od 2
    std::shuffle(randBase.begin(), randBase.end(), g); // Wszystkie wartosci bazy w losowej kolejnosci.

    //Obliczenie s i d
    unsigned long long d = primeCandidate - 1LL;
    unsigned int s = 0;

    while (not d & 1) // Dopoki d parzyste
    {
        s += 1;
        d >>= 1; // Dzielenie inta przez 2
    }

    //Rozdanie pierwszych zadan
    for (rank = 1; rank < limit; ++rank)
    {
        MPI_Send(&d, 0, MPI_UNSIGNED_LONG_LONG, rank, WORKTAG, MPI_COMM_WORLD); //Konieczne aby wystartowac slavy
        MPI_Send(&d, 1, MPI_UNSIGNED_LONG_LONG, rank, WORKTAG, MPI_COMM_WORLD);
        MPI_Send(&s, 1, MPI_UNSIGNED, rank, WORKTAG, MPI_COMM_WORLD);
        MPI_Send(&(randBase[randIter]), 1, MPI_UNSIGNED_LONG_LONG, rank, WORKTAG, MPI_COMM_WORLD);
        work--;
        randIter++;
    }

    //Odebranie wynikow od tych co skonczyli i rozeslanie kolejnych zadan
    while (work > 0)
    {
        MPI_Recv(&partialResult, 1, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        if (0 == partialResult) // Jezeli chociaz jeden zwroci 0 to liczba napewno nie jest pierwsza
        {
            result = false;
            break; //Przerywamy petle poniewaz proces ktory zwroci 0 odrazu sie konczy wiec nie mozna mu wysylac nowego zadania a nawet nie ma sensu tego robic
        }
        probability /= 4; // Prawdopodobienstwo braku pierwszosci zmniejsza sie

        MPI_Send(&(randBase[randIter]), 1, MPI_UNSIGNED_LONG_LONG, status.MPI_SOURCE, WORKTAG, MPI_COMM_WORLD);

        work--;
        randIter++;
    }

    //Koniec zadan
    for (rank = 1; rank < limit - (result ? 0:1); ++rank) //Odjecie tego result to w przypadku kiedy jeden stwierdzil ze jest nie pierwsza
    {
        MPI_Recv(&partialResult, 1, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        if (result) // Szkoda czasu na sprawdzanie jezeli juz wczesniej mozemy wiedziec ze liczba nie jest pierwsza
        {
            if (0 == partialResult) // Jezeli chociaz jeden zwroci 0 to liczba napewno nie jest pierwsza
            {
                result = false;
            }
            probability /= 4; // Prawdopodobienstwo braku pierwszosci zmniejsza sie
        }
    }

    //Zakonczenie reszty procesow
    for (rank = 1; rank < numprocs; ++rank)
    {
        MPI_Send(0, 0, MPI_UNSIGNED_LONG_LONG, rank, DIETAG, MPI_COMM_WORLD);
    }

    if (result)
    {
        std::cout << "TAK" << std::endl;
        std::cout << 1 - probability << std::endl;
    }
    else
    {
        std::cout << "NIE" << std::endl;
    }
}