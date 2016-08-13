#ifndef mail_h_
#define mail_h_

#define EMAILSFILE "Emails/emails.txt"

int haveMail();
void sendEmail(char *mailAddr);
int sendAllEmails();
char * getMailText();

#endif
