#include "Lib.h"


/*-------------------------------------------------------------------------------*/
/* create_Rabbit  is a funtion  that creates a rabbit initialize it also         */
/*                                                                               */
/* Imput : info is the structure of the global information  structure            */
/*                                                                               */
/* Output: it will return a rabbit created with type Rabbit_t                    */
/*-------------------------------------------------------------------------------*/
Rabbit_t *    create_Rabbit(Rab_t_Oth_info * info)
{
    Rabbit_t *  Rabbit = (Rabbit_t *) calloc(1, sizeof(Rabbit_t));
    double      chance_ofDeathatbirthForMOm = genrand_real1();

    Rabbit->age = 0;
    Rabbit->Rabnumber = info->idofActualRab; // set the id of the rabbit
    sex_Assign(Rabbit);
    
    maturity_Assign(Rabbit);
    Rabbit->dOrA = 0; // means rabbit baby alive;
    Rabbit->survivalRate = 0.5; // 50 % chance at young age;
    nbLitters_Assign(Rabbit, info->CDF_for_litter, info->sizeCDF);
    nbKittens_Assign(Rabbit);
    Rabbit->Tkit = 0;
    Rabbit->TLitt = 0;
    // if a new born baby is born we increment the number of rabbits , females and males alive but also total rabbit and male and female generated  
    info->totNumbRabAlive++;
    info->totRabbitgenerated++;
    if(Rabbit->Sexe == 'F')
    {
        info->numberFemalesAlive++;
        info->totalRabbitfemaGen++;
    }
    else
    {
        info->numberMalesAlive++;
        info->totalRabbitMalesgen++;
    }
    return Rabbit;
}

/*-------------------------------------------------------------------------------*/
/* motherGivesLife  is a funtion  that checks if the mother is fertile,          */
/*       if  she can still give birth,and creates a rabbit                       */
/* and kills her if she is below her survival rate                               */
/*                                                                               */
/* Imput : info is the structure of the global information  structure            */
/*                   Rabbit is the structure of the rabbit                       */
/*                                                                               */
/* Output: void                                                                  */
/*-------------------------------------------------------------------------------*/
void    motherGivesLife(Rabbit_t ** Rabbit, int place, Rab_t_Oth_info * info)
{
    double MotherChanceOfInfertily = genrand_real1();
    double MotherchanceOfdeath = genrand_real1();
    if (MotherChanceOfInfertily >= 0.10) // means the mother is fertile
    {
        if (MotherchanceOfdeath > 0.15)
        {
            if (Rabbit[place]->TLitt <= Rabbit[place]->Litt) // if the rabbit did not exceeed the amount
            {                                                // of litters in this year.
                for (int i = 0; i < Rabbit[place]->kit; i++)
                {
                    Rabbit[info->idofActualRab] = create_Rabbit(info); // it can give birth to another
                    info->idofActualRab++;
                    info->totBabiesGen++;
                }
                Rabbit[place]->TLitt++; // we increment each time the number of times it is possible to have kids per month
            }
        }
        else 
        { // baby is not born mother dies 
            Rabbit[place]->dOrA = 1;
            info->totdeathAt_Child_birthFem_Matu++; // mother dies giving birth
            info->totNumbRabAlive--;
            info->numberFemalesAlive--;
            info->totdeath++;
            info->totDeFem++;
            info->totDeFemAfMatu++;
            info->totdeathAfMat++;
        }
    }
}

/*-------------------------------------------------------------------------------*/
/* survival_Rate_Monthly  is a funtion  that checks if the rabbit can survive    */
/*                   kills if it is below the survival rate                      */
/*                                                                               */
/* Imput : info is the structure of the global information  structure            */
/*                   Rabbit is the structure of the rabbit                       */
/*                                                                               */
/* Output: void                                                                  */
/*-------------------------------------------------------------------------------*/
void    survival_Rate_Monthly(Rabbit_t * Rabbit, Rab_t_Oth_info * info)
{
    double ChanceOfSurv_adult = genrand_real1();
    double ChanceOfSurv_kids = genrand_real1();

    if(Rabbit->age >= Rabbit->ageOfMatu)
    {
        if (ChanceOfSurv_adult > Rabbit->survivalRate) // An adult rabbit has 
        {                                              // Rabbit->survivalRate % chance of survival
            Rabbit->dOrA = 1; // Rabbit dies
            if(Rabbit->Sexe == 'F')
            {
                info->totNumbRabAlive--;
                info->numberFemalesAlive--;
                info->totdeath++;
                info->totDeFem++;
                info->totDeFemAfMatu++;
                info->totdeathAfMat++;
            }
            else
            {
                info->totNumbRabAlive--;
                info->numberMalesAlive--;
                info->totdeath++;
                info->totDeMal++;
                info->totDeMalAfMatu++;
                info->totdeathAfMat++;
            }
        }
    }// else the rabbit survives to see onather day

    if(Rabbit->age < Rabbit->ageOfMatu)
    {
        if (ChanceOfSurv_kids > Rabbit->survivalRate) // for little rabbit it is 
        {                                             //  Rabbit->survivalRate % chance of survival
            Rabbit->dOrA = 1; // rabbit dies
            if(Rabbit->Sexe == 'F')
            {
                info->totNumbRabAlive--;
                info->numberFemalesAlive--;
                info->totdeath++;
                info->totDeFem++;
                info->totDeFemBeMatu++;
                info->totdeathBeforeMat++;
            }
            else
            {
                info->totNumbRabAlive--;
                info->numberMalesAlive--;
                info->totdeath++;
                info->totDeMal++;
                info->totDeMalBeMatu++;
                info->totdeathBeforeMat++;
            }
        }
    }     // else the rabbit survives to see onather day
}

/*-------------------------------------------------------------------------------*/
/* Dimini_Surv_Matu_Rab_yearly is a funtion that diminushes the survival rate    */
/*                   of a mature rabbit having to be greater than 7 years old    */
/*                                                                               */
/* Imput : info is the structure of the global information  structure            */
/*                   Rabbit is the structure of the rabbit                       */
/*                                                                               */
/* Output: void                                                                  */
/*-------------------------------------------------------------------------------*/
void   Dimini_Surv_Matu_Rab_yearly(Rabbit_t * Rabbit, Rab_t_Oth_info * info)
{
    
    if(Rabbit->age >= Rabbit->ageOfMatu) // if the rabbit reaches its mature age 5, 6, 7 or 8 months
    {
        if(Rabbit->dOrA == 0)
        {
            if(Rabbit->age > 84) // else if it is 7 years old converted from month 
            {

                Rabbit->survivalRate -= 0.15;  // diminishe survival rate by 15 %
                if(Rabbit->survivalRate <= 0.0)  // when the survivale rate reaches 0 % 
                {                                                     //  kill it
                    Rabbit->dOrA = 1;
                    if(Rabbit->Sexe == 'F')
                    {
                        info->totNumbRabAlive--;
                        info->numberFemalesAlive--;
                        info->totdeath++;
                        info->totDeFem++;
                        info->totDeFemAfMatu++;
                        info->totdeathAfMat++;
                    }
                    else
                    {
                        info->totNumbRabAlive--;
                        info->numberMalesAlive--;
                        info->totdeath++;
                        info->totDeMal++;
                        info->totDeMalAfMatu++;
                        info->totdeathAfMat++;
                    }
                }
            }
        }
    }
}