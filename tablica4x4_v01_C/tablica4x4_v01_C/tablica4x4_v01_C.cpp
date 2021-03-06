// tablica4x4_v01_C.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//Under "Project -> Properties -> C/C++ -> Preprocessor -> Preprocessor Definitions" add _CRT_SECURE_NO_WARNINGS

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define L_WIERSZY 4
#define L_KOLUMN  4

FILE * fptr;

void wprowadz_dane(int tab[][L_KOLUMN])
{
	int temp = 0;
	for (int wiersze = 0; wiersze < L_WIERSZY; wiersze++)
	{
		for (int kolumny = 0; kolumny < L_KOLUMN; kolumny++)
		{
			printf("Podaj wartosc [%d][%d]: ", wiersze, kolumny);
			scanf("%d", &temp);
			tab[wiersze][kolumny] = temp;
		}
	}
}

void wprowadz_dane_losowo(int tab[][L_KOLUMN])
{
	int temp = 0;
	for (int wiersze = 0; wiersze < L_WIERSZY; wiersze++)
	{
		for (int kolumny = 0; kolumny < L_KOLUMN; kolumny++)
		{
			temp = rand();
			tab[wiersze][kolumny] = (temp % 100) + 1;
		}
	}
}

void wyswietl_dane(int tab[][L_KOLUMN])
{
	int temp = 0;
	for (int wiersze = 0; wiersze < L_WIERSZY; wiersze++)
	{
		for (int kolumny = 0; kolumny < L_KOLUMN; kolumny++)
		{
			printf("%4d", tab[wiersze][kolumny]);
		}
		printf("\n");
	}
	printf("\n");
}

void wyswietl_dane_posortowane(int tab[])
{
	int temp = 0;
	for (int i = 0; i < (L_WIERSZY*L_KOLUMN); i++)
	{
		printf("%4d", tab[i]);
	}
	printf("\n");
}

float srednia(int tab[][L_KOLUMN])
{
	float suma = 0;
	for (int wiersze = 0; wiersze < L_WIERSZY; wiersze++)
	{
		for (int kolumny = 0; kolumny < L_KOLUMN; kolumny++)
		{
			suma += tab[wiersze][kolumny];
		}
	}
	return (suma / (L_WIERSZY * L_KOLUMN));
}

int cmpfunc(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}

float mediana(int tab[][L_KOLUMN], int tab_sort[])
{
	for (int wiersze = 0; wiersze < L_WIERSZY; wiersze++)
	{
		for (int kolumny = 0; kolumny < L_KOLUMN; kolumny++)
		{
			tab_sort[wiersze*L_WIERSZY + kolumny] = tab[wiersze][kolumny];
		}
	}
	qsort(tab_sort, L_KOLUMN*L_WIERSZY, sizeof(tab_sort[0]), cmpfunc);
	return ((float)(tab_sort[(L_WIERSZY*L_KOLUMN - 1) / 2] + tab_sort[(L_WIERSZY*L_KOLUMN) / 2]) / 2);
}

void zapisz_dane(int tab[][L_KOLUMN])
{
	fptr = fopen("tablica.txt", "w");
	if (fptr == 0)
	{
		printf("Blad otwierania pliku!\n");
		exit(1);
	}

	for (int wiersze = 0; wiersze < L_WIERSZY; wiersze++)
	{
		for (int kolumny = 0; kolumny < L_KOLUMN; kolumny++)
		{
			fprintf(fptr, "%4d", tab[wiersze][kolumny]);
		}
		fprintf(fptr, "\n");
	}

	fclose(fptr);
}

void wczytaj_dane(int tab[][L_KOLUMN])
{
	fptr = fopen("tablica.txt", "r");
	if (fptr == 0)
	{
		printf("Blad otwierania pliku!\n");
		exit(1);
	}

	for (int wiersze = 0; wiersze < L_WIERSZY; wiersze++)
	{
		for (int kolumny = 0; kolumny < L_KOLUMN; kolumny++)
		{
			fscanf(fptr, "%d", &tab[wiersze][kolumny]);
		}
	}

	fclose(fptr);
}

void zamien_min_max(int tab[][L_KOLUMN])
{
	int w_min = tab[0][0], w_max = tab[0][0];

	for (int wiersze = 0; wiersze < L_WIERSZY; wiersze++)
	{
		for (int kolumny = 0; kolumny < L_KOLUMN; kolumny++)
		{
			if (tab[wiersze][kolumny] < w_min) w_min = tab[wiersze][kolumny];
			if (tab[wiersze][kolumny] > w_max) w_max = tab[wiersze][kolumny];
		}
	}

	for (int wiersze = 0; wiersze < L_WIERSZY; wiersze++)
	{
		for (int kolumny = 0; kolumny < L_KOLUMN; kolumny++)
		{
			if (tab[wiersze][kolumny] == w_min) tab[wiersze][kolumny] = w_max;
			else if (tab[wiersze][kolumny] == w_max) tab[wiersze][kolumny] = w_min;
		}
	}
}

void menu(void)
{
	printf("\n");
	printf("1 - wprowadz dane\n");
	printf("2 - wyswietl dane\n");
	printf("3 - oblicz srednia i mediane\n");
	printf("4 - zamien wartosc minimalna z maksymalna\n");
	printf("5 - generuj dane losowo\n");
	printf("z - zapisz dane do pliku\n");
	printf("w - wczytaj dane z pliku\n");
	printf("k - koniec programu\n");
	printf("\n");
}

int main()
{
	int tablica[L_WIERSZY][L_KOLUMN] = { 0 };
	int tab_sort_temp[L_WIERSZY*L_KOLUMN] = { 0 };
	char opcja = 0;

	while (opcja != 'k')
	{
		menu();
		opcja = _getch();
		//_getch(); //dummy
		//opcja = getchar();
		//getchar();

		switch (opcja)
		{
		case '1':
			wprowadz_dane(tablica);
			break;

		case '2':
			wyswietl_dane(tablica);
			break;

		case '3':

			printf("Srednia wartosci znajdujacych sie w tabeli wynosi: %f\n", srednia(tablica));
			printf("Mediana wartosci znajdujacych sie w tabeli wynosi: %f\n", mediana(tablica, tab_sort_temp));
			break;

		case '4':
			zamien_min_max(tablica);
			printf("Zamieniono wartosc minimalna z maksymalna.\n");
			break;

		case '5':
			wprowadz_dane_losowo(tablica);
			printf("Wygenerowano dane losowo.\n");
			break;

		case 'z':
			zapisz_dane(tablica);
			printf("Zapisano dane do pliku.\n");
			break;

		case 'w':
			wczytaj_dane(tablica);
			printf("Odczytano dane z pliku.\n");
			break;

		case 'k':
			//zakonczenie programu
			break;

		default:
			printf("Wybierz wlasciwa opcje.\n\n");
			break;
		}
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
