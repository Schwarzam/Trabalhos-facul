from flask import Flask, jsonify

app = Flask(__name__)

# Taxas de câmbio fictícias
TAXAS = {
    'dolar': 0.19,  # 1 Real = 0.19 Dólar
    'euro': 0.16    # 1 Real = 0.16 Euro
}

@app.route('/convertemoeda/<float:valor>', methods=['GET'])
def convertemoeda(valor):
    if valor <= 0:
        return jsonify({'erro': 'Por favor, insira um valor positivo não zero'}), 400
    
    valor_dolar = valor * TAXAS['dolar']
    valor_euro = valor * TAXAS['euro']
    
    resposta = {
        'conversao': {
            'server': 2,
            'real': valor,
            'dolar': valor_dolar,
            'euro': valor_euro
        }
    }
    
    return jsonify(resposta)

if __name__ == '__main__':
    app.run(debug=True)