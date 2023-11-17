from flask import Flask, jsonify
import hashlib

import logging
import os

if not os.path.exists('/app/logs'):
    os.makedirs('/app/logs')

logging.basicConfig(filename='/app/logs/app.log', level=logging.INFO, format='%(asctime)s - %(message)s')
log = logging.getLogger('werkzeug')
log.setLevel(logging.ERROR)

app = Flask(__name__)

contas = {}

def gerar_numero_conta(usuario):
    return hashlib.sha256(usuario.encode()).hexdigest()

@app.route('/AbreConta/<usuario>/<valor_inicial>')
def abre_conta(usuario, valor_inicial):
    logging.info('AbreConta: %s %s', usuario, valor_inicial)
    valor_inicial = int(valor_inicial)
    numero_conta = gerar_numero_conta(usuario)
    contas[numero_conta] = valor_inicial
    return jsonify({'numero_conta': numero_conta})

@app.route('/Saque/<numero_conta>/<valor>')
def saque(numero_conta, valor):
    logging.info('Saque: %s %s', numero_conta, valor)
    valor = int(valor)
    if numero_conta in contas:
        if contas[numero_conta] >= valor:
            contas[numero_conta] -= valor
            return jsonify({'sucesso': True})
        else:
            return jsonify({'erro': 'Saldo insuficiente'}), 400
    return jsonify({'erro': 'Conta não encontrada'}), 404

@app.route('/Deposito/<numero_conta>/<valor>')
def deposito(numero_conta, valor):
    logging.info('Deposito: %s %s', numero_conta, valor)
    valor = int(valor)
    if numero_conta in contas:
        contas[numero_conta] += valor
        return jsonify({'sucesso': True})
    return jsonify({'erro': 'Conta não encontrada'}), 404

@app.route('/Saldo/<numero_conta>')
def saldo(numero_conta):
    logging.info('Saldo: %s', numero_conta)
    if numero_conta in contas:
        return jsonify({'saldo': contas[numero_conta]})
    return jsonify({'erro': 'Conta não encontrada'}), 404

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')