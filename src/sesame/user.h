#ifndef _USER_H_
#define _USER_H_

#define USER_FILE "/etc/sesame/sesame.txt"
#define USER_LEN	81
#define USER_DELIM	","

typedef struct USER_RECORD_STRUCT {
	char userpin[USER_LEN];
	char email[USER_LEN];
} UserRecord;

int userIsValid(char* userpin);
int userGetEmail(char* userpin, char* outEmail);


#endif