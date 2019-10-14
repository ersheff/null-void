Null/Void

This repo contains the Pd patches and Arduino code for Anna Weisling's <emph>Null/Void<emph> dissertation project.

Prepping the Raspberry Pi:
1. Install Raspbian Lite onto your micro SD card https://www.raspberrypi.org/downloads/raspbian/
2. Create blank file named "ssh" in boot directory on micro SD card (enables SSH)
3. SSH into Pi via Terminal `ssh -XY pi@raspberrypi.local`
4. Install Git `sudo apt-get install git`


Setup Pd and Arduino:
1. Install Pd Vanilla
    - On macOS: download from http://puredata.info/downloads/pure-data or Miller Puckette's site http://msp.ucsd.edu/software.html
    - On Pi: install via apt-get in the terminal `sudo apt-get install puredata`
2. Install Pd dependencies&mdash;comport, rampsmooth~, and tanh~
    - On macOS: recommended through Pd's "Find externals" in the Help menu
    - On Pi: possibly via apt-get? (double check this)
        - `sudo apt-get install pd-comport`
        - `sudo apt-get install pd-cyclone`
3. Download/update the Pd and Arduino repo via Git
     - First time `git clone https://github.com/ersheff/null-void.git`
     - Updates `git pull`
4. Upload Arduino code to Arduino (recommended from macOS)
5. Prep startup script (to-do)

Pd patches, Arduino code, and Raspberry Pi setup by Eric Sheffield
Anna Weisling & Eric Sheffield © 2019


To-dos:
- In patch
    - Finish initializations and mode changes
- Create startup script
    - Pd starup flags to try/investigate
        - nogui
        - rt (audio flag?)
        - audiodev (once I figure out what it is)
        - audiobuf (in ms)
        - blocksize (in samples)
        - alsa (default, probably not necessary)
        - listdev