#ifndef _SESAME_H_
#define _SESAME_H_


#define USERPIN_LEN 81
#define USEROTP_LEN 81


void sesameGetUserPin();
void sesameGetUserOTP();
void sesameShowPinForm();
void sesameShowOTPForm();
void sesameHandleHeader();
void sesameHandleFooter();
int sesameCheckOTP();
void sesameGenOTP();
int sesameIsValidUserPin();
void sesameShowPinError();
void sesameShowOTPError();
void sesameSendOTP();

#endif