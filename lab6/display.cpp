#include <pthread.h>
#include <semaphore.h>

sem_t A2B;

void *A(void *vargp)
{
	//...

	V(&A2B);
}


void *B(void *vargp)
{
	P(&A2B);

	//...
}

void concurrent_run()
{
	//create peer threads
	pthread_create(&tid[0], NULL, dmem_update, NULL);
	pthread_create(&tid[1], NULL, CC_update, NULL);
	pthread_create(&tid[2], NULL, reg_update, NULL);
	//...
	pthread_create(&tid[12], NULL, W_logic_update, NULL);

	while (!error)
	{
		cycle++;
		//KICK START the first clock cycle
		V(&control2dmem);
		//...
		V(&control2W_reg);
		
		P(&F_logic2control);
		//...
		P(&W_logic2control);

		printf("---control\n");

		//the last thread
		control_update();
		//output result
		table();
	}

	for (int i = 0; i < NUM_THREAD; i++)
		pthread_cancel(tid[i]);

	return;
}

