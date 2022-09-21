# utilities

validate_exit() {
    if [ $? != 0 ]; then
        exit 1
    fi
}

# state variabls

TARGET=
ROOT_DIR=~/Development/kyst
COMPILE_CMD="make"
CONFIGURE=false
RUN=true

SLN=kyst.sln

WIN=false
if [ "$OSTYPE" = "msys" ]; then
    WIN=true
    ROOT_DIR="c:/Users/darko/Development/kyst/"    
fi

# command line arguments

while getopts "t:c" option; do
    case $option in
        t)
            TARGET=$OPTARG
            ;;
        c)
            CONFIGURE=true
            ;;        
    esac
done

if [ -z $TARGET  ] || [ $TARGET = ${SLN} ] || [ $TARGET = "engine" ]; then
    RUN=false
fi

# configuration

if [ $CONFIGURE = true ]; then
    echo "INFO: configure MSBuild"
    cd ${ROOT_DIR}/build
    cmake ..
    validate_exit
    
    if [ $WIN == true ]; then
        echo "INFO: configure Ninja"    
        cd $ROOT_DIR/ninja/
        cmake -G"Ninja" ..
        validate_exit
    fi
    mv compile_commands.json ..

    exit 0
fi

# build

EXE_NAME=./$TARGET
if [ $WIN == true ]; then
    EXE_NAME=${EXE_NAME}.exe
    if [ -z $TARGET ]; then
        TARGET=${SLN}
    else 
        TARGET=${TARGET}.vcxproj
    fi
    # COMPILE_CMD="MSBuild.exe -target:Build /property:Configuration=Release"
    COMPILE_CMD="MSBuild.exe -target:Build /property:Configuration=Debug"
fi

echo "COMPILE_CMD: ${COMPILE_CMD}"
cd $ROOT_DIR/build
$COMPILE_CMD $TARGET
validate_exit

# run

if [ $RUN == true ]; then
    echo "EXE_NAME: ${EXE_NAME}"    
    cd $ROOT_DIR/bin
    $EXE_NAME
fi

