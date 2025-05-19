import yfinance as yf

data=yf.download(["AAPL", "NVDA", "IONQ", "PLTR"], "2025-01-01", "2025-05-12", interval='1h')
data.to_csv('test3.csv')
