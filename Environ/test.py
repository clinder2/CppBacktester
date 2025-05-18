import yfinance as yf

data=yf.download(["AAPL", "NVDA", "IONQ", "PLTR"], "2025-01-01", "2025-05-12")
data.to_csv('test2.csv')
