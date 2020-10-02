# TESTEAR EL RECONOCIMIENTO DE CARAS EN TIAGo
## SmartFaceRecognition
Es el componente encargado del reconocimiento de caras. Ahora mismo lo tengo entrenado simplemente para reconocer a Barack Obama, a Joe Biden y a mi. Así que podéis probar poniendo fotos de Obama y Biden a ver si los reconoce.
En este componente hay un script llamado [load_recognition.sh](Face-recognition/SmartFaceRecognition/smartsoft/src/load_recognition.sh) que lanza el código python [realtime_face_recognition.py](Face-recognition/realtime_face_recognition.py) de reconocimiento de caras

## Pasos a seguir para testear con Docker Nvidia GPU
1. Copiar [docker-compose.yml](Face-recognition/docker-compose.yml), [Dockerfile.gpu](Face-recognition/Dockerfile.gpu), el archivo python [realtime_face_recognition.py](Face-recognition/realtime_face_recognition.py) y las fotos [obama.jpg](Face-recognition/obama.jpg) y [biden.jpg](Face-recognition/biden.jpg) en una carpeta llamada face_recognition en nuestro host.

2. Antes de ejecutar pal_docker.sh, debemos crear la imagen docker para face_recognition en nuestro host:
	Instalar docker-compose:
	`curl -L "https://github.com/docker/compose/releases/download/1.27.4/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose`
	`chmod +x /usr/local/bin/docker-compose`
	Queremos que el contenedor docker pueda acceder a la webcam y que pueda mostrar un display desde el deployment del sistema de TIAGo:
	`xhost +local:docker`
	`export XSOCK=/tmp/.X11-unix`
	`export XAUTH=/tmp/.docker.xauth`
	`xauth nlist $DISPLAY | sed -e 's/^..../ffff/' | xauth -f $XAUTH nmerge -`
	Creamos la imagen del docker para face_recognition:
	`cd /host_path_to/face_recognition`
	`docker-compose up`

3. Añadir estas líneas al final de **pal_docker.sh**:
	-v /host_path_to/face_recognition:/root/exchange/repos/face_recognition \
	-v /var/run/docker.sock:/var/run/docker.sock \
	-v /root/.Xauthority:/root/.Xauthority:rw \
	--env="DISPLAY" \
	--device=/dev/video0:/dev/video0 \

4. Tener instalado docker en el entorno PAL de SmartSoft. Para ello añadí a **Dockerfile_SmartSoft_PAL_public_3_12** estas líneas:
	# Docker installation
	RUN apt-get update
	RUN apt-get install -y apt-transport-https ca-certificates curl gnupg-agent software-properties-common
	RUN curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
	RUN add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu xenial stable"
	RUN apt-get update
	RUN apt-get -y install docker-ce

5. Ejecutar pal_docker.sh

6. Añadir el componentes SmartFaceRecognition al entorno SmartSoft e incluirlo en el sistema de TIAGo.

7. Asegurarse que [load_recognition_gpu.sh](Face-recognition/SmartFaceRecognition/smartsoft/src/load_recognition_gpu.sh) tiene permisos de ejecución.

9. La carpeta creada en el host en el paso 1 aparecerá ahora en el docker SmartSoft de PAL en /root/exchange/repos/face_recognition.

10. Hacer el deploy del sistema y al hacer click en start le llegará el streaming de video de la cámara y a cualquiera que no sea obama o biden lo reconocerá como "Unknown".

