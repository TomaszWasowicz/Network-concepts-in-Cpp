libcurl is a client-side URL library 


https://curl.se/ libcurl is free and open source software, 
it is client-side URL library, for transferring data with URLs. 
The command line utility (or API) is curl, 
it is one of common used utility in Linux.

libcurl and curl support most common used protocol like:
HTTP HTTPS, FTP, SFTP, IMAP, POP3, SCP, SFTP, SMTP, TFTP, 
TELNET, LDAP, or FILE. It works on many platforms like UNIX, 
AIX, Linux OpenBSD. 

In order to test the example, a echo web service server should be created, 
and it should be able to receive HTTP GET and HTTP POST requests with parameters

The example can also be executed through command line.

curl command line example: (server IP 192.168.0.107) curl --get http://192.168.0.107:1234/MyEchoWS curl --get http://192.168.0.107:1234/MyEchoWS -d "Name=Allan" -d "Gender=Male"

curl http://192.168.0.107:1234/MyEchoWS -d "Name=Allan" curl http://192.168.0.107:1234/MyEchoWS -d "{ Name : Allan Rose, Gender : Male }"
