/**
 * Andre oblig i PROG1001, grunnleggende programmering.
 * 
 * tanken er at programmet skal brukes av kino ansatte til å registrere 
 * nye filmer og selge billetter til disse filmene og til slutt se 
 * totalt antall solgte billetter
 * 
 * @file oblig_2
 * @date 26.09.24
 * @author Sverre Mæhlum
 */

#include <stdio.h>  // printf, scanf
#include <ctype.h> // toupper
#include <string.h> // strcspn

const int MAXANTALL = 10;   ///< Maks antall filmer
const int STRLEN = 40;  ///< Maks tekstlengde

int main(){

    char filmTittel[MAXANTALL][STRLEN]; // Filmenes titler
    char menyValg;  // Brukeren valg (S, L, B, Q)
    int filmLengde[MAXANTALL];  // Filmenes lengde i minutter
    int sal[MAXANTALL]; // Salene filmene går
    int billetterSolgt[MAXANTALL];  // Antall billetter solgt
    int antFilmer = 0; // Totalt antall filmer registrert
    int billettAntall; // Antall billetter solgt til en film
    int filmValg; // Ønsket filmnr for billettsalg
    int minutter; // midlertidig lagring for filmLengde[i] % 60, til utskrift
    int timer; // midlertidig lagring for filmLengde [i] / 60, til utskrift

    //stopper programmet dersom bruker skriver q eller Q i menyvalg.
    while(menyValg != 'Q'){
        //skriver ut menyvalgene
        printf("Menyvalg:\n");
        printf("\tS - Se filmer\n");
        printf("\tL - Legg til ny film\n");
        printf("\tB - Selge en eller flere billetter til en film\n");
        printf("\tQ - Avslutt\n");
        printf("Valg: ");

        //bruker taster inn menyvalg, og små bokstaver blir gjort om til store.
        scanf("%c", &menyValg); fflush(stdin);
        menyValg = toupper(menyValg); 

        switch (menyValg)
        {
        case 'S': // S - skriver ut alle registrerte filmer
            printf("\tRegistrerte filmer:\n");
            for (int i = 0; i < antFilmer; i++)
            {
                //regner ut timer og minutter individuelt
                timer = filmLengde[i] / 60;
                minutter = filmLengde[i] % 60;

                //skriver ut tid, sal og tittel på filmen
                printf("\t\t%i: %i time(r) og %i minutt(er) Sal: %i %s", i+1, timer, minutter, sal[i], filmTittel[i]);
            }
    
            break;
        case 'L': //L - Legg til ny film
            //bruker skriver inn tittel, tid, og sal til en ny film
            printf("\tTittel: ");
            fgets(filmTittel[antFilmer], STRLEN, stdin);
            printf("\tTid i min: ");
            scanf("%i", &filmLengde[antFilmer]); fflush(stdin);
            printf("\tSal: ");
            scanf("%i", &sal[antFilmer]); fflush(stdin);
            printf("\t\tFilm lagt til.\n");
            billetterSolgt[antFilmer] = 0; // setter antall billeterSolgt til 0
            antFilmer++; //øker antfilmer med 1

            break;
        case 'B': // B - Selge en eller flere billetter til en film
            //sjekker om det er noen registrerte filmer
            if (antFilmer != 0)
            {
                //resetter filmValg
                filmValg = 0;
                //do løkke som spør om filmvalg og tar kun imot gyldig svar
                do {
                    printf("\tHvilken film vil du selge billetter til (1-%i)?:", antFilmer);
                    scanf("%i", &filmValg); fflush(stdin);
                }while(filmValg < 1 || filmValg > antFilmer);

                //spør bruker hvor mange billetter de vil kjøpe
                printf("\tHvor mange billetter vil du selge?:");
                scanf("%i", &billettAntall); fflush(stdin); 

                //justerer antall billetter solgt til riktig mengde
                billetterSolgt[filmValg-1] = billetterSolgt[filmValg-1] + billettAntall; 
                printf("\t\tBillett(er) solgt.\n");
            }else{
                printf("\tIngen registrerte filmer.\n");
            }
            
            break;
        case 'Q': //avslutter programmet ved å vise totalt solgte billeter
            printf("\tBilletter solgt:\n");
            for (int i = 0; i < antFilmer; i++)
            {
                //sletter "newline" lagret i filmTittel[i]
                if (filmTittel[i][strcspn(filmTittel[i], "\n")] == '\n')
                {
                    filmTittel[i][strcspn(filmTittel[i], "\n")] = '\0';
                }
                //skriver ut navn på film og solgte billetter
                printf("\t\t%s, Solgt: %i\n", filmTittel[i], billetterSolgt[i]);
            }
            
            break;
        default:
            printf("\tugyldig input\n");
            break;
        }
    }
    return 0;
}