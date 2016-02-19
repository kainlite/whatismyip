FROM mercury/proxygen

WORKDIR /root
RUN git clone https://github.com/kainlite/whatismyip whatismyip 
RUN cd whatismyip && mkdir build && cd build && cmake .. && make
