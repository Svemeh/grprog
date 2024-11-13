/**
 *  Skjelett/grunnlag for oblig nr 4 i GrProg, høsten 2024.
 *
 *  @author Karianne Kjønås
 *  @author Sondre Gunneng
 *  @author FrodeH
 * 
 * oblig utført av
 * 
 * @author Sverre Mæhlum
 * @file oblig_4
 * 
 */


#include <stdio.h>              //  printf, scanf
#include <ctype.h>              //  toupper
#include <stdlib.h>             //  sizeof, malloc, free
#include <string.h>             //  strlen, strcpy, strcmp
#include <stdbool.h>            //  bool
#include "LesData.h"            //  Verktøykasse for lesing av diverse data


#define   MAXLAG      10		///<  Max antall lag
#define   MAXKAMPER  100		///<  Max antall kamper
const int MAXMAAL  =  20;       ///<  Max antall mål
const int STRLEN   =  80;    	///<  Max.tekstlengde.


/**
 *  Lag (med navn, mål scoret, mål sluppet inn og totale poeng).
 */
struct Lag {
    char *navn;
    int  maalScoret,
         maalSluppetInn,
         poeng;
};


/**
 *  Kamp (med to lag som spiller, mål for hver av lagene,
 *        og sjekk på om kampen er ferdigspilt).
 */
struct Kamp {
    struct Lag *lag1, *lag2;
    int  maalLag1,
         maalLag2;
    bool ferdig;
};


struct Lag* finnLag(const char* navn);
void frigiAllokertMemory();
bool kampFerdig(const struct Kamp* kamp);
void kampLesData(struct Kamp* kamp);
void kampRegistrerResultat(struct Kamp* kamp);
void kampSkrivData(const struct Kamp* kamp);
void kampSlettResultat(struct Kamp* kamp);
void lagFjernPoeng(struct Lag* lag, const int scoret, const int inn);
void lagGiPoeng(struct Lag* lag, const int scoret, const int inn);
void lagLesData(struct Lag* lag, char* navn);
void lagSkrivData(const struct Lag* lag);
void lagSkrivNavn(const struct Lag* lag);
void lagSlettData(struct Lag* lag);
void nyKamp();
void nyttLag();
void registrerResultat();
void skrivAlleLag();
void skrivKamper();
void skrivMeny();
void slettResultat();


struct Lag* gLagene[MAXLAG];         ///<    Lagene i oversikten.
int gAntallLag = 0;                  ///<    Antall lag hittil.
struct Kamp* gKampene[MAXKAMPER];    ///<    Kampene i oversikten.
int gAntallKamper = 0;               ///<    Antall kamper hittil.


/**
 *  Hovedporgrammet:
 */
int main () {
    char kommando;

    skrivMeny();
    kommando = lesChar("\nKommando");

    while (kommando != 'Q')  {
      switch (kommando)  {
        case 'K': nyKamp();                break;
        case 'L': nyttLag();               break;
        case 'R': registrerResultat();     break;
        case 'A': skrivAlleLag();          break;
        case 'S': skrivKamper();           break;
        case 'F': slettResultat();         break;
        default:  skrivMeny();             break;
      }
      kommando = lesChar("\nKommando");
    }

    frigiAllokertMemory();

    return 0;
}


//*************************************************************************

/**
 *    Går igjennom 'gLagene' og sjekker om 'navn' allerede eksisterer.
 *
 *    @param    navn  -  Et lagnavn
 *    @return   Peker til aktuelt Lag eller NULL (om ikke funnet)
 */
struct Lag* finnLag(const char* navn) {
    for(int i = 0; i < gAntallLag; i++)       //  Går gjennom alle lagene:
        if( !strcmp(gLagene[i]->navn, navn))  //  Matchende navn?
            return gLagene[i];                //  Ja: returnerer lag-peker.

    return NULL;                              //  Ingen matchende lag funnet.
}


/**
 *  Frigir all allokert memory fra programmets kjøretid.
 */
void frigiAllokertMemory() {
    int i;

    for(i = 0; i < gAntallLag; i++) {   //  Går igjennom ALLE lagene:
        lagSlettData(gLagene[i]);       //  'Lag' frigir sine allokerte data.
        free(gLagene[i]);               //  Sletter HELE laget.
    }

    for(i = 0; i < gAntallKamper; i++)  //  Går igjennom ALLE kampene:
        free(gKampene[i]);              //  Sletter HELE kampen.
}


/**
 *  Returnerer om 'kamp' er ferdigspilt.
 *
 *  @param    kamp  -  Kampen som sjekkes for status om ferdigspilt eller ei
 *  @return   Om kampen er ferdigspilt eller ei
 */
bool kampFerdig(const struct Kamp* kamp) {
    if (kamp->ferdig == false)
    {
        return false;
    } else {
        return true;
    }
}


/**
 *  Leser inn deltagerlagene til 'kamp'
 *
 *  @param   kamp  -  Aktuell kamp å oppdatere
 *  @see     finnLag(...)
 */
void kampLesData(struct Kamp* kamp) {

// Leser inn lag 1
    char buffer[STRLEN];
    do {
        lesText("skriv inn lag nummer en", buffer, STRLEN);
    } while (finnLag(buffer) == NULL);
    gKampene[gAntallKamper]->lag1 = finnLag(buffer);

    // Leser inn lag 2 
    do {
            lesText("skriv inn lag nummer to", buffer, STRLEN);
    } while (finnLag(buffer) == NULL);
    gKampene[gAntallKamper]->lag2 = finnLag(buffer);

    // Nullstiller/klargjør all relevant data
    gKampene[gAntallKamper]->maalLag1 = 0;
    gKampene[gAntallKamper]->maalLag2 = 0;
    gKampene[gAntallKamper]->ferdig = false;
}


/**
 *  Registrerer resultatet på en kamp.
 *
 *  @param   kamp  -  Kampen som skal få sitt resultat innlagt
 *  @see     lagGiPoeng(...)
 */
void kampRegistrerResultat(struct Kamp* kamp) {
    // Sjekker om kampen er ferdig spilt allerede
    if (kamp->ferdig == true) {
        printf("Kampen er ferdig spilt.\n");
        return;
    }

    // Skriver opp antall mål begge lag fikk
    lagSkrivNavn(kamp->lag1);
    kamp->maalLag1 = lesInt("\tMål scoret:", 0, 10);
    lagSkrivNavn(kamp->lag2);
    kamp->maalLag2 = lesInt("\tMål Scoret:", 0, 10);

    // Utdeler poeng og oppdaterer mål scoret og sluppet inn på lag struct
    lagGiPoeng(kamp->lag1, kamp->maalLag1, kamp->maalLag2);
    lagGiPoeng(kamp->lag2, kamp->maalLag2, kamp->maalLag1);
    
    // Skriver ut kamp data til bruker
    kampSkrivData(kamp);

    // Registrerer kamp som ferdig spilt
    kamp->ferdig = true;
}


/**
 *  Skriver ut all data om en kamp.
 *
 *  @param   kamp  -  Kampen som skrives ut på skjermen
 *  @see     lagSkrivNavn(...)
 */
void kampSkrivData(const struct Kamp* kamp) {
    printf("\n");
    lagSkrivNavn(kamp->lag1);
    printf(" %i", kamp->maalLag1);
    printf(" VS ");
    printf("%i ", kamp->maalLag2);
    lagSkrivNavn(kamp->lag2);
    printf("\n");
}


/**
 *  Sletter resultatet for en kamp.
 *
 *  @param   kamp  -  Kampen som får slettes/nukkstilt sitt resultat
 *  @see     lagFjernPoeng(...)
 */
void kampSlettResultat(struct Kamp* kamp) {
    // Sjekker om kampen er ferdig spilt
    if (kamp->ferdig == false) {
        printf("Kamp er ikke ferdig spilt.\n");
        return;
    }
    // Fjerner poeng og oppdaterer lag statestikk
    lagFjernPoeng(kamp->lag1, kamp->maalLag1, kamp->maalLag2);
    lagFjernPoeng(kamp->lag2, kamp->maalLag2, kamp->maalLag1);

    // Kampen blir satt til uferdig igjen
    kamp->ferdig = false;
}


/**
 *  Fjerner poengene til et gitt lag.
 *
 * @param   lag     -  Laget som evt får sine poeng redusert
 * @param   scoret  -  Antall mål scoret
 * @param   inn     -  Antall mål sluppet inn
 */
void lagFjernPoeng(struct Lag* lag, const int scoret, const int inn) {
    // Fjerner poeng utdelt fra kampen
    if (scoret == inn) 
    {
        lag->poeng = lag->poeng - 1;
    } else if (scoret > inn) 
    {
        lag->poeng = lag->poeng - 3;
    }

    // Oppdaterer mål statestikk på lag struct
    lag->maalScoret = lag->maalScoret - scoret;
    lag->maalSluppetInn = lag->maalSluppetInn - inn;
}


/**
 *  Gir poeng til et gitt lag. Samt oppdaterer mål statestikk på lag struct
 *
 * @param   lag     -  Laget evt får poeng
 * @param   scoret  -  Antall mål scoret
 * @param   inn     -  Antall mål sluppet inn
 */
void lagGiPoeng(struct Lag* lag, const int scoret, const int inn) {

    // Utdeler poeng, Seier blir tre poeng, Uavgjort blir ett poeng, tap er null
    if (scoret == inn) 
    {
        lag->poeng = lag->poeng + 1;
    } else if (scoret > inn) 
    {
        lag->poeng = lag->poeng + 3;
    }

    // Oppdaterer mål statestikk
    lag->maalScoret = lag->maalScoret + scoret;
    lag->maalSluppetInn = lag->maalSluppetInn + inn;
}


/**
 *  Lagets navn oppdateres, og initialiserer/nullstiller andre datamedlemmer.
 *
 * @param   lag   -  Laget som oppdateres
 * @param   navn  -  Lagets allerede innleste navn
 */
void lagLesData(struct Lag* lag, char* navn) {
    lag->navn = strdup(navn); // strdup for at minnnet tildeles og lagrer navnet
    lag->maalScoret = 0;
    lag->maalSluppetInn = 0;
    lag->poeng = 0;
}


/**
 *  Skriver data for et lag ut på skjermen.
 *
 *  @param   lag  -  Laget som skrives ut
 */
void lagSkrivData(const struct Lag* lag) {
    printf("\nNavn:   %s\n", lag->navn);
    printf("Målscoret:  %i\n", lag->maalScoret);
    printf("Mål Sluppet inn:    %i\n", lag->maalSluppetInn);
    printf("Poeng:  %i\n", lag->poeng);
}


/**
 *  Skriver ut navnet til et lag på skjermen.
 *
 *  @param   lag  -  Laget som får skrevet sitt navn
 */
void lagSkrivNavn(const struct Lag* lag) {
    printf("%s", lag->navn);
}


/**
 *  Frigjør allokert memory ifm et lags navn.
 *
 *  @param   lag  -  Laget som frigir allokert memory for sitt navn
 */
void lagSlettData(struct Lag* lag) {
    free(lag->navn);
}


/**
 *  Legger (om mulig) inn en ny kamp i datastrukturen.
 *
 *  @see  kampLesData(...)
 */
void nyKamp () {
    // Sjekker om det er plass til flere kamper
    if (gAntallKamper >= MAXKAMPER) {
        printf("Maksimum antall kamper registrert.\n");
        return;
    } else {
        // Sjekker om det er minst 2 lag
        if (gAntallLag <= 1) {
            printf("ikke nok lag er registrert for å registrere en ny kamp");
            return;
        } else {

            // Allokerer riktig mengde minne til gKamper[...]
            gKampene[gAntallKamper] = (struct Kamp*)malloc(sizeof(struct Kamp));
            if (gKampene[gAntallKamper] == NULL) {
                printf("Feil ved allokering av minne.\n");
                return;
            } 

            // Initialsierer kampen
            kampLesData(gKampene[gAntallKamper]);
            
            // Skriver ut kamp informasjon 
            printf("Kamp nummer %i registrert\n", gAntallKamper + 1);
            printf("Kamp:   %s VS %s\n",
                gKampene[gAntallKamper]->lag1->navn,
                gKampene[gAntallKamper]->lag2->navn);

            // Øker antall kamper med 1
            gAntallKamper++;
        }
    }
}


/**
 *  Legger (om mulig) inn et nytt lag i datastrukturen.
 *
 * @see   finnLag(...)
 * @see   lagLesData(...)
 * 
 */
void nyttLag() {
    // Sjekker om det er plass til flere lag
    if (gAntallLag >= MAXLAG) {
        printf("Maksimum antall lag registrert.\n");
        return;

    } else {

        // Leser inn lagnavn i char arrayen "buffer"
        char buffer[STRLEN]; 
        lesText("Lagnavn", buffer, STRLEN); 
        
        // Sjekker at lagnavn ikke allerede er i bruk.
        if (finnLag(buffer))
        {
            printf("Laget du forsøker å legge til eksisterer allerede\n");
            return;
        
        } else {

            // Allokerer riktig mengde minne til gLagene[...]
            gLagene[gAntallLag] = (struct Lag*)malloc(sizeof(struct Lag)); 
            if (gLagene[gAntallLag] == NULL) {
                printf("Feil ved allokering av minne.\n");
                return;
            }
            
            // initialiserer laget med navnet gitt i @buffer
            lagLesData(gLagene[gAntallLag], buffer);

            //skriver ut lag navn og hvilken array nummer den er lagret i
            printf("Laget %s er registrert som lag %i\n",
                     gLagene[gAntallLag]->navn, gAntallLag + 1);

            // øker antall lag med 1
            gAntallLag++; 
        }
    }
}


/**
 *  Registrerer resultatet for en kamp.
 *
 *  @see  registrerKampResultat(...)
 */
void registrerResultat() {
    if (gAntallKamper == 0) {
        printf("Ingen kamper er registrert.\n");
        return;
    }
    // Bruker velger kamp
    int Tall = 0;
    Tall = lesInt("Kamp nummer:", 1, gAntallKamper);

    // Registrer resultatet av kamp
    kampRegistrerResultat(gKampene[Tall-1]);
}


/**
 *  Skriver alle lagene ut på skjermen.
 *
 *  @see  lagSkrivData(...)
 */
void skrivAlleLag() {
    // Sjekker at minst et lag er registrert
    if (gAntallLag == 0)
    {
        printf("Ingen lag registrert.\n");
        return;
    }
    // For alle lag registrert -> skriv ut lag data
    for (int i = 0; i < gAntallLag; i++) {
        lagSkrivData(gLagene[i]);
    }
}


/**
 *  Skriver ut på skjermen alle kamper som har et resultat registrert.
 *
 *  @see  ferdigKamp(...)
 *  @see  kampSkrivData(...)
 */
void skrivKamper() {
    // Sjekker om noen kamper har blitt registrert
    if (gAntallKamper == 0)
    {
        printf("Ingen kamper har blitt registrert.\n");
        return;
    } 
    // for alle kamper som er ferdig spilt -> skriv ut kamp data
    for (int i = 0; i < gAntallKamper; i++) {
        if (kampFerdig(gKampene[i]))
        {
            kampSkrivData(gKampene[i]);
        }
    }
}


/**
 *  Skriver programmets menyvalg/muligheter paa skjermen.
 */
void skrivMeny() {
    printf("\nFølgende kommandoer er tilgjengelig:\n");
    printf("K - Registrer ny (K)amp\n");
    printf("L - Registrer nytt (L)ag\n");
    printf("A - Skriv ut (A)lle lag\n");
    printf("S - (S)kriv ut alle ferdigspilte kamper\n");
    printf("R - (R)egistrer resultat i en kamp\n");
    printf("F - (F)jern resultat til en kamp\n");
    printf("Q - (Q)uit/avslutt\n");
}


/**
 *  Slett resultatet for en gitt kamp.
 *
 * @see  kampSlettResultat(...)
 */
void slettResultat() {
    if (gAntallKamper == 0) {
        printf("Ingen kamper er registrert.\n");
        return;
    }
    // Bruker velger kamp
    int Tall = 0;
    Tall = lesInt("Kamp nummer:", 1, gAntallKamper);

    // sletter resultat fra valgt kamp
    kampSlettResultat(gKampene[Tall-1]);
}
