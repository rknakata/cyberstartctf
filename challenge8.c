#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "challenge8.h"

int main(int argc,char *argv[])
{
    int retVal; /* return value */
    char flagCurl[100]; /* holds the validation response */

    char urlPt1[200]; /* holds the url for pt 1 to be curled */
    char urlPt2[200]; /* holds the url for pt 2 to be curled */
    char urlPt3[200]; /* holds the url for pt 3 to be curled */
    char urlPt4[200]; /* holds the url for pt 4 to be curled */
    char urlPt5[200]; /* holds the url for pt 5 to be curled */
    char urlValidation[500]; /* holds the url for validation to be curled */
    
    char code[20]; /* holds all the parts combined (secret code)*/

    char urlResponse1[20]; /* holds the html for pt 1 */
    char urlResponse2[20]; /* holds the html for pt 2 */
    char urlResponse3[20]; /* holds the html for pt 3 */
    char urlResponse4[20]; /* holds the html for pt 4 */
    char urlResponse5[20]; /* holds the html for pt 5 */
    char urlValidationResponse[100]; /* holds the html for the validation */

    code[0] = '\0'; /* initialize the string to null */

    retVal = 0; /* if retVal doesnt change there are no errors */

    /* copy the urls into the variables */
    strcpy(urlPt1, "http://us.joincyberstart.com/c8-files/clock-pt1");
    strcpy(urlPt2, "http://us.joincyberstart.com/c8-files/clock-pt2");
    strcpy(urlPt3, "http://us.joincyberstart.com/c8-files/clock-pt3");
    strcpy(urlPt4, "http://us.joincyberstart.com/c8-files/clock-pt4");
    strcpy(urlPt5, "http://us.joincyberstart.com/c8-files/clock-pt5");    
    strcpy(urlValidation, "http://us.joincyberstart.com/c8-files/get-flag?string="); /* cat on the parts later */

    /* store the html in the html holders and update the secret code */
    getCurl(urlResponse1, urlPt1, 0); /* pass in 0 so it does not add on a " after the curl call */

    strcat(code, urlResponse1);

    getCurl(urlResponse2, urlPt2, 0); 
    strcat(code, urlResponse2);

    getCurl(urlResponse3, urlPt3, 0); 
    strcat(code, urlResponse3);

    getCurl(urlResponse4, urlPt4, 0); 
    strcat(code, urlResponse4);

    getCurl(urlResponse5, urlPt5, 0); 
    strcat(code, urlResponse5);

    /* secret code is filled update urlValidation URL */

    strcat(urlValidation, code); /* cat the secret code to the validation url */
    strcat(urlValidation, "\""); /* curl wants the url in quotation marks cuz the ? mark is a bash command */

    /* curl the validation url with the secret code */

    getCurl(urlValidationResponse, urlValidation ,1); /* pass in 1 so it add " */

    /* print the urlValidationResponse */

    printf("%s\n", urlValidationResponse);

    /* You have the flag */

    return retVal;
}

int getCurl(char code[500] ,char url[], int last)
{
    int retVal; /* return 0 if functions properly */
    char argument[500]; /* holds the argument to be sent to popen */
    FILE *commandOutput; /* used for popen */
    char error[500]; /* size of error */

    strcpy(error, code);

    retVal = 0;

    printf("%s\n", url);

    /* concatinate theargument */
    if (last == 1) /* you are on the last curl */
    {
        strcpy(argument, "curl \"");
    }
    else /* you are not on the last curl */
    {
        strcpy(argument, "curl ");
    }
    strcat(argument, url);

    printf("argument:%s\n",argument); /* prints url */

    /* get the output from the curl */
    commandOutput = popen(argument, "r");
    if(commandOutput == NULL)
    {
        printf("Error Failed to retrieve the HTML\n");
        retVal = -1; /* password was no retrieved failed */
    }

    /* read in the output of the command */
    while (fgets(code, sizeof(error)-1, commandOutput) != NULL)
    {
        /* print the retrieved password to console */
        printf("Retrieved HTML: %s", code);
        printf("\n");
    }
    return retVal;
}
