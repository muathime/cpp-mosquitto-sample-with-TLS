all: pub sub
	echo "Build finish!"

publish: publish.cpp
	g++ publish.cpp -o pub -lmosquitto && ./pub

subscribe: subscribe.cpp
	g++ subscribe.cpp -o sub -lmosquitto && ./sub

clean:
	rm pub && clear

