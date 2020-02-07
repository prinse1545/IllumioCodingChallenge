# IllumioCodingChallenge
A packet-filtering implementation of a firewall class

Notes to the reviewer:

Having only 2 hours to complete this challenge was quite a hassle. My first intuition was to use python and pandas to be able to easily read in the csv file, but after reading the entire documnet I decided that python would be too inefficient so I opted for the use of C++ instead. I immediately knew that I needed an efficient data structure to not only insert the rules efficiently, but more importantly to match the rules with incoming packets reasonably quickly. Having taken a data structures course last semeseter I decided it might be prudent to use a red black tree as a solution since its search operation is of O(log(n)). I quickly copied and pasted the code for the red black tree that I already had and began implementing the firewall class. I also quickly realized that it would be to my advantage to split the one red black tree into four red black trees, tcpOutbound, tcpInbound, udpOutbound, and udpInbound since the data of what protocol and what direction the packet was coming from would be stored in the trees themselves. After I had figured out my design details, the implementaion was a breeze despite some bugs with converting the port from a string to an integer using a stringstream and reading in the file itself (it took me 15 minutes to realize that the reason my program wasn't able to read the file inside the firewall folder was because the executable was outside of the folder). Because most of my time was spent implementing the firewall class I did not have a lot of time to test it extensively, nor document it properly. Furthermore, I wish that I had had more time to experiment with different data structures. One that comes to mind is a map or an unordered map which both could potentially have a shorter run time. I also wonder if using a database such as mongoDB or mySQL would've proved beneficial, but since I had never implemented those in C++ I decided it would be better to stick with something I know. One last thing that I would've liked to do if I had more time was to come up with a more elegant solution for dealing with the ranges of the ip addresses and ports. Overall I'm quite proud of what I was able to come up in just 2 hours and hope you enjoy despite the lack of extensive testing and documentaion.

Rankings of Teams:

1. Platform Team
2. Data Team
3. Policy Team


