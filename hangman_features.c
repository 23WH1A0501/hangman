#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_WORD_LENGTH 20
#define MAX_NAME_LENGTH 30
#define MAX_WRONG_GUESSES 6

char* HANGMANPICS[] = {
    "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n",
    "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========\n",
    "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========\n",
    "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========\n",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========\n",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========\n",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========\n"
};

char* word_list[] = {
    "aardvark", "baboon", "camel", "jazz", "grass", "follow", "castle", "cloud",
    "apple", "banana", "cherry", "dog", "elephant", "fish", "giraffe", "house", 
    "island", "jungle", "kitten", "lemon", "monkey", "notebook", "orange", 
    "pencil", "queen", "rabbit", "snake", "tiger", "umbrella", "vase", 
    "water", "xylophone", "yacht", "zebra", "ant", "ball", "car", "duck", 
    "egg", "frog", "goat", "hat", "igloo", "juice", "key", "lion", "moon", 
    "nurse", "owl", "piano", "quilt", "ring", "star", "tree", "unicorn", 
    "violin", "whale", "xray", "yogurt", "zoo", "airplane", "bicycle", 
    "cactus", "drum", "eagle", "flamingo", "guitar", "hippo", "insect", 
    "jelly", "kangaroo", "lizard", "mountain", "nest", "octopus", 
    "penguin", "quokka", "robot", "sun", "train", "umbrella", "vulture", 
    "wolf", "xenon", "yarn", "zeppelin", "archer", "butterfly", "clown", 
    "dolphin", "engine", "flower", "galaxy", "honey", "ice", "jacket", 
    "kite", "lamp", "mirror", "napkin", "onion", "parrot", "quiver", 
    "rose", "sand", "turtle", "vaccine", "wave", "xenon", "yak", 
    "zeppelin"
};

char chosen_word[MAX_WORD_LENGTH];
char blank_list[MAX_WORD_LENGTH];
int update_display = 0;
char guess;
int score = 0;
char player_name[MAX_NAME_LENGTH];

void making_a_guess() {
    int x = 0;
    bool correct_guess = false;

    while (chosen_word[x] != '\0') {
        if (guess == chosen_word[x]) {
            blank_list[x] = guess;
            correct_guess = true;
        }
        x++;
    }

    if (!correct_guess) {
        printf("There is no %c, sorry.\n", guess);
        update_display++;
    }
}

void display_hint() {
    int hint_position = rand() % strlen(chosen_word);
    blank_list[hint_position] = chosen_word[hint_position];
    printf("Hint: The word now looks like this: %s\n", blank_list);
}

void play_game() {
    srand(time(NULL));
    int word_index = rand() % (sizeof(word_list) / sizeof(word_list[0]));
    strcpy(chosen_word, word_list[word_index]);

    int word_length = strlen(chosen_word);
    for (int i = 0; i < word_length; i++) {
        blank_list[i] = '_';
    }
    blank_list[word_length] = '\0';

    printf("%s\n", HANGMANPICS[update_display]);
    printf("Welcome to hangman, %s.\n%s\n", player_name, blank_list);
    printf("Make a guess? ");
    scanf(" %c", &guess);

    making_a_guess();
    printf("%s\n", HANGMANPICS[update_display]);
    printf("%s\n", blank_list);

    while (update_display < MAX_WRONG_GUESSES) {
        if (strcmp(blank_list, chosen_word) == 0) {
            printf("YOU WIN!\n");
            score += 10;
            break;
        }
        printf("Make another guess (or type 'hint' for a hint)? ");
        scanf(" %s", &guess);

        if (strcmp(&guess, "hint") == 0) {
            display_hint();
            continue;
        }

        making_a_guess();
        printf("%s\n", HANGMANPICS[update_display]);
        printf("%s\n", blank_list);
    }

    if (update_display == MAX_WRONG_GUESSES) {
        printf("GAME OVER.\nThe word was: %s" , chosen_word);
    }

    printf("\nYour current score is: %d\n", score);
}

int main() {
    printf("Enter your name: ");
    scanf("%s", player_name);

    char play_again;
    do {
        play_game();
        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &play_again);
    } while (play_again == 'y' || play_again == 'Y');

    printf("Thanks for playing, %s! Your final score is: %d\n", player_name, score);

    return 0;
}

