TASKNO=5
APP=sterowanie-dronem
TASKDIR=${HOME}/edu/po/zad/z${TASKNO}

__start__: obj dat ./${APP}
	rm -f core.* core; ./${APP}

# Tworzy katalog "obj" gdy go nie ma
# 
obj:
	mkdir obj

dat:
	mkdir dat


./${APP}: obj/main.o obj/Rotacja.o obj/lacze_do_gnuplota.o obj/Dron.o obj/Graniastoslup.o obj/Prostopadloscian.o\
			obj/BrylaGeometryczna.o obj/Scena.o obj/Plaskowyz.o obj/Gora_z_grania.o obj/Gora_z_ostrym_szczytem.o obj/ElementSceny.o
	g++ -o ./${APP} obj/main.o obj/Rotacja.o obj/lacze_do_gnuplota.o obj/Dron.o obj/Graniastoslup.o obj/Prostopadloscian.o\
			obj/BrylaGeometryczna.o obj/Scena.o obj/Plaskowyz.o obj/Gora_z_grania.o obj/Gora_z_ostrym_szczytem.o obj/ElementSceny.o


ext: ./${APP}_rozszerzony
	rm -f core.* core; echo "2i 1+3.1i 2 ? / + ?" | ./${APP}_rozszerzony


obj/main.o: src/main.cpp inc/Rotacja.hh inc/lacze_do_gnuplota.hh inc/Macierz3x3.hh inc/Macierz.hh\
           inc/Wektor.hh inc/Dron.hh inc/Graniastoslup.hh inc/Prostopadloscian.hh inc/BrylaGeometryczna.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/main.o src/main.cpp

obj/lacze_do_gnuplota.o: src/lacze_do_gnuplota.cpp inc/lacze_do_gnuplota.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/Rotacja.o: src/Rotacja.cpp inc/Rotacja.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/Rotacja.o src/Rotacja.cpp

obj/Dron.o: src/Dron.cpp inc/Dron.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/Dron.o src/Dron.cpp

obj/BrylaGeometryczna.o: src/BrylaGeometryczna.cpp inc/BrylaGeometryczna.hh inc/Macierz3x3.hh inc/Rotacja.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/BrylaGeometryczna.o src/BrylaGeometryczna.cpp

obj/Graniastoslup.o: src/Graniastoslup.cpp inc/Graniastoslup.hh inc/BrylaGeometryczna.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/Graniastoslup.o src/Graniastoslup.cpp

obj/Prostopadloscian.o: src/Prostopadloscian.cpp inc/Prostopadloscian.hh inc/BrylaGeometryczna.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/Prostopadloscian.o src/Prostopadloscian.cpp
	
obj/Scena.o: src/Scena.cpp inc/Scena.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/Scena.o src/Scena.cpp

obj/Plaskowyz.o: src/Plaskowyz.cpp inc/Plaskowyz.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/Plaskowyz.o src/Plaskowyz.cpp

obj/Gora_z_grania.o: src/Gora_z_grania.cpp inc/Gora_z_grania.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/Gora_z_grania.o src/Gora_z_grania.cpp

obj/Gora_z_ostrym_szczytem.o: src/Gora_z_ostrym_szczytem.cpp inc/Gora_z_ostrym_szczytem.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/Gora_z_ostrym_szczytem.o src/Gora_z_ostrym_szczytem.cpp

obj/ElementSceny.o: src/ElementSceny.cpp inc/ElementSceny.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/ElementSceny.o src/ElementSceny.cpp
clean:
	rm -f obj/* ./${APP} core.* core

${TASKDIR}:
	mkdir -p ${TASKDIR}/bin.diablo ${TASKDIR}/bin.panamint

__TARGET__:
	if [ ! "${HOST}" = "diablo" ] && [ ! "${HOST}" = "panamint" ]; then exit 1; fi

export: __TARGET__ ./${APP}  ./${APP}_rozszerzony ${TASKDIR}
	mv ${APP} ${APP}_rozszerzony ${HOME}/edu/po/zad/z${TASKNO}/bin.${HOST}/

help:
	@echo
	@echo " make        - tworzenie i uruchomienie aplikacji"
	@echo " make ext    - tworzenie i uruchomienie aplikacji w wersji rozszerzonej"
	@echo " make clean  - usuniecie produktow kompilacji i konsolidacji"
	@echo " make help   - wyswietla niniejsza informacje"
	@echo
