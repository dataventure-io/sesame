/*
	sesame.c

	The main file of the sesame program

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "cgic.h"
#include "md5.h"
#include "wire.h"
#include "user.h"
#include "mail.h"
#include "sesame.h"

char userpin[USERPIN_LEN];
char userotp[USEROTP_LEN];
char input_userotp[USEROTP_LEN];

/*
	called from the cgic library
*/
int cgiMain() {
	

	/* send the top of the page*/
	sesameHandleHeader();
	

	/* check if the user is submitting a pin */
	if (cgiFormSubmitClicked("submit_userpin") == cgiFormSuccess)
	{
		sesameGetUserPin();

		if (!sesameIsValidUserPin())
		{
			sesameShowPinError();
			sesameShowPinForm();
		}
		else
		{
			sesameGenOTP();
			sesameSendOTP();
			sesameShowOTPForm();
		}
		
	}
	/* check if the user is submitting their one-time password */
	else if (cgiFormSubmitClicked("submit_userotp") == cgiFormSuccess)
	{
		if (sesameCheckOTP())
		{
			sesameSendNotification();
		}
		else
		{
			sesameShowOTPError();
		}
			
		sesameShowPinForm();
	}
	/* otherwise show the pin input box */
	else
	{
		sesameShowPinForm();
	}
	
	/* Finish up the page */
	sesameHandleFooter();
	return 0;
}

/*
	Sends the content type and establishes the CSS stuff for the page.
	Using the bootstrap CSS library
*/
void sesameHandleHeader()
{
	/* Send the content type, letting the browser know this is HTML */
	cgiHeaderContentType("text/html");

	/* Top of the page */
	fprintf(cgiOut, "<!doctype html>\n");
	fprintf(cgiOut, "<html lang=\"en\">\n");
	fprintf(cgiOut, "  <head>\n");
	fprintf(cgiOut, "    <!-- Required meta tags -->\n");
	fprintf(cgiOut, "    <meta charset=\"utf-8\">\n");
	fprintf(cgiOut, "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\">\n");
	fprintf(cgiOut, "\n");
	fprintf(cgiOut, "    <!-- Bootstrap CSS -->\n");
	fprintf(cgiOut, "    <link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css\" integrity=\"sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh\" crossorigin=\"anonymous\">\n");
	fprintf(cgiOut, "\n");
	fprintf(cgiOut, "    <title>Sesame</title>\n");
	fprintf(cgiOut, "  </head>\n");
	fprintf(cgiOut, "  <body>\n");
	fprintf(cgiOut, "  <div class=\"container\">\n");
	fprintf(cgiOut, "  <h1>Sesame</h1>\n");
}


/*
	ends the page
*/
void sesameHandleFooter()
{
	fprintf(cgiOut, "</div></body></html>\n");
}


/*
	HTML form markup to submit the pin.  Pin must be in the list on file.
	
*/
void sesameShowPinForm() {

	fprintf(cgiOut, "<form action=\"/cgi-bin/sesame.cgi\" method=\"post\">\n");
	fprintf(cgiOut, "Pin: <input type=\"text\" name=\"userpin\" value=\"\">\n");
	fprintf(cgiOut, "    <input type=\"submit\" name=\"submit_userpin\" value=\"Submit\"></>");
	fprintf(cgiOut, "</form>\n");
	fprintf(cgiOut, "\n");
}


/*
	Retrieve the userpin from the input tag
*/
void sesameGetUserPin() {
	cgiFormStringNoNewlines("userpin", userpin, USERPIN_LEN);
}


/*
	HTML form markup to get the OTP from the user
*/
void sesameShowOTPForm() {

	//fprintf(cgiOut, "User OTP=%s<br/>", userotp);
	fprintf(cgiOut, "<form action=\"/cgi-bin/sesame.cgi\"  method=\"post\">\n");
	fprintf(cgiOut, "Enter OTP: <input type=\"text\" name=\"input_userotp\" value=\"\">\n");
	fprintf(cgiOut, "    <input type=\"submit\" name=\"submit_userotp\" value=\"Open\"></>\n");
	fprintf(cgiOut, "    <input type=\"hidden\" name=\"userpin\" value=\"%s\"/>\n", userpin);
	fprintf(cgiOut, "</form>\n");
	fprintf(cgiOut, "\n");

}

/*
	generate a one-time password
*/
void sesameGenOTP()
{
	char otp[USEROTP_LEN];
	MD5_HASH md5_hash;
	time_t seconds;

	// get the current time in seconds since 1-Jan 1970
	seconds = time(NULL);

	// calc two minute intervals - this will be the amount 
	// of time that the OTP is valid
	long two_min_intervals = (long) (seconds / 120);

	// combine the userpin and the otp into a string
	sprintf(otp, "%s%ld", userpin, two_min_intervals);

	// generate a hash of the string
	md5(&md5_hash, otp, strlen(otp));

	// convert the hash into a string
	sprintf(userotp,"%ld", labs((long)md5_hash.h0));

	// keep the string to 6 characters
	userotp[6] = '\0';

}

/*
	Get the one-time password from the user
*/
void sesameGetUserOTP() {
	cgiFormStringNoNewlines("input_userotp", input_userotp, USEROTP_LEN);
}


/*
	Generate an OTP and compare to what the user submitted
*/

int sesameCheckOTP() {
	int otpMatch = 0;

	//fprintf(cgiOut, "get the pin number from the user<br/>\n");
	sesameGetUserPin();

	//fprintf(cgiOut, "generate an OTP based on the pin<br/>\n");
	sesameGenOTP();

	//fprintf(cgiOut, "get the OTP from the user<br/>\n");
	sesameGetUserOTP();

	//fprintf(cgiOut, "compare the user-supplied OTP to the generated OTP.<br/>\n");
	// if they match, then send a one-shot signal
	if (!strcmp(input_userotp, userotp))
	{
		//fprintf(cgiOut, "the strings match<br/>\n");

		otpMatch = 1;
		wireOneShot();
	}

	return otpMatch;
}

/*
	Display error message when the pin is not valid
*/
void sesameShowPinError()
{
	fprintf(cgiOut, "<p class=\"text-danger\">Pin is not valid</p>");
}

/*
	Display an error message when the one-time password is not valid
*/
void sesameShowOTPError()
{
	fprintf(cgiOut, "<p class=\"text-danger\">OTP is not valid.</p>");
}

/*
	Call the user module to determine if the pin is valid
*/
int sesameIsValidUserPin()
{
	
	return userIsValid(userpin);
}

/*
	Call the mail module to the email address associated with the pin
*/
void sesameSendOTP()
{
	char email[USER_LEN];
	
	if (userGetEmail(userpin, email))
	{
		mailSendOTP(email, userotp);
	}
}

void sesameSendNotification()
{
	char email[USER_LEN];
	char adminEmail[USER_LEN];
	int hasUserEmail	= userGetEmail(userpin, email);
	int hasAdminEmail	= userGetEmail("admin", adminEmail);

	if (hasUserEmail && hasAdminEmail)
	{
		mailSendNotification(adminEmail, userpin, email);
	}
}