/**
 * første Oblig i PROG1001, grunnleggende programmering.
 * 
 * @file oblig_1
 * @date 05.09.24
 * @author Sverre Mæhlum
 */


#include <stdio.h> // gir tilgang til printf og scanf
#define STRLEN 40

int main() {

    // skaper nødvendige variabler og legger til verdiene gitt i oppgaveteksten
    int antallTestede[31] = {30, 50};
    int antallSmittede[31] = {2, 10};
    char skoleNavn[STRLEN];
    int totaltTestede;
    int totaltSmittede;
    float smitteProsent;

    //spør bruker om navn på skolen
    printf("Navn på Skolen: ");
    fgets(skoleNavn, STRLEN, stdin);

    //skriver ut Skole: %s(navn på skole)
    printf("\nSkole : %s\n", skoleNavn);
    //skriver ut antall testede og antall smittede for dag 1 og 2
    printf("Dag 1: %i, %i\n", antallTestede[0], antallSmittede[0]);
    printf("Dag 2: %i, %i\n\n", antallTestede[1], antallSmittede[1]);

    //spør bruker om antall nye testede på dag 3
    printf("Antall nye testede dag 3: ");
    scanf("%i", &antallTestede[2]);
    //spør bruker om antall nye postitive på dag 3
    printf("Antall nye smittede dag 3: ");
    scanf("%i", &antallSmittede[2]);

    //skriver ut Skole: %s(navn på skole)
    printf("\nSkole: %s\n", skoleNavn);
    //skriver ut antall testede og smittede for dag 1, 2 og 3
    printf("Dag 1: %i, %i\n", antallTestede[0], antallSmittede[0]);
    printf("Dag 2: %i, %i\n", antallTestede[1], antallSmittede[1]);
    printf("Dag 2: %i, %i\n\n", antallTestede[2], antallSmittede[2]);

    //skriver ut totalt antall testede 
    totaltTestede = antallTestede[0] + antallTestede[1] + antallTestede[2];
    printf("Totalt antall testede: %i\n", totaltTestede);

    //skriver ut totalt antall smittede
    totaltSmittede = antallSmittede[0] + antallSmittede[1] + antallSmittede[2];
    printf("Totalt antall smittede: %i\n", totaltSmittede);

    // skriver ut smitteprosenten (totalt smittede / antall testede * 100)
    smitteProsent = (float)totaltSmittede / (float)totaltTestede * 100.0;
    printf("Smitteprosenten ligger på: %f %%\n", smitteProsent);

    return 0; // slutt
}