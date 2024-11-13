/**
 * tredje oblig i PROG1001, grunnleggende programmering.
 * 
 * 
 * @file oblig_3
 * @date 08.10.24
 * @author Sverre Mæhlum
 */


#include <stdio.h>
#include <stdbool.h> // booleans
#include <ctype.h> // toupper
#include <string.h> // strlen

#define STRLEN 80 ///< Tekstlengde
const int ANTAAR = 10; ///< Antall år lagret i arrayen.

void fyllInnAarstall(int aar[], const int n, const int min, const int max);
char lesKommando();
int lesTall(const char tekst[], const int min, const int max);
void lesTekst(const char ledetekst[], char tekst[]); 
bool sjekkForDuplikat(int arr[], const int aarstall, const int grense);
void skrivMeny(); 
void skrivTekstUtenVokaler(const char tekst[]); 
void valgAar(int aar[], const int n); 
bool gTomArray = true; ///< Om fortsatt ingen årstall lest inn
/**
 * hovedprogrammet
 */
int main(){
    char kommando;
    char teksten[STRLEN] = "";
    int aarstall[ANTAAR];

    skrivMeny();
    kommando = lesKommando();

    while (kommando != 'Q') {
        switch (kommando) {
        case 'F': fyllInnAarstall(aarstall, ANTAAR, 1961, 2030); break;
        case 'V': valgAar(aarstall, ANTAAR); break;
        case 'L': lesTekst("Skriv inn en tekst", teksten); break;
        case 'T': skrivTekstUtenVokaler(teksten); break;
        default: skrivMeny(); break;
        }
    kommando = lesKommando();
    }   
    return 0;
}
/**
 * leser in brukerens input
 */
char lesKommando(){
    char input;
    printf("skriv in meny valg: ");
    scanf("%c", &input); fflush(stdin);
    return toupper(input);
}
/**
 * sjekker for om et tall allerede eksisterer i en array
 * og returnerer en tilsvarende bool
 * 
 * @param arr   - arrayen vi ser etter duplikat i
 * @param aarstall  - årstallet vi ser etter en duplikat til
 * @param grense    - hvor mange år i arr den søker gjennom
 */
bool sjekkForDuplikat(int arr[], const int aarstall, const int grense){
    bool duplikat = false;
    for (int i = 0; i < grense; i++)
    {
        if (arr[i] == aarstall)
        {
            duplikat = true;
        }
    }
    return duplikat; 
}

/**
 * bruker fyller inn alle årstall. Funksjonen sier ifra
 * dersom årstallet allerede eksisterer i arrayen
 * 
 * @param aar   - array hvor årstallene blir lagt til
 * @param n     - hvor mange årstall som skal legges til
 * @param min   - min årstall til godkjent interval
 * @param max   - max årstall til godkjent interval
 */
void fyllInnAarstall(int aar[], const int n, const int min, const int max) {
    for (int i = 0; i < n; i++)
    {
        int aarstall = lesTall("tast in årstall: ", min, max);
        if (sjekkForDuplikat(aar, aarstall, n))
        {
            printf("%i er allerede et element i arrayen\n", aarstall);
        }else{
            aar[i] = aarstall;
            gTomArray = false;
        }
    }
}

/**
 * finner alle valg år lagt in i aar[] av bruker tidligere
 * skiller mellom stortingsvalg og kommunevalg
 * 
 * @param aar   - array med årstall bruker har lagt til tidligere
 * @param n     - antall antall årstall koden må se gjennom
 */
void valgAar(int aar[], const int n){
    //to arrayer som skal ta vare på hvilke år som er valg år
    int stortingsValg[20] = {1961};
    int kommuneValg[20] = {1963};

    if (gTomArray == false) //sjekker om bruker har lagt til årstall ennå
    {
        //skriver opp de neste 20 stortingsvalg og kommunevalg.
        for (int i = 1; i < 20; i++)
        {
            stortingsValg[i] = stortingsValg[i-1]+4;
            kommuneValg[i] = kommuneValg[i-1]+4;
        }
        // skriver ut de årene som er stortingsvalg eller kommunevalg.
        for (int i = 0; i < n; i++) //i representer år i array
        {
            for (int j = 0; j < n/4; j++) //j representerer valgår
            {
                if (aar[i] == stortingsValg[j])
                {
                printf("%i er det stortings valg\n", aar[i]);
                }else if (aar[i] == kommuneValg[j])
                {
                 printf("%i er det kommune valg\n", aar[i]);  
                }
            } 
        }
    }else{
        printf("ingen årstall i array.\n");
    }     
}

/**
 * skriver ut en tekst uten vokaler
 * 
 * @param tekst     - teksten der vokaler skal fjernes
 */
void skrivTekstUtenVokaler(const char tekst[]){
    //finner lengden til teksten. Dette er så mange ganger looped skal kjøre.
    for (int i = 0; i < strlen(tekst); i++)
    {
        //ser etter en vokal i tekst[i]
        char n;
        n = toupper(tekst[i]);
        if (n == 'A'||n == 'E'||n == 'I'||n == 'O'||n == 'U'||n == 'Y')
        {
            //vokal funnet, gjør ingenting
        }else{
            //vokal ikke funnet, skriver ut bokstav
            printf("%c", tekst[i]);
        }
    }
    

}

/**
 * leser inn et tall som bruker taster inn. Tallet må være innenfor min og max,
 * hvis ikke så spør funksjon på nytt.
 * 
 * @param tekst     - en tekst til brukeren om hva brukeren skal taste inn
 * @param min       - minimum verdien bruker kan taste inn
 * @param max       - maksimum verdien en bruker kan taste inn
 */
int lesTall(const char tekst[], const int min, const int max)  {
   int tall;
   do  {
     printf("\t%s (%i-%i):  ", tekst, min, max);
     scanf("%i", &tall);     getchar();
   } while (tall < min  ||  tall > max);
   return tall;
}

/**
 * skriver ut menyvalgene brukeren har
 */
void skrivMeny(){
    printf("Menyvalg:\n");
    printf("\tF - fyll inn årstall\n");
    printf("\tV - valg år\n");
    printf("\tL - Les tekst\n");
    printf("\tT - Skriv tekst uten vokaler\n");
    printf("\tQ - Avslutt programmet\n");
}

/**
 * leser inn en tekst som brukeren har skrevet inn
 * 
 * @param ledetekst - instrukser til hva brukeren skal taste inn
 * @param tekst     - hvor teksten skrives inn
 */
void lesTekst(const char ledetekst[], char tekst[])  {
  printf("\t%s:  ", ledetekst);
  fgets(tekst, STRLEN, stdin); //  Oppdaterer ORIGINALEN/aktuell parameter.
}
