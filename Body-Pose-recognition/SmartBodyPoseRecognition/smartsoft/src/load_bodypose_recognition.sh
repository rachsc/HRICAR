#!/bin/sh

docker run --rm --device=/dev/video0:/dev/video0 -e DISPLAY=$DISPLAY -v /root/.Xauthority:/root/.Xauthority:rw -v /tmp/.X11-unix/:/tmp/.X11-unix --name pose_container pose_image
cd /root/exchange/repos/SystemTIAGoManualNavigation/smartsoft/SystemTIAGoManualNavigation.deployment/DockerImage/SmartBodyPoseRecognition_data
