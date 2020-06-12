helpfunc() {
    echo
    echo "Usage: $0 [OPTIONS]"
    echo -e "\t-r/d Release mode or Debug mode build"
    echo -e "\t-h Show this help text"
    echo
    exit 1
}

function build_print {
    echo
    echo ------------ Building $1 $2 ------------
    echo
}

while getopts "rdh" opt
do
    case "$opt" in
        r ) opt_lvl=-O3 lvl_name="release" ;;
        d ) opt_lvl=-O0 lvl_name="debug" ;;
        h ) helpfunc ;;
        ? ) helpfunc ;;
    esac
done

if [[ "$lvl_name" != "release" ]]; then
    lvl_name="debug"
fi

rm -rf build
mkdir build

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    build_print LINUX $lvl_name
    clang++ $opt_lvl -std=c++17 -o build/rwc.out src/main.cpp src/Lexer.cpp
elif [[ "$OSTYPE" == "darwin"* ]]; then
    build_print MACOS $lvl_name
    clang++ $opt_lvl -std=c++1z -o build/rwc.out src/main.cpp src/Lexer.cpp
else
    echo Building using this script on the current operating system is currently unsupported.
    echo If you are on windows, then use build.bat or run.bat instead.
fi
