docker build -t js . -and docker run --rm -v "$(pwd):/app" -p 8080:8080 js

