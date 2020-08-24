# RSSk8r
REALLY SICK SYNDIK8R<br>
RSSk8r is a command line (for now?) tool written in C that facilitates quick and easy publishing to an rss feed on your local computer. I made this because I couldn't find an rss feed builder that was open source and worked on GNU/Linux. RSSk8r is released under GPLv3 so you're free to copy, distribute or modify it as you see fit.

# Usage
When run from the command line, it's possible to pass the location of your rss file as an argument. If you don't, or if you run it by double-clicking, you'll be prompted to supply the rss file's location once the program is loaded. The file must be a .xml file which contains at least one rss post (indicated by the \<item\> tag). Documentation for the RSS format can be found at http://blogs.law.harvard.edu/tech/rss. There is a sample.xml file available in this repository if you need it.
<br><br>Once you've supplied a valid file, the program prompts you for the following information for each post: URL, TITLE, DESCRIPTION. It then timestamps the post and adds it to the top of your RSS file's posts. Every RSS post needs a unique ID, and this is generated from the URL attached to the post. If there is no URL, I suggest keysmashing some random characters to ensure your audience's RSS reader recognises it as a unique post. There are character limits shown for each input field. It is possible to post images or extra links using html inside the description box.
<br><br>The program keeps track of how many items you've pushed in your session, and after each push the program prompts for the next URL. It is possible to upload your .xml file in between pushes without closing the program. This program is intended to be run inside a herbstluftwm/i3 terminal alongside your rss reader, as a less algorithm and surveillance based alternative to a share button, but I am not the boss of you so use it however works for you.
# Screenshots
Using with gnome and feedreader
<img src="https://github.com/Echolalien/rssk8r/blob/master/Screenshot%20from%202020-08-23%2018-53-24.png">
Using with herbstluftwm and newsboat
<img src="https://github.com/Echolalien/rssk8r/blob/master/screenshot.png">
Thanks to stormy for screenshots
