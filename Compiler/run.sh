./build.sh -r
if [ $? -eq 0 ]; then
    echo
    echo ------------ Finished build ------------
    echo
    ./build/rwc.out
else
    echo Build failed
fi
