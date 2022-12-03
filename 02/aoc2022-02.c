#include <stdio.h>
#include <stdlib.h>

int get_outcome(char theirs, char ours) {
    char winning_shape = ((theirs - 'A' + 1) % 3) + 'X';
    char drawing_shape = theirs - 'A' + 'X';

    if (winning_shape == ours) {
        return 6;
    } else if (drawing_shape == ours) {
        return 3;
    } else {
        return 0;
    }
}

int get_score(char theirs, char ours) {
    return (ours - 'X' + 1) + get_outcome(theirs, ours);
}

int get_shape(char theirs, char outcome) {
    if (outcome == 'Z') {
        return ((theirs - 'A' + 1) % 3) + 1;
    } else if (outcome == 'Y') {
        return theirs - 'A' + 1;
    } else {
        return ((theirs - 'A' + 5) % 3) + 1;
    }
}

int final_score(char theirs, char outcome) {
    return get_shape(theirs, outcome) + ((outcome - 'X') * 3);
}

