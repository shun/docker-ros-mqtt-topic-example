FROM eclipse-mosquitto

RUN apk update \
    && apk --no-cache add \
        nginx \
        nodejs \
        npm \
        supervisor \
    && npm install -g @vue/cli \
    && mkdir -p /var/log/supervisor /run/nginx
