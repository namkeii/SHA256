FROM archlinux:latest

RUN pacman -Syu --noconfirm \
    && pacman -S --noconfirm \
        gcc \
        make \
        libcxx \
        libcxxabi \
        libstdc++

WORKDIR /app
