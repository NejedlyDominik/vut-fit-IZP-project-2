/***************************************************************/
/***                      Projekt č. 2                       ***/
/***               Práce s iteračními výpočty                ***/
/***                                                         ***/
/***               Dominik Nejedlý (xnejed09)                ***/
/***                          2018                           ***/
/***************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


double cfrac_log(double x, unsigned int n);
double taylor_log(double x, unsigned int n);
double taylor_pow(double x, double y, unsigned int n);
double taylorcf_pow(double x, double y, unsigned int n);
int zkontroluj_argumenty(int argc, char *argv[]);
int chybova_hlaseni(int argc, int pomocna_promenna, char *argv[]);
int preved_a_tiskni_log(char *argv[]);
int preved_a_tiskni_pow(char *argv[]);


int main(int argc, char *argv[])
{
	int pomocna_promenna;	// Slouzi pro nacitani navratovych hodnot volanych funkci.

	pomocna_promenna = zkontroluj_argumenty(argc, argv);
	
	// Pokud se pomocna_promenna nerovna 0, program se ukonci, vytiskne chybove hlaseni a vrati prislusnou navratovou hodnotu.
	if(pomocna_promenna != 0)
	{
		return chybova_hlaseni(argc, pomocna_promenna, argv);
	}
	
	// Pokud je pocet argumentu roven 4, probehne funkce logaritmu, jinak je zavolana funkce pro vypocet umocneni. Vzdy take probiha kontrola navratove hodnoty.
	if(argc == 4)
	{
		pomocna_promenna = preved_a_tiskni_log(argv);

		if(pomocna_promenna != 0)
		{
			return chybova_hlaseni(argc, pomocna_promenna, argv);
		}
	}
	else
	{
		pomocna_promenna = preved_a_tiskni_pow(argv);

		if(pomocna_promenna != 0)
		{
			return chybova_hlaseni(argc, pomocna_promenna, argv);
		}
	}
	return 0;
}


/**
 * Funkce prevadi retezec na cislo datoveho typu double.
 */
int preved_na_double(double *cislo, char *retezec)
{
	char *textova_cast = NULL;

	*cislo = strtod(retezec, &textova_cast);

	// Pokud dany retezec neni pouze cislo, tak vrati 5.
	if(strlen(textova_cast) != 0)
	{
		return 5;
	}
	return 0;
}


/**
 * Funkce prevadi retezec na cislo datoveho typu unsigned int.
 */
int preved_na_uint(unsigned int *cislo, char *retezec)
{
	char *textova_cast = NULL;

	*cislo = strtoul(retezec, &textova_cast, 10);

	// Pokud dany retezec neni pouze cele cislo, tak vrati 6.
	if(strlen(textova_cast) != 0)
	{
		return 6;
	}
	
	//Pokud je cislo mensi, nebo rovno 0, tak vrati 7.
	if(retezec[0] == '-' || *cislo == 0)
	{
		return 7;
	}
	return 0;
}


/**
 * Funkce slouzi k prvotni kontrole argumentu.
 */
int zkontroluj_argumenty(int argc, char *argv[])
{
	// Pokud nebyl zadan zadny argument, vrati 1.
	if(argc < 2)
	{
		return 1;
	}

	// Pokud 1. argument neodpovida funkci logaritmu ani funkci umocneni, tak vrati 2.
	if((strcmp(argv[1], "--log") != 0) && (strcmp(argv[1], "--pow") != 0))
	{
		return 2;
	}
	
	// kontrola poctu argumentu pro funkci logaritmu
	if((strcmp(argv[1], "--log") == 0) && argc != 4)
	{
		return 3;
	}

	// kontrola poctu argumentu pro funkci umocneni
	if((strcmp(argv[1], "--pow") == 0) && argc != 5)
	{
		return 4;
	}

	return 0;
}


/**
 * Funkce, která podle návratových hodnot ostatních funkcí, které jí jsou předávány, tiskne chybová hlášení.
 */
int chybova_hlaseni(int argc, int pomocna_promenna, char *argv[])
{
	switch(pomocna_promenna)
	{
		case 1:
			fprintf(stderr, "Pri spusteni programu nebyly zadany zadne argumenty!\n");
			break;
		case 2:
			fprintf(stderr, "Na pozici 1. argumentu zadana neznama funkce(\"%s\")! Jako 1. argument zadejte \"--log\", nebo \"--pow\".\n", argv[1]);
			break;
		case 3:
			fprintf(stderr, "Zadan nespravny pocet argumentu pro vypocet prirozeneho logaritmu! Pro vypocet zadejte 3 argumenty.\n");
			break;
		case 4:
			fprintf(stderr, "Zadan nespravny pocet argumentu pro vypocet exponencialni funkce! Pro vypocet zadejte celkem 4 argumenty.\n");
			break;
		case 5:
			fprintf(stderr, "V 2. argumentu se nachazi nepodporovany znak! Jako 2. argument pro %s zadejte kladne realne cislo.\n", (argc == 4) ? "vypocet logaritmu" : "funkci umocneni");
			break;
		case 6:
			fprintf(stderr, "V %d. argumentu se nachazi nepodporovany znak v poctu iteraci! Jako %d. argument zadejte kladne cele cislo.\n", (argc == 4) ? 3 : 4, (argc == 4) ? 3 : 4);
			break;
		case 7:
			fprintf(stderr, "Nepodporovany pocet iteraci(%s)! Na pozici %d. argumentu zadejte cele kladne cislo.\n", argv[argc - 1], argc - 1);
			break;
		case 8:
			fprintf(stderr, "V 3. argumentu funkce na umocneni se nachazi nepodporovany znak! Mocninou muze byt pouze libovolne realne cislo.\n");
			break;
		
	}

	return pomocna_promenna;
}


/**
 * Funkce převede číselné argumenty na čísla, zavolá funkce pro výpočty logaritmu a výsledky vytiskne.
 */
int preved_a_tiskni_log(char *argv[])
{
	double x;				// Cislo, na kterem je provadena funkce logaritmu.
	double vysledek;		// Promenna, do ktere se uklada vysledek funkce logaritmu z matematicke knihovny.
	unsigned int n;			// Promenna sloužici pro ulozeni poctu iteraci.
	int pomocna_promenna;	// Slouzi pro kontrolu navratovych hodnot volanych funkci pro prevadeni retezcu na cisla.
	
	// Do promenne x ulozi prevedene cislo a do promenne pomocna_promenna navratovou hodnotu funkce prevadeni.
	pomocna_promenna = preved_na_double(&x, argv[2]);

	// Pokud je pomocna_promenna rovna nule, prevede pocet iteraci a navratovou hodnotu prevadeci funkce ulozi do promenne pomocna_promenna.
	if(pomocna_promenna == 0)
	{
		pomocna_promenna = preved_na_uint(&n, argv[3]);
	}
	
	// Pokud se pomocna promenna nerovna 0, vrati pomocnou promennou.
	if(pomocna_promenna != 0)
	{
		return pomocna_promenna;
	}

	// Ulozi vysledek funkce logaritmu z matematicke knihovny do promenne vysledek.
	vysledek = log(x);
	
	printf("       log(%g) = %.12g\n", x, vysledek);

	// Pokud je hodnota v promenne vysledek nekonecna, nebo zadna, vytiskne vysledek.
	printf(" cfrac_log(%g) = %.12g\n", x, (isinf(vysledek) || isnan(vysledek)) ? vysledek : cfrac_log(x, n));
	printf("taylor_log(%g) = %.12g\n", x, (isinf(vysledek) || isnan(vysledek)) ? vysledek : taylor_log(x, n));

	return 0;
}


/**
 * Funkce prevede ciselne argumenty na cisla, zavola funkce pro vypocty umocneni a vysledky vytiskne.
 */
int preved_a_tiskni_pow(char *argv[])
{
	double x;					// Cislo, ktere je umocnovano.
	double y;					// cislo mocniny
	double vysledek;			// Promenna, do ktere se uklada vysledek funce umocneni z matematicke knihovny.
	double vysledek_taylor;		// Slouzi pro vysledek funkce taylor_pow.
	double vysledek_taylorcf;	// Slouži pro vysledek funkce taylorcf_pow.
	unsigned int n;				// pocet iteraci
	int pomocna_promenna;		// kontrola navratovych hodnot

	pomocna_promenna = preved_na_double(&x, argv[2]);

	if(pomocna_promenna != 0)
	{
		return pomocna_promenna;
	}

	pomocna_promenna = preved_na_double(&y, argv[3]);
		
	if(pomocna_promenna != 0)
	{
		return pomocna_promenna + 3;
	}

	pomocna_promenna = preved_na_uint(&n, argv[4]);

	if(pomocna_promenna != 0)
	{
		return pomocna_promenna;
	}

	// Ulozi vysledek funkce umocneni z matematicke knihovny do promenne vysledek.
	vysledek = pow(x, y);

	// Pokud neni splnena podminka, do promennych pro vypocet taylorovym polynomem se ulozi vysledek z funkce pow().
	if(!isinf(vysledek) && !isnan(vysledek) && vysledek != 0 && (fabs(x) != 1 || !isinf(y)))
	{
		// Abychom mohli pracovat se zapornymi cisli, tak pouzivame funkci fabs().
		vysledek_taylor = taylor_pow(fabs(x), y, n);
		vysledek_taylorcf = taylorcf_pow(fabs(x), y, n);

		// Pokud je splnena podminka nadrazena teto, je jasne, ze pokud je x < 0, je y urcite cele cislo (muzeme je tedy pretypovat na datovy typ integer).
		if(x < 0 && fabs((int)y % 2) == 1)
		{
			// Z podminky vypliva, ze pokud je x < 0 a cislo mocniny (tedy y) je liche, tak potom celkový vysledek bude zaporny (princip umocnovani zapornych cisel).
			vysledek_taylor *= -1;
			vysledek_taylorcf *= -1;
		}
	}
	else
	{
		vysledek_taylor = vysledek;
		vysledek_taylorcf = vysledek;
	}

	printf("         pow(%g,%g) = %.12g\n", x, y, vysledek);
	printf("  taylor_pow(%g,%g) = %.12g\n", x, y, vysledek_taylor);
	printf("taylorcf_pow(%g,%g) = %.12g\n", x, y, vysledek_taylorcf);

	return 0;
}


/**
 * Funkce pro vypocet citatele, ktery je předavan funkci pro vypocet logaritmu pomoci zretezeneho zlomku.
 * Prvnim parametrem je primarni hodnota pro vypocet a druhym je cislo aktualni iterace.
 */
double citatel(double z, unsigned int i)
{
	double citatel;

	if(i == 1)
	{
		citatel = 2 * z;
		return citatel;
	}
	else
	{
		citatel = (i - 1) * z;
		citatel *= citatel;
		return citatel;
	}
}


/**
 * Funkce pro vypocet jmenovatele, ktery je předavan funkci pro vypocet logaritmu pomoci zretezeneho zlomku.
 * Parametrem je cislo aktualni iterace.
 */
double jmenovatel(unsigned int i)
{
	double jmenovatel = 2.0 * i - 1.0;
	return jmenovatel;
}


/**
 * Funkce pro vypocet logaritmu pomoci zretezeneho zlomku. Parametrem je logaritmovane cislo a pocet iteraci.
 */
double cfrac_log(double x, unsigned int n)
{
	double z = (x - 1.0) / (x + 1.0);	// Primarni hodnota, se kterou se pri vypoctu pracuje.
	double vysledek = 0.0;
	
	// Cyklus pro vypocet daneho zretezeneho zlomku.
	for(unsigned int i = n; i >= 1; i--)
	{
		vysledek = citatel(z, i) / (jmenovatel(i) - vysledek);
	}

	return vysledek;
}


/**
 * Aplikace vypoctu logaritmu taylorovym polynomem. Funkci je predana konstantni hodnota, pocatecni citatel a pocet iteraci.
 */
double vypocti_taylor_log(double konstantni_hodnota, double citatel, unsigned int n)
{
	double vysledek = 0.0;	

	// cyklus vypoctu
	for(unsigned int i = 1; i <= n; i++)
	{
		// K vysledku se neustale pricitaji nasledujici cleny rozvoje.
		vysledek += citatel / i;

		// Jelikoz je v citateli mocnina, citatel je vzdy pronasoben konstantni hodnotou, ktera ma hodnotu prvniho citatele, cimz se docili efektu umocnovani.
		citatel *= konstantni_hodnota;
	}

	return vysledek;
}


/**
 * Funkce pro vypocet logaritmu pomoci taylorova polynomu. Funkci je predano logaritmovane cislo a pocet iteraci.
 */
double taylor_log(double x, unsigned int n)
{
	double konstantni_hodnota;	// Promenna pro hodnotu, ktera se behem vypoctu nemeni.
	double citatel;				// pocatecni citatel

	// Rozhoduje o typu taylorova polynomu.
	if(x < 1.0)
	{
		konstantni_hodnota = 1.0 - x;
		citatel = -konstantni_hodnota;
		
		// Vrati navratovou hodnotu volane funkce.
		return vypocti_taylor_log(konstantni_hodnota, citatel, n);
	}
	else
	{
		konstantni_hodnota = (x - 1.0) / x;
		citatel = konstantni_hodnota;
		
		return vypocti_taylor_log(konstantni_hodnota, citatel, n);
	}
}


/**
 * Samotna implementace vypoctu umocneni taylorovym polynomem. Jako parametry prijima konstantni hodnotu a pocet iteraci.
 */
double vypocti_umocneni(double konstantni_hodnota, unsigned int n)
{
	double vysledek = 0.0;
	double iterace = 1.0;	// promenna uchovavajici vzdy hodnotu prave jednoho prvku v taylorove polynomu (tedy hodnota, o kterou se zmeni vysledek s kazdou iteraci)

	for(unsigned int i = 1; i <= n; i++)
	{
		// Do vysledku postupne pricitame hodnoty jednotlivych prvku taylorova polynomu.
		vysledek += iterace;

		// Dany prvek vypocitame vzdy pronasobenim predchazejiciho prvku konstantni hodnotou (simuluje umocneni v citateli) a vydelenim postupne se zvetsujicim cislem (simuluje faktorial).
		iterace *= konstantni_hodnota / i;
	}

	return vysledek;
}


/**
 * Funkce pro vypocet umocneni cisla taylorovym polynomem, ve kterem je pro vypocet logaritmu volana funkce, ktera logaritmus pocita pomoci taylorova polynomu.	
 * Jako parametry prijima umocnovane cislo, mocninu a pocet iteraci.
 */				
double taylor_pow(double x, double y, unsigned int n)
{
	double konstantni_hodnota = y * taylor_log(x, n);	// Promenna, ktera si v ramci vypoctu uchovava stale stejnou hodnotu.

	return vypocti_umocneni(konstantni_hodnota, n);
}


/**
 * Funkce pro vypocet umocneni cisla taylorovym polynomem, ve kterem je pro vypocet logartmu volana funkce, ktera logaritmus pocita pomoci zretezenych zlomku.
 * Jako parametry prijima umocnovane cislo, mocninu a pocet iteraci.
 */
double taylorcf_pow(double x, double y, unsigned int n)
{
	double konstantni_hodnota = y * cfrac_log(x, n);	// Promenna, ktera si v ramci vypoctu uchovava stale stejnou hodnotu.

	return vypocti_umocneni(konstantni_hodnota, n);
}