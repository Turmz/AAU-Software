/**
 *
 * ----------------------------------------------
 * EXAM: Imperative Programming (IMPR) (DAT1, SW1, IxD3) - AAL
 * ----------------------------------------------
 * Student ID: ..... Sigvardsen_Tummas_20164825
 * Name: ........... Tummas Jóhan Sigvardsen
 * Email: .......... tsgiva16@students.aau.dk
 * Study: .......... Interaktionsdesign
 * Student number: . 20164825
 * ----------------------------------------------
 *
 **/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_EVENT_CHARACTERS 30
#define MAX_NAME_CHARACTERS 30
#define MAX_TEAM_CHARACTERS 4
#define MAX_NATION_CHARACTERS 4
#define MAX_POSITION_CHARACTERS 4
#define MAX_TIME 10
 
 
typedef struct race
{
    char event[MAX_EVENT_CHARACTERS];
    char firstName[MAX_NAME_CHARACTERS];
    char lastName[MAX_NAME_CHARACTERS];
    int age;
    char team[MAX_TEAM_CHARACTERS];
    char nation[MAX_NATION_CHARACTERS];
    char position[MAX_POSITION_CHARACTERS];
    char time[MAX_TIME];
}race;
 
typedef struct contestant
{
    char firstName[MAX_NAME_CHARACTERS];
    char lastName[MAX_NAME_CHARACTERS];
    int age;
    char team[MAX_TEAM_CHARACTERS];
    char nation[MAX_TEAM_CHARACTERS];
    int points;
}contestant;
 
/* Prototypes */
void printToTerminal(race*, int, contestant*, contestant*, char*, char*);
void clearScreen();
int lines_counter(void);
int readFile(race* allResults);
void fillInContestantStruct(race*, int, contestant*);
void pointsOne(race*, int, contestant*);
void pointsTwo(race*, int, contestant*);
void pointsThree(race*, int, contestant*);
/* Assignment 1 */
void contestantsFromBelgiumUnder23(race*, int);
/* Assignment 2 */
int checkIfDuplicate(contestant*, char*, char*, int);
void contestantsFromDenmark(race*, int, contestant*, contestant*);
int sortTeamsOfDanishContestants(const void *a, const void *b);
int sortNamesOfDanishContestants(contestant*, contestant*);
/* Assignment 3 */
void topTenContestants(race*, int, contestant*);
void sortTopTenContestants(contestant*, int);
int compareTopTenContestants(const void *c, const void *d);
/* Assignment 4 */
void mostOTLDNFperEvent(race*, int , char*, char*);

/* Main funtion */
int main(int argc, char const *argv[])
{
    int lines_in_file = lines_counter();

    race allResults[lines_in_file];
    contestant allContestants[lines_in_file];
    contestant danishContestants[lines_in_file];
    char mostOTLandDNF[MAX_EVENT_CHARACTERS];
    char event [MAX_EVENT_CHARACTERS];
    int amountOfResults = readFile(allResults);
    fillInContestantStruct(allResults, amountOfResults, allContestants);

    /* Prints all results, if "--print" is before the program in terminal.*/
    if(argc == 2 && strcmp(argv[1], "--print") == 0){
        contestantsFromBelgiumUnder23(allResults, amountOfResults);
        printf(" \n");        
        contestantsFromDenmark(allResults, amountOfResults, allContestants, danishContestants);
        printf(" \n");  
        topTenContestants(allResults, amountOfResults, allContestants);
        printf(" \n");  
        mostOTLDNFperEvent(allResults, amountOfResults, event, mostOTLandDNF);
        printf(" \n");  
        printf("Opgave 5 ikke lavet.\n");
        printf("Opgave 6 ikke lavet.\n");
        getchar();
    }
    else{
        printf("");
    }

    /* Assignments where individual points were established. */
    pointsOne(allResults, amountOfResults, allContestants);
    pointsTwo(allResults, amountOfResults, allContestants);
    pointsThree(allResults, amountOfResults, allContestants);
    
    /* Menu system for the assignments. */
    int userInput();    
    int input = 1;
        printf("Hej og velkommen. Dette program er lavet\n");
        printf("af Tummas Johan Sigvardsen. Studienr. 20164825.\n");
    while(input){
    input = userInput();
        switch(input)
        {
        case 1:
            clearScreen();
            printf("---------------------------------------------- \n");
            printf("OPGAVE 1: \n");
            printf("--------------------------------------------- \n");
            printf("Find og udskriv loebsresultaterne for\n");
            printf("alle belgiske cykelryttere under 23 aar. \n");
            printf("I denne opgave er det OK at lave en funktion\n");
            printf("som blot printer resultaterne direkte.\n");
            printf("---------------------------------------------- \n");    
            printf("RESULTAT:\n"); 
            printf("---------------------------------------------- \n"); 
            contestantsFromBelgiumUnder23(allResults, amountOfResults);
            printf("---------------------------------------------- \n \n");
            printf("  \n");
            break;

        case 2:
            clearScreen();
            printf("---------------------------------------------- \n");
            printf("OPGAVE 2: \n");
            printf("--------------------------------------------- \n");
            printf("Find og udskriv alle de danske ryttere,\n");
            printf("som har deltaget i et eller flere af de fire \n");
            printf("cykelloeb.\n");
            printf("Sorter primaert disse efter de hold som de\n");
            printf("koerer paa. Hvis der er to danske ryttere paa\n");
            printf("samme hold, sorteres de sekundaert alfabetisk\n");
            printf("efter fornavn. Ogsaa i denne opgave er det OK\n");
            printf("at lave en funktion som blot printer \n");
            printf("resultaterne direkte. \n");  
            printf("---------------------------------------------- \n");    
            printf("RESULTAT:\n"); 
            printf("---------------------------------------------- \n");                 
            contestantsFromDenmark(allResults, amountOfResults, allContestants, danishContestants);
            printf("---------------------------------------------- \n \n");            
            break;

        case 3:
            clearScreen();
            printf("---------------------------------------------- \n");
            printf("OPGAVE 3: \n");
            printf("---------------------------------------------- \n"); 
            printf("Udskriv de 10 ryttere som har opnaaet flest point.\n");
            printf("Sorter primaert rytterne efter antal point.\n");
            printf("Ved pointlighed sorteres efter alder (den yngste foerst).\n");
            printf("Ved alderslighed sorteres alfabetisk efter\n");
            printf("efternavnet. (Efternavnet er den del af rytterens\n");
            printf("navn som er skrevet med udelukkende store bogstaver).\n"); 
            printf("---------------------------------------------- \n");    
            printf("RESULTAT:\n");  
            printf("---------------------------------------------- \n");     
            topTenContestants(allResults, amountOfResults, allContestants);
            printf("---------------------------------------------- \n \n");  
            break;

        case 4:
            clearScreen();
            printf("---------------------------------------------- \n");
            printf("OPGAVE 4: \n");
            printf("---------------------------------------------- \n");    
            printf("Find for hvert af de fire loeb det hold,\n");
            printf("der har flest ryttere med en \n");
            printf("placering angivet som OTL eller DNF.\n");  
            printf("---------------------------------------------- \n");    
            printf("RESULTAT:\n");  
            printf("---------------------------------------------- \n");                
            mostOTLDNFperEvent(allResults, amountOfResults, event, mostOTLandDNF);
            printf("---------------------------------------------- \n \n"); 
            break;

        case 5:
            clearScreen(); 
            printf("---------------------------------------------- \n");
            printf("OPGAVE 5: \n");
            printf("---------------------------------------------- \n");
            printf("Find den nation, der samlet set har begaaet sig\n");
            printf("bedst i de fire cykelloeb. Dette maales efter\n");
            printf("summen af points, som ryttere fra nationen har\n");
            printf("opnaaet i loebene. (Hvis der er pointlighed mellem\n");
            printf("to eller flere nationer, er det op til dig\n");
            printf("at vaelge een af disse).\n");
            printf("---------------------------------------------- \n");    
            printf("RESULTAT:\n");     
            printf("---------------------------------------------- \n");                
            printf("Opgave ikke lavet.\n");
            printf("---------------------------------------------- \n \n"); 
            break;

        case 6:
            clearScreen(); 
            printf("OPGAVE 6: \n");
            printf("---------------------------------------------- \n");
            printf("Find i hvert af de fire cykelloeb mediantiden af \n");
            printf("loebet. Mediantiden M af et bestemt cykelloeb er \n");
            printf("den opnaaede loebstid, hvor halvdelen af\n");
            printf("loebstiderne er mindre end eller lig med M,\n");
            printf("og halvdelen af tiderne er stoerre end eller \n");
            printf("lig med M. Loebsresultater med en placering\n");
            printf("angivet som OTL eller DNF indgaar ikke, naar\n");
            printf("vi beregner mediantiden. Hvis antallet af \n");
            printf("ryttere i et loeb er lige oensker vi at gruppen\n");
            printf("af ryttere med 'en hoej tid' er een mindre end\n");
            printf("gruppen med 'en lav tid', relativ til M). \n");
            printf("---------------------------------------------- \n");    
            printf("RESULTAT:\n");     
            printf("---------------------------------------------- \n");                
            printf("Opgave ikke lavet.\n");
            printf("---------------------------------------------- \n \n"); 
            break;
        
        case 0:
            clearScreen();
            break;

        default:
            clearScreen();
            printf("---------------------------------------------- \n");                
            printf("Valg ikke muligt!!\n");
            printf("---------------------------------------------- \n \n"); 
            }

        }
    return 0;
}

/* Function to print out the text for the menu system. */
int userInput(){
    int choice;
        printf("\n");
        printf("For at bruge menuen nedenfor, skal de skrive tallet\n");
        printf("paa den oenskede opgave. Det vil sige, at foerste\n");
        printf("opgave er markeret som (1), naeste som (2), osv.\n");
        printf("\n");
        printf("|-------------------------------------------------|\n");
        printf("|                                                 |\n");        
        printf("|   Skriv (1) hvis de oensker at se Opgave 1      |\n");
        printf("|   Skriv (2) hvis de oensker at se Opgave 2      |\n");
        printf("|   Skriv (3) hvis de oensker at se Opgave 3      |\n");
        printf("|   Skriv (4) hvis de oensker at se Opgave 4      |\n");
        printf("|   Skriv (5) hvis de oensker at se Opgave 5      |\n");
        printf("|   Skriv (6) hvis de oensker at se Opgave 6      |\n");
        printf("|                                                 |\n"); 
        printf("|   Skriv (0) hvis de oensker lukke programmet.   |\n");
        printf("|                                                 |\n");         
        printf("|-------------------------------------------------|\n");
        printf("\n"); 
        printf("Skriv den opgave de oensker at se: ");
        scanf("%d", &choice);
        printf("\n");
    return choice;
    }
/*Function that clears the terminal. Cls for DOS-systems and clear for UNIX-systems.*/
void clearScreen(){
    system("@cls||clear");
}

/* Function to count lines from file. */
int lines_counter(void){
    FILE *fp = fopen("cykelloeb-2017", "r");
    int countedLines = 0, ch = 0;
    while(!feof(fp)){
        ch = fgetc(fp);
        if(ch == '\n'){
            countedLines++;
        }
    }

    return countedLines;
}


/* Function reads file, and fills "race" struct. */ 
int readFile(race* allResults) {
    int amountOfResults = 0;
    FILE *fp;
    char* filename = "cykelloeb-2017";
 
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
 
    while(!feof(fp)){

    fscanf(fp," %s %*c %s %[^\"]%*c %d %s %s %s %s ",
        allResults[amountOfResults].event,
        allResults[amountOfResults].firstName,
        allResults[amountOfResults].lastName,
        &allResults[amountOfResults].age,
        allResults[amountOfResults].team,
        allResults[amountOfResults].nation,  
        allResults[amountOfResults].position,
        allResults[amountOfResults].time
        );
 
        amountOfResults++;
    }
 
/* Function converts the contestants time from a string to an integer,
 * and the returns it as a string. This is done to prevent problems,
 * if a contestant for example gets the result "DND" and therefore "0" time,
 * and not the standard "XX:XX:XX" format.
 */
    int convertSeconds(char *time){

        int seconds = 0;
        int minutes = 0;
        int hours = 0;

        sscanf(time, " %d:%d:%d", &hours, &minutes, &seconds);

        return (hours * 3600) + (minutes * 60) + seconds;
    } 
    fclose(fp);
 
    return amountOfResults;
}

/* Function reads from "race"-struct and fills "contestant" struct. */ 
void fillInContestantStruct(race *allResults, int amountofResults, contestant *allContestants){
    int i = 0;
    for(i = 0; i < amountofResults; i++) {
        allContestants[i].points = 0;
        strcpy(allContestants[i].firstName, allResults[i].firstName);
        strcpy(allContestants[i].lastName, allResults[i].lastName);
        allContestants[i].age = allResults[i].age;
        strcpy(allContestants[i].team, allResults[i].team);
        strcpy(allContestants[i].nation, allResults[i].nation);
    }
}



/**
* ----------------------------------
*   1. Deltagelse og gennemførelse i et cykelløb (indenfor eller uden for en evt. tidsgrænse) giver 2 point. 
* ----------------------------------
**/
void pointsOne(race* allResults, int amountofResults, contestant* allContestants){

    int comparePosition = 0;
    for(int i = 0; i <= amountofResults; i++){
        if(!(strcmp(allResults[i].position, "DNF") == 0))
        {
            allContestants[i].points += 2;
            comparePosition = atoi(allResults[i].position);
        } 
    }
}

/**
* ----------------------------------
*   2. Hvis man gennemfører cykelløbet uden at overskride løbets tidsgrænse får man (M - P)/17 extra-point,
*      hvor M er antallet af ryttere der har gennemført løbet (inden for tidsgrænsen) og P er rytterens placering i løbet.
* ----------------------------------
**/
void pointsTwo(race* allResults, int amountofResults, contestant* allContestants){

    int countedLines = lines_counter();
    int m = 0; // antallet af ryttere der har gennemført løbet
    for (int i = 0; i < countedLines; i++){
        if (!(strcmp(allResults[i].position, "OTL") == 0 ||
              strcmp(allResults[i].position, "DNF") == 0 ))
        {
            m += 1;
        }   
    } 
    for(int j = 0; j < countedLines; j++){
        allContestants[j].points += (m - atoi(allResults[j].position))/17;

    }
}


/**
* ----------------------------------
*   3. Oven i dette får vinderen af et cykelløb 8 ekstra point, nummer to får 5 ekstra point, og nummer tre får 3 ekstra point.
* ----------------------------------
**/
void pointsThree(race* allResults, int amountofResults, contestant* allContestants){
    int comparePosition = 0;
    
    for(int i = 0; i <= amountofResults; i++){
        comparePosition = atoi(allResults[i].position);

    if(comparePosition == 1) {
        allContestants[i].points += 8;
        }
    if(comparePosition == 2) {
        allContestants[i].points += 5;
        }
    if(comparePosition == 3) {
        allContestants[i].points += 3;
        }
       
    if(strcmp(allResults[i].position, "OTL")){
        printf("");
        }
    }    
}



/**
* ----------------------------------
*   OPGAVE 1:
*   Find og udskriv løbsresultaterne for alle belgiske cykelryttere under 23 år.
*   I denne opgave er det OK at lave en funktion som blot printer resultaterne direkte.
* ----------------------------------
**/
/* Function solves "OPGAVE 1". */
void contestantsFromBelgiumUnder23(race* allResults, int amountofResults){
    int i = 0;
    for(i = 0; i <= amountofResults; i++) {
        if(strcmp(allResults[i].nation, "BEL") == 0 && allResults[i].age < 23){
        printf("%s %s %s %d %s %s %s %s \n",
            allResults[i].event,
            allResults[i].firstName,
            allResults[i].lastName,
            allResults[i].age,
            allResults[i].team,
            allResults[i].nation,  
            allResults[i].position,
            allResults[i].time);    
        }

    else {
        printf("");
    }
    }
}



/**
* ----------------------------------
*   OPGAVE 2:
*   Find og udskriv alle de danske ryttere, som har deltaget i et eller flere af de fire cykelløb.
*   Sorter primært disse efter de hold som de kører på. Hvis der er to danske ryttere på samme hold,
*   sorteres de sekundært alfabetisk efter fornavn. Også i denne opgave er det OK at lave en funktion som
*   blot printer resultaterne direkte.
* ----------------------------------
**/
/* Function checks if there are duplicates in the array */
int checkIfDuplicate(contestant* allContestants, char* contestantFirstName, char* contestantLastName, int count){
    int i;
    for(i = 0; i < count; i++){
         if((strcmp(allContestants[i].firstName, contestantFirstName) == 0) &&
            (strcmp(allContestants[i].lastName, contestantLastName) == 0)){
            return 0;
        }         
    }
    return 1;
}

/* Function solves "OPGAVE 2". */
void contestantsFromDenmark(race* allResults, int amountOfResults, contestant* allContestants, contestant *danishContestants){ 
    int countedLines = lines_counter();
    int i = 0;
    int j = 0;
    for(i; i <= amountOfResults; i++) {
        if(checkIfDuplicate(allContestants, allContestants[i].firstName, allContestants[i].lastName, i)){
            if(strcmp(allResults[i].nation, "DEN") == 0){
                strcpy(danishContestants[j].firstName, allContestants[i].firstName);
                strcpy(danishContestants[j].lastName, allContestants[i].lastName);
                strcpy(danishContestants[j].team, allContestants[i].team);
                strcpy(danishContestants[j].nation, allContestants[i].nation);
                j++;      
            }      
       }
    } 
    qsort(danishContestants, j, sizeof(contestant), sortTeamsOfDanishContestants);
    for(i = 0; i < j; i++) {
            printf("%s %s (%s) %s\n",
            danishContestants[i].firstName,
            danishContestants[i].lastName,
            danishContestants[i].team,
            danishContestants[i].nation);
    }
} 

/* Function sorts the teams */
int sortTeamsOfDanishContestants(const void *a, const void *b){
   contestant *contestant_a = (contestant *)a, *contestant_b = (contestant *)b;
   if(strcmp(contestant_a -> team, contestant_b -> team)){
        return strcmp (contestant_a -> team, contestant_b -> team);
   }
    else {
        return sortNamesOfDanishContestants(contestant_a, contestant_b); 
    }
}

/* Function sorts contestants name */
int sortNamesOfDanishContestants(contestant* contestant_a, contestant* contestant_b){ 
    return strcmp(contestant_a -> firstName, contestant_b -> firstName); 
}



/**
* ----------------------------------
*   OPGAVE 3:
*   Udskriv de 10 ryttere som har opnået flest point. Sorter primært rytterne efter antal point.
*   Ved pointlighed sorteres efter alder (den yngste først). Ved alderslighed sorteres
*   alfabetisk efter efternavnet. (Efternavnet er den del af rytterens navn som er skrevet med udelukkende store bogstaver).
* ----------------------------------
**/
/* Function solves "OPGAVE 3". */
void topTenContestants(race* allResults, int amountofResults, contestant* allContestants){
    int i = 0;
    int j= 0;
    sortTopTenContestants(allContestants, amountofResults);
    for(i = 0; j < 10; i++){
        if (checkIfDuplicate(allContestants, allContestants[i].firstName, allContestants[i].lastName, i)){
            j++;
        printf("%s %s er %d og har %d point.\n",
            allContestants[i].firstName,
            allContestants[i].lastName,
            allContestants[i].age,
            allContestants[i].points);
        }
    }
}

/* Function sorts the top ten contestants */
void sortTopTenContestants(contestant* allContestants, int amountOfResults){
    int i = 0;
    qsort(allContestants, amountOfResults, sizeof(contestant), compareTopTenContestants);
}

/* Function sorts the top ten contestants by age and points*/
int compareTopTenContestants(const void *c, const void *d){
    contestant *contestant_c = (contestant*)c, *contestant_d = (contestant* )d;
    int points = 0, age = 0;

    points = (contestant_d -> points - contestant_c -> points);
        if(points == 0){

    age = (contestant_c -> age - contestant_d -> age );
        if(age == 0){
            return (strcmp(contestant_c -> firstName, contestant_d -> firstName) &&
                    strcmp(contestant_c -> lastName, contestant_d -> lastName));
        }
        else {
            return age;
        }
    }
        else {
            return points;
    }
}



/**
* ----------------------------------
*   OPGAVE 4:
*   Find for hvert af de fire løb det hold, der har flest ryttere med en placering angivet som OTL eller DNF.
* ----------------------------------
*/
/* Function solves "OPGAVE 4". */
void mostOTLDNFperEvent(race* allResults, int amountOfResults, char* event, char* mostOTLandDNF){
    int i = 0;
    int temporary = 0;
    int maximum = 0;
    event = allResults[i].event;
    for (i; i <= amountOfResults; i++){
        if (strcmp(event, allResults[i].event) == 0){
            if (strcmp(allResults[i].position, "DNF") == 0 ||
                strcmp(allResults[i].position, "OTL") == 0){
                temporary += 1;
            }
        }
        else {
            printf("%s havde %d deltagere med 'OTL' eller 'DNF' positioner.\n", event, temporary);

            if(temporary > maximum){
                mostOTLandDNF = event;
                maximum = temporary;
                temporary = 0;
            }
                event = allResults[i].event;
            }
    }
    printf(" \n");
    printf("%s havde flest ryttere med en placering\n", mostOTLandDNF, maximum);
    printf("angivet som OTL eller DNF.\n");
}


/**
* ----------------------------------
*   OPGAVE 5:
*   Find den nation, der samlet set har begået sig bedst i de fire cykelløb.
*   Dette måles efter summen af points, som ryttere fra nationen har opnået i løbene.
*   (Hvis der er pointlighed mellem to eller flere nationer, er det op til dig at vælge én af disse).
* ----------------------------------
**/


/**
* ----------------------------------
*   OPGAVE 6:
*   Find i hvert af de fire cykelløb mediantiden af løbet. Mediantiden M af et bestemt cykelløb er den opnåede løbstid,
*   hvor halvdelen af løbstiderne er mindre end eller lig med M, og halvdelen af tiderne er større end eller lig med M.
*   Løbsresultater med en placering angivet som OTL eller DNF indgår ikke, når vi beregner mediantiden.
*   Hvis antallet af ryttere i et løb er lige ønsker vi at gruppen af ryttere med "en høj tid"
*   er én mindre end gruppen med "en lav tid", relativ til M).
* ----------------------------------
**/