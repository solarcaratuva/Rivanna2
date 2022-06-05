FROM ghcr.io/armmbed/mbed-os-env:mbed-os-6.15.1-latest

ENV DEBIAN_FRONTEND=noninteractive

RUN set -x \
    && apt -y update \
    && apt -y install \
    clangd-12 \
    vim \
    nano \
    usbutils \
    && :

RUN set -x \
    && pip3 install -U \
    cantools \
    platformio \
    && :
