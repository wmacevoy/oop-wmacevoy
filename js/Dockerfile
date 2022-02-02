# To Build: docker build -t js .
# To Run: docker run -v "$PWD:/app" -p 8080:8080 -t js


FROM node:12-alpine
# Adding build tools to make yarn install work on Apple silicon / arm64 machines
RUN apk add --no-cache python2 g++ make
RUN mkdir /app
WORKDIR /app
RUN yarn global add http-server
EXPOSE 8080
# COPY . .
# RUN yarn install --production
#CMD ["/bin/sh","-c","while true; do sleep 1; echo -n .; done"]
CMD ["http-server"]