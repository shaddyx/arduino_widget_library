FROM python:3.10.0-buster

ENV APP_VERSION="5.2.4" \
    APP="platformio-core"

LABEL app.name="${APP}" \
      app.version="${APP_VERSION}" \
      maintainer="Anatolii.Yakushko <shaddyx@gmail.com>"

RUN pip install -U platformio==${APP_VERSION} && \
    mkdir -p /workspace && \
    mkdir -p /.platformio && \
    chmod a+rwx /.platformio && \
    apt update && apt install -y git build-essential cmake automake && apt-get clean autoclean && apt-get autoremove --yes && rm -rf /var/lib/{apt,dpkg,cache,log}/

#USER 1001

WORKDIR /workspace

RUN pio platform install "native"

#ADD ./ /workspace

#RUN chmod +x entrypoint.sh



#ENTRYPOINT ["./entrypoint.sh"] 