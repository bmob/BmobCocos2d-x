pre := ./src/

objs := $(pre)/json_reader.o $(pre)/json_value.o $(pre)/json_writer.o \
#objs := main.o

libjson.so:$(objs)
#	g++ -o1 -o main $(objs) -ltemplate
	g++  -shared  -fPIC  -o  libjson.so  $(objs)
	cp libjson.so ../libs/
	rm libjson.so $(objs)

clean:
	rm libjson.so $(objs)