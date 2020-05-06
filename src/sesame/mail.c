/*
	mail.c

	The mail module to send the OTP to the email address.
*/

#include <stdlib.h>

#include "mail.h"

void mailSendOTP(char* email, char* otp)
{
	char cmd[CMD_BUF_LEN];

	sprintf(cmd, "echo \"%s\" | mail -s \"One Time Password\" %s\n", otp, email);

	system(cmd);
}