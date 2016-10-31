CXX=pgc++
CXXFLAGS=-fast -acc -ta=nvidia:rdc -Minfo=accel
CC=pgcc
CFLAGS=-fast -acc -ta=nvidia:rdc -Minfo=accel
CUDAC=nvcc
CUDAFLAGS=-std=c++11 -gencode arch=compute_50,code=compute_50 -Xcompiler -fopenmp -lgomp
FC=pgfortran
FFLAGS=-fast -acc -ta=nvidia -Minfo=accel
LDFLAGS=-Mcuda #-L$(CUDA_HOME)/lib64 -lcudart

all: main

.SUFFIXES:
.SUFFIXES: .c .o .f90 .cu .cpp .cuf
.c.o:
	$(CC) $(CFLAGS) -c $<
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<
.f90.o:
	$(FC) $(FFLAGS) -c $<
.cuf.o:
	$(FC) $(FFLAGS) -c $<
.cu.o:
	$(CUDAC) $(CUDAFLAGS) -c $<
.PHONY: clean
clean:
	rm -rf *.o *.ptx *.cub *.lst *.mod $(EXES)

main: main.o UniformRandomInt.o BaseRandom.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS) -lstdc++

clean:
	rm -Rf main pgprof* *.o core
