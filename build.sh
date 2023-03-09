PYTHON_VERSION=$(python -c "import sys; print(sys.version_info[0])")

if [ $PYTHON_VERSION -ge 3 ] && [ $(python -c "import sys; print(sys.version_info[1])") -ge 6 ]; then
    echo "Python version is 3.6 or higher"
else
    echo "Python version is less than 3.6"
fi

python scripts/build.py