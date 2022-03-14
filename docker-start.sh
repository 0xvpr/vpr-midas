#!/bin/sh

# Creator:    VPR
# Created:    March 13th, 2022
# Updated:    March 13th, 2022

set -e pipefail
set -e errexit
set -e nounset
set -e xtrace

PROJECT="midas"

DOCKER_IMAGE="${PROJECT}-dev"
DOCKER_WORK_DIR="/home/${DOCKER_IMAGE}/${PROJECT}"

docker run -itv "${PWD}:${DOCKER_WORK_DIR}" "${DOCKER_IMAGE}"
