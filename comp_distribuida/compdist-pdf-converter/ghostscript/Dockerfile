FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update -y && apt-get install -y
RUN apt-get install -y ghostscript
RUN apt-get install -y python3-pip

WORKDIR /app

COPY ./flaskapp.py /app/
COPY ./templates /app/templates/

RUN pip3 install Flask Flask-RESTful

EXPOSE 5000

CMD ["python3", "flaskapp.py"]

# Build image
# sudo docker build -t gs .

# Run on port 5001
# sudo docker run -p 5001:5000 gs 
