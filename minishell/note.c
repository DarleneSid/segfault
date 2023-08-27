exit
	print "exit"
	AND EXIT
exit 12
	exit (12 % 256)
	print "exit"
	AND EXIT 
// exit n > 256
// 	exit (12 % 256)
// 	print "exit"
// 	AND EXIT
exit abc 12
	exit (2)
	print "bash: exit: abc: numeric argument required"
	AND EXIT
// exit abc 12 abc
// 	exit (2)
// 	print "bash: exit: abc: numeric argument required"
// 	AND EXIT
exit 12 abc
	print "exit"
	print "bash: exit: too many arguments"
	AND NOT EXIT
exit 9223372036854775807
	print "exit"
	AND EXIT
exit 9223372036854775808 OR ABOVE
	exit (2);
	print "exit"
	print "bash: exit: abc: numeric argument required"
	AND EXIT


NEED FUNC TO FREE EVERYTHING
NEED TO FREE EVERYTHING BEFORE EXIT
