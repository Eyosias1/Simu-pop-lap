#include "Lib.h"


/*-------------------------------------------------------------------------------*/
/* sex_Assign  is a funtion  that assigns the sex for a baby rabbit              */
/*                                                                               */
/* Imput : Rabbit is the structure of the rabbit that we will assign the sex     */
/*                                                                               */
/* Output: void                                                                  */
/*-------------------------------------------------------------------------------*/
void sex_Assign(Rabbit_t * Rabbit)
{
    double sexProb = genrand_real1(); // probability of being male or female

    if (sexProb < 0.5)
    {
        Rabbit->Sexe = 'M';
    }
    else
    {
        Rabbit->Sexe = 'F';
    }
}


/*-------------------------------------------------------------------------------*/
/* maturity_Assign  is a funtion that assigns the maturity age for a baby rabbit */
/*                                                                               */
/* Imput : Rabbit is the structure of the rabbit that we will assign the maturity*/
/*                                                                               */
/* Output: void                                                                  */
/*-------------------------------------------------------------------------------*/
void maturity_Assign(Rabbit_t * Rabbit)
{
    double  probMaturity = genrand_real1(); // the probability of beign in one maturity class
    int     max_MatLev = 4; // there are four types or level of maturity
    double     prob = 0.25; // initial probability, and since there are 
    for (int i = 0; i < max_MatLev; i++) //four level and it is uniform we chosse 0.25
    {
        if(probMaturity <= prob)  // if the probabibilty is les the prob we assign the level
        {                          // of maturity 5 + i 
            Rabbit->ageOfMatu = i + 5;  // why 5 because the min is 5 month and the max is 8
            break;                      // and since i starts at 0 and ends at 3 we add 5
        }
        else // else we increment
        {
            prob += 0.25;
        } 
    }  
}