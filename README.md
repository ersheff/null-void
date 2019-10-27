# Null/Void

This repo contains the Pd patches and Arduino code for Anna Weisling's **Null/Void** dissertation project.

## Prepping the Raspberry Pi
1. Flash the backup image to your micro SD card using [balenaEtcher](https://www.balena.io/etcher/).
2. Connect the Pi to ethernet (either home network or by using internet sharing on macOS) and boot.
3. SSH into the Pi via terminal with `ssh -X pi@raspberrypi.local` (if you are asked whether to trust the host the first time, say yes).
4. The image already includes a version of the Null/Void repo and is set to run the **_main.pd** patch at boot. Quit Pd with `killall pd`. 
5. Update the Null/Void repo by running the following commands:
     - Change directory to null-void with `cd null-void`.
     - Update the repo with `git pull`.

## Prepping the Arduino
Download the Arduino code from the repo separately and upload to your Arduino (recommended from macOS).

## Running the Pi
Just plug it in. After about 30-40 seconds, the **_main.pd** patch will start automatically.

### To-dos:
- Add Anna’s features
- Add some kind of startup bloop for when the patch launches
- Remove redundant calibration swipe at boot AND serial connect (if possible)


Pd patches, Arduino code, and Raspberry Pi setup by Eric Sheffield  
Anna Weisling & Eric Sheffield © 2019
