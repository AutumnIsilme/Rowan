helpfunc()
{
    echo
    echo "Usage: $0 [OPTIONS]"
    echo -e "\t-r/d Release mode or Debug mode build"
    echo -e "\t-h Show this help text"
    echo
    exit 1
}

rm -rf build
mkdir build
while getopts "rh" opt
do
    case "$opt" in
        r ) parameterR=1 ;;
        h ) helpfunc ;;
        ? ) helpfunc ;;
    esac
done

if [ -z "$parameterR" ]; then
    echo
    echo ------------ Building debug ------------
    echo
    clang++ -O2 -o build/rwc.out src/main.cpp src/Lexer.cpp
    exit $?
else
    echo
    echo ------------ Building release ------------
    echo
    clang++ -O3 -o build/rwc.out src/main.cpp src/Lexer.cpp
    exit $?
fi
