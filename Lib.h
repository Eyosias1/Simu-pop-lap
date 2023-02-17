
#ifndef LIB_H
#define LIB_H
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/###*Standard lib headers*###\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#define NBRABMAXARR 1000000000 // number of arrays allocated for the rabbit

/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/###** Makoto Random variates genrators**###\/\/\/\/\/\/\/\/\/\/\/\/\/\*/

void            init_genrand(unsigned long s);
void            init_by_array(unsigned long init_key[], int key_length);
unsigned long   genrand_int32(void);
long            genrand_int31(void);
double          genrand_real1(void);
double          genrand_real2(void);
double          genrand_real3(void);
double          genrand_res53(void);

/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/###**Structure-of-Rabiit**###\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
typedef struct Rabbit
{
    int Rabnumber; // it is the id of the rabbit and also the place it is in the array - 1
    int age;       // age actual of the Rabbit
    int ageOfMatu; // age of Maturity
    double survivalRate; // survival rate of Rabbit 
    int dOrA;      // if its dead 1 or 0 if its alive
    int kit;      // NbKittens it can have monthly if female
    int Litt;     // NbLitters it can have yearly  if female
    int Tkit;     // Total number of actul kittens it has if female
    int TLitt;   // Total number of actual Litters it has   if female
    char Sexe;  // the sex of the rabbit	
} Rabbit_t;

typedef struct Rabbit_other_info
{
    double * CDF_for_litter; // the CDF array calculated to assign number of Litter
    int sizeCDF; // size of the array of the CDf
    int idofActualRab; // id of the last rabbit generated inside the array
    int totRabbitgenerated; // total rabbits generated 
    int totBabiesGen; // totol babies generated
    int totalRabbitMalesgen; //total male rabbits generated
    int totalRabbitfemaGen; // total female rabbits generated
    int totNumbRabAlive; // total number of Rabbit alive
    int numberMalesAlive; // number of males alive
    int numberFemalesAlive; // number of females alive
    int totdeath; // total death of rabbit
    int totDeFem; // total dead of females;
    int totDeMal; // total dead of Males;
    int totdeathAt_Child_birthFem_Matu; // total number of female death at child birth (meaning after giving birth)
    int totdeathBeforeMat;// total death before maturity
    int totDeFemBeMatu; // total dead females before Maturity;
    int totDeMalBeMatu; // total dead Males before Maturity;
    int totdeathAfMat; // total male and female death after maturity
    int totDeFemAfMatu; // total dead females after  Maturity;
    int totDeMalAfMatu; // total dead Males after Maturity;
} Rab_t_Oth_info;

/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/###**RabbitSimu.c**###\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
void            NumberOfCouples(int month);
Rab_t_Oth_info* StartRabbitSimu(int numberOfRabInitial, int years);
void            Free_The_Space(Rabbit_t ** arr, Rab_t_Oth_info * info);
void            Free_The_SpaceInfo(Rab_t_Oth_info * info);

/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/###**assign-Maturity-And-Sex.c**###\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
void            sex_Assign(Rabbit_t * Rabbit);
void            maturity_Assign(Rabbit_t * Rabbit);

/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/###**assign-litter-And-Kittens.c**###\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
void            nbLitters_Assign(Rabbit_t * Rabbit, double * CDF_Litter, int size);
void            nbKittens_Assign(Rabbit_t * Rabbit);
int             giveBirth_this_month(Rabbit_t * Rabbit);

/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/###**Death-Or-Creation.c**###\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
Rabbit_t   *    create_Rabbit(Rab_t_Oth_info * info);
void            motherGivesLife(Rabbit_t ** Rabbit, int place, Rab_t_Oth_info * info);
void            survival_Rate_Monthly(Rabbit_t * Rabbit, Rab_t_Oth_info * info);
void            Dimini_Surv_Matu_Rab_yearly(Rabbit_t * Rabbit, Rab_t_Oth_info * info);

/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/###**utile_stuff.c**###\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
int             ReturnYearIntoMonth(int year);
int             ReturnMonthIntoYear(int month);
double          cumulate(double * Tab, int size);
double  *       doProb(double * arr, int size);
double  *       CumDensFunc(double * Obs, int size, double * Proba);
double  *       FindCDF(int size, double * obs);
void            confiInter2(int exp, double * Exp, double mean, char * str, FILE * fd);
void            ComputeConfiInter(int exp, int initialRabNum, int Years);

#endif