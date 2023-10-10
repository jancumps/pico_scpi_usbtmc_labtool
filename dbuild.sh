#!/bin/bash

docker build -t picobuilder ./.github/workflows 

# For CI build
docker run -it -v $_/../..:/armbuild picobuilder /bin/bash  -c "$(cat ./build.sh)"

# For jumping into the shell when local
#docker run -it -v $_/../..:/armbuild picobuilder /bin/bash