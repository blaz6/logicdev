EXECUTABLE=./HelloWorld
if test -f "$EXECUTABLE"; then
    echo "==> Installing HelloWorld globally..."
    sudo cp ./HelloWorld /usr/bin/
    echo "==> Successfully installed"
else
    echo "Please first run ./build.sh!"
fi