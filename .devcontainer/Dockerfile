FROM yoshiyasu1111/verilator:v5.048

# 環境変数の設定
ENV LANG=ja_JP.UTF-8 \
    LANGUAGE=ja_JP:ja \
    LC_ALL=ja_JP.UTF-8 \
    DISPLAY=:1 \
    RESOLUTION=1024x768x24 \
    XAUTHLOCALQUEUEDIR=/tmp/user-x11 \
    XDG_RUNTIME_DIR=/tmp/runtime-veriuser

RUN useradd -m veriuser -s /bin/bash \
    && apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends cmake ninja-build git ca-certificates libsdl3-dev xvfb x11vnc locales \
    && sed -i -E 's/# (ja_JP.UTF-8)/\1/' /etc/locale.gen \
    && locale-gen \
    && update-locale LANG=ja_JP.UTF-8 \
    && mkdir -p /tmp/user-x11 && chmod 1777 /tmp/user-x11 \
    && rm -fr /var/lib/apt/lists/*

RUN echo '#!/bin/bash\n\
Xvfb $DISPLAY -screen 0 $RESOLUTION -nolisten tcp &\n\
sleep 1\n\
x11vnc -display :1 -forever -shared -passwd password -bg &\n\
sleep 1\n\
exec "$@"' > /home/veriuser/entrypoint.sh && chmod +x /home/veriuser/entrypoint.sh

ENTRYPOINT ["/home/veriuser/entrypoint.sh"]