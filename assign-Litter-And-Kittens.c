#include "Lib.h"

/*-------------------------------------------------------------------------------*/
/* giveBirth_this_month  is a funtion checks if it can have kids this month      */
/*                                                                               */
/* Imput : Rabbit is the structure of the rabbit                                 */
/*                                                                               */
/* Output: returns either 1 meaning it can have birth or 0 meaning not this month*/
/*-------------------------------------------------------------------------------*/
int     giveBirth_this_month(Rabbit_t * Rabbit)
{
    double chanceOfBirth = genrand_real1();

    if(chanceOfBirth <= Rabbit->Litt / 12.0) // the chance of birth this month using the number of litter
    {                                       // meaning the more the number of litter the more it has a 
        return 1;                           // chance to give this month
    }
    else
    {
        return 0;
    }
}



/*-------------------------------------------------------------------------------*/
/* nbLitters_Assign is a funtion  that assigns the rabbit or a                   */
/*             structure of rabbit the number of litters it can have this year   */
/*                                                                               */
/* Imput : Rabbit is the structure of the rabbit that we will assign the number  */
/*                          of litters for this year, CDF is the cumulative      */
/*           distributive array that has the probabilites for each array, size is*/
/*                           the size of the array  CDF_litter                   */
/*                                                                               */
/* Output: void                                                                  */
/*-------------------------------------------------------------------------------*/
void    nbLitters_Assign(Rabbit_t * Rabbit, double * CDF_Litter, int size)
{
    double chance_ofNblitt = genrand_real1();

    for(int i = 0; i < size; i++)
    {
        if(chance_ofNblitt <= CDF_Litter[i])
        {
            Rabbit->Litt = i + 3; // this means if it finds an interval which it is inside 
                                //  we add the number of litters it can have in a year
                                // and since it has between 3-9 and since the array starts from 0 
                                // we add 3, because the max of array CDF is 6 we add 6 + 3 = 9 max litter
                                // in a year same for the first element 0 + 3 = 3 which is min litter in a year.
            break;
        }
    }
}

/*-------------------------------------------------------------------------------*/
/* nbLitters_Assign is a funtion  that assigns the rabbit or a structure         */
/*              of rabbit the number of kittens it can have per month this year  */
/*                                                                               */
/* Imput : Rabbit is the structure of the rabbit                                 */
/*                                                                               */
/* Output: void                                                                  */
/*-------------------------------------------------------------------------------*/
void  nbKittens_Assign(Rabbit_t * Rabbit)
{
    double  probOfKittens = genrand_real1(); // probability of being in a interval that assigns number of kitten

    if(probOfKittens >= 0 && probOfKittens < 0.25)
    {
        if (probOfKittens <= 0.125)
        {
            Rabbit->kit = 2;
        }
        else
        {
            Rabbit->kit = 6;
        }
    }
    if(probOfKittens >= 0.25 && probOfKittens < 0.50)  // as we can see the chance of having
    {
        Rabbit->kit = 3;                               // 3, 4 and 5 is equal
    }
    if(probOfKittens >= 0.50 && probOfKittens < 0.75)
    {
        Rabbit->kit = 4;
    }
    if(probOfKittens >= 0.75 && probOfKittens <= 1)
    {
        Rabbit->kit = 5;
    }
}