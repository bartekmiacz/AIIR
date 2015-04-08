Pod Windowsem konieczne jest zainstalowanie MPICH2:
https://www.mpich.org/static/tarballs/1.4.1p1/mpich2-1.4.1p1-win-ia32.msi

Przydatne komendy aby zobaczyć czy wszystko działa (wszystkie wymagaja administracyjnej konsoli):
smpd -status
smpd -install   ->instaluje usluge mpi 

mpiexec -remove    -> usuwa zapisane dane logowania
mpiexec -register  -> dodaje nowe dane logowania. Przy pytaniu o nazwe uzytkownika najlepiej kliknac enter wtedy zostanie wzieta nazwa aktualnego uzytkownika
						haslo nalezy wpisac swoje do konta
mpiexec -validate  -> sprawdza czy zapamietane dane logowania sa poprawne

Podczas instalacji MPICH2 pod windą najlepiej zainstalowac dla wszystkich uzytkownikow.

Aby odpalić w trybie mpi:
mpiexec -np <ilosc_procesow> <sciezka_do_binarki> <kandydat_na_liczbe_pierwsza> <ilosc_testow>

Odpalenie w konsoli debugowej Visuala po prostu dziala jak odpalenie jednego procesu wiec tylko master.

Pod Linuksem dziala bez zadnych problemow.
Aby zainstalowac na Ubuntu: sudo apt-get install mpich

Potem wystarczy tylko uzyc cmake do konfiguracji i make do kompilacji.

Aby odpalic w trybie mpi:

mpirun -np <ilosc_procesow> <sciezka_do_binarki> <kandydat_na_liczbe_pierwsza> <ilosc_testow>

Wiekszosc zmiennych czerpie oznaczenia z tej strony z algorytmem:
http://edu.i-lo.tarnow.pl/inf/alg/001_search/0019.php

Wyjscie programu:
Jezeli sukces: TAK\n<prawdopodobienstwo>\n
W innym przypadku: NIE\n
