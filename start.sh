cd src

clear

# this is asio installed library path
ASIO=/home/...../asio

# release version
# clear && g++ $(find . -name "*.cpp") -I./asio/include -pthread -o rise

# debug version
g++ -g -O0 -fsanitize=address -fno-omit-frame-pointer $(find . -name "*.cpp") -I"$ASIO/include" -pthread -o rise

./rise