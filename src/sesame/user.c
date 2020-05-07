/*
	user.c

	The user module to retrieve user pins and email addresses

*/
#include <stdio.h>
#include <string.h>

#include "user.h"
#include "util.h"


/*
	Check if the user pin is valid
*/
int userIsValid(char* userpin)
{
	char email[USER_LEN];

	if (utilStrNullOrEmpty(userpin) == UTIL_SUCCESS ) return 0;

	return userGetEmail(userpin, email);
}

/*
	Retrieve the email address from the user list
*/
int userGetEmail(char* userpin, char* outEmail)
{
	if (utilStrNullOrEmpty(userpin)) return 0;
	FILE* userFile;
	char line[2 * USER_LEN];
	int found = 0;

	userFile = fopen(USER_FILE, "r");

	if (!userFile) return found;

	while (fgets( line, 2 * USER_LEN, userFile) && !found)
	{
		char* u = strtok(line, USER_DELIM);
		if (!utilStrNullOrEmpty(u))
		{
			if (!strcmp(userpin, u))
			{
				char* e = strtok(NULL, USER_DELIM);
				
				if (!utilStrNullOrEmpty(e))
				{
					strcpy(outEmail, e);
					int len = strlen(outEmail);
					if (outEmail[len - 1] == '\n') outEmail[len - 1] = '\0';
				}
				
				found = 1;
			}
		}
	}

	fclose(userFile);

	return found;
}