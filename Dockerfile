FROM debian:bullseye

RUN apt-get update && \
    apt-get install -y build-essential locales && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

RUN sed -i '/en_US.UTF-8/s/^# //' /etc/locale.gen && \
    locale-gen
ENV LANG=en_US.UTF-8
ENV LANGUAGE=en_US:en
ENV LC_ALL=en_US.UTF-8

WORKDIR /app
COPY . /app

RUN gcc -std=c99 -D_XOPEN_SOURCE=700 main.c -o programa

CMD ["./programa"]

