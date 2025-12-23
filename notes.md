# Key Features
### Actual TCP/IP Protocol. 
Make a protocol. Establish a TCP connections

### Make it Hackable First. 
\n or \0 is bad practice and makes things hackable? - Only seems bad practice when saninitzation isnt done
Make a whitelist of allowable characters

### Fix the Hackable Version. 
Switch to a "length specified" protocol. What this means is that your 
protocol explicitly gives the length of every message in a confirmed fixed length 
format before sending any data. What this does is allows your server to properly 
allocate the correct size buffer, but also allows your server to immediately reject 
any messages that are too large. The line terminated protocol (hackable version) 
has the problem that a server has to completely read all the data before knowing that a 
message is too large. It also has to continually and correctly grow buffers to handle the space, 
which is a proven way to have a buffer overflow.

### Client and Server: 
Eventually need a custom client. GUI and TUI (Text UI) interfaces. 
Do a TUI first then make a GUI.





