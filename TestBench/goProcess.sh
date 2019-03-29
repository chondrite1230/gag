rm -r ../bin
cd ../build
rm -r *
cmake ../source
make -j 4
make install
cd ../TestBench
#../bin/Application_Main
