#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mail.h"


// Called from client
int haveMail()
{
	int result = 0;
    
    char str[] = "You've got mail!";
    
	printf("\n%s\n", str);
	result = sendAllEmails();
	
	if(result == 0){
		printf("Error sending emails\n");
	}
    
    return result;
}

// Grab the emails from the email file
int sendAllEmails(){
	int res = 0;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	FILE *file;
	
	// Open the file
	file = fopen(EMAILSFILE, "r");
	
	// If opened, proceed
	if(file != NULL){
		// Send each email
		
		while((read = getline(&line, &len, file)) != -1){
			line[strcspn(line, "\n")] = 0; // Get rid of the newline
			printf("Sending email to:%s\n", line);
			sendEmail(line);
			printf("Sent email to:%s\n\n", line);
		}
		
		fclose(file);
		if(line){
			free(line);
		}
		res = 1;
	}
	
	return res;
}

// Send the email
void sendEmail(char *addr){
	
	char cmd[100];
	
	// Email body  
	char *body = getMailText();
	
	// Temp file for sending the text  
	char tempFile[100]; 
	strcpy(tempFile,tempnam("/tmp","sendmail"));
	FILE *fp = fopen(tempFile,"w"); 
	fprintf(fp,"%s\n",body); 
	fclose(fp);

	// Send email with system()
	sprintf(cmd,"sendmail %s < %s",addr,tempFile); // Setup command
	system(cmd);

}

// Create the mail text here
char * getMailText(){
	char email[1024];
	char * res;
	struct tm *tm;
	time_t t;
	char timeStr[128];
	char dateStr[128];
	
	t = time(NULL);
	tm = localtime(&t);
	
	// Get the date and time
	// For my sanity: http://man7.org/linux/man-pages/man3/strftime.3.html
	strftime(timeStr, sizeof(timeStr), "%I:%M:%S %p", tm);
	strftime(dateStr, sizeof(dateStr), "%d/%m/%Y", tm);
	
	strcpy(email, "You've got mail in your mailbox!\n");
	strcat(email, "Mail arrived: ");
	strcat(email, dateStr);
	strcat(email, " at ");
	strcat(email, timeStr);
	strcat(email, ".\n");
	
	res = email;
	
	return res;
}
