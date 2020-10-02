FROM python:3.5

# Install Build Utilities
RUN apt-get update && \
	apt-get install -y gcc make cmake apt-transport-https ca-certificates build-essential git python3-pip
RUN python3 -m pip install opencv-python
RUN apt-get update && \
	apt-get install -y libgl1-mesa-glx

# Check Python Environment
RUN python3 --version
RUN pip3 --version

# set the working directory for containers
WORKDIR  /usr/src/pose

# Installing opencv3
#RUN git clone https://github.com/Itseez/opencv.git
#RUN mv opencv opencv-3
#RUN mkdir /usr/src/pose/opencv-3/build
#RUN cd /usr/src/pose/opencv-3/build
#RUN cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local /usr/src/pose/opencv-3
#RUN make
#RUN make install

# set the working directory for containers
#WORKDIR  /usr/src/pose

# Installing Dependencies
##COPY requirements.txt .
COPY . .
RUN python3 -m pip install --upgrade setuptools
RUN python3 -m pip install --no-cache-dir -r requirements.txt
RUN python3 -m pip install tensorflow==1.14.0
RUN cd /usr/src/pose/tf_pose/pafprocess && \
	apt-get update && \
        apt-get install -y swig && \
        swig -python -c++ pafprocess.i && python3 setup.py build_ext --inplace
# Copy all the files from the project’s root to the working directory
##COPY . .

# Running Python Application
CMD ["python3", "run_webcam.py", "--model=mobilenet_thin", "--resize=432x368", "--camera=0"]
