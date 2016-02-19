FROM mercury/proxygen

RUN apt-get install google-mock

WORKDIR /root
RUN git clone https://github.com/kainlite/whatismyip whatismyip 
RUN cd whatismyip && mkdir build && cd build && cmake .. && make
