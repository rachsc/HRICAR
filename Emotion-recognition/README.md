# TESTEAR EL RECONOCIMIENTO DE EMOCIONES EN TIAGo
## SmartEmotionRecognition
Es el componente encargado del reconocimiento de expresiones faciales (emociones). Este componente utiliza OpenCV para la detección de caras y un modelo ya diseñado y entrenado con Keras porque el objetivo es utilizar redes neuronales convolucionales (CNN) para detectar las 7 emociones básicas: felicidad, tristeza, miedo, sorpresa, asco, enfado y neutral.
En este componente hay un script llamado [load_emotionrecognition.sh](Emotion-recognition/SmartEmotionRecognition/smartsoft/src/load_emotionrecognition.sh) que lanza el código python [real_time_emotion_recognition.py](Emotion-recognition/emotion-recognition-src/real_time_emotion_recognition.py) de reconocimiento de emociones.

## Pasos a seguir
1. Añadir los dos componentes (SmartEmotionRecognition y ComponentROSCamera) al entorno SmartSoft e incluirlos en el sistema de TIAGo.

2. Copiar la carpeta donde está el código fuente python del reconocimiento de emociones [emotion-recognition-src](Emotion-recognition/emotion-recognition-src) en el directorio deseado.

3. Instalar los módulos necesarios en vuestro entorno SmartSoft de PAL:
    `pip install --upgrade pip`
    `cd /YOUR_PATH/Emotion-recognition/emotion-recognition-src`
    `python -m pip install -r requirements.txt`
    `python -m pip install tensorflow --ignore-installed`

4. Asegurarse que [load_emotionrecognition.sh](Emotion-recognition/SmartEmotionRecognition/smartsoft/src/load_emotionrecognition.sh) tiene permisos de ejecución.

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
	- SmartEmotionRecognition/smartsoft/src/CaptureTask.cc el path para lanzar el script load_emotionrecognition.sh
	- load_emotionrecognition.sh el path para lanzar el código python real_time_emoton_recognition.py (no cambiar la última lína salvo si el Sistema de TIAGo está en otro directorio) 
    
9. Hacer el deploy del sistema y al hacer click en start le llegará el streaming de video de la cámara y se desplegará una ventana donde detecta la cara indicando su expresión facial y otra ventana donde aparece el porcentaje de cada emoción.
