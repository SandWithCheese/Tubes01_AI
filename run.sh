#!/bin/bash

# Build the binary
docker run -it --rm \
    -v "$(pwd)":/app \
    cpp-opengl-app /bin/bash -c "cd /app/build && cmake .. && make"

# Run the container
docker run -it --rm \
    -e DISPLAY="$DISPLAY" \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v "$(pwd)":/app \
    --network=host \
    cpp-opengl-app
