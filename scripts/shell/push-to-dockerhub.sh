#!/bin/bash

DOCKER_REPOSITORY_USERNAME=$1
DOCKER_REPOSITORY_PASSWORD=$2

echo "$DOCKER_REPOSITORY_PASSWORD" | docker login -u "$DOCKER_REPOSITORY_USERNAME" --password-stdin
docker push edsonsoares/poco_restful_webservice
