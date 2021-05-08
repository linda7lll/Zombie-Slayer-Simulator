/*
 * linda turkmen 
 *
 */


#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



/*number of zombies in the game: 
you should synchronize threads editing this variable*/
int zombieCounter = 0;
int deadZombie = 0;


/* Returns true if number of zombies in the room are 
greater than or equal to 100.*/
int tooManyZombiesInTheRoom(){
	if(zombieCounter > 99)
		return true;
	return false;
}

/* Returns true if there is at least one zombies in the room.*/
int zombiesExist(){
	if(zombieCounter >= 0)
		return true;
	else 
		return false;
}
/*Returns the number of zombies killed.*/
int getKilledCount(){
	return deadZombie;
}

/* Returns the number of zombies in the room.*/
int getInTheRoomCount(){
	return zombieCounter;
}

/*Returns true if more than 100 zombies have been killed.*/
int killed100Zombies(){
	if(deadZombie > 99)
		return true;
	return false;
}

/* Keeps track of number of zombies entered.*/
void zombieEntered(){
	while (!(tooManyZombiesInTheRoom()) && !(killed100Zombies()) && zombiesExist())
	{
		srand(time(NULL));
		int randomity = rand()%2;
		if(randomity == 0){
			usleep(2);
			++zombieCounter;
			printf("Total Zombies in Room -> %d \n", getInTheRoomCount());
			
		}
	}
}
/* Keeps track of number of zombies killed.*/
void zombieKilled(){
	
	while(!(tooManyZombiesInTheRoom()) && !(killed100Zombies()) && zombiesExist())
	{
		srand(time(NULL));
		int randomity = rand()%2;
		if(randomity == 0){
			usleep(2);
			--zombieCounter;
			++deadZombie;
			printf("Killed Zombie Count -> %d \n", getKilledCount());
		}
	}
	
}

/*doorman thread*/
 void *doorMan(void *p) 
  {
	zombieEntered();
  }

/*slayer thread*/
void *slayer(void *p){
	zombieKilled();
 }

/*simulator main thread*/
int main(int argc, char **argv){
	int dMan = atoi(argv[1]);
	pthread_t doorman[dMan];
	pthread_t slayerVar;
	
	pthread_create(&slayerVar, NULL, slayer, NULL);
	
	for(int i = 0; i < dMan; i++){
		pthread_create(&doorman[i], NULL, doorMan, NULL);
		pthread_join(doorman[i], NULL);
	}
		
	pthread_join(slayerVar, NULL);
		
}
