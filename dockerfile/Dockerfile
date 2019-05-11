FROM runmymind/docker-android-sdk:ubuntu-standalone

ENV ANDROID_HOME /opt/android-sdk-linux
ENV ANDROID_SDK_ROOT /opt/android-sdk-linux
ENV ANDROID_SDK_HOME /opt/android-sdk-linux
ENV ANDROID_SDK /opt/android-sdk-linux
ENV PATH ${PATH}:/opt/android-sdk-linux/platform-tools:/opt/android-sdk-linux/tools/bin:/opt/android-sdk-linux/emulator:/opt/android-sdk-linux/bin:

RUN sdkmanager

RUN apt update
RUN apt install -y cmake ant



#COPY Gopkg.lock Gopkg.toml /go/src/project/
#WORKDIR /go/src/project/
## Install library dependencies
#RUN dep ensure -vendor-only

# This results in a single layer image
#
#ENTRYPOINT ["/bin/project"]
#CMD ["--help"]