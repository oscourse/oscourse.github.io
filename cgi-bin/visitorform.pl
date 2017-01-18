#!/usr/local/bin/perl

use Time::Local;
#use Time::localtime;
use Mail::Mailer;
use CGI qw(:standard);
use CGI::Carp;

#=========================
# GLOBALS
#=========================
$DEFAULT_CGI = "http://websrv.cs.binghamton.edu/reference/travel/visitorform.cgi";

$OUTPUT_TYPE = "HTML";
$OUTPUT_TITLE = "VISITOR TRAVEL FORM ONLINE v1.0";
$ERR_MESSAGE = "Unknown Error/Default Error Message";
$CONTENT_PRINTED = 0;



#=========================
# SEQ of EVENTS
#=========================
main();
exit 0;

#=========================
# MAIN
#=========================
sub main{ 
	printcontent();
	printheader();

	if( param('reqtype') eq "Submit Form" ){

	    if( param('money') eq "yes" && 
	       ( !param('budget_no') || !param('SS_no') ) ){
		warning1();
	    }
#	    elsif( param('money') eq "no" && param('traveladvance') eq "yes"){
#		warning2();
#	    }
	    else{
		sendoutmail();
		confirmscreen();
	    }
	}
	else{
	    formscreen();
	}
	printfooter();
}


#====================
# PRINT CONTENT-TYPE
#====================
sub printcontent{
	if($OUTPUT_TYPE eq "GIF"){
		print "Content-type: image/gif\n\n";
	}
	elsif ($OUTPUT_TYPE eq "JPEG"){
		print "Content-type: image/jpeg\n\n";
	}
	elsif ($OUTPUT_TYPE eq "HTML") {
		print "Content-type: text/html\n\n";
	}
	else {
		$ERR_MESSAGE = "Unknown Content type Request";
		errorout();
	}
	$CONTENT_PRINTED = 1;
}


#===========
# header
#==========
sub printheader{

print <<Head_start;
    <HTML>
    <HEAD>
    <TITLE>CS\@FSU : Travel Authorization Form for Visitor</TITLE>

    <BASE HREF=\"http://www.cs.fsu.edu/\">

    <META   NAME=\"resource-type\"  CONTENT=\"document\">
    <META   NAME=\"description\"    CONTENT=\"Travel Authorization Form for Visitor\">
    <META   NAME=\"keywords\"       CONTENT=\"travel, visitor\">
    <META   NAME=\"distribution\"   CONTENT=\"local\">
    <META   NAME=\"copyright\"      CONTENT=\"2000\">

    <LINK REL=\"stylesheet\" TYPE=\"text/css\" HREF=\"style.css\" TITLE=\"StyleSheet\">

    </HEAD>
    <BODY>

    <TABLE><TR><TD WIDTH=1%>
    <A HREF=\"http://www.fsu.edu\">
    <IMG SRC=\"/icons/fsuseal.gif\" BORDER=0 ALIGN=LEFT>
    </A></TD><TD WIDTH=99%><CENTER>
    <A HREF=\"http://www.fsu.edu/~fsuas/\">COLLEGE OF ARTS AND SCIENCES<BR>
    <A HREF=\"http://www.cs.fsu.edu\">DEPARTMENT OF COMPUTER SCIENCE</A><BR>
    <A HREF=\"http://www.cs.fsu.edu/reference/\">REFERENCE & HELP</A><BR>
    <A HREF=\"http://www.cs.fsu.edu/reference/travel/\">TRAVEL</A><BR>
 
    </CENTER></TD></TR></TABLE>
 

Head_start

}

#=============
# footer
#============
sub printfooter{
    print "</BODY>
    </HTML>";
}

#==============
# fill out form
#==============
sub formscreen{
    print "<H1>Travel Authorization Form for Visitors</H1>";
    print "<HR>";
    print "<P><EM>All travel must be approved in advance</EM>, via a Travel
Authorization Request (TAR) form.</P>";

    print "<P>Please file in the appropriate information below; it will be
automatically sent to the <A HREF=\"people/staff.html\#dupont\">departmental
travel
representative</A>, who will let you know when the form is ready
to be signed. Also, please print out a copy of the form you send, as
a backup.</P>";

    print "<P><A HREF=\"reference/travel/rules.html\">If you are not already familiar
with the State of Florida rules regarding allowable travel
expenses, it would be a good idea to learn more about them by
following this link.</A></P>";

    print "<h3>General Data (applicable to all requests)</h3>";

    print "<form method=\"POST\" action=\"http://www.cs.fsu.edu/reference/travel/visitorform.cgi\">
  <table border=\"0\">
  <tr>
      <td width = \"365\" align=\"left\">Name:</td></tr>
  <tr>
      <td><input type=\"text\" size=\"30\" name=\"name\"></td></tr>
  <tr><td>Email Address:</td></tr>
  <tr>
      <td><input type=\"text\" size=\"40\" name=\"email\"></td></tr>
  <tr>
     <td>Mailing Address (this is the address to which your reimbursement check from Florida State University will be sent):</td>
  </tr>

  <tr>
    <td><input type=\"text\" size =\"100\" name=\"mailing_address\"></td>
  </tr>


  <tr>
      <td>Position:</td></tr>
  <tr>
      <td><input type=\"text\" size=\"40\" name=\"position\"></td></tr>
  <tr>
      <td width = \"365\" align=\"left\">Destination:</td></tr>
  <tr>
      <td><input type=\"text\" size=\"30\" name=\"dest\"></td>
      <!--<td><input type=\"text\" size=\"10\" name=\"dest_num\"></td>--></tr>
  </table>

  <table border=\"0\">
  <tr><td align=\"left\">Departure Date:</td>
      <td align=\"left\">Departure Time:</td></tr>
  <tr><td><input type=\"text\" size=\"14\" name=\"dep_date\"></td>
      <td><input type=\"text\" size=\"14\" name=\"dep_time\"></td></tr>
  <tr><td align=\"left\">Return Date:</td>
      <td align=\"left\">Return Time:</td></tr>
  <tr><td><input type=\"text\" size=\"14\" name=\"ret_date\"></td>
      <td><input type=\"text\" size=\"14\" name=\"ret_time\"></td></tr>
  </table>


Purpose of Trip: (e.g., to attend the ACM Symposium on High Reliablity Computing)<br>
  <textarea name=\"purpose\" rows=\"6\" cols=\"70\"></textarea><br>

<p>
Do you want expenses of the trip to be paid from a budget administered by FSU?
<ol>
  <li> <input type=\"radio\" name=\"money\" value=\"yes\">Yes
  <li> <input type=\"radio\" name=\"money\" VALUE=\"no\">No
</ol>

If you answered yes, please fill in the remainder of the form. Otherwise, proceed to the bottom of this page and press submit (after checking your data).<br>



<h3>Information when you want expenses of the trip to be paid from a budget administered by FSU:</h3>
<p> Please be sure that you:<br>
    <ol>
       <li>Retain all receipts.
       <li>Turn in all receipts with your request for reimbursement.
    </ol>


Budget Number: (Note: This field must be filled in order to process this form)
<br>
<input type=\"text\" size=\"15\" name=\"budget_no\" value=\"\"><br>

Social Security Number:(Note: This field must be filled in order to process this form)<br>
<input type=\"text\" size=\"15\" name=\"SS_no\"><br>

<p>
Benefit to state/sponsored project (Note: This field must be filled in order to process this form. Please provide a clear, concise, 
statement of the benefit your travel will provide to the State of Florida
of to a state-sponsored project. For example, Professional development, Public service, Dissemination of research results, Student recruitment, and Seeking sponsor for research. Do not use abbreviations or acronyms).<br>

  <textarea name=\"benefit\" rows=\"6\" cols =\"70\"></textarea><br>
<br>


<p>
Itinerary (day/time of departure and return):<br>
<textarea name=\"itinerary\" rows=\"6\" cols =\"70\"></textarea><br>
<br>



<p>
Expenditure breakdown:
<p>

<b>Airline</b><br>
Would you make the reservation or the department do it?<br>
<ol>
  <li> <input type=\"radio\" name=\"air_res\" value=\"I\">I make the reservation
  <li> <input type=\"radio\" name=\"air_res\" VALUE=\"dept\">The department make the reservation
</ol>

If you make the reservation, please fill out the following box. (Note: There are State of Florida restrictions on
which air carrier you can use and the allowable cost.
If you are not familiar with these rules, please follow this
<A HREF=\"reference/travel/rules.html#air\">link</A> to read about
them.):<br>
<input type=\"text\" size=\"70\" name=\"airfare\"><br>

<p>
<b>Hotel</b><br>
Would you make the reservation or the department do it?<br>
<ol>
  <li> <input type=\"radio\" name=\"hotel_res\" value=\"I\">I make the reservation
  <li> <input type=\"radio\" name=\"hotel_res\" VALUE=\"dept\">The department make the reservation
</ol>

If you make the reservation, please give name, nights, and cost. (Note: There are State of Florida
restrictions on allowable hotel expenses.
If you are not familiar with these rules, please follow this
<A HREF=\"reference/travel/rules.html#hotel\">link</A> to read about
them.):<br>
<input type=\"text\" size=\"70\" name=\"hotel\"
 value =\"Hotel: x nights \@ y $/night = $$$\"><br>


<p>
<b>Auto Rental</b><br>
Would you make the reservation or the department do it?<br>
<ol>
  <li> <input type=\"radio\" name=\"auto_res\" value=\"I\">I make the reservation
  <li> <input type=\"radio\" name=\"auto_res\" VALUE=\"dept\">The department make the reservation
</ol>

If you make the reservation, please give name, nights, and cost. (Note:
There are State of Florida restrictions on
which auto rental company you can use and the allowable cost.
If you are not familiar with these rules, please follow this
<A HREF=\"reference/travel/rules.html#hotel\">link</A> to read about
them.):<br>
<input type=\"text\" size=\"70\" name=\"auto\"
 value=\"Company: x days @ y $/hour = $$$\"><br>


<p>
Private Mileage:<br>
<input type=\"text\" size=\"70\" name=\"mileage\"><br>

<!--
<p>
If meals are included in conference registration fee?
<ol>
  <li> <input type=\"radio\" name=\"mealincluded\" value=\"yes\">
        Yes<br>
  <li> <input type=\"radio\" name=\"mealincluded\" VALUE=\"no\">
        No<br>
</ol>

If so, sepcify the registration fee:<br>
-->

Registration Fee:<br>
<input type=\"text\" size=\"70\" name=\"reg_fee\"><br>

Per Diem (Meals based on $21 per day):<br>
<input type=\"text\" size=\"70\" name=\"perdiem\"><br>


<p>
Incidental Expenses (Cab-fare, parking, etc):<br>
<textarea name=\"incidentals\" rows=\"6\" cols =\"70\"></textarea><br>

<h3>Non-Reimbursable Expenses</h3>
    <ul>
       <li>Meals included in conference fees </li>
       <li>Airline stopover charges or additional rerouting of air flight when made for personal convenience</li>
       <li>Car rental charges over the compact car rate, unless justified</li>
       <li>Driver's license or renewal fees</li>
       <li>Actual operating expenses for personal vehicles</li>
       <li>Traffic or parking violations and fines; court fees</li>
       <li>Personal expenses (toiletries, salons/barbers, city tours, golf fees, country club dues, health and fitness fees, pet care, shoe shine, souvenirs, personal entertainment, baby-sitting, hotel in-room movies and mini-bar sevices, newspapers)</li>
       <li>Food service tips</li>
       <li>Unauthorized trips</li>

    </ul>


<hr>
<br>

<h3>Please verify all information before submitting:</h3>

<ul>
  <li>Please remember that you must turn in a copy of the program/agenda.
  <li>Please retain all receipts.
  <li>Please turn in all receipts at one time together with your request if you want expenses of the trip to be paid from a budget administered by FSU.
</ul>

Thank you!<br><br> 

<input type=\"submit\" name=\"reqtype\" value=\"Submit Form\">
<input type=\"reset\" value=\"Clear Form\">
</form>
";

}


#===========
# warning #1
#===========
sub warning1{
    print "<h1>Sorry</h1>";
    print "<hr>";
    print "Your request cannot be sent to the departmental travel representative, since both Budget Number and SSN must be supplied if you want expenses of the trip to be paid from a budget administered by FSU. Please try again!";

}


#===========
# warning #2
#===========
sub warning2{
    print "<h1>Sorry</h1>";
    print "<hr>";
    print "Your request cannot be sent to the departmental travel representative, since you cannot request a travel advance if you do not want expenses of the trip to be paid from a budget administered by FSU. Please try again!";
}


#==============
# send out mail
#=============
sub sendoutmail{
  
    read(STDIN, $buffer, $ENV{'CONTENT_LENGTH'});

    my $visitorname=param('name');
    my $subject="Travel Authorization Information for Visitor";
    my $travelrep="Robin";

    my $body0="
Reply-to: $visitorname\n
Subject: Travel Authorization Information for Visitor.\n\n

Dear $travelrep:\n
Please process the following travel authorization request.\n\n
Remote host: $ENV{'REMOTE_HOST'}\n
Remote IP address: $ENV{'REMOTE_ADDR'}\n
----------------------------------------------------------\n\n
";


#   my $date=param('date');

   my $date=localtime();


    my $email=param('email');
    my $mailing_address = param('mailing_address');
    my $position=param('position');
    my $destination=param('dest');
    my $emergencynum=param('dest_num');
    my $departuredate=param('dep_date');
    my $departuretime=param('dep_time');
    my $returndate=param('ret_date');
    my $returntime=param('ret_time');
    my $purpose=param('purpose');
#    my $conflict=param('conflict');

    my $body1="
Name: $visitorname\n
Email: $email\n
Mailing Address : $mailing_address \n
Date: $date\n
Position: $position\n
Destination: $destination\n
Departure Date: $departuredate\t\t  Departure Time: $departuretime\n
Return Date: $returndate\t\t Return Time: $returntime\n
Purpose: $purpose\n
";



    my $money=param('money');

    my $body3="
Do you want expenses of the trip to be paid from a budget administered by FSU?: $money\n
";

    my $body4="";
    my $budget_no=param('budget_no');
    my $ss_no=param('SS_no');
    my $benefit=param('benefit');
#   my $others=param('others');
    my $itinerary=param('itinerary');
#   my $internation=param('internation');
#   my $flightcheck=param('flightcheck');
    my $air_res=param('air_res');
    my $airfare=param('airfare');
    my $hotel_res=param('hotel_res');
    my $hotel=param('hotel');
#   my $hotel2=param('hotel_2');
    my $auto_res=param('auto_res');
    my $auto=param('auto');
#   my $auto2=param('auto_2');
    my $mileage=param('mileage');
#   my $mealincluded=param('mealincluded');
    my $regfee=param('reg_fee');
    my $perdiem=param('perdiem');
#   my $perdieminternation=param('perdieminternation');
    my $incidentals=param('incidentals');

    if ($money eq "yes"){
	$body4=$body4."
Budget Number: $budget_no\n
SSN: $ss_no\n
Benefit: $benefit\n
Itinerary: $itinerary\n
Who make the airline reservation? $air_res\n
Airline and Cost: $airfare\n
Who make the hotel reservation? $hotel_res\n
Hotel: $hotel\n
Who make the Auto Rental reservation? $auto_res\n
Auto Rental: $auto\n
Private Mileage: $mileage\n
Registration Fee: $regfee\n
";
    }

	$body4=$body4."
Per Diem: $perdiem\n
Incidental Expreses: $incidentals\n
";

   
  $body=$body0.$body1.$body2.$body3.$body4;
    $recipient = "mcelhane\@cs.fsu.edu,jreed\@cs.fsu.edu";
 #  $recipient = "webmast\@cs.fsu.edu";
#  $recipient = "ming\@cs.fsu.edu, webmast\@cs.fsu.edu";

    $subject="Travel Authorization Information for Visitor";
  $mailer = Mail::Mailer->new("sendmail");
  $mailer->open({ From	=> $email,
       		  To	=> $recipient,
		  Subject => $subject,
		})
	    or die "Can't open: $!\n";
   print $mailer $body;
   $mailer->close();

  $mailer = Mail::Mailer->new("sendmail");
  $mailer->open({ From	=> $email,
       		  To	=> $email,
		  Subject => $subject,
		})
	    or die "Can't open: $!\n";
   print $mailer $body;
   $mailer->close();

}

#===============
# confirm Screen
#===============
sub confirmscreen{

    my $visitorname=param('name');
    my $date=localtime();
#    my $date=param('date');
    my $email=param('email');
    my $position=param('position');
    my $destination=param('dest');
#    my $emergencynum=param('dest_num');
    my $departuredate=param('dep_date');
    my $departuretime=param('dep_time');
    my $returndate=param('ret_date');
    my $returntime=param('ret_time');
    my $purpose=param('purpose');
#    my $conflict=param('conflict');
#    my $arrangements=param('arrangements');
    my $money=param('money');
#    my $traveladvance=param('traveladvance');

    my $budget_no=param('budget_no');
    my $ss_no=param('SS_no');
    my $benefit=param('benefit');
#    my $others=param('others');
    my $itinerary=param('itinerary');
#    my $internation=param('internation');
#    my $flightcheck=param('flightcheck');
    my $air_res=param('air_res');
   my $airfare=param('airfare');
    my $hotel_res=param('hotel_res');
    my $hotel=param('hotel');
#    my $hotel2=param('hotel_2');
    my $auto_res=param('auto_res');
   my $auto=param('auto');
#    my $auto2=param('auto_2');
    my $mileage=param('mileage');
#    my $mealincluded=param('mealincluded');
    my $regfee=param('reg_fee');
    my $perdiem=param('perdiem');
#    my $perdieminternation=param('perdieminternation');
    my $incidentals=param('incidentals');
#    my $webpage=param('webpage');
#    my $url=param('URL');
#    my $moneyadd=param('money_add');
#    my $otheradd=param('otheradd');


    print "<h1>Please Verify</h1><hr>";
    print "You have input the following data. Please check it for accuracy. If
you have made a minor error, please<a href=\"mailto:dupont\@cs.fsu.edu\">
click here to mail Robin DuPont</a> and indicate the changes you wish made.
Otherwise, reload the form and reenter each field.<br><br>";
    print "Name: $visitorname<br>";
    print "Date: $date<br>";
    print "Email Address: $email<br>";
    print "Position: $position<br>";
    print "Destination: $destination<br>";
    
    print "Departure date: $departuredate<br>";
    print "Departure time: $departuretime<br>";
    print "Return date: $returndate<br>";
    print "Return time: $returntime<br>";
    print "Purpose: <br>$purpose<br>";
#    print "Conflict with class: $conflict<br>";

#    if ( $conflict eq "yes")
#    {
#	print "Arrangements: <br>$arrangements<br>";
#    }

    print "Do you want expenses of the trip to be paid from a budget administered by FSU?: $money<br>";
#    print "Requesting travel advance?: $traveladvance<br>";

    if ($money eq "yes" ){
	print "Budget number: $budget_no<br>";
	print "SSN: $ss_no<br>";
	print "Benefit: <br>$benefit<br>";
#	print "Others from CS: $others<br>";
	print "Itinerary: <br>$itinerary<br>";
#	print "Is this travel international? $internation<BR>";
#	print "Requesting a flight check? $flightcheck<BR>";
	print "Who will make the airline reservation? $air_res<BR>";
	print "Airline and cost:  $airfare<br>";
	print "Who will make the hotel reservation? $hotel_res<BR>";
	print "Hotel: $hotel<br>"; 
#	print "Hotel #2: $hotel2<br>"; 
	print "Who will make auto rental reservation? $auto_res<BR>";
	print "Auto Rental:  $auto<br>";
#	print "Auto Rental:  $auto2<br>";
	print "Private Mileage:  $mileage<br>";
#	print "Meals are included in the registration fee? $mealincluded<BR>";
#	if( $mealincluded eq "yes"){
	print "Registration Fee:  $regfee<br>";

#	}
	print "Per Diem:  $perdiem<br>";
#	print "Per Diem (international):  $perdieminternation<br>";
#	print "Incidental Expenses:  <br>$incidentals<br>";
# 	print "Does the conference have a webpage? $webpage<BR>";

#	if( $webpage eq "yes" ){
#	    print "URL of the conference: $url<BR>";
#	}

#	print "Reimbursement check sent to: "; 

#	if ($moneyadd eq "cs")
#	{
#	    print "Computer Science Department<br>";
# 	}
#	else
#	{ 
#	    print "$otheradd<br>";   
#	}
    } 
}






