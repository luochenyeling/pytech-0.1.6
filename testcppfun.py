#%%
# python setup.py build_ext --inplace
# python setup.py sdist bdist_wheel
# twine upload --repository pypi dist/*
# pypi-AgEIcHlwaS5vcmcCJGI0YjAxYThhLWViODYtNGM0My1iOTc0LTFkN2M1YTQzMGVlMgACKlszLCI1NjE2N2QxYi00NzM2LTRmOGUtOTEwMC0xYzNkMTY1NWE1NGUiXQAABiDAonIig0WJJS4JZ3xxJJMMDwUKZfb_ZmSTJlgIPD5arA
#%%
import pytech
import numpy as np
from src.getETFprice import Params,GetETFprice
from datetime import datetime
import pandas as pd
#print(pytech.__doc__)
#print(pytech.Signals.MACDcrossup.__doc__)
#%%
sparams=Params()
getETFprice=GetETFprice(sparams)
ETFcode='510300.SH'
startDate='2016-01-01'
endDate=datetime.now().date().strftime('%Y-%m-%d')
#%%
df=getETFprice.getETFprice(ETFcode,startDate,endDate)
#%%
params = pytech.Params()
params.C=df.C
# params.C=np.array([0.49,0.506,0.516,0.514,0.517,0.525,0.526,0.529,0.554,0.532,0.564,0.577,0.579,0.579,0.57,0.557,0.57,0.577,0.58,0.577,0.569,0.571,0.585,	0.578,	0.576,	0.575,	0.571,	0.558,	0.551,	0.535,	0.543,	0.543,	0.551,	0.54,	0.536,	0.524,	0.526,	0.512,	0.515,	0.519,0.528,0.515,0.532,0.526,0.511,0.511,0.505,0.514,0.514,0.53,0.55,0.541,0.547])
signals=pytech.Signals()
res=signals.MACDcrossup(params)

df=pd.DataFrame({'C':params.C,'res':res})

print(np.where(res)[0])
# %%
