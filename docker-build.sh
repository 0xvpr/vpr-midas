#!/bin/sh

# Creator:    VPR
# Created:    March 13th, 2022
# Updated:    March 13th, 2022

set -e pipefail
set -e errexit
set -e nounset
set -e xtrace

PROJECT="midas"

DOCKER_FILE="Dockerfile"
DOCKER_IMAGE="${PROJECT}-dev"

# Builds docker image using root Dockerfile
docker build -f "${__docker_file}" -t "${DOCKER_IMAGE}" .
