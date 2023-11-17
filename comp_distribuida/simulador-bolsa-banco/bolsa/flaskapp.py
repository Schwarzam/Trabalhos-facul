from flask import Flask, jsonify
import yfinance as yf
import numpy as np
import pandas as pd

import logging
import os

if not os.path.exists('/app/logs'):
    os.makedirs('/app/logs')

logging.basicConfig(filename='/app/logs/app.log', level=logging.INFO, format='%(asctime)s - %(message)s')
log = logging.getLogger('werkzeug')
log.setLevel(logging.ERROR)

from datetime import datetime, timedelta

app = Flask(__name__)


def simulate_gbm(stock_name, start_date, end_date, pred_end_date, scen_size):
    """
    Adapted from https://github.com/mariomack/stochastic-asset-pricing-in-continuous-time
    """
    prices = yf.download(tickers=stock_name, start=start_date, end=pred_end_date)['Adj Close']
    train_set = prices.loc[:end_date]
    test_set = prices.loc[end_date:pred_end_date]
    daily_returns = ((train_set / train_set.shift(1)) - 1)[1:]
    
    So = train_set[-1]
    dt = 1  # day
    n_of_wkdays = pd.date_range(start=pd.to_datetime(end_date, format="%Y-%m-%d") + pd.Timedelta('1 days'),
                                end=pd.to_datetime(pred_end_date, format="%Y-%m-%d")).to_series().map(lambda x: 1 if x.isoweekday() in range(1, 6) else 0).sum()
    T = n_of_wkdays
    N = T / dt
    t = np.arange(1, int(N) + 1)
    mu = np.mean(daily_returns)
    sigma = np.std(daily_returns)
    b = {str(scen): np.random.normal(0, 1, int(N)) for scen in range(1, scen_size + 1)}
    W = {str(scen): b[str(scen)].cumsum() for scen in range(1, scen_size + 1)}

    drift = (mu - 0.5 * sigma ** 2) * t
    diffusion = {str(scen): sigma * W[str(scen)] for scen in range(1, scen_size + 1)}

    S = np.array([So * np.exp(drift + diffusion[str(scen)]) for scen in range(1, scen_size + 1)])
    S = np.hstack((np.array([[So] for scen in range(scen_size)]), S))  # add So to the beginning series
    S_max = [S[:, i].max() for i in range(0, int(N))]
    S_min = [S[:, i].min() for i in range(0, int(N))]
    S_pred = .5 * np.array(S_max) + .5 * np.array(S_min)
    
    return S_pred[-1]

# Função para obter o preço mais recente de uma ação
def get_current_stock_price(ticker):
    data = yf.download(ticker, period="1d")
    if not data.empty:
        return data['Close'].iloc[-1]
    else:
        return None

# Função para simular preço futuro (implemente a lógica GBM aqui)
def simulate_future_price(ticker, n_days_ahead):
    # Placeholder para a lógica de simulação
    return np.random.random()  # Substituir pela lógica real de simulação

@app.route('/GetStockPrice/<ticker>')
def get_stock_price(ticker):
    logging.info('Ticker: %s', ticker)
    price = get_current_stock_price(ticker)
    if price:
        return jsonify({'ticker': ticker, 'current_price': price})
    else:
        return jsonify({'error': 'Data not available'}), 404

@app.route('/GetStockFuturePrice/<ticker>/<int:n_days_ahead>')
def get_stock_future_price(ticker, n_days_ahead):
    if n_days_ahead > 180:
        return jsonify({'error': 'NDaysAhead must be <= 180'}), 400

    logging.info('Ticker: %s, NDaysAhead: %d', ticker, n_days_ahead)
    # Calculate the date range for the training data
    end_date = datetime.now()
    start_date = end_date - timedelta(days=180)
    pred_end_date = end_date + timedelta(days=n_days_ahead)

    # Formatting dates in 'YYYY-MM-DD' format
    start_date_str = start_date.strftime('%Y-%m-%d')
    end_date_str = end_date.strftime('%Y-%m-%d')
    pred_end_date_str = pred_end_date.strftime('%Y-%m-%d')

    scen_size = 10000  # Number of scenarios for GBM

    try:
        prediction = simulate_gbm(ticker, start_date_str, end_date_str, pred_end_date_str, scen_size)
        
        return jsonify({"pred": prediction})
    except Exception as e:
        print(e)
        return jsonify({'error': str(e)}), 500
    
if __name__ == '__main__':
    app.run(debug=True, port=5000, host='0.0.0.0')
