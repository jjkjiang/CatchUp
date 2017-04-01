# CatchUp
The idea behind this project is to help gamers (or any general users of software that have patch notes) by creating an easy GUI to browse through changes since a certain date all neatly compiled together into their respective categories, chronologically.

## Considerations
This app was made with game communities in mind that tend to post patch notes in parallel with the official sites. Since every company has their own individual way of formatting their notes, parsing is done seperately from the client to lower the amount of scrapes required to actually serve users. A file produced by a scraping program that formats to the type readable by this application should be able to work for all games. This will not be a web app since I don't believe I would be able to afford hosting and I would like this to be a free service, so this will be a client-side portable app. Individual softwares' parsed text files can be done by individuals and hosted at websites or even just on GitHub.

## Tech Used
The client-side app will be built using C++ and the QT framework for our GUI, and the sample scraping/parsing program will be done with Python using beautifulsoup.

## Building
Use the CMake file provided! A compiled build will be provided when the project is closer to completion.
