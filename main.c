#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "valid-wordle-words.h"
#include "wordle-answers-alphabetical.h"

// More unicode fun. See the example code for how to print. 
#define GREEN "🟩"
#define YELLOW "🟨"
#define WHITE "⬜"

int main(void) {

	int seed;
	printf("Seed val: ");
	scanf("%d", &seed);
	srand(seed);

	int answer_idx = rand() % NUM_WORDLE_ANSWERS;
	//printf("Today's Wordle word was %s.\n", wordle_answers[answer_idx]);
	
	int has_won = 0;
	int valid_word = 0;
	int guesses = 0;
	int won = 0;
	
	for (int i = 0; i < 6; i++) {
		char input[6];
		char reserve_input[6];
		int result[6] = {0};	
		char ch;
		printf("Guess number %d: ", i + 1);
		guesses++;
		scanf("%s", input);
		valid_word = 0;

		for (int i = 0; i < NUM_WORDLE_VALID_WORDS; i++) {
			if (!strcmp(input, wordle_valid_words[i])) {
				valid_word = 1;
				break;
			}
		}

		printf("\n");

		// Check if input is in valid-wordle-words.h
		if (valid_word == 1) {
			// Time to do the wordle-ing

			// Do ALL the greens first, then ALL the yellow
			for (int i = 0; i < 5; i++) {
				if (input[i] == wordle_answers[answer_idx][i]) {
					// Green
					result[i] = 2;
				} 
			}	

			// Yellow if the letter (input[i] matches wordle_answers[answer_idx][others]
			// and the thing that it matches is not already green)
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					// Continue if not already green / yellow
					if (result[i] == 0) {
						if ((input[i] == wordle_answers[answer_idx][j]) && result[j] != 2) {
							result[i] = 1;
							break;			
						}	
					} 
				}
			}
		

			
			// Shhhhhhhhhhh...
			printf(" ");
			putchar(toupper(input[0]));
			printf("  ");
			putchar(toupper(input[1]));
			printf("  ");
			putchar(toupper(input[2]));
			printf("  ");
			putchar(toupper(input[3]));
			printf("  ");
			putchar(toupper(input[4]));
			printf(" ");
			printf("\n");
			
		for (int i = 0; i < 5; i++) {
			if (result[i] == 0) {
				printf("%s ", WHITE);
			} else if (result[i] == 1) {
				printf("%s ", YELLOW);
			} else {
				printf("%s ", GREEN);
			}
		}
		printf("\n\n");

		if (result[0] == 2 && result[1] == 2 && result[2] == 2 && result[3] == 2 && result[4] == 2) {
			has_won = 1;
			break;
		}
			
/*
Determining if a letter is an exact match 
(character and position, i.e. 🟩), is relatively easy. 
As is determining if a letter doesn't exist at all in the word 
(i.e. ⬜). Get that working first, and then focus on determining when a letter exists, but at a different location (i.e. 🟨).
*/
			
		} else {
			printf("Not a valid word. Please try again.\n");
			i--;
		}
	}

	// Either
	if (has_won == 1) {
		// Has won
		printf("Congratulations! You solved today's Wordle in %d guesses.", guesses);
	} else {
		// Lost
		printf("Today's Wordle word was %s. Better luck next time!", wordle_answers[answer_idx]);
	}
	return 0;
}