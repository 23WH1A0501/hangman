#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_WORD_LENGTH 20

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

int main() {
    srand(time(NULL));
    int word_index = rand() % (sizeof(word_list) / sizeof(word_list[0]));
    strcpy(chosen_word, word_list[word_index]);

    int word_length = strlen(chosen_word);
    for (int i = 0; i < word_length; i++) {
        blank_list[i] = '_';
    }
    blank_list[word_length] = '\0';

    printf("%s\n", HANGMANPICS[update_display]);
    printf("Welcome to hangman.\n%s\n", blank_list);
    printf("Make a guess? ");
    scanf(" %c", &guess);

    making_a_guess();
    printf("%s\n", HANGMANPICS[update_display]);
    printf("%s\n", blank_list);

    while (update_display < 6) {
        if (strcmp(blank_list, chosen_word) == 0) {
            printf("YOU WIN!\n");
            break;
        }
        printf("Make another guess? ");
        scanf(" %c", &guess);

        making_a_guess();
        printf("%s\n", HANGMANPICS[update_display]);
        printf("%s\n", blank_list);
    }

    if (update_display == 6) {
        printf("GAME OVER.\nThe word was %s" , chosen_word);
    }

    return 0;
}
