#!/usr/bin/perl

use Mail::Mailer;

print "Content-type:text/html\n\n";

read(STDIN, $buffer, $ENV{'CONTENT_LENGTH'});
@pairs = split(/&/, $buffer);
foreach $pair (@pairs) {
        ($name, $value) = split(/=/, $pair);
        $value =~ tr/+/ /;
        $value =~ s/%([a-fA-F0-9][a-fA-F0-9])/pack("C", hex($1))/eg;
#        $value =~ s/\n/ /g;     # replace newlines with spaces
#        $value =~ s/\r//g;      # remove hard returns
        $value =~ s/\cM//g;     # delete ^M's
        $FORM{$name} = $value;
}

open(OUTF,">>../comments/survey.out") or dienice("Couldn't open survey.out for
writing: $!");

# This locks the file so no other CGI can write to it at the 
# same time...
flock(OUTF,2);
# Reset the file pointer to the end of the file, in case 
# someone wrote to it while we waited for the lock...
seek(OUTF,0,2);

print OUTF "\n---------------------------------------------------------------\n";
print OUTF "$FORM{'comments'}\n";

close(OUTF);

$email="kartik\@cs.binghamton.edu";
$subject="[CS552] Course Feedback";
$mailer = Mail::Mailer->new("sendmail");
$mailer->open({ From	=> $email,
       		To	=> $email,
		Subject => $subject,
	      })
	 or die "Can't open: $!\n";
print $mailer "$FORM{'comments'}\n";
$mailer->close();

print "<html><head><title>Feedback Form</title></head>\n";
print "<body>\n";
print "<h2>Thanks for your feedback!</h2>\n";
print "</body></html>";

sub dienice {
        my($msg) = @_;
        print "<h2>Error</h2>\n";
        print $msg;
        exit;
}
