#pragma once

/*
- Used to indicate the nickname parameter supplied to a
command is currently unused.
*/
#define ERR_NOSUCHNICK 401
// "<nickname> :No such nick/channel"
#define ERRDESC_NOSUCHNICK "%s :No such nick/channel"

/*
- Used to indicate the server name given currently
doesn't exist.
*/
#define ERR_NOSUCHSERVER 402
// "<server name> :No such server"
#define ERRDESC_NOSUCHSERVER "%s :No such server"


/*
- Used to indicate the given channel name is invalid.
*/
#define ERR_NOSUCHCHANNEL 403
// "<channel name> :No such channel"
#define ERRDESC_NOSUCHCHANNEL "%s :No such channel"

/*
- Sent to a user who is either (a) not on a channel
which is mode +n or (b) not a chanop (or mode +v) on
a channel which has mode +m set and is trying to send
a PRIVMSG message to that channel.
*/
#define ERR_CANNOTSENDTOCHAN 404
// "<channel name> :Cannot send to channel"
#define ERRDESC_CANNOTSENDTOCHAN "%s :Cannot send to channel"

/*
- Sent to a user when they have joined the maximum
number of allowed channels and they try to join
another channel.
*/
#define ERR_TOOMANYCHANNELS 405
// "<channel name> :You have joined too many channels"
#define ERRDESC_TOOMANYCHANNELS "%s :You have joined too many channels"

/*
- Returned by WHOWAS to indicate there is no history
information for that nickname.
*/
#define ERR_WASNOSUCHNICK 406
// "<nickname> :There was no such nickname"
#define ERRDESC_WASNOSUCHNICK "%s :There was no such nickname"

/*
- Returned to a client which is attempting to send a
PRIVMSG/NOTICE using the user@host destination format
and for a user@host which has several occurrences.
*/
#define ERR_TOOMANYTARGETS 407
// "<target> :Duplicate recipients. No message delivered"
#define ERRDESC_TOOMANYTARGETS "%s :Duplicate recipients. No message delivered"

/*
- PING or PONG message missing the originator parameter
which is required since these commands must work
without valid prefixes.
*/
#define ERR_NOORIGIN 409
#define ERRDESC_NOORIGIN ":No origin specified"

/*

*/
#define ERR_NORECIPIENT 411
// ":No recipient given (<command>)"
#define ERRDESC_NORECIPIENT ":No recipient given (%s)"


/*
returned by PRIVMSG to indicate that
the message wasnt delivered for some reason.
*/
#define ERR_NOTEXTTOSEND 412
#define ERRDESC_NOTEXTTOSEND ":No text to send"

/*
returned by PRIVMSG to indicate that
the message wasnt delivered for some reason.
ERR_NOTOPLEVEL and ERRDESC_WILDTOPLEVEL are errors that
are returned when an invalid use of
"PRIVMSG $<server>" or "PRIVMSG #<host>" is attempted.
*/
#define ERR_NOTOPLEVEL 413
// "<mask> :No toplevel domain specified"
#define ERRDESC_NOTOPLEVEL "%s :No toplevel domain specified"

/*
returned by PRIVMSG to indicate that
the message wasnt delivered for some reason.
ERR_NOTOPLEVEL and ERRDESC_WILDTOPLEVEL are errors that
are returned when an invalid use of
"PRIVMSG $<server>" or "PRIVMSG #<host>" is attempted.
*/
#define ERR_WILDTOPLEVEL 414
// "<mask> :Wildcard in toplevel domain"
#define ERRDESC_WILDTOPLEVEL "%s :Wildcard in toplevel domain"

/*
- Returned to a registered client to indicate that the
command sent is unknown by the server.
*/
#define ERR_UNKNOWNCOMMAND 421
// "<command> :Unknown command"
#define ERRDESC_UNKNOWNCOMMAND "%s :Unknown command"

/*
- Server's MOTD file could not be opened by the server.
*/
#define ERR_NOMOTD 422
#define ERRDESC_NOMOTD ":MOTD File is missing"

/*
- Returned by a server in response to an ADMIN message
when there is an error in finding the appropriate
information.
*/
#define ERR_NOADMININFO 423
// "<server> :No administrative info available"
#define ERRDESC_NOADMININFO "%s :No administrative info available"

/*
- Generic error message used to report a failed file
operation during the processing of a message.
*/
#define ERR_FILEERROR 424
// ":File error doing <file op> on <file>"
#define ERRDESC_FILEERROR ":File error doing %s"

/*
- Returned when a nickname parameter expected for a
command and isn't found.
*/
#define ERR_NONICKNAMEGIVEN 431
#define ERRDESC_NONICKNAMEGIVEN ":No nickname given"

/*
- Returned after receiving a NICK message which contains
characters which do not fall in the defined set.  See
section x.x.x for details on valid nicknames.
*/
#define ERR_ERRONEUSNICKNAME 432
// "<nick> :Erroneus nickname"
#define ERRDESC_ERRONEUSNICKNAME "%s :Erroneus nickname"

/*
- Returned when a NICK message is processed that results
in an attempt to change to a currently existing
nickname.
*/
#define ERR_NICKNAMEINUSE 433
// "<nick> :Nickname is already in use"
#define ERRDESC_NICKNAMEINUSE "%s :Nickname is already in use"

/*
- Returned by a server to a client when it detects a
nickname collision (registered of a NICK that
already exists by another server).
*/
#define ERR_NICKCOLLISION 436
// "<nick> :Nickname collision KILL"
#define ERRDESC_NICKCOLLISION "%s :Nickname collision KILL"

/*
- Returned by the server to indicate that the target
user of the command is not on the given channel.
*/
#define ERR_USERNOTINCHANNEL 441
// "<nick> <channel> :They aren't on that channel"
#define ERRDESC_USERNOTINCHANNEL "%s :They aren't on that channel"

/*
- Returned by the server whenever a client tries to
perform a channel effecting command for which the
client isn't a member.
*/
#define ERR_NOTONCHANNEL 442
// "<channel> :You're not on that channel"
#define ERRDESC_NOTONCHANNEL "%s :You're not on that channel"

/*
- Returned when a client tries to invite a user to a
channel they are already on.
*/
#define ERR_USERONCHANNEL 443
// "<user> <channel> :is already on channel"
#define ERRDESC_USERONCHANNEL "%s :is already on channel"

/*
- Returned by the summon after a SUMMON command for a
user was unable to be performed since they were not
logged in.
*/
#define ERR_NOLOGIN 444
// "<user> :User not logged in"
#define ERRDESC_NOLOGIN "%s :User not logged in"

/*
- Returned as a response to the SUMMON command.  Must be
returned by any server which does not implement it.
*/
#define ERR_SUMMONDISABLED 445
#define ERRDESC_SUMMONDISABLED ":SUMMON has been disabled"

/*
- Returned as a response to the USERS command.  Must be
returned by any server which does not implement it.
*/
#define ERR_USERSDISABLED 446
#define ERRDESC_USERSDISABLED ":USERS has been disabled"


/*
- Returned by the server to indicate that the client
must be registered before the server will allow it
to be parsed in detail.
*/
#define ERR_NOTREGISTERED 451
#define ERRDESC_NOTREGISTERED ":You have not registered"

/*
- Returned by the server by numerous commands to
indicate to the client that it didn't supply enough
parameters.
*/
#define ERR_NEEDMOREPARAMS 461
// "<command> :Not enough parameters"
#define ERRDESC_NEEDMOREPARAMS "%s :Not enough parameters"

/*
- Returned by the server to any link which tries to
change part of the registered details (such as
password or user details from second USER message).
*/
#define ERR_ALREADYREGISTRED 462
#define ERRDESC_ALREADYREGISTRED ":You may not reregister"

/*
- Returned to a client which attempts to register with
a server which does not been setup to allow
connections from the host the attempted connection
is tried.
*/
#define ERR_NOPERMFORHOST 463
#define ERRDESC_NOPERMFORHOST ":Your host isn't among the privileged"

/*
- Returned to indicate a failed attempt at registering
a connection for which a password was required and
was either not given or incorrect.
*/
#define ERR_PASSWDMISMATCH 464
#define ERRDESC_PASSWDMISMATCH ":Password incorrect"

/*
- Returned after an attempt to connect and register
yourself with a server which has been setup to
explicitly deny connections to you.
*/
#define ERR_YOUREBANNEDCREEP 465
#define ERRDESC_YOUREBANNEDCREEP ":You are banned from this server"

/*

*/
#define ERR_KEYSET 467
// "<channel> :Channel key already set"
#define ERRDESC_KEYSET "%s :Channel key already set"

/*

*/
#define ERR_CHANNELISFULL 471
// "<channel> :Cannot join channel (+l)"
#define ERRDESC_CHANNELISFULL "%s :Cannot join channel (+l)"

/*

*/
#define ERR_UNKNOWNMODE 472
// "<char> :is unknown mode char to me"
#define ERRDESC_UNKNOWNMODE "%s :is unknown mode char to me"

/*

*/
#define ERR_INVITEONLYCHAN 473
// "<channel> :Cannot join channel (+i)"
#define ERRDESC_INVITEONLYCHAN "%s :Cannot join channel (+i)"

/*

*/
#define ERR_BANNEDFROMCHAN 474
// "<channel> :Cannot join channel (+b)"
#define ERRDESC_BANNEDFROMCHAN "%s :Cannot join channel (+b)"

/*

*/
#define ERR_BADCHANNELKEY 475
// "<channel> :Cannot join channel (+k)"
#define ERRDESC_BADCHANNELKEY "%s :Cannot join channel (+k)"

/*

*/
#define ERR_BADCHANMASK 476
// "<channel> :Bad Channel Mask"
#define ERRDESC_BADCHANMASK "%s :Bad Channel Mask"

/*
- Any command requiring operator privileges to operate
must return this error to indicate the attempt was
unsuccessful.
*/
#define ERR_NOPRIVILEGES 481
#define ERRDESC_NOPRIVILEGES ":Permission Denied- You're not an IRC operator"

/*
- Any command requiring 'chanop' privileges (such as
MODE messages) must return this error if the client
making the attempt is not a chanop on the specified
channel.
*/
#define ERR_CHANOPRIVSNEEDED 482
// "<channel> :You're not channel operator"
#define ERRDESC_CHANOPRIVSNEEDED "%s :You're not channel operator"

/*
- Any attempts to use the KILL command on a server
are to be refused and this error returned directly
to the client.
*/
#define ERR_CANTKILLSERVER 483
#define ERRDESC_CANTKILLSERVER  ":You cant kill a server!"

/*
- If a client sends an OPER message and the server has
not been configured to allow connections from the
client's host as an operator, this error must be
returned.
*/
#define ERR_NOOPERHOST 491
#define ERRDESC_NOOPERHOST ":No O-lines for your host"

/*
- Returned by the server to indicate that a MODE
message was sent with a nickname parameter and that
the a mode flag sent was not recognized.
*/
#define ERR_UMODEUNKNOWNFLAG 501
#define ERRDESC_UMODEUNKNOWNFLAG ":Unknown MODE flag"

/*
- Error sent to any user trying to view or change the
user mode for a user other than themselves.
*/
#define ERR_USERSDONTMATCH 502
#define ERRDESC_USERSDONTMATCH ":Cant change mode for other users"

/*
- Error sent to a user when they try to set invalid limit
"<channel> l <limit> :Invalid limit mode parameter. Syntax: <limit>."
*/
#define ERR_INVLIMITMODE 503
#define ERRDESC_INVLIMITMODE "%s :Invalid limit mode parameter. Syntax: <limit>."

/*
- Error sent when there is nothing to change
*/
#define ERR_EMPTYLINE 601
#define ERRDESC_EMPTYLINE ""