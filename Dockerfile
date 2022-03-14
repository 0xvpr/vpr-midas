# Creator:    VPR
# Created:    March 13th, 2022
# Updated:    March 13th, 2022

FROM ubuntu:20.04

# Set env to avoid user input interruption during installation
ENV TZ=America/Chicago
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Install deps
RUN apt-get update -y
RUN apt-get install -y --no-install-recommends sudo \
                                               zsh \
                                               zsh-autosuggestions \
                                               git \
                                               curl \
                                               wget \
                                               vim \
                                               tree \
                                               tmux \
                                               zip \
                                               unzip \
                                               pkg-config \
                                               m4 \
                                               libtool \
                                               automake \
                                               gnutls-bin \
                                               make \
                                               build-essential \
                                               mingw-w64 \
                                               mingw-w64-common \
                                               mingw-w64-i686-dev \
                                               mingw-w64-x86-64-dev

# Change login shell to zsh
RUN chsh -s /bin/zsh $(whoami)

# Create omega-zero user && working directory
RUN mkdir -p /home/midas-dev
ENV HOME=/home/root
WORKDIR /home/midas-dev/midas
