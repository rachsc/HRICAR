# TESTEAR EL RECONOCIMIENTO DE CARAS EN TIAGo
## SmartFaceRecognition
Es el componente encargado del reconocimiento de caras. Ahora mismo lo tengo entrenado simplemente para reconocer a Barack Obama, a Joe Biden y a mi. Así que podéis probar poniendo fotos de Obama y Biden a ver si los reconoce.
En este componente hay un script llamado [load_recognition.sh](SmartFaceRecognition/smartsoft/src/load_recognition.sh) que lanza el código python [realtime_face_recognition.py](realtime_face_recognition.py) de reconocimiento de caras

## ComponentROSCamera
Es el componente que me permite conectarme al tópico de la cámara "/usb_cam/image_raw" cogiendo la imagen a través de "sensor_msgs.Image" como se puede ver en el archivo [cam.rosinterfacespool](ComponentROSCamera/model/cam.rosinterfacespool).

## Pasos a seguir
1. Añadir ambos componentes al entorno SmartSoft e incluirlos en el sistema de TIAGo.

2. Copiar el archivo python [realtime_face_recognition.py](realtime_face_recognition.py y las fotos [obama.jpg](obama.jpg) y [biden.jpg](biden.jpg) en una carpeta.

3. Instalar el módulo de python face_recognition: `pip install face_recognition`

4. Asegurarse que [load_recognition.sh](SmartFaceRecognition/smartsoft/src/load_recognition.sh) tiene permisos de ejecución.

5. Instalar el paquete usb_cam de ROS:

    `cd /YOUR_PATH_TO_CATKIN_WORKSPACE/src`
    
    `git clone https://github.com/ros-drivers/usb_cam.git`
    
    `cd ..`
    
    `catkin build`
    
    `source devel/setup.bash`
    
6. Pueden testear este paquete así:

    `roslaunch usb_cam usb_cam-test.launch`

7. En el launch file de usb_cam está configurado para que coja la señal de video de /dev/video0. Si la cámara no va a estar ahí, debéis cambiarlo.

8. Cambiar los paths en:
	- SmartFaceRecognition/smartsoft/src/CaptureTask.cc el path para lanzar el script load_recognition.sh
	- load_recognition.sh el path para lanzar el código python realtime_face_recognition.py
	- realtime_face_recognition.py el path donde coge las fotos de Obama y Biden. 
    
9. Hacer el deploy del sistema y al hacer click en start le llegará el streaming de video de la cámara y a cualquiera que no sea obama o biden lo reconocerá como "Unknown".
