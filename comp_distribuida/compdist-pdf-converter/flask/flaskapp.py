from flask import Flask, render_template, request, send_from_directory
import os
import pdftotext

import logging
from datetime import datetime

if not os.path.exists('/app/logs'):
    os.makedirs('/app/logs')

logging.basicConfig(filename='/app/logs/app.log', level=logging.INFO, format='%(asctime)s - %(message)s')
log = logging.getLogger('werkzeug')
log.setLevel(logging.ERROR)

app = Flask(__name__)

UPLOAD_DIR = "./uploads"

if not os.path.exists(UPLOAD_DIR):
    os.makedirs(UPLOAD_DIR)

@app.route('/', methods=['GET'])
def index():
    logging.info(f"/ - IP {request.remote_addr}")
    return render_template('index.html')

@app.route('/convert', methods=['POST'])
def convert_pdf_to_text():
    uploaded_file = request.files.get('pdf')
    
    if not uploaded_file:
        return 'No file uploaded', 400

    file_path = os.path.join(UPLOAD_DIR, uploaded_file.filename)
    uploaded_file.save(file_path)

    # Convert PDF to text
    with open(file_path, "rb") as f:
        pdf = pdftotext.PDF(f)

    txt_output_path = os.path.join(UPLOAD_DIR, uploaded_file.filename + ".txt")
    with open(txt_output_path, "w") as txt_file:
        txt_file.write("\n".join(pdf))

    logging.info(f"/convert - IP {request.remote_addr}. File: {uploaded_file.filename}.")
    return send_from_directory(UPLOAD_DIR, uploaded_file.filename + ".txt", as_attachment=True)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
