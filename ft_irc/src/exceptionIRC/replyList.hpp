#pragma once

/*
Dummy reply number. Not used.
*/
#define RPL_NONE 300
#define RPLDESC_NONE ""

/*
- Reply format used by USERHOST to list replies to
the query list.  The reply string is composed as
follows:

<reply> ::= <nick>['*'] '=' <'+'|'-'><hostname>

The '*' indicates whether the client has registered
as an Operator.  The '-' or '+' characters represent
whether the client has set an AWAY message or not
respectively.
*/
#define RPL_USERHOST 302
// ":[<reply>{<space><reply>}]"
#define RPLDESC_USERHOST ":[<reply>{<space><reply>}]"

/*
- Reply format used by ISON to list replies to the
query list.
*/
#define RPL_ISON 303
// ":[<nick> {<space><nick>}]"
#define RPLDESC_ISON ":[<nick> {<space><nick>}]"

/*

*/
#define RPL_AWAY 301
// "<nick> :<away message>"
#define RPLDESC_AWAY "%s :%s"

/*

*/
#define RPL_UNAWAY 305
#define RPLDESC_UNAWAY ":You are no longer marked as being away"

/*
- These replies are used with the AWAY command (if
allowed).  RPL_AWAY is sent to any client sending a
PRIVMSG to a client which is away.  RPL_AWAY is only
sent by the server to which the client is connected.
Replies RPL_UNAWAY and RPL_NOWAWAY are sent when the
client removes and sets an AWAY message.
*/
#define RPL_NOWAWAY 306
// 
#define RPLDESC_NOWAWAY ":You have been marked as being away"


/*

*/
#define RPL_WHOISUSER 311
// "<nick> <user> <host> * :<real name>"
#define RPLDESC_WHOISUSER "%s %s %s * :%s"


/*

*/
#define RPL_WHOISSERVER 312
// "<nick> <server> :<server info>"
#define RPLDESC_WHOISSERVER "%s %s :%s"

/*

*/
#define RPL_WHOISOPERATOR 313
// "<nick> :is an IRC operator"
#define RPLDESC_WHOISOPERATOR "%s :is an IRC operator"

/*

*/
#define RPL_WHOISIDLE 317
// "<nick> <integer> :seconds idle"
#define RPLDESC_WHOISIDLE "%s %i :seconds idle"


/*

*/
#define RPL_ENDOFWHOIS 318
// "<nick> :End of /WHOIS list"
#define RPLDESC_ENDOFWHOIS "%s :End of /WHOIS list"


/*
- Replies 311 - 313, 317 - 319 are all replies
generated in response to a WHOIS message.  Given that
there are enough parameters present, the answering
server must either formulate a reply out of the above
numerics (if the query nick is found) or return an
error reply.  The '*' in RPL_WHOISUSER is there as
the literal character and not as a wild card.  For
each reply set, only RPL_WHOISCHANNELS may appear
more than once (for long lists of channel names).
The '@' and '+' characters next to the channel name
indicate whether a client is a channel operator or
has been granted permission to speak on a moderated
channel.  The RPL_ENDOFWHOIS reply is used to mark
the end of processing a WHOIS message.
*/
#define RPL_WHOISCHANNELS 319
// "<nick> :{[@|+]<channel><space>}"
#define RPLDESC_WHOISCHANNELS "<nick> :{[@|+]<channel><space>}"

/*

*/
#define RPL_WHOWASUSER 319
// "<nick> <user> <host> * :<real name>"
#define RPLDESC_WHOWASUSER "%s %s %s * :%s"

/*
- When replying to a WHOWAS message, a server must use
the replies RPL_WHOWASUSER, RPL_WHOISSERVER or
ERR_WASNOSUCHNICK for each nickname in the presented list. 
At the end of all reply batches, there must
be RPL_ENDOFWHOWAS (even if there was only one reply
and it was an error).
*/
#define RPL_ENDOFWHOWAS 369
// "<nick> :End of WHOWAS"
#define RPLDESC_ENDOFWHOWAS "%s :End of WHOWAS"


/*

*/
#define RPL_LISTSTART 321
#define RPLDESC_LISTSTART "Channel :Users  Name"


/*

*/
#define RPL_LIST 322
// "<channel> <# visible> :<topic>"
#define RPLDESC_LIST "%s %s :%s"

/*
- Replies RPL_LISTSTART, RPL_LIST, RPL_LISTEND mark
the start, actual replies with data and end of the
server's response to a LIST command.  If there are
no channels available to return, only the start
and end reply must be sent.
*/
#define RPL_LISTEND 323
// 
#define RPLDESC_LISTEND ":End of /LIST"

/*

*/
#define RPL_CHANNELMODEIS 324
// "<channel> <mode> <mode params>"
#define RPLDESC_CHANNELMODEIS "%s %s %s"

/*

*/
#define RPL_NOTOPIC 331
// "<channel> :No topic is set"
#define RPLDESC_NOTOPIC "%s :No topic is set"


/*
- When sending a TOPIC message to determine the
channel topic, one of two replies is sent.  If
the topic is set, RPL_TOPIC is sent back else
RPL_NOTOPIC.
*/
#define RPL_TOPIC 332
// "<channel> :<topic>"
#define RPLDESC_TOPIC "%s :%s"

/*
- Returned by the server to indicate that the
attempted INVITE message was successful and is
being passed onto the end client.
*/
#define RPL_INVITING 341
// "<channel> <nick>"
#define RPLDESC_INVITING "%s %s"

/*
- Returned by a server answering a SUMMON message to
indicate that it is summoning that user.
*/
#define RPL_SUMMONING 342
// "<user> :Summoning user to IRC"
#define RPLDESC_SUMMONING "%s :Summoning user to IRC"


/*
- Reply by the server showing its version details.
The <version> is the version of the software being
used (including any patchlevel revisions) and the
<debuglevel> is used to indicate if the server is
running in "debug mode".

The "comments" field may contain any comments about
the version or further version details.
*/
#define RPL_VERSION 351
// "<version>.<debuglevel> <server> :<comments>"
#define RPLDESC_VERSION "%s.%s %s :%s"


/*

*/
#define RPL_WHOREPLY 352
// "<channel> <user> <host> <server> <nick> <H|G>[*][@|+] :<hopcount> <real name>"
#define RPLDESC_WHOREPLY "<channel> <user> <host> <server> <nick> <H|G>[*][@|+] :<hopcount> <real name>"

/*
- The RPL_WHOREPLY and RPL_ENDOFWHO pair are used
to answer a WHO message.  The RPL_WHOREPLY is only
sent if there is an appropriate match to the WHO
query.  If there is a list of parameters supplied
with a WHO message, a RPL_ENDOFWHO must be sent
after processing each list item with <name> being
the item.
*/
#define RPL_ENDOFWHO 315
// "<name> :End of /WHO list"
#define RPLDESC_ENDOFWHO "%s :End of /WHO list"

/*

*/
#define RPL_NAMREPLY 353
// "<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]"
#define RPLDESC_NAMREPLY "<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]"


/*
- To reply to a NAMES message, a reply pair consisting
of RPL_NAMREPLY and RPL_ENDOFNAMES is sent by the
server back to the client.  If there is no channel
found as in the query, then only RPL_ENDOFNAMES is
returned.  The exception to this is when a NAMES
message is sent with no parameters and all visible
channels and contents are sent back in a series of
RPL_NAMEREPLY messages with a RPL_ENDOFNAMES to mark
the end.
*/
#define RPL_ENDOFNAMES 366
// "<channel> :End of /NAMES list"
#define RPLDESC_ENDOFNAMES "%s :End of /NAMES list"


/*

*/
#define RPL_LINKS 364
// "<mask> <server> :<hopcount> <server info>"
#define RPLDESC_LINKS "%s %S :%i %s"

/*
- In replying to the LINKS message, a server must send
replies back using the RPL_LINKS numeric and mark the
end of the list using an RPL_ENDOFLINKS reply.
*/
#define RPL_ENDOFLINKS 365
// "<mask> :End of /LINKS list"
#define RPLDESC_ENDOFLINKS "%s :End of /LINKS list"

/*

*/
#define RPL_BANLIST 367
// "<channel> <banid>"
#define RPLDESC_BANLIST "%s %i"


/*
- When listing the active 'bans' for a given channel,
a server is required to send the list back using the
RPL_BANLIST and RPL_ENDOFBANLIST messages.  A separate
RPL_BANLIST is sent for each active banid.  After the
banids have been listed (or if none present) a
RPL_ENDOFBANLIST must be sent.
*/
#define RPL_ENDOFBANLIST 368
// "<channel> :End of channel ban list"
#define RPLDESC_ENDOFBANLIST "%s :End of channel ban list"


/*

*/
#define RPL_INFO 371
// ":<string>"
#define RPLDESC_INFO ":%s"

/*
- A server responding to an INFO message is required to
send all its 'info' in a series of RPL_INFO messages
with a RPL_ENDOFINFO reply to indicate the end of the
replies.

*/
#define RPL_ENDOFINFO 374
#define RPLDESC_ENDOFINFO ":End of /INFO list"

/*

*/
#define RPL_MOTDSTART 375
// ":- <server> Message of the day - "
#define RPLDESC_MOTDSTART ":- %s Message of the day - "


/*

*/
#define RPL_MOTD 372
// ":- <text>"
#define RPLDESC_MOTD ":- %s"


/*
- When responding to the MOTD message and the MOTD file
is found, the file is displayed line by line, with
each line no longer than 80 characters, using
RPL_MOTD format replies.  These should be surrounded
by a RPL_MOTDSTART (before the RPL_MOTDs) and an
RPL_ENDOFMOTD (after).
*/
#define RPL_ENDOFMOTD 376
#define RPLDESC_ENDOFMOTD ":End of /MOTD command"

/*
- RPL_YOUREOPER is sent back to a client which has
just successfully issued an OPER message and gained
operator status.

*/
#define RPL_YOUREOPER 381
#define RPLDESC_YOUREOPER ":You are now an IRC operator"

/*
- If the REHASH option is used and an operator sends
a REHASH message, an RPL_REHASHING is sent back to
the operator.
*/
#define RPL_REHASHING 382
// "<config file> :Rehashing"
#define RPLDESC_REHASHING "%s :Rehashing"


/*
- When replying to the TIME message, a server must send
the reply using the RPL_TIME format above.  The string
showing the time need only contain the correct day and
time there.  There is no further requirement for the
time string.
*/
#define RPL_TIME 391
// "<server> :<string showing server's local time>"
#define RPLDESC_TIME "%s :%s"


/*

*/
#define RPL_USERSSTART 392
#define RPLDESC_USERSSTART ":UserID   Terminal  Host"

/*

*/
#define RPL_USERS 393
// ":%-8s %-9s %-8s"
#define RPLDESC_USERS ":%-8s %-9s %-8s"

/*

*/
#define RPL_ENDOFUSERS 394
#define RPLDESC_ENDOFUSERS ":End of users"


/*
- If the USERS message is handled by a server, the
replies RPL_USERSTART, RPL_USERS, RPL_ENDOFUSERS and
RPL_NOUSERS are used.  RPL_USERSSTART must be sent
first, following by either a sequence of RPL_USERS
or a single RPL_NOUSER.  Following this is
RPL_ENDOFUSERS.
*/
#define RPL_NOUSERS 395
#define RPLDESC_NOUSERS ":Nobody logged in"


/*

*/
#define RPL_TRACELINK 200
// "Link <version & debug level> <destination> <next server>"
#define RPLDESC_TRACELINK "Link %s %s %s"

/*
201     RPL_TRACECONNECTING
                        "Try. <class> <server>"

*/
#define RPL_TRACECONNECTING 201
// "Try. <class> <server>"
#define RPLDESC_TRACECONNECTING "Try. %s %s"

/*

*/
#define RPL_TRACEHANDSHAKE 202
// "H.S. <class> <server>"
#define RPLDESC_TRACEHANDSHAKE "H.S. %s %s"


/*

*/
#define RPL_TRACEUNKNOWN 203
// "???? <class> [<client IP address in dot form>]"
#define RPLDESC_TRACEUNKNOWN "???? <class> [<client IP address in dot form>]"


/*

*/
#define RPL_TRACEOPERATOR 204
// "Oper <class> <nick>"
#define RPLDESC_TRACEOPERATOR "Oper %s %s"

/*
205     RPL_TRACEUSER
                        "User <class> <nick>"

*/
#define RPL_TRACEUSER 205
// "User <class> <nick>"
#define RPLDESC_TRACEUSER "User %s %s"

/*

*/
#define RPL_TRACESERVER 206
// "Serv <class> <int>S <int>C <server> <nick!user|*!*>@<host|server>"
#define RPLDESC_TRACESERVER "Serv <class> <int>S <int>C <server> <nick!user|*!*>@<host|server>"


/*

*/
#define RPL_TRACENEWTYPE 208
// "<newtype> 0 <client name>"
#define RPLDESC_TRACENEWTYPE "%s 0 %s"

/*
- The RPL_TRACE* are all returned by the server in
response to the TRACE message.  How many are
returned is dependent on the the TRACE message and
whether it was sent by an operator or not.  There
is no predefined order for which occurs first.
Replies RPL_TRACEUNKNOWN, RPL_TRACECONNECTING and
RPL_TRACEHANDSHAKE are all used for connections
which have not been fully established and are either
unknown, still attempting to connect or in the
process of completing the 'server handshake'.
RPL_TRACELINK is sent by any server which handles
a TRACE message and has to pass it on to another
server.  The list of RPL_TRACELINKs sent in
response to a TRACE command traversing the IRC
network should reflect the actual connectivity of
the servers themselves along that path.
RPL_TRACENEWTYPE is to be used for any connection
which does not fit in the other categories but is
being displayed anyway.
*/
#define RPL_TRACELOG 261
// "File <logfile> <debug level>"
#define RPLDESC_TRACELOG "File %s %s"

/*

*/
#define RPL_STATSLINKINFO 211
// "<linkname> <sendq> <sent messages> <sent bytes> <received messages> <received bytes> <time open>"
#define RPLDESC_STATSLINKINFO "<linkname> <sendq> <sent messages> <sent bytes> <received messages> <received bytes> <time open>"

/*

*/
#define RPL_STATSCOMMANDS 212
// "<command> <count>"
#define RPLDESC_STATSCOMMANDS "%s %i"

/*

*/
#define RPL_STATSCLINE 213
// "C <host> * <name> <port> <class>"
#define RPLDESC_STATSCLINE "C <host> * <name> <port> <class>"

/*

*/
#define RPL_STATSNLINE 214
// "N <host> * <name> <port> <class>"
#define RPLDESC_STATSNLINE "N <host> * <name> <port> <class>"

/*

*/
#define RPL_STATSILINE 215
// "I <host> * <host> <port> <class>"
#define RPLDESC_STATSILINE "I <host> * <host> <port> <class>"


/*

*/
#define RPL_STATSKLINE 216
// "K <host> * <username> <port> <class>"
#define RPLDESC_STATSKLINE "K <host> * <username> <port> <class>"


/*

*/
#define RPL_STATSYLINE 218
// "Y <class> <ping frequency> <connect frequency> <max sendq>"
#define RPLDESC_STATSYLINE "Y <class> <ping frequency> <connect frequency> <max sendq>"

/*

*/
#define RPL_ENDOFSTATS 219
// "<stats letter> :End of /STATS report"
#define RPLDESC_ENDOFSTATS "<stats letter> :End of /STATS report"

/*

*/
#define RPL_STATSLLINE 241
// "L <hostmask> * <servername> <maxdepth>"
#define RPLDESC_STATSLLINE "L <hostmask> * <servername> <maxdepth>"


/*

*/
#define RPL_STATSUPTIME
// ":Server Up %d days %d:%02d:%02d"
#define RPLDESC_STATSUPTIME ":Server Up %d days %d:%02d:%02d"


/*

*/
#define RPL_STATSOLINE 243
// "O <hostmask> * <name>"
#define RPLDESC_STATSOLINE "O <hostmask> * <name>"

/*

*/
#define RPL_STATSHLINE 244
// "H <hostmask> * <servername>"
#define RPLDESC_STATSHLINE "H <hostmask> * <servername>"

/*
- To answer a query about a client's own mode,
RPL_UMODEIS is sent back.
*/
#define RPL_UMODEIS 221
// "<user mode string>"
#define RPLDESC_UMODEIS "%s"


/*

*/
#define RPL_LUSERCLIENT
// ":There are <integer> users and <integer> invisible on <integer> servers"
#define RPLDESC_LUSERCLIENT ":There are %i users and %i invisible on %i servers"


/*

*/
#define RPL_LUSEROP 252
// "<integer> :operator(s) online"
#define RPLDESC_LUSEROP "%i :operator(s) online"

/*

*/
#define RPL_LUSERUNKNOWN 253
// "<integer> :unknown connection(s)"
#define RPLDESC_LUSERUNKNOWN "%i :unknown connection(s)"

/*

*/
#define RPL_LUSERCHANNELS 254
// "<integer> :channels formed"
#define RPLDESC_LUSERCHANNELS "%i :channels formed"

/*
- In processing an LUSERS message, the server
sends a set of replies from RPL_LUSERCLIENT,
RPL_LUSEROP, RPL_USERUNKNOWN,
RPL_LUSERCHANNELS and RPL_LUSERME.  When
replying, a server must send back
RPL_LUSERCLIENT and RPL_LUSERME.  The other
replies are only sent back if a non-zero count
is found for them.
*/
#define RPL_LUSERME 255
// ":I have <integer> clients and <integer> servers"
#define RPLDESC_LUSERME ":I have %i clients and %i servers"


/*

*/
#define RPL_ADMINME 256
// "<server> :Administrative info"
#define RPLDESC_ADMINME "%s :Administrative info"

/*

*/
#define RPL_ADMINLOC1 257
// ":<admin info>"
#define RPLDESC_ADMINLOC1 ":%s"

/*

*/
#define RPL_ADMINLOC2 258
// ":<admin info>"
#define RPLDESC_ADMINLOC2 ":%s"

/*
- When replying to an ADMIN message, a server
is expected to use replies RLP_ADMINME
through to RPL_ADMINEMAIL and provide a text
message with each.  For RPL_ADMINLOC1 a
description of what city, state and country
the server is in is expected, followed by
details of the university and department
(RPL_ADMINLOC2) and finally the administrative
contact for the server (an email address here
is required) in RPL_ADMINEMAIL.
*/
#define RPL_ADMINEMAIL 259
// ":<admin info>"
#define RPLDESC_ADMINEMAIL ":%s"

