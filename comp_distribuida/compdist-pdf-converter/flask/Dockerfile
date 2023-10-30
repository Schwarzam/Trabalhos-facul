FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update -y && apt-get install -y
RUN apt-get install -y ghostscript
RUN apt-get install -y python3-pip

COPY ./flaskapp.py /app/
COPY ./templates /app/templates/

RUN pip3 install Flask Flask-RESTful

EXPOSE 5000

CMD ["python3", "app.py"]