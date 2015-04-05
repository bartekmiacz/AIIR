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
mpiexec.exe -np <ilosc_procesow> <sciezka_do_skompilowanego_pliku>

Odpalenie w konsoli debugowej Visuala po prostu dziala jak odpalenie jednego procesu.

Pod Linuksem dziala bez zadnych problemow.
Aby zainstalowac na Ubuntu: sudo apt-get install mpich

Potem wystarczy tylko uzyc cmake do konfiguracji i make do kompilacji.

Aby odpalic w trybie mpi:

mpirun -np <ilosc_procesow> <sciezka_do_binarki>
