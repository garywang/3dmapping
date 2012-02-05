
gl-dir=${PWD}/gl-117-1.3.2-src/src
kinect-dir=${PWD}/openFrameworks/addons/ofxKinect/example

all: 
	cd ${gl-dir}; make CXXLD="touch gl-117; echo"
	rm ${kinect-dir}/bin/example -f
	cd ${kinect-dir}; make USER_LDFLAGS=${gl-dir}/*.o
	cp ${kinect-dir}/bin/example ${gl-dir}/gl-117-kinect

