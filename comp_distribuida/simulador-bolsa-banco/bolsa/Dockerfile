FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update -y && apt-get install -y
RUN apt-get install -y python3-pip

WORKDIR /app

COPY ./flaskapp.py /app/
COPY ./templates /app/templates/

RUN pip3 install Flask Flask-RESTful yfinance==0.2.31 pandas==1.5.1 numpy==1.23.0

EXPOSE 5000

CMD ["python3", "flaskapp.py"]

# Build image
# sudo docker build -t bolsa .

# Run on port 5001
# docker run -p 5001:5000 -v ${PWD}/logs:/app/logs bolsa
