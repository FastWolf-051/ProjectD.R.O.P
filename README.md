# Project D.R.O.P
This is the first ever private server for the Project R.I.S.E<br>
This private server runs on game version v0.3.296710<br>
This project was written in C++ with using "asio" networking library from scratch in 2 days by fastwolf (me)<br>

For now, project only contains full login flow (which was kinda annoying to write), and because of that you can play in login screen<br>
I needed to publish this as soon as possible, that's why code quality in this project isn't perfect at some point.

# How to use
First of all, this project is using an .env file for sensitive data, and before launching server you need to to open file which is in **src/config/.config**<br>
You don't need to change anything in .config file, launch as it is<br>
Second, this project includes asio library, and on linux you can download this library like
```sh
sudo apt install libasio-dev
```
Then extract installed asio library, and update your installed library path in start.sh, and you are done<br>
Enjoy launching it

# Launching client

# Android
Now i'm decided to make a client to run with this server.<br>
Go to the https://mega.nz/folder/jComyLZb#jT0N2GlveP6xa0KsPnAy-w<br>
Then you will se an apk file and .so file. The .so file is script for client.<br>
Download those 2 files, and after installing apk file you need to run client script<br>
From PC you need to install an specific version of frida, do it like this
```sh
python3 -m pip uninstall frida frida-tools
python3 -m pip install --user frida==16.7.3 frida-tools==13.7.1
```

After installing, open cmd, type
```sh
frida -U gadget -l libfastwolf.so
```
And here you go!, you've just launched an android client!

# iOS
Launching an iOS client will be an bit easier, cuz it only changes destination ip.<br>
First of all, download the clean ipa file: https://drive.google.com/file/d/1PnzTPKl7i_xLzkQjH8aazyjx1S_wVR7Y/view
And in that link there is also ipPatcher.py which needs to be put inside Payload/Slash-IOS-Shipping.app<br>
Run that ipPatcher.py file on a macOS terminal to patch the binary<br>
Then compress the "Payload" folder once you're done<br>
And at last, change the ".zip" to ".ipa" through rename.<br>
And here you go!, you've just launched an iOs xlient!<br>

## Screenshots in-game
![Login Screen](images/login_screen.png)
Login in-game screen
![Lobby Screen](images/lobby_screen.png)
Lobby in-game screen
![Quests Screen](images/quests_screen.png)
Quests in-game screen

# Notice
If you want to fork, update or even rewrite this project to another language, you need to mention that original source was made by me

# Questions
If you have any question about server, you can direct message me<br>
On discord: fastdevlid
