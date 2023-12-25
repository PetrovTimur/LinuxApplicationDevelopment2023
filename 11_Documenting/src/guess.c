/** @mainpage Minimal program that guesses your number
 * @copydetails guesser
 */

/** @page guesser Minimal program that guesses your number
 * Random number guesser
 * @section SYNOPSIS
 * `guess` [ \a OPTION ]
 * @section DESCRIPTION
 * Guess user-picked number by asking simple yes/no questions.
 *
 * This is free and unencumbered software released into the public domain.
 * 
 * You can specify --roman / -r to use roman numeral system.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>
#include <argp.h>

/** @file guess.c
 * Implementation
 * 
 * Rather than randomly guessing the number, this program uses binary search,
 * asking user basic yes/no questions to downsize possible answers list.
 * 
 */

#define _(STRING) gettext(STRING)

const char *argp_program_version =
  "guesser 1.0";
const char *argp_program_bug_address =
  "<s02200459@gse.cs.msu.ru>";

static char doc[] =
  ("Gueeser -- a minimal program that guesses your number between 1 and 100");

static struct argp_option options[] = {
  {"roman",  'r', 0,      0,  ("Use roman numerals") },
  { 0 }
};

struct arguments
{
  int roman;
};

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = state->input;

  switch (key)
    {
    case 'r':
      arguments->roman = 1;
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

static struct argp argp = { options, parse_opt, 0, doc };

static char *data[100] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X",
						"XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX",
						"XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX",
						"XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX",
						"XL", "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX",
						"L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX",
						"LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX",
						"LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX",
						"LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX",
						"XC", "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"};


/** Convert integer to string
 * @param number number to convert
 * @return string corresponding to @p number
 */

char *my_itoa(int number) {
	char *res = (char *) malloc(10 * sizeof(char));
	snprintf(res, 10, "%d", number);
	return res;
}

/** Calculate decimal for roman @p number
 * @param number number in roman numeral system
 * @return integer corresponding to @p number
 */

int roman_to_decimal(char* number) {
	for (int i = 0; i < 100; i++) {
		if (!strcmp(number, data[i]))
			return i + 1;
	}
}

/** Calculate roman representaion for decimal @p number
 * @param number number in decimal numeral system
 * @return roman number corresponding to decimal @p number
 */

char *decimal_to_roman(int number) {
	char *res = (char *) malloc(10 * sizeof(char));
	strcpy(res, data[number - 1]);
	return res;
}


int main(int argc, char **argv)
{
	struct arguments arguments;
	arguments.roman = 0;
	argp_parse (&argp, argc, argv, 0, 0, &arguments);

	bindtextdomain("messages", TEXTDOMAINDIR);
	textdomain("messages");
	setlocale(LC_ALL, "");

	int left = 0, right = 100;
	char *left_str = arguments.roman ? decimal_to_roman(left + 1) : my_itoa(left + 1);
	char *right_str = arguments.roman ? decimal_to_roman(right) : my_itoa(right);
	printf(_("Pick a number between %s and %s\n"), left_str, right_str);
	free(left_str);
	free(right_str);

	while (right - left > 1) {
		int mid = (right + left) / 2;
		char *mid_str = arguments.roman ? decimal_to_roman(mid) : my_itoa(mid);
		printf(_("Is your number more than %s? [yes/no]\t\t"), mid_str);
		free(mid_str);

		char ans[20];
		int n = scanf("%s", ans);

		if (!strcasecmp(ans, _("yes"))) {
			left = mid;
		} else if (!strcasecmp(ans, _("no"))) {
			right = mid;
		}

	}

	right_str = arguments.roman ? decimal_to_roman(right) : my_itoa(right);
	printf(_("Your number is: %s\n"), right_str);
	free(right_str);

	return 0;
}