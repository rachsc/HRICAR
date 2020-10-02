# TESTEAR EL RECONOCIMIENTO DE POSE CORPORAL EN TIAGo
## SmartBodyPoseRecognition
Es el componente encargado del reconocimiento de pose corporal. Ahora mismo lo tengo entrenado para diferenciar entre "standing" y "sitting" y detectar el esqueleto de la persona. 
En este componente hay un script llamado [load_bodypose_recognition.sh](SmartBodyPoseRecognition/smartsoft/src/load_bodypose_recognition.sh) que lanza el código python [run_webcam.py](pose-estimation-detection/run_webcam.py).

## Pasos a seguir para testear con Docker (No GPU)
1. Copiar la carpeta en una carpeta [pose-estimation-detection](pose-estimation-detection) en nuestro host.

2. Antes de ejecutar pal_docker.sh, debemos crear la imagen docker para body pose recognition en nuestro host. Para ello ejecutamos los siguientes comandos en el host:
	```
	cd /host_path_to/pose-estimation-detection
	```
	```
	docker build -t pose_image .
	```

3. Añadir estas líneas al final de **pal_docker.sh**:
	```
	-v /host_path_to/pose-estimation-detection:/root/exchange/repos/pose-estimation-detection \
	-v /var/run/docker.sock:/var/run/docker.sock \
	-v /root/.Xauthority:/root/.Xauthority:rw \
	--env="DISPLAY" \
	--device=/dev/video0:/dev/video0 \
	```

4. Tener instalado docker en el entorno PAL de SmartSoft. Para ello añadí a **Dockerfile_SmartSoft_PAL_public_3_12** estas líneas:
	```
	RUN apt-get update
	RUN apt-get install -y apt-transport-https ca-certificates curl gnupg-agent software-properties-common
	RUN curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
	RUN add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu xenial stable"
	RUN apt-get update
	RUN apt-get -y install docker-ce
	```

5. Ejecutar pal_docker.sh

6. Añadir el componentes SmartBodyPoseRecognition al entorno SmartSoft e incluirlo en el sistema de TIAGo.

7. Asegurarse que [load_bodypose_recognition.sh](SmartBodyPoseRecognition/smartsoft/src/load_bodypose_recognition.sh) tiene permisos de ejecución.

9. La carpeta creada en el host en el paso 1 aparecerá ahora en el docker SmartSoft de PAL en /root/exchange/repos/pose-estimation-detection 

10. Hacer el deploy del sistema y al hacer click en start le llegará el streaming de video de la cámara.
