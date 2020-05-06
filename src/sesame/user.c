/*
	user.c

	The user module to retrieve user pins and email addresses

*/
#include <stdio.h>
#include <string.h>

#include "user.h"

UserRecord userRec;

/*
	Check if the user pin is valid
*/
int userIsValid(char* userpin)
{
	char* email = userGetEmail(userpin);
	
	return (email ? 1 : 0);
}

/*
	Retrieve the email address from the user list
*/
char* userGetEmail(char* userpin)
{
	FILE* userFile;
	char line[2 * USER_LEN];
	char* email = NULL;
	int found = 0;

	userFile = fopen(USER_FILE, "r");

	if (!userFile) return email;

	while (fgets( line, 2 * USER_LEN, userFile) && !found)
	{
		char* u = strtok(line, "\t");
		if (u != NULL)
		{
			if (!strcmp(userpin, u))
			{
				strcpy(userRec.userpin,u);
				
				char* e = strtok(NULL, "\t");
				
				if (e != NULL)
				{
					strcpy(userRec.email, e);
					int len = strlen(userRec.email);
					if (userRec.email[len - 1] == '\n') userRec.email[len - 1] = '\0';
				}

				
					email = userRec.email;
				found = 1;
			}
		}
	}

	fclose(userFile);

	return email;
}