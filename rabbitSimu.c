#include "Lib.h"





int main()
{
    // Start by initialising 
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);
    NumberOfCouples(12*5); // example of question 1 of lab4 
    ComputeConfiInter(2, 20, 2);// example  test of question 2 of lab4
}


/*-------------------------------------------------------------------------------*/
/* NumberOfCoouples    gives the number of couples of rabbit population          */
/*                                                                               */
/* Imput : int Month, which is the number of month                               */ 
/*                                                                               */
/*                                                                               */
/* Output: void                                                                  */
/*-------------------------------------------------------------------------------*/
void    NumberOfCouples(int month)
{
    long long int Fib1    = 1;
    long long int Fib2    = 1;
    long long int numCp   = 1;
    int i       = 2;
    do
    {
        Fib1 = Fib2;
        Fib2 = numCp;
        numCp = Fib1 + Fib2;
        i += 1; 
    } while (i < month);
    printf("#################### Question 1 of lab 4 ##########################\n");
    printf("In this simple model we have in :\nMonth %d we have %lld couples of rabbit\n\n\n", i, numCp);
}












/*-------------------------------------------------------------------------------*/
/* Free_The_Space  is a funtion that  frees all the space allocated     */
/*                                for each rabbit.                               */
/*                                                                               */
/* Imput : arr is the array wich contains all the rabbits created                */
/* info the structure that contains information of all the rabbits               */
/*                 like the recent place of the rabbit generated                 */
/*                                                                               */
/* Output: void                                                                  */
/*-------------------------------------------------------------------------------*/
void Free_The_Space(Rabbit_t ** arr, Rab_t_Oth_info * info)
{
    for (int i = 0; i < info->idofActualRab; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

/*-------------------------------------------------------------------------------*/
/* Free_The_SpaceInfo  is a funtion that  frees all the space allocated          */
/*                                for the information structure                  */
/*                                                                               */
/* Imput : info is the structure information that contains global information    */
/*                                                                               */
/* Output: void                                                                  */
/*-------------------------------------------------------------------------------*/
void Free_The_SpaceInfo(Rab_t_Oth_info * info)
{
    free(info->CDF_for_litter);
    free(info);
}
/*-------------------------------------------------------------------------------*/
/* StartRabbitSimu  is a funtion that starts the simulation for a certain year   */
/*                                                                               */
/*                                                                               */
/* Imput : numberOfRabInitial is the number of initial rabbit to start off       */
/*                 years is the number of years to simulate it                   */
/*                                                                               */
/* Output: the output will be a structure containing the global information.     */
/*                           of the sumulation it will return Rab_t_Oth_info     */
/*-------------------------------------------------------------------------------*/
Rab_t_Oth_info*   StartRabbitSimu(int numberOfRabInitial, int years)
{
    int         size    = 7;
    double  *   Obs     = calloc(size, sizeof(double)); // chances for 3 to 9 litters
    Obs[0] = 100, Obs[1] = 200,  Obs[2] = 350,
    Obs[3] = 500,
    Obs[4] = 350, Obs[5] = 200, Obs[6] = 100;
    Rabbit_t ** arrOfRab = (Rabbit_t **) calloc(NBRABMAXARR,sizeof(Rabbit_t *));
    Rab_t_Oth_info * info = (Rab_t_Oth_info *) calloc(1, sizeof(Rab_t_Oth_info));
    info->CDF_for_litter = NULL; 
    info->CDF_for_litter= FindCDF(size, Obs);
    info->sizeCDF = size;
    info->idofActualRab = 0;
    int numberRabAtstart = numberOfRabInitial;
    int mois = ReturnYearIntoMonth(years);

    // initialisse the population at first with a number of population given
    for (int i = 0; i < numberRabAtstart; i++)
    {
        arrOfRab[i] = create_Rabbit(info);
        info->idofActualRab++;
    }
    // starts the simulation     
    for(int i = 1; i <= mois; i++)
    {
        // going through all the rabbit
        for(int j = 0; j < info->totRabbitgenerated; j++)
        {
            // if the rabbit reached maturity we set its survival rate from 50%->75%
            if (arrOfRab[j]->age == arrOfRab[j]->ageOfMatu)
            {
                arrOfRab[j]->survivalRate = 0.75;
            }
            
            // if it is a mature female and also if in this month it should give birth
            if(arrOfRab[j]->age >= arrOfRab[j]->ageOfMatu)
            {
                if(arrOfRab[j]->Sexe == 'F' && arrOfRab[j]->dOrA == 0) // if it is a female and alive
                {
                    int birth = giveBirth_this_month(arrOfRab[j]);
                    if(birth == 1) // if birth equals one then she is giving birth this month
                    {
                        motherGivesLife(arrOfRab,j, info);
                    }
                }
                
            }
            
            if(arrOfRab[j]->dOrA == 0) // if it is alive 
            {
                if(arrOfRab[j]->Sexe == 'F' && (arrOfRab[j]->age > 0 && arrOfRab[j]->age % 12 == 0)) // if the rabbit is a female and they aged a year
                {                                                                                       //   we assign again the nb litters and nb kittens for next year.   
                    nbLitters_Assign(arrOfRab[j], info->CDF_for_litter, info->sizeCDF);
                    nbKittens_Assign(arrOfRab[j]);
                }
            }
            
        }
        
        
        if (i % 12 == 0) // every year starting from 0 to 12 
        {
            for (int y = 0; y < info->totRabbitgenerated; y++)
            {
                Dimini_Surv_Matu_Rab_yearly(arrOfRab[y], info);
            }
        }
        // in the end of the month we add new information
        for (int k = 0; k < info->totRabbitgenerated; k++)
        {
            if(arrOfRab[k]->dOrA == 0 && (i % 4 == 0)) // if the rabbit is not dead and if it has been a year
            {                                           // we apply the survival rate function
                survival_Rate_Monthly(arrOfRab[k], info);
            }
            if(arrOfRab[k]->dOrA == 0) // if the rabbit is alive we increment every bodys age by 1
            {
                arrOfRab[k]->age++;
            }
        }
    }
    Free_The_Space(arrOfRab, info);
    
    return info;
}









