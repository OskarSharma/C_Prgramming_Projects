#ifndef __HANGMAN_HELPERS_H__
#define __HANGMAN_HELPERS_H__

/*
* DO NOT MODIFY ANYTHING THAT IS CURRENTLY HERE.
*/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The longest length that a secret can be.
#define MAX_LENGTH 256

// The player loses as soon as they make their 6th incorrect guess.
#define LOSING_MISTAKE 6

#define MSG_LONG_SECRET_d "The secret phrase is over %d characters.\n"

#define MSG_INVALID_CHAR_c                                                    \
    "Invalid character: '%c'\n"                                               \
    "The secret phrase must contain only\n"                                   \
    "lowercase letters, spaces, hyphens, and apostrophes.\n"

#define MSG_PROMPT "Guess a letter: "

#define MSG_LOSE_s "You lose! The secret phrase was: %s\n"

#define MSG_WIN_s "You win! The secret phrase was: %s\n"

#define MSG_WRONG_NUM_ARGS                                                    \
    "Wrong number of arguments.\n"                                            \
    "Usage: hangman \"secret word or phrase\"\n"                              \
    "If the secret is multiple words, you must quote it.\n"

const char punctuation[] = " '-";

const char *arts[] = { "\n"
                       "  _____\n"
                       " |     |\n"
                       "       |\n"
                       "       |\n"
                       "       |\\\n"
                       "       | \\\n"
                       "     __|__\\\n",
    "\n"
    "  _____\n"
    " |     |\n"
    "(_)    |\n"
    "       |\n"
    "       |\\\n"
    "       | \\\n"
    "     __|__\\\n",
    "\n"
    "  _____\n"
    " |     |\n"
    "(_)    |\n"
    " |     |\n"
    " |     |\\\n"
    "       | \\\n"
    "     __|__\\\n",
    "\n"
    "  _____\n"
    " |     |\n"
    "(_)    |\n"
    "/|     |\n"
    " |     |\\\n"
    "       | \\\n"
    "     __|__\\\n",
    "\n"
    "  _____\n"
    " |     |\n"
    "(_)    |\n"
    "/|\\    |\n"
    " |     |\\\n"
    "       | \\\n"
    "     __|__\\\n",
    "\n"
    "  _____\n"
    " |     |\n"
    "(_)    |\n"
    "/|\\    |\n"
    " |     |\\\n"
    "/      | \\\n"
    "     __|__\\\n",
    "\n"
    "  _____\n"
    " |     |\n"
    "(_)    |\n"
    "/|\\    |\n"
    " |     |\\\n"
    "/ \\    | \\\n"
    "     __|__\\\n" };

#endif
