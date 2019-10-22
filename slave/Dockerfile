FROM ros:kinetic

RUN apt update \
    && apt install -y \
        curl \
        nginx \
        nodejs \
        npm \
        ros-kinetic-rosbridge-server \
        supervisor \
    && npm install -g n \
    && n stable \
    && npm install -g @vue/cli \
    && apt remove --purge -y nodejs npm \
    && rm -rf /var/lib/apt/lists/* \
    && mkdir -p /var/log/supervisor

