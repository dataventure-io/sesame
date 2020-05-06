#ifndef _USER_H
#define _USER_H

#define USER_FILE "/etc/sesame/sesame.txt"
#define USER_LEN	81
typedef struct USER_RECORD_STRUCT {
	char userpin[USER_LEN];
	char email[USER_LEN];
} UserRecord;
int userIsValid(char* userpin);
char* userGetEmail(char* userpin);


#endif