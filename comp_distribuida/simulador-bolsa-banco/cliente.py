import requests

# Parâmetros iniciais
acoes = ["AAPL", "MSFT", "GOOG", "AMZN", "PETR4.SA", "VALE3.SA"]
N = 30  # Dias para simulação
URL_SIMULADOR = "http://localhost:5001"  # Ajustar para sua URL
URL_BANCO = "http://localhost:5002"  # Ajustar para sua URL
INVESTIMENTO_TOTAL = 10000  # Valor total a investir

#Criar conta
res = requests.get(f"{URL_BANCO}/AbreConta/teste/{INVESTIMENTO_TOTAL}")
NUMERO_CONTA = res.json()['numero_conta']

print("Saldo inicial: ", requests.get(f"{URL_BANCO}/Saldo/{NUMERO_CONTA}").json()['saldo'])

# 1. Obter o valor atual das ações usando a API GetStockPrice
valores_atuais = {}
for acao in acoes:
    resposta = requests.get(f"{URL_SIMULADOR}/GetStockPrice/{acao}")
    valores_atuais[acao] = resposta.json()['current_price']

# 2. Consultar o valor futuro das ações após N dias usando a API GetStockFuturePrice
valores_futuros = {}
for acao in acoes:
    resposta = requests.get(f"{URL_SIMULADOR}/GetStockFuturePrice/{acao}/{N}")
    valores_futuros[acao] = resposta.json()['pred']

# 3. Estratégia de investimento: gastar o mesmo valor em cada ação
valor_por_acao = INVESTIMENTO_TOTAL / len(acoes)

# 4. Sacar o valor necessário da conta corrente
requests.get(f"{URL_BANCO}/Saque/{NUMERO_CONTA}/{INVESTIMENTO_TOTAL}")

# 5. Calcular o resultado do investimento
resultado = sum(valores_futuros[acao] - valores_atuais[acao] for acao in acoes) * (valor_por_acao / valores_atuais[acao])
resultado = int(resultado)

## 6. Valor final da conta corrente
valor_final = INVESTIMENTO_TOTAL + resultado
if valor_final > 0:
    requests.get(f"{URL_BANCO}/Deposito/{NUMERO_CONTA}/{valor_final}")
else:
    requests.get(f"{URL_BANCO}/Saque/{NUMERO_CONTA}/{-valor_final}")

# 7. Imprimir o resultado
print("Resultado de investimento: ", resultado)
print("Saldo final: ", requests.get(f"{URL_BANCO}/Saldo/{NUMERO_CONTA}").json()['saldo'])