import yfinance as yf
import statsmodels.api as sm
import numpy as np
import pandas as pd

""" data=yf.download(["AAPL", "NVDA", "IONQ", "PLTR"], "2025-01-01", "2025-05-12", interval='1h')
data.to_csv('test3.csv') """

data = [93.98999786376950,
100.81999969482400,
107.77999877929700,
112.77999877929700,
114.6500015258790,
116.08000183105500,
118.44000244140600,
116.19999694824200,
124.27999877929700,
123.7699966430660,
108.86000061035200,
110.4800033569340,
119.1500015258790,
117.30000305175800]

data = pd.read_csv("HistoricData/test2.csv")

data = data["Close.1"]


a,b,c,d,e = sm.tsa.stattools.levinson_durbin(data[69:], 20)
print(b)
a=data.values
a=a[70:]
a=a.astype(float)
print(a)
print(np.dot(a, np.flip(b)))

""" 1.44547 next
0.297473 DB
-12.7256 next
-0.514258 DB
-136.621 next
0.397578 DB
4.53485 next """

#python3 /Users/christopherlinder/Desktop/CppBacktester/Environ/test.py    