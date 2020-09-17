# TESTEAR EL RECONOCIMIENTO DE CARAS EN TIAGo
## SmartFaceRecognition
Es el componente encargado del reconocimiento de caras. Ahora mismo lo tengo entrenado simplemente para reconocer a Barack Obama, a Joe Biden y a mi. Así que podéis probar poniendo fotos de Obama y Biden a ver si los reconoce.
En este componente hay un script llamado [load_recognition.sh](SmartFaceRecognition/smartsoft/src/load_recognition.sh) que lanza el código python [realtime_face_recognition.py]() de reconocimiento de caras

## ComponentROSCamera
Es el componente que me permite conectarme al tópico de la cámara "/usb_cam/image_raw" cogiendo la imagen a través de "sensor_msgs.Image" como se puede ver en el archivo [cam.rosinterfacespool](ComponentROSCamera/model/cam.rosinterfacespool).

## Pasos a seguir
1. Añadir ambos componentes al entorno SmartSoft e incluirlos en el sistema de TIAGo.
2. 

