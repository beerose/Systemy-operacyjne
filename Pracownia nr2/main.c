/*
Autor programu: Aleksandra Sikora
Tytuł programu: Uniwersalny symulator algorytmów planowania przydziału procesora
Data wydania: 04-01-16
*/
#include<stdio.h>


int main()
{	int number;

	int b_time[30];
	int w_time[30];
	int t_time[30];

    float a_w_time = 0.0;
    float a_t_time = 0.0;
    
    int total = 0;		
    int i;  
    int j;		

	int  temp;
	int  sum = 0;
	int  position;
	int  process[20];
	int  priority[20];
	int  counter = 0;
	int  time_quantum; 
  	int  tmp[10];
  	int  pre[10];
  	int  wait_time = 0, turnaroundd_time = 0;

	printf("\nWybierz odpowiednią cyfrę:\n 1 - algorytm FCFS\n 2 - algorytm SJF \n 3 - planowanie priorytetowe \n 4 - planowanie rotacyjne \n");
	scanf("%d",&number);


	switch ( number ) {
		case 1:
			
			printf("Wpisz liczbę procesów:\t");
			scanf("%d", &total);
			printf("\nWpisz czas trwania fazy procesów:\n\n");
			for(i = 0; i < total; i++)
			{
				printf("Proces [%d]:", i + 1);
				scanf("%d", &b_time[i]);
			}
			w_time[0] = 0;   				
			for(i = 1; i < total; i++)			
			{
				w_time[i] = 0;
				for(j = 0; j < i; j++)
				{
				        w_time[i] = w_time[i] + b_time[j];
				}
			}
			printf("\nProces\t\tCzas trwania fazy\tCzas przetwarzania\tCzas cyklu przetwarzania\n");
			for(i = 0; i < total; i++)
			{
				t_time[i] = b_time[i] + w_time[i];    
				a_w_time = a_w_time + w_time[i];	
				a_t_time = a_t_time + t_time[i];
				printf("\nProces [%d]\t\t\t%.2d\t\t%.2d\t\t%.2d", i + 1, b_time[i], w_time[i], t_time[i]);
			}
			printf("\n");
			a_w_time = a_w_time / i;
			a_t_time = a_t_time / i;
			printf("\nŚredni czas oczekiwania = %f", a_w_time);
			printf("\nŚredni czas przetwarzania = %f", a_t_time);
			printf("\n");
			return 0;
 		break;
	
		case 2:
			
				printf("\nWpisz liczbę procesów:\t");
		    	scanf("%d", &total); 
		    	for(i = 0; i < total; i++)
		    	{
		    	printf("Wpisz czas trwania fazy procesów:\t");
				scanf("%d", &b_time[i]);
				process[i] = i + 1; 
		    	for(i = 0; i < total; i++)
		    	{
					position = i;
					for(j = i + 1; j < total; j++)					
					{
				    		if(b_time[j] < b_time[position])
							{
					      		        position = j;
						    }
					}
					temp = b_time[i];							
					b_time[i] = b_time[position];
					b_time[position] = temp;
					temp = process[i];
					process[i] = process[position];
					process[position] = temp;
		    	}	
		    	w_time[0] = 0;
		    	for(i = 1; i < total; i++)			
		    	{
					w_time[i] = 0;
					for(j = 0; j < i; j++)
				    {
							    w_time[i] = w_time[i] + b_time[j];
					} 
		    	}
		    	printf("\nProces\t\tCzas trwania fazy\tCzas przetwarzania\tCzas cyklu przetwarzania\n");
		    	for(i = 0; i < total; i++)
				{
					t_time[i] = b_time[i] + w_time[i];   
					a_w_time = a_w_time + w_time[i];	
					a_t_time = a_t_time + t_time[i];
					printf("\nProces [%d]\t\t%.2d\t\t\t%.2d\t\t\t%.2d", process[i], b_time[i], w_time[i], t_time[i]);
				}
				printf("\n");
				a_w_time = a_w_time / i;
				a_t_time = a_t_time / i;
				printf("\nŚredni czas oczekiwania = %f", a_w_time);
				printf("\nŚredni czas przetwarzania = %f", a_t_time);
				printf("\n");
			    return 0;
		break;

		case 3:
				printf("Wpisz liczbę procesów:\t");
		    	scanf("%d", &total);
		    	printf("\nWpisz czas trwania fazy i priorytety procesów:\n");
		    	for(i = 0; i < total; i++)
		    	{
	        	printf("\nProces[%d]\n", i + 1);
		        printf("Czas trwania fazy:\t");
		        scanf("%d", &b_time[i]);
		        printf("Priorytet:\t");
		        scanf("%d", &priority[i]);
		        process[i] = i + 1;
				}
			    for(i = 0; i < total; i++)
				{
		        	position = i;
		        	for(j = i + 1; j < total; j++)				
		        	{
		            		if(priority[j] < priority[position])
		                	{
								position = j;
							}
	        		}
		        	temp = priority[i];
		        	priority[i] = priority[position];
		        	priority[position] = temp; 
		        	temp = b_time[i];
		        	b_time[i] = b_time[position];
		        	b_time[position] = temp;
		        	temp = process[i];
		        	process[i] = process[position];
		        	process[position] = temp;
	    		}
		    	w_time[0] = 0;
		    	for(i = 1; i < total; i++)
		    	{
		        	w_time[i] = 0;
		        	for(j = 0; j < i; j++)
		            {
						w_time[i] = w_time[i] + b_time[j];
					}
		    	}
		    	printf("\nProces\t\tCzas trwania fazy\tCzas przetwarzania\tCzas cyklu przetwarzania\n");
		    	for(i = 0; i < total; i++)
				{
					t_time[i] = b_time[i] + w_time[i];    
					a_w_time = a_w_time + w_time[i];	
					a_t_time = a_t_time + t_time[i];
					printf("\nProces [%d]\t\t%.2d\t\t\t%.2d\t\t\t%.2d", process[i], b_time[i], w_time[i], t_time[i]);
				}
				printf("\n");
				a_w_time = a_w_time / i;
				a_t_time = a_t_time / i;
				printf("\nŚredni czas oczekiwania = %f", a_w_time);
				printf("\nŚredni czas przetwarzania = %f", a_t_time);
				printf("\n");
			    return 0;
		break;

		case 4:
				printf("\nWpisz liczbę procesów:\t"); 
			  	scanf("%d", &total); 
			  	j = total; 
			  	printf("\nWpisz czas trwania fazy:\n");
			  	for(i = 0; i < total; i++) 
			  	{
					
			    	printf("\nProces[%d]\n", i + 1);
		        	printf("Czas trwania fazy:\t");
			    	scanf("%d", &b_time[i]); 
			    	tmp[i] = b_time[i];
			    	pre[i] =0;
			  	} 
			  	printf("\nWpisz kwant czasu:\t"); 
			  	scanf("%d", &time_quantum); 
			    printf("\nProces\t\tCzas trwania fazy\t Czas cyklu przetwarzania\t Czas oczekiwania\n");
			  	for(sum = 0, i = 0; j != 0;) 
			  	{ 
		    		if(tmp[i] <= time_quantum && tmp[i] > 0) 
		    		{ 
		      			sum = sum + tmp[i]; 	
		      			tmp[i] = 0;				
		      			counter = 1; 
		      						
		    		} 
		    		else if(tmp[i] > 0) 
		    		{ 
		      			tmp[i] = tmp[i] - time_quantum; 
		      			pre[i] = pre[i] + 1;			
		      			sum = sum + time_quantum;						
		    		} 
		    		if(tmp[i] == 0 && counter == 1) 
		    		{ 
		      			j--; 
		 				printf("\nProces[%d]\t\t%d ms\t\t\t %d ms\t\t\t\t %d ms", i + 1, b_time[i], sum ,sum - b_time[i]);
		      			wait_time = wait_time + sum - b_time[i]; 				
		      			turnaroundd_time = turnaroundd_time + sum ; 			
		      			counter = 0; 
		    		} 
		    		if(i == total - 1) 
		      		{
						i = 0; 
					}
		    		else if(0 <= sum) 				
		      		{
						i++;
					}
		    		
				} 
				a_w_time = wait_time * 1.0 / total;
				a_t_time = turnaroundd_time * 1.0 / total;
			  	printf("\n\nŚredni czas oczekiwania:\t%f ms", a_w_time); 
			  	printf("\nŚredni czas cyklu przetwarzania:\t%f ms\n ", a_t_time); 
			  	return 0; 
		break;
		
}
}
