PYTHON_VERSION=$(python -c "import sys; print(sys.version_info[0])")

if [ $PYTHON_VERSION -ge 3 ] && [ $(python -c "import sys; print(sys.version_info[1])") -ge 6 ]; then
    python scripts/build.py
else
    echo "Python version is less than 3.6. Please upgrade your python to version 3.6 or above"
fi