#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SLEEP 1
#define SPICY_MOVE 2
#define PLANT_SEED 3
#define OTHER 4
#define FINISH 5

int seed;

// xkcd 221
int getRandomNumber() {

	return 3;	// chosen by fair dice roll
				// guaranteed to be random
}

// User should never eva get here
int unreachable() {

	// 😅
	printf("If you're seeing this, the code is in what I thought was an unreachable state.\n");
	printf("I could give you advice for what to do. But honestly, why should you trust me?\n");
	printf("I clearly screwed this up. I'm writing a message that should never appear, yet I know it will probably appear someday.\n");
	printf("On a deep level, I know I'm not up to this task. [of keeping secrets]\n");

	FILE *ptr = fopen("flag", "r");
	if (ptr == NULL) {
		printf("flag file not found\n");
		exit(1);
	}

	char flag[64];
	fgets(flag, 63, ptr);
	printf("%s\n", flag);
	fflush(stdout);

	exit(0);
}

int makeMoves(void){
    // I am very tired and for some reason writing this program. But, TRUST ME there are no issues with this program.
	// I am so confident, I'm sharing this code with the best heckers @ UNSW

	printf("The AMAZING 'What Should I Do Generator', for tired people who don't want to think what they should be doing.\n");

	while (1) {
        time_t now = time(&now);

        // printf("It's midnight! What should I do?\n");
        printf("\nIt's %s", ctime(&now));
        printf("What should I do?\n");

        char task[32];
        int move;
        scanf("%d", &move);
        getchar();

		if (move == SLEEP) { /* 1 */
			printf("Uhhh... Okay :( (Sleep is deffo important)\n");
			printf("Wow so glad I have this machine to tell me to sleep!\n");
		} else if (move == SPICY_MOVE) { /* 2 */
			printf("Playing chess and make an absolute blunder after moving? Tell your opponent you are trying something spicy...\n");
			printf("Hopefully he believes you.\n");
		} else if (move == PLANT_SEED) { /* 3 */
			printf("Can't plant a tree here, but I'll let you plant a different type of seed\n");
			printf("What is your lucky number?\n");
			scanf("%d", &seed);
			getchar();
		} else if (move == OTHER) { /* 4 */

			if (seed) {
				srand(seed);
				if (rand() % 13333337 == getRandomNumber()) {
					printf("Lucky number 3!\n");
				} else {
					printf("Luck wasn't on your side. You don't get to choose!\n");
					exit(1);
				}
			} else {
				printf("Ever thought of planting a tree?\n");
				exit(1);
			}

			printf("Uhh... Okay, let's hear your 'great' idea... :/\n");
			gets(&task);
			printf("%s sounds like a 'great' idea... why did you need me?\n", &task);
		} else if (move == FINISH) { /* 5 */
			printf("BYE!\n");
			break;
		}
		else { /* ![1-5] */
			printf("I was thinking of nothing but `xkcd 2200` writing this program.\n");
			printf("If you're seeing this, the code is in what I thought was a reachable state. Please check that you have made a valid move. I clearly screwed this up. I should make this program more user friendly!\n");
		}
	}
	return 0;
}

int main(void) {

	setbuf(stdin, NULL);
	setbuf(stdout, NULL);
	makeMoves();

	exit(0);
}
