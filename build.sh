TARGET=
PROJ_DIR=~/Development/kyst
COMPILE_CMD="make"
SLN=kyst.sln

while getopts "t:" option; do
    case $option in
        t)
            TARGET=$OPTARG
            ;;
    esac
done

EXE_NAME=./$TARGET
if [ "$OSTYPE" = "msys" ]; then
    EXE_NAME=${EXE_NAME}.exe
    if [ -z $TARGET ]; then
        TARGET=${SLN}
    else 
        TARGET=${TARGET}.vcxproj
    fi
    COMPILE_CMD="MSBuild.exe -target:Build /property:Configuration=Release"
    PROJ_DIR="c:/Users/darko/Development/kyst/"
fi

echo "COMPILE_CMD: ${COMPILE_CMD}"
echo "EXE_NAME: ${EXE_NAME}"

cd $PROJ_DIR/build
$COMPILE_CMD $TARGET

if [ -z $TARGET  ] || [ $TARGET = ${SLN} ]; then
    exit 0
fi

cd $PROJ_DIR/bin
$EXE_NAME
