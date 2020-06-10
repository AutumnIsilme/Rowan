helpfunc()
{
    echo
    echo "Usage: $0 [OPTIONS]"
    echo -e "\t-r/d Release mode or Debug mode build"
    echo -e "\t-h Show this help text"
    echo
    exit 1
}

while getopts "rdh" opt
do
    case "$opt" in
        r ) parameterR=1 ;;
        d ) parameterR=0 ;;
        h ) helpfunc ;;
        ? ) helpfunc ;;
    esac
done

rm -rf build
mkdir build

if [ $parameterR -eq 0 ]; then
    echo
    echo ------------ Building debug ------------
    echo
    clang++ -O0 -o build/rwc.out src/main.cpp src/Lexer.cpp
    exit $?
else
    echo
    echo ------------ Building release ------------
    echo
    clang++ -O3 -o build/rwc.out src/main.cpp src/Lexer.cpp
    exit $?
fi
