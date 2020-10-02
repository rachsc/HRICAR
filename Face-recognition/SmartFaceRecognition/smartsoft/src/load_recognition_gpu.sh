#!/bin/sh
cd /root/exchange/repos/face_recognition
docker-compose run -e DISPLAY=$DISPLAY -v /root/.Xauthority:/root/.Xauthority:rw -v /tmp/.X11-unix/:/tmp/.X11-unix face_recognition python3 facerec_from_webcam_faster.py
cd /root/exchange/repos/SystemTIAGoManualNavigation/smartsoft/SystemTIAGoManualNavigation.deployment/DockerImage/SmartFaceRecognition_data
