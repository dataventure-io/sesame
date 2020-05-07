/*
	mail.c

	The mail module to send the OTP to the email address.
*/

#include <stdlib.h>
#include <stdio.h>

#include "mail.h"
#include "util.h"

void mailSendOTP(char* email, char* otp)
{
	if(utilStrNullOrEmpty(email)) return;
	if (utilStrNullOrEmpty(otp)) return;

	char cmd[CMD_BUF_LEN];

	sprintf(cmd, "echo \"%s\" | mail -s \"One Time Password\" %s\n", otp, email);

	system(cmd);
}

void mailSendNotification(char* adminEmail, char* userpin, char* userEmail)
{
	if (utilStrNullOrEmpty(adminEmail)) return;
	if (utilStrNullOrEmpty(userEmail)) return;

	char cmd[CMD_BUF_LEN];
	char timestr[UTIL_TIMESTR_LEN];

	utilGetTime(timestr);

	sprintf(cmd, "echo \"%s (%s) has accessed device at %s\" | mail -s \"Sesame Access Notification\" %s\n", userpin, userEmail, timestr, adminEmail );

	system(cmd);
}