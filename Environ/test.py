import yfinance as yf

data=yf.download(["AAPL", "NVDA", "IONQ"], "2025-04-01", "2025-05-01")
data.to_csv('test.csv')