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
Just plug it in. After about 30-40 seconds, the **_main.pd** patch will start automatically, and you will hear a lovely startup chime.

## Refreshing the local installation
Run the following commands from the terminal on the Pi that needs its local Null/Void installation replaced with the current version in the remote repo:
`git fetch origin`
`git reset --hard origin/master`

Pd patches, Arduino code, and Raspberry Pi setup by Eric Sheffield  
Anna Weisling & Eric Sheffield © 2019
