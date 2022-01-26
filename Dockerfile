FROM gcc

COPY . /usr/src

WORKDIR /usr/src

RUN g++ -std=c++17 ./src/index.cpp -pthread -o ./.src/index && ./.src/index

CMD [ "./.src/index" ]