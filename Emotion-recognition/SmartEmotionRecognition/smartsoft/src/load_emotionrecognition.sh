#!/bin/sh
pwd > /root/exchange/repos/Emotion-recognition/out.txt
cd /root/exchange/repos/Emotion-recognition
python real_time_emotion_recognition.py
cd /root/exchange/repos/SystemTIAGoManualNavigation/smartsoft/SystemTIAGoManualNavigation.deployment/DockerImage/SmartEmotionRecognition_data
