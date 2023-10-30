import os
from flask import Flask, request, send_from_directory, jsonify, render_template
import subprocess

import logging
from datetime import datetime

if not os.path.exists('/app/logs'):
    os.makedirs('/app/logs')

logging.basicConfig(filename='/app/logs/app.log', level=logging.INFO, format='%(asctime)s - %(message)s')

app = Flask(__name__)

UPLOAD_DIR = "./UPLOAD"
OUTPUT_DIR = "./OUTPUT"

if not os.path.exists(UPLOAD_DIR):
    os.makedirs(UPLOAD_DIR)

if not os.path.exists(OUTPUT_DIR):
    os.makedirs(OUTPUT_DIR)

@app.route('/reduce-pdf', methods=['POST'])
def reduce_pdf():
    uploaded_file = request.files['pdf']
    
    if not uploaded_file:
        logging.info(f"Request to /reduce-pdf without file. IP: {request.remote_addr}")
        return 'No selected file', 400
    
    file_path = os.path.join(UPLOAD_DIR, uploaded_file.filename)
    output_path = os.path.join(OUTPUT_DIR, "comp_" + uploaded_file.filename)
    uploaded_file.save(file_path)

    start_size = os.path.getsize(file_path)
    
    # PDF compression with Ghostscript
    quality = request.form.get('quality', 'screen')
    subprocess.run([
        "gs", "-sDEVICE=pdfwrite", f"-dPDFSETTINGS=/{quality}",
        "-dNOPAUSE", "-dBATCH", "-dQUIET", 
        f"-sOutputFile={output_path}", file_path
    ])

    end_size = os.path.getsize(output_path)

    logging.info(f"/reduce-pdf - IP {request.remote_addr}. File: {uploaded_file.filename}. Start size: {start_size} bytes. End size: {end_size} bytes.")

    return send_from_directory(OUTPUT_DIR, "comp_" + uploaded_file.filename, as_attachment=True)

@app.route('/', methods=['GET'])
def index():
    return render_template('index.html')
    
if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)
    
