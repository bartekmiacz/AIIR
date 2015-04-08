#include <slave.hpp>
#include <mpi.h>
#include <ciso646>
#include <InfInt.h>
#include <iostream>

InfInt fastPower(InfInt a, InfInt n)
{
    InfInt result = 1;
    InfInt power = n;
    InfInt value = a;

    while (power>0)
    {
        if (power%2 == 1)
        {
            result = result*value;
        }
        value = value*value;
        power /= 2;
    }
    return result;
}

void slave(unsigned long long primeCandidate)
{
    MPI_Status status;
    unsigned long long a;
    unsigned long long d;
    unsigned int s;
    char ok = 1;
    char nok = 0;

    MPI_Recv(&a, 1, MPI_UNSIGNED_LONG_LONG, MASTER_TAG, MPI_ANY_TAG, MPI_COMM_WORLD, &status); // pierwszy odbierany jest start
    //Jezeli nie bedzie die tag to ta wiadomosc zostanie po prostu nadpisana
    if (status.MPI_TAG == DIETAG) //Szybkie zakonczenie jezeli proces w ogole nie wystartuje
    {
        return;
    }

    //d oraz s przyjmowane sa raz poniewaz nie zmieniaja sie w ramach danej liczby pierwszej
    MPI_Recv(&d, 1, MPI_UNSIGNED_LONG_LONG, MASTER_TAG, WORKTAG, MPI_COMM_WORLD, &status);
    MPI_Recv(&s, 1, MPI_UNSIGNED, MASTER_TAG, WORKTAG, MPI_COMM_WORLD, &status);

    while(true)
    {
        MPI_Recv(&a, 1, MPI_UNSIGNED_LONG_LONG, MASTER_TAG, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        if (status.MPI_TAG == DIETAG)
        {
            return;
        }

        unsigned long long x = (fastPower(a, d)% primeCandidate).toUnsignedLongLong();

        if (1 == x or primeCandidate - 1 == x)
        {
            MPI_Send(&ok, 1, MPI_CHAR, MASTER_TAG, WORKTAG, MPI_COMM_WORLD);
            continue;
        }

        unsigned int j = 1;
        while (j < s and primeCandidate - 1 != x)
        {
            x = (x*x) % primeCandidate;
            if (1 == x)
            {
                MPI_Send(&nok, 1, MPI_CHAR, MASTER_TAG, WORKTAG, MPI_COMM_WORLD);
                return;
            }
            j++;
        }

        if (primeCandidate - 1 != x)
        {
            MPI_Send(&nok, 1, MPI_CHAR, MASTER_TAG, WORKTAG, MPI_COMM_WORLD);
            return;
        }
        MPI_Send(&ok, 1, MPI_CHAR, MASTER_TAG, WORKTAG, MPI_COMM_WORLD);
    }
}