# release version
clear && g++ $(find . -name "*.cpp") -I./asio/include -pthread -o rise

# debug version
clear && g++ -g -O0 -fsanitize=address -fno-omit-frame-pointer $(find . -name "*.cpp") -I./asio/include -pthread -o rise

./rise