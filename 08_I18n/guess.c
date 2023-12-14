#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

int main(int argc, char const *argv[])
{

	bindtextdomain("messages", "../locale");
	textdomain("messages");
	setlocale(LC_ALL, "");

	printf(_("Pick a number between 1 and 100\n"));
	int left = 0, right = 100;
	while (right - left > 1) {
		int mid = (right + left) / 2;
		printf(_("Is your number more than %d? [yes/no]\t"), mid);

		char ans[20];
		int n = scanf("%s", ans);

		if (!strcasecmp(ans, _("yes"))) {
			left = mid;
		} else if (!strcasecmp(ans, _("no"))) {
			right = mid;
		}

	}

	printf(_("Your number is: %d\n"), right);

	return 0;
}