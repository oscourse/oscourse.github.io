#!/usr/bin/perl

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

open(OUTF,">>../srs/review.html") or dienice("Couldn't open review.txt for writing: $!");

# This locks the file so no other CGI can write to it at the 
# same time...
flock(OUTF,2);
# Reset the file pointer to the end of the file, in case 
# someone wrote to it while we waited for the lock...
seek(OUTF,0,2);

print OUTF "<hr>\n<br>\n";
print OUTF "Review for Paper <b><i>``";
print OUTF "$FORM{'title'}";
print OUTF "''</b></i><br>\n";
print OUTF "By <b>";
print OUTF "$FORM{'yourname'}\n";
print OUTF "</b><br>\n";
print OUTF "<p>``";
print OUTF "$FORM{'comments'}";
print OUTF "''</p>\n\n";

close(OUTF);

#$email="kartik\@cs.binghamton.edu";
#$subject="Paper Review";
#$mailer = Mail::Mailer->new("sendmail");
#$mailer->open({ From	=> $email,
#       		To	=> $email,
#		Subject => $subject,
#	      })
#	 or die "Can't open: $!\n";
#print $mailer "$FORM{'comments'}\n";
#$mailer->close();

print "<html><head><title>Review Done</title></head>\n";
print "<body>\n";
print "<h2>Thanks for your review!</h2>\n";
print "You can read other people's reviews <a href=../srs/review.html>here</a>\n";
print "</body></html>";

sub dienice {
        my($msg) = @_;
        print "<h2>Error</h2>\n";
        print $msg;
        exit;
}
