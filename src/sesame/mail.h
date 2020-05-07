#ifndef _MAIL_H_
#define _MAIL_H_

#define CMD_BUF_LEN	255
void mailSendOTP(char* email, char* otp);
void mailSendNotification(char* adminEmail, char* userpin, char* userEmail);

#endif



