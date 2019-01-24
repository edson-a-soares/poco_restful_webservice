FROM edsonsoares/poco:1.9-ubuntu

ENV DEBIAN_FRONTEND noninteractive

ENV CMAKE_DIRECTORY_NAME cmake-3.7.2
ENV CMAKE_FILE_NAME cmake-3.7.2.tar.gz
ENV CMAKE_DOWNLOAD_URL https://cmake.org/files/v3.7/cmake-3.7.2.tar.gz
ENV CMAKE_SHA256 dc1246c4e6d168ea4d6e042cfba577c1acd65feea27e56f5ff37df920c30cae0

ENV POCO_DOWNLOAD_URL https://pocoproject.org/releases/poco-1.9.0/poco-1.9.0-all.tar.gz
ENV POCO_DOWNLOAD_SHA256 0387bf0f9d313e2311742e1ad0b64e07f2f3e76039eed20e3b9aa9951b88e187

# Install application dependencies
RUN apt-get update -qq \
	&& apt-get install -yq software-properties-common python-software-properties \
	&& apt-add-repository ppa:ubuntu-toolchain-r/test \
	&& apt-get update \
	# Install CMake 3.7.2, GCC/G++ 6 and other dependencies
	&& apt-get install -yq --no-install-recommends \
		curl \
		git \
		libssl-dev \
		apt-utils \
		build-essential \
		unixodbc \
		unixodbc-dev \
		ca-certificates \
		libncurses-dev \
		pkg-config \
		apache2 \
		apache2-dev \
		cmake \
		gcc-6 \
		g++-6 \
	&& update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-6 60 --slave /usr/bin/g++ g++ /usr/bin/g++-6

# Download and Install CMake 3.7.2
RUN curl -fsSL "${CMAKE_DOWNLOAD_URL}" -o /tmp/cmake.tar.gz \
    && echo "$CMAKE_SHA256  /tmp/cmake.tar.gz" | sha256sum -c - \
    && tar --directory /tmp -xzf /tmp/cmake.tar.gz \
    && cd /tmp/$CMAKE_DIRECTORY_NAME && ./configure \
    && make && make install \
    && rm -rf /tmp/$CMAKE_FILE_NAME /tmp/cmake.tar.gz

# The variable expansion technique used in this variable definition allows passes arguments
# from the command line and persist them in the final image by leveraging the ENV instruction.
ARG POCO_WEBSERVICE_ENVIRONMENT
ENV POCO_WEBSERVICE_ENVIRONMENT=${POCO_WEBSERVICE_ENVIRONMENT:-development}

# It sets the build-time parameters default values
ARG CMAKE_BUILD_TYPE=Release

# Install the Web Service
COPY . /tmp/webservice
RUN cd /tmp/webservice \
    && cmake . \
        -DENABLE_TESTS=OFF \
        -DENABLE_STANDALONE_SERVICE=OFF \
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} \
    && make && make install \
    && rm -rf /tmp/webservice

# Add the Apache Connector file configuration file to the image
COPY data/settings/poco.load /etc/apache2/mods-available/poco.load

COPY scripts/shell/apache-setup-for-dockerfile.sh /tmp/apache-setup-for-dockerfile.sh

RUN chmod +x /tmp/apache-setup-for-dockerfile.sh \
    && /usr/sbin/apache2ctl stop \
    && /tmp/apache-setup-for-dockerfile.sh $POCO_WEBSERVICE_ENVIRONMENT \
    && rm /tmp/apache-setup-for-dockerfile.sh

CMD ["/usr/sbin/apache2ctl", "-DFOREGROUND"]

