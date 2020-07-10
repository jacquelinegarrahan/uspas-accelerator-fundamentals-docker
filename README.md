
#Set host IP
IP=$(ifconfig en0 | grep inet | awk '$1=="inet" {print $2}')
xhost + $IP


Scientific linux 5
root 5.28.00


open -a XQuartz


# G4Beamline:
docker run -d --name accelerator-fundamentals -e DISPLAY=$IP:0 -v /tmp/.X11-unix:/tmp/.X11-unix accelerator-fundamentals ./app/G4beamline/bin/g4blgui