#include <stdio.h>
#include <iostream>
#include <vector>
#include <tuple>
#include "techcpp.h"
#include <Python.h>
#include <pybind11/pybind11.h> 
#include <pybind11/stl.h>
#include <sstream>


std::tuple<std::vector<double>, std::vector<double>> ARoon(std::vector<double> &p, int n1){
    int n=p.size();
    int n2=2;
    CMyARoon aroon(n1, n2);
    std::vector<double> up,down;
    up.reserve(n);
    down.reserve(n);
    for (double data : p){
        aroon.Append(data, true);
        up.push_back(aroon.Up(0));
        down.push_back(aroon.Down(0));
    }
    return std::make_tuple(up, down);
}

std::tuple<std::vector<double>, std::vector<double>> ASI(std::vector<double> &H,std::vector<double> &L,std::vector<double> &C,std::vector<double> &O, int n1, int n2){
    int n=H.size();
    int n3=2;
    CMyASI asi(n1, n2,n3);
    std::vector<double> rASI, rASIMA;
    rASI.reserve(n);
    rASIMA.reserve(n);
    for (int i=0; i<n; i++){
        asi.Append(H[i], L[i], C[i], O[i], true);
        rASI.push_back(asi.ASI(0));
        rASIMA.push_back(asi.ASIMA(0));
    }
    return std::make_tuple(rASI, rASIMA);
}

std::tuple<std::vector<double>, std::vector<double>> ATR(std::vector<double> &H,std::vector<double> &L,std::vector<double> &C, int n1){
    int n=H.size();
    int n2=2;
    CMyATR atr(n1, n2);
    std::vector<double> rMTR,rATR;
    rMTR.reserve(n);
    rATR.reserve(n);
    for (int i=0; i<n; i++){
        atr.Append(H[i], L[i], C[i], true);
        rMTR.push_back(atr.MTR(0));
        rATR.push_back(atr.ATR(0));
    }
    return std::make_tuple(rMTR, rATR);
}

std::vector<double> AveDev(std::vector<double> &p, int n1){
    int n=p.size();
    int n2=2;
    CMyAveDev avedev(n1, n2);
    std::vector<double> res;
    res.reserve(n);
    for (double data : p){
        avedev.Append(data, true);
        res.push_back(avedev.AveDev(0));
    }
    return res;
}

std::vector<double> BBI(std::vector<double> &p, int n1, int n2, int n3, int n4){
    int n=p.size();
    int n5=2;
    CMyBBI bbi(n1, n2, n3, n4, n5);
    std::vector<double> res;
    res.reserve(n);
    for (double data : p){
        bbi.Append(data, true);
        res.push_back(bbi.BBI(0));
    }
    return res;
}

std::tuple<std::vector<double>, std::vector<double>,std::vector<double>> BOLL(std::vector<double> &p, int n1){
    int n=p.size();
    int n2=2;
    CMyBOLL boll(n1, n2);
    std::vector<double> rboll,up,down;
    rboll.reserve(n);
    up.reserve(n);
    down.reserve(n);
    for (double data : p){
        boll.Append(data, true);
        rboll.push_back(boll.BOLL(0));
        up.push_back(boll.UPPER(0));
        down.push_back(boll.LOWER(0));
    }
    return std::make_tuple(rboll,up, down);
}

std::vector<double> CCI(std::vector<double> &H,std::vector<double> &L,std::vector<double> &C, int n1){
    int n=H.size();
    int n2=2;
    CMyCCI cci(n1, n2);
    std::vector<double> res;
    res.reserve(n);
    for (int i=0; i<n; i++){
        cci.Append(H[i], L[i], C[i], true);
        res.push_back(cci.CCI(0));
    }
    return res;
}

std::vector<double> DMA(std::vector<double> &p, double fSmooth){
    int n=p.size();
    CMyDMA dma(n+1);
    std::vector<double> res;
    res.reserve(n);
    for (double data : p){
        dma.Append(data, fSmooth,true);
        res.push_back(dma.DMA(0));
    }
    return res;
}

std::tuple<std::vector<double>, std::vector<double>> DMAI(std::vector<double> &p, int n1, int n2, int n3){
    int n=p.size();
    int n4=2;
    CMyDMAI dmai(n1, n2, n3,n4);
    std::vector<double> rDIF, rDIFMA;
    rDIF.reserve(n);
    rDIFMA.reserve(n);   
    for (double data : p){
        dmai.Append(data, true);
        rDIF.push_back(dmai.DIF(0));
        rDIFMA.push_back(dmai.MADIF(0));
    }
    return std::make_tuple(rDIF, rDIFMA);
}

std::tuple<std::vector<double>, std::vector<double>,std::vector<double>,std::vector<double>> DMI(std::vector<double> &H,std::vector<double> &L,std::vector<double> &C, int n1, int n2){
    int n=H.size();
    int n3=2;
    CMyDMI dmi(n1, n2,n3);
    std::vector<double> rPDI, rMDI, rADX, rADXR;
    rPDI.reserve(n);
    rMDI.reserve(n);
    rADX.reserve(n);
    rADXR.reserve(n);
    for (int i=0; i<n; i++){
        dmi.Append(H[i], L[i], C[i], true);
        rPDI.push_back(dmi.PDI(0));
        rMDI.push_back(dmi.MDI(0));
        rADX.push_back(dmi.ADX(0));
        rADXR.push_back(dmi.ADXR(0));
    }
    return std::make_tuple(rPDI, rMDI, rADX, rADXR);
}

std::vector<double> EMA(std::vector<double> &p, int n1){
    int n=p.size();
    int n2=2;
    CMyEMA ema(n1, n2);
    std::vector<double> res;
    res.reserve(n);
    for (double data : p){
        ema.Append(data, true);
        res.push_back(ema.EMA(0));
    }
    return res;

}

std::vector<double> HL(std::vector<double> &p, int n1, int n2){
    int n=p.size();
    CMyHL hl(n1, n2);
    std::vector<double> res;
    res.reserve(n);
    for (double data : p){
        hl.Append(data, true);
        res.push_back(hl.HL());
    }
    return res;
}
std::tuple<std::vector<double>, std::vector<double>,std::vector<double>> KDJ(std::vector<double> &H,std::vector<double> &L,std::vector<double> &C, int n1, int n2, int n3){
    int n=H.size();
    int n4=2;
    CMyKDJ kdj(n1, n2, n3, n4);
    std::vector<double> rK, rD, rJ;
    rK.reserve(n);
    rD.reserve(n);
    rJ.reserve(n);
    for (int i=0; i<n; i++){
        kdj.Append(H[i], L[i], C[i], true);
        rK.push_back(kdj.K(0));
        rD.push_back(kdj.D(0));
        rJ.push_back(kdj.J(0));
    }
    return std::make_tuple(rK, rD, rJ);
}
std::vector<double> MA(std::vector<double> &p, int n1){
    int n=p.size();
    int n2=2;
    CMyMA ma(n1, n2);
    std::vector<double> res;
    res.reserve(n);
    for (double data : p){
        ma.Append(data, true);
        res.push_back(ma.MA(0));
    }
    return res;
}

std::tuple<std::vector<double>, std::vector<double>,std::vector<double>> MACD(std::vector<double> &p, int n1, int n2, int n3){
    int n=p.size();
    int n4=2;
    CMyMACD macd(n1, n2, n3, n4);
    std::vector<double> rDIF, rDEA, rMACD;
    rDIF.reserve(n);
    rDEA.reserve(n);
    rMACD.reserve(n);
    for (double data : p){
        macd.Append(data, true);
        rDIF.push_back(macd.DIF(0));
        rDEA.push_back(macd.DEA(0));
        rMACD.push_back(macd.MACD(0));
    }
    return std::make_tuple(rDIF, rDEA, rMACD);
}

std::tuple<std::vector<double>, std::vector<double>> MeanStd(std::vector<double> &p, int n1, int n2){
    int n=p.size();
    int n3=2;
    CMyMeanStd meanstd(n1, n3, n2);
    std::vector<double> rMean, rStd;
    rMean.reserve(n);
    rStd.reserve(n);
    for (double data : p){
        meanstd.Append(data, true);
        rMean.push_back(meanstd.Mean(0));
        rStd.push_back(meanstd.Std(0));
    }
    return std::make_tuple(rMean, rStd);
}

std::tuple<std::vector<double>, std::vector<double>> MFI(std::vector<double> &H,std::vector<double> &L,std::vector<double> &C,std::vector<double> &V, int n1, int n2){
    int n=H.size();
    int n3=2;
    CMyMFI mfi(n1, n2, n3);
    std::vector<double> rMFI, rMAMFI;
    rMFI.reserve(n);
    rMAMFI.reserve(n);
    for (int i=0; i<n; i++){
        mfi.Append(H[i], L[i], C[i], V[i], true);
        rMFI.push_back(mfi.MFI(0));
        rMAMFI.push_back(mfi.MAMFI(0));
    }
    return std::make_tuple(rMFI, rMAMFI);
}

std::tuple<std::vector<double>, std::vector<double>> MTM(std::vector<double> &p, int n1, int n2){
    int n=p.size();
    int n3=2;
    CMyMTM mtm(n1, n2, n3);
    std::vector<double> rMTM, rMTMMA;
    rMTM.reserve(n);
    rMTMMA.reserve(n);
    for (double data : p){
        mtm.Append(data, true);
        rMTM.push_back(mtm.MTM(0));
        rMTMMA.push_back(mtm.MAMTM(0));
    }
    return std::make_tuple(rMTM, rMTMMA);
}

std::tuple<std::vector<double>, std::vector<double>> OBV(std::vector<double> &C,std::vector<double> &V, int n1){
    int n=C.size();
    int n2=2;
    CMyOBV obv(n1, n2);
    std::vector<double> rOBV, rMAOBV;
    rOBV.reserve(n);
    rMAOBV.reserve(n);
    for (int i=0; i<n; i++){
        obv.Append(C[i], V[i], true);
        rOBV.push_back(obv.OBV(0));
        rMAOBV.push_back(obv.MAOBV(0));
    }
    return std::make_tuple(rOBV, rMAOBV);
}

std::tuple<std::vector<double>, std::vector<double>> ROC(std::vector<double> &p, int n1, int n2){
    int n=p.size();
    int n3=2;
    CMyROC roc(n1, n2, n3);
    std::vector<double> rROC, rMAROC;
    rROC.reserve(n);
    rMAROC.reserve(n);
    for (double data : p){
        roc.Append(data, true);
        rROC.push_back(roc.ROC(0));
        rMAROC.push_back(roc.MAROC(0));
    }
    return std::make_tuple(rROC, rMAROC);
}

std::tuple<std::vector<double>, std::vector<double>,std::vector<double>> RSI(std::vector<double> &p, int n1, int n2, int n3){
    int n=p.size();
    int n4=2;
    CMyRSI rsi(n1, n2, n3, n4);
    std::vector<double> rRSI1, rRSI2, rRSI3;
    rRSI1.reserve(n);
    rRSI2.reserve(n);
    rRSI3.reserve(n);
    for (double data : p){
        rsi.Append(data, true);
        rRSI1.push_back(rsi.RSI1(0));
        rRSI2.push_back(rsi.RSI2(0));
        rRSI3.push_back(rsi.RSI3(0));
    }
    return std::make_tuple(rRSI1, rRSI2, rRSI3);
} 

std::tuple<std::vector<double>, std::vector<double>> SAR(std::vector<double> &H,std::vector<double> &L, int n1,int BaseAF,int AddAF,int MaxAF){
    int n=H.size();
    int n2=2;
    CMySAR sar(n1, BaseAF, AddAF, MaxAF,n2);
    std::vector<double> rSAR, rDirection;
    rSAR.reserve(n);
    rDirection.reserve(n);
    for (int i=0; i<n; i++){
        sar.Append(H[i], L[i], true);
        rSAR.push_back(sar.SAR(0));
        rDirection.push_back(sar.Direction(0));
    }
    return std::make_tuple(rSAR, rDirection);
}

std::vector<double> SMA(std::vector<double> &p, int n1, int n2){
    int n=p.size();
    int n3=2;
    CMySMA sma(n1, n2, n3);
    std::vector<double> res;
    res.reserve(n);
    for (double data : p){
        sma.Append(data, true);
        res.push_back(sma.SMA(0));
    }
    return res;
}

std::vector<double> STD(std::vector<double> &p, int n1){
    int n=p.size();
    int n2=2;
    CMyStd cmystd(n1, n2);
    std::vector<double> res;
    res.reserve(n);
    for (double data : p){
        cmystd.Append(data, true);
        res.push_back(cmystd.Std(0));
    }
    return res;
}

std::tuple<std::vector<double>, std::vector<double>> TRIX(std::vector<double> &p, int n1, int n2){
    int n=p.size();
    int n3=2;
    CMyTrix trix(n1, n2, n3);
    std::vector<double> rTRIX, rMATRIX;
    rTRIX.reserve(n);
    rMATRIX.reserve(n);
    for (double data : p){
        trix.Append(data, true);
        rTRIX.push_back(trix.TRIX(0));
        rMATRIX.push_back(trix.MATRIX(0));
    }
    return std::make_tuple(rTRIX, rMATRIX);
}

std::vector<double> WMA(std::vector<double> &p, int n1){
    int n=p.size();
    int n2=2;
    CMyWMA wma(n1, n2);
    std::vector<double> res;
    res.reserve(n);
    for (double data : p){
        wma.Append(data, true);
        res.push_back(wma.WMA(0));
    }
    return res;
}

std::tuple<std::vector<double>, std::vector<double>> WR(std::vector<double> &H,std::vector<double> &L,std::vector<double> &C, int n1, int n2){
    int n=H.size();
    int n3=2;
    CMyWR wr(n1, n2, n3);
    std::vector<double> rWR1, rWR2;
    rWR1.reserve(n);
    rWR2.reserve(n);
    for (int i=0; i<n; i++){
        wr.Append(H[i], L[i], C[i], true);
        rWR1.push_back(wr.WR1(0));
        rWR2.push_back(wr.WR2(0));
    }
    return std::make_tuple(rWR1, rWR2);
}

//信号类函数
class Params{
    public:
    std::vector<double> H={};
    std::vector<double> L={};
    std::vector<double> C={};
    std::vector<double> O={}; 
    std::vector<double> V={};

    int MAdx=5;
    int MAcx=20;

    int EMAdx=5;
    int EMAcx=20;

    int WMAdx=5;
    int WMAcx=20;

    int MACDdx=12;
    int MACDcx=26;
    int MACDdea=9;

    int ATR1bs=2; //市场价格<ATR1bs 倍ATR
    int ATR2xj=2; //市场价格 >= ATR2xj 倍ATR
    int ATR2sj=3; //市场价格 <= ATR2sj 倍ATR
    int ATRzq=14; //ATR参数=ATRzq 日

    int ASIn=14;
    int ASIm=6;
    int ASItpzq=30;

    int ROCn=20;

    int RSIdx=6;
    int RSIcx=14;

    int AROONz=50;
    int AROONzq=25;

    int BOLLn=20;

    int Kentner_ATRn=40;
    int Kentner_ATRmid=60;
    double Kentner_ATRbs=2.0;

    int KDJrsv=9;
    int KDJk=3;
    int KDJd=3;

    int BBIn1=3;
    int BBIn2=6;
    int BBIn3=12;
    int BBIn4=24;

    int WRoverbuywr1=20;
    int WRoversellwr1=80;
    int WRn=30;

    int MFIzq=14;
    int MFIjxzq=6;

    int OBVn=30;

    int CCIn=14;
    int CCIoverbuy=100;
    int CCIoversell=-100;

    int TRIXzq=12;
    int TRIXjxzq=20;

    int MTMzq=12;
    int MTMjxzq=6;

    int DMAn1=10;
    int DMAn2=5;
    int DMAm=10;

    int DMIn=14;

    int BIASjx=10;
    int BIAS1glv=0;
    int BIAS2glvxj=0;
    int BIAS2glvsj=50;
};

class Signals{
    public:

    std::vector<bool> MAcrossup(Params& params){
        int n=params.C.size();
        std::vector<double> madx,macx;
        madx.reserve(n);
        macx.reserve(n);
        madx=MA(params.C,params.MAdx);
        macx=MA(params.C,params.MAcx);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(madx[i]>macx[i] && madx[i-1]<macx[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> MAcrossdown(Params& params){
        int n=params.C.size();
        std::vector<double> madx,macx;
        madx.reserve(n);
        macx.reserve(n);
        madx=MA(params.C,params.MAdx);
        macx=MA(params.C,params.MAcx);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(madx[i]<macx[i] && madx[i-1]>macx[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> MAlong(Params& params){
        int n=params.C.size();
        std::vector<double> madx,macx;
        madx.reserve(n);
        macx.reserve(n);
        madx=MA(params.C,params.MAdx);
        macx=MA(params.C,params.MAcx);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(params.C[i]>madx[i] && madx[i]>macx[i]){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> MAshort(Params& params){
        int n=params.C.size();
        std::vector<double> madx,macx;
        madx.reserve(n);
        macx.reserve(n);
        madx=MA(params.C,params.MAdx);
        macx=MA(params.C,params.MAcx);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(params.C[i]<madx[i] && madx[i]<macx[i]){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> EMAcrossup(Params& params){
        int n=params.C.size();
        std::vector<double> emadx,emacx;
        emadx.reserve(n);
        emacx.reserve(n);
        emadx=EMA(params.C,params.EMAdx);
        emacx=EMA(params.C,params.EMAcx);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(emadx[i]>emacx[i] && emadx[i-1]<emacx[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> EMAcrossdown(Params& params){
        int n=params.C.size();
        std::vector<double> emadx,emacx;
        emadx.reserve(n);
        emacx.reserve(n);
        emadx=EMA(params.C,params.EMAdx);
        emacx=EMA(params.C,params.EMAcx);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(emadx[i]<emacx[i] && emadx[i-1]>emacx[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> EMAlong(Params& params){
        int n=params.C.size();
        std::vector<double> emadx,emacx;
        emadx.reserve(n);
        emacx.reserve(n);
        emadx=EMA(params.C,params.EMAdx);
        emacx=EMA(params.C,params.EMAcx);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(params.C[i]>emadx[i] && emadx[i]>emacx[i]){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> EMAshort(Params& params){
        int n=params.C.size();
        std::vector<double> emadx,emacx;
        emadx.reserve(n);
        emacx.reserve(n);
        emadx=EMA(params.C,params.EMAdx);
        emacx=EMA(params.C,params.EMAcx);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(params.C[i]<emadx[i] && emadx[i]<emacx[i]){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> WMAcrossup(Params& params){
        int n=params.C.size();
        std::vector<double> wmadx,wmacx;
        wmadx.reserve(n);
        wmacx.reserve(n);
        wmadx=WMA(params.C,params.WMAdx);
        wmacx=WMA(params.C,params.WMAcx);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(wmadx[i]>wmacx[i] && wmadx[i-1]<wmacx[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> WMAcrossdown(Params& params){
        int n=params.C.size();
        std::vector<double> wmadx,wmacx;
        wmadx.reserve(n);
        wmacx.reserve(n);
        wmadx=WMA(params.C,params.WMAdx);
        wmacx=WMA(params.C,params.WMAcx);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(wmadx[i]<wmacx[i] && wmadx[i-1]>wmacx[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> WMAlong(Params& params){
        int n=params.C.size();
        std::vector<double> wmadx,wmacx;
        wmadx.reserve(n);
        wmacx.reserve(n);
        wmadx=WMA(params.C,params.WMAdx);
        wmacx=WMA(params.C,params.WMAcx);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(params.C[i]>wmadx[i] && wmadx[i]>wmacx[i]){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> WMAshort(Params& params){
        int n=params.C.size();
        std::vector<double> wmadx,wmacx;
        wmadx.reserve(n);
        wmacx.reserve(n);
        wmadx=WMA(params.C,params.WMAdx);
        wmacx=WMA(params.C,params.WMAcx);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(params.C[i]<wmadx[i] && wmadx[i]<wmacx[i]){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> MACDcrossup(Params& params){
        int n=params.C.size();
        std::vector<double> dea,macd;
        dea.reserve(n);
        macd.reserve(n);
        std::tie(std::ignore,dea,macd)=MACD(params.C,params.MACDdx,params.MACDcx,params.MACDdea);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(macd[i-1]<0 && macd[i]>0 && dea[i-1]<=dea[i]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> MACDcrossdown(Params& params){
        int n=params.C.size();
        std::vector<double> dea,macd;
        dea.reserve(n);
        macd.reserve(n);
        std::tie(std::ignore,dea,macd)=MACD(params.C,params.MACDdx,params.MACDcx,params.MACDdea);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(macd[i-1]>0 && macd[i]<0 && dea[i-1]>=dea[i]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> ATRxy(Params& params){
        int n=params.C.size();
        std::vector<double> atr;
        atr.reserve(n);
        std::tie(std::ignore,atr)=ATR(params.H,params.L,params.C,params.ATRzq);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(params.C[i]<params.ATR1bs*atr[i]){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> ATRqj(Params& params){
        int n=params.C.size();
        std::vector<double> atr;
        atr.reserve(n);
        std::tie(std::ignore,atr)=ATR(params.H,params.L,params.C,params.ATRzq);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(params.C[i]>=params.ATR2xj*atr[i] && params.C[i]<=params.ATR2sj*atr[i]){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> ASIcrossup(Params& params){
        int n=params.C.size();
        std::vector<double> rASI,rASIMA;
        rASI.reserve(n);
        rASIMA.reserve(n);
        std::tie(rASI,rASIMA)=ASI(params.H,params.L,params.C,params.O,params.ASIn,params.ASIm);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(rASI[i]>rASIMA[i] && rASI[i-1]<rASIMA[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> ASIcrossdown(Params& params){
        int n=params.C.size();
        std::vector<double> rASI,rASIMA;
        rASI.reserve(n);
        rASIMA.reserve(n);
        std::tie(rASI,rASIMA)=ASI(params.H,params.L,params.C,params.O,params.ASIn,params.ASIm);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(rASI[i]<rASIMA[i] && rASI[i-1]>rASIMA[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> ASIupbreakthrough(Params& params){
        int n=params.C.size();
        std::vector<double> rASI;
        rASI.reserve(n);
        std::tie(rASI,std::ignore)=ASI(params.H,params.L,params.C,params.O,params.ASIn,params.ASIm);
        std::vector<double> rASItpmax;
        rASItpmax.reserve(n);
        rASItpmax=HL(rASI,1,params.ASItpzq-1);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<params.ASItpzq-1; i++){
            res.push_back(false);
        }
        for(int i=params.ASItpzq-1; i<n; i++){
            if(rASI[i]>rASItpmax[i-1]){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> ASIdownbreakthrough(Params& params){
        int n=params.C.size();
        std::vector<double> rASI;
        rASI.reserve(n);
        std::tie(rASI,std::ignore)=ASI(params.H,params.L,params.C,params.O,params.ASIn,params.ASIm);
        std::vector<double> rASItpmin;
        rASItpmin.reserve(n);
        rASItpmin=HL(rASI,1,params.ASItpzq-1);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<params.ASItpzq-1; i++){
            res.push_back(false);
        }
        for(int i=params.ASItpzq-1; i<n; i++){
            if(rASI[i]<rASItpmin[i-1]){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> ROCcrossup(Params& params){
        int n=params.C.size();
        std::vector<double> roc;
        roc.reserve(n);
        std::tie(roc,std::ignore)=ROC(params.C,params.ROCn,params.ROCn);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(roc[i]>0 && roc[i-1]<0){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> ROCcrossdown(Params& params){
        int n=params.C.size();
        std::vector<double> roc;
        roc.reserve(n);
        std::tie(roc,std::ignore)=ROC(params.C,params.ROCn,params.ROCn);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(roc[i]<0 && roc[i-1]>0){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> RSIcrossup(Params& params){
        int n=params.C.size();
        std::vector<double> rrsi1,rrsi2;
        rrsi1.reserve(n);
        rrsi2.reserve(n);
        std::tie(rrsi1,rrsi2,std::ignore)=RSI(params.C,params.RSIdx,params.RSIcx,params.RSIcx);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(rrsi1[i]>rrsi2[i] && rrsi1[i-1]<rrsi2[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> RSIcrossdown(Params& params){
        int n=params.C.size();
        std::vector<double> rrsi1,rrsi2;
        rrsi1.reserve(n);
        rrsi2.reserve(n);
        std::tie(rrsi1,rrsi2,std::ignore)=RSI(params.C,params.RSIdx,params.RSIcx,params.RSIcx);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(rrsi1[i]<rrsi2[i] && rrsi1[i-1]>rrsi2[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> AROONupgrade(Params& params){
        int n=params.C.size();
        std::vector<double> rup;
        rup.reserve(n);
        std::tie(rup,std::ignore)=ARoon(params.C,params.AROONzq);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(rup[i]>params.AROONz){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> AROONupless(Params& params){
        int n=params.C.size();
        std::vector<double> rup;
        rup.reserve(n);
        std::tie(rup,std::ignore)=ARoon(params.C,params.AROONzq);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(rup[i]<params.AROONz){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> AROONdowngrade(Params& params){
        int n=params.C.size();
        std::vector<double> rrdown;
        rrdown.reserve(n);
        std::tie(std::ignore,rrdown)=ARoon(params.C,params.AROONzq);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(rrdown[i]>params.AROONz){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> AROONdownless(Params& params){
        int n=params.C.size();
        std::vector<double> rrdown;
        rrdown.reserve(n);
        std::tie(std::ignore,rrdown)=ARoon(params.C,params.AROONzq);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(rrdown[i]<params.AROONz){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> BOLLbreakup(Params& params){
        int n=params.C.size();
        std::vector<double> bollup;
        bollup.reserve(n);
        std::tie(std::ignore,bollup,std::ignore)=BOLL(params.C,params.BOLLn);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(params.C[i]>bollup[i] && params.C[i-1]<=bollup[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> BOLLbreakdown(Params& params){
        int n=params.C.size();
        std::vector<double> bolldown;
        bolldown.reserve(n);
        std::tie(std::ignore,std::ignore,bolldown)=BOLL(params.C,params.BOLLn);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(params.C[i]<bolldown[i] && params.C[i-1]>=bolldown[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> BOLLlocalup(Params& params){
        int n=params.C.size();
        std::vector<double> bollup,bollmid;
        bollup.reserve(n);
        bollmid.reserve(n);
        std::tie(bollmid,bollup,std::ignore)=BOLL(params.C,params.BOLLn);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(params.C[i]>=bollmid[i] && params.C[i]<=bollup[i]){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> BOLLlocaldown(Params& params){
        int n=params.C.size();
        std::vector<double> bolldown,bollmid;
        bolldown.reserve(n);
        bollmid.reserve(n);
        std::tie(bollmid,std::ignore,bolldown)=BOLL(params.C,params.BOLLn);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(params.C[i]<=bollmid[i] && params.C[i]>=bolldown[i]){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> Kentner_ATRbreakup(Params& params){
        int n=params.C.size();
        std::vector<double> atr;
        atr.reserve(n);
        std::tie(std::ignore,atr)=ATR(params.H,params.L,params.C,params.Kentner_ATRn);
        std::vector<double> mid,up;
        mid.reserve(n);
        up.reserve(n);
        mid=EMA(params.C,params.Kentner_ATRmid);
        for(int i=0; i<n; i++){
            up.push_back(mid[i]+params.Kentner_ATRbs*atr[i]);
        }
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(params.C[i]>up[i] && params.C[i-1]<up[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> Kentner_ATRbreakdown(Params& params){
        int n=params.C.size();
        std::vector<double> atr;
        atr.reserve(n);
        std::tie(std::ignore,atr)=ATR(params.H,params.L,params.C,params.Kentner_ATRn);
        std::vector<double> mid,down;
        mid.reserve(n);
        down.reserve(n);
        mid=EMA(params.C,params.Kentner_ATRmid);
        for(int i=0; i<n; i++){
            down.push_back(mid[i]-params.Kentner_ATRbs*atr[i]);
        }
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(params.C[i]<down[i] && params.C[i-1]>down[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> Kentner_ATRoverup(Params& params){
        int n=params.C.size();
        std::vector<double> atr;
        atr.reserve(n);
        std::tie(std::ignore,atr)=ATR(params.H,params.L,params.C,params.Kentner_ATRn);
        std::vector<double> mid,up;
        mid.reserve(n);
        up.reserve(n);
        mid=EMA(params.C,params.Kentner_ATRmid);
        for(int i=0; i<n; i++){
            up.push_back(mid[i]+params.Kentner_ATRbs*atr[i]);
        }
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(params.C[i]>up[i]){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> Kentner_ATRbelowdown(Params& params){
        int n=params.C.size();
        std::vector<double> atr;
        atr.reserve(n);
        std::tie(std::ignore,atr)=ATR(params.H,params.L,params.C,params.Kentner_ATRn);
        std::vector<double> mid,down;
        mid.reserve(n);
        down.reserve(n);
        mid=EMA(params.C,params.Kentner_ATRmid);
        for(int i=0; i<n; i++){
            down.push_back(mid[i]-params.Kentner_ATRbs*atr[i]);
        }
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(params.C[i]<down[i]){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> KDJcrossup(Params& params){
        int n=params.C.size();
        std::vector<double> k,d;
        k.reserve(n);
        d.reserve(n);
        std::tie(k,d,std::ignore)=KDJ(params.H,params.L,params.C,params.KDJrsv,params.KDJk,params.KDJd);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(k[i]>d[i] && k[i-1]<=d[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> KDJcrossdown(Params& params){
        int n=params.C.size();
        std::vector<double> k,d;
        k.reserve(n);
        d.reserve(n);
        std::tie(k,d,std::ignore)=KDJ(params.H,params.L,params.C,params.KDJrsv,params.KDJk,params.KDJd);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(k[i]<d[i] && k[i-1]>=d[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }   

    std::vector<bool> KDJlong(Params& params){
        int n=params.C.size();
        std::vector<double> k,d,j;
        k.reserve(n);
        d.reserve(n);
        j.reserve(n);
        std::tie(k,d,j)=KDJ(params.H,params.L,params.C,params.KDJrsv,params.KDJk,params.KDJd);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(k[i]>50 && d[i]>50 && j[i]>50){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> KDJshort(Params& params){
        int n=params.C.size();
        std::vector<double> k,d,j;
        k.reserve(n);
        d.reserve(n);
        j.reserve(n);
        std::tie(k,d,j)=KDJ(params.H,params.L,params.C,params.KDJrsv,params.KDJk,params.KDJd);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(k[i]<50 && d[i]<50 && j[i]<50){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> BBIcrossup(Params& params){
        int n=params.C.size();
        std::vector<double> bbi;
        bbi.reserve(n);
        bbi=BBI(params.C,params.BBIn1,params.BBIn2,params.BBIn3,params.BBIn4);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(params.C[i]>bbi[i] && params.C[i-1]<bbi[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> BBIcrossdown(Params& params){
        int n=params.C.size();
        std::vector<double> bbi;
        bbi.reserve(n);
        bbi=BBI(params.C,params.BBIn1,params.BBIn2,params.BBIn3,params.BBIn4);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(params.C[i]<bbi[i] && params.C[i-1]>bbi[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> BBIlong(Params& params){
        int n=params.C.size();
        std::vector<double> bbi;
        bbi.reserve(n);
        bbi=BBI(params.C,params.BBIn1,params.BBIn2,params.BBIn3,params.BBIn4);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(params.C[i]>bbi[i]){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> BBIshort(Params& params){
        int n=params.C.size();
        std::vector<double> bbi;
        bbi.reserve(n);
        bbi=BBI(params.C,params.BBIn1,params.BBIn2,params.BBIn3,params.BBIn4);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(params.C[i]<bbi[i]){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> WRoverbuy(Params& params){
        int n=params.C.size();
        std::vector<double> wr;
        wr.reserve(n);
        std::tie(wr,std::ignore)=WR(params.H,params.L,params.C,params.WRn,params.WRn);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(wr[i]<params.WRoverbuywr1){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> WRoversell(Params& params){
        int n=params.C.size();
        std::vector<double> wr;
        wr.reserve(n);
        std::tie(wr,std::ignore)=WR(params.H,params.L,params.C,params.WRn,params.WRn);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(wr[i]>params.WRoversellwr1){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> MFIcrossup(Params& params){
        int n=params.C.size();
        std::vector<double> mfi,mamfi;
        mfi.reserve(n);
        std::tie(mfi,mamfi)=MFI(params.H,params.L,params.C,params.V,params.MFIzq,params.MFIjxzq);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(mfi[i]>mamfi[i] && mfi[i-1]<mamfi[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> MFIcrossdown(Params& params){
        int n=params.C.size();
        std::vector<double> mfi,mamfi;
        mfi.reserve(n);
        std::tie(mfi,mamfi)=MFI(params.H,params.L,params.C,params.V,params.MFIzq,params.MFIjxzq);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(mfi[i]<mamfi[i] && mfi[i-1]>mamfi[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> OBVpriceup(Params& params){
        int n=params.C.size();
        std::vector<double> obv;
        obv.reserve(n);
        std::tie(obv,std::ignore)=OBV(params.C,params.V,params.OBVn);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(obv[i]<obv[i-1] && params.C[i]>params.C[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> OBVpricedown(Params& params){
        int n=params.C.size();
        std::vector<double> obv;
        obv.reserve(n);
        std::tie(obv,std::ignore)=OBV(params.C,params.V,params.OBVn);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(obv[i]>obv[i-1] && params.C[i]<params.C[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> CCIoverbuy(Params& params){
        int n=params.C.size();
        std::vector<double> cci;
        cci.reserve(n);
        cci=CCI(params.H,params.L,params.C,params.CCIn);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(cci[i]>params.CCIoverbuy){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> CCIoversell(Params& params){
        int n=params.C.size();
        std::vector<double> cci;
        cci.reserve(n);
        cci=CCI(params.H,params.L,params.C,params.CCIn);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(cci[i]<params.CCIoversell){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> TRIXcrossup(Params& params){
        int n=params.C.size();
        std::vector<double> trix,matrix;
        trix.reserve(n);
        matrix.reserve(n);
        std::tie(trix,matrix)=TRIX(params.C,params.TRIXzq,params.TRIXjxzq);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(trix[i]>matrix[i] && trix[i-1]<matrix[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> TRIXcrossdown(Params& params){
        int n=params.C.size();
        std::vector<double> trix,matrix;
        trix.reserve(n);
        matrix.reserve(n);
        std::tie(trix,matrix)=TRIX(params.C,params.TRIXzq,params.TRIXjxzq);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(trix[i]<matrix[i] && trix[i-1]>matrix[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> TRIXlong(Params& params){
        int n=params.C.size();
        std::vector<double> trix,matrix;
        trix.reserve(n);
        matrix.reserve(n);
        std::tie(trix,matrix)=TRIX(params.C,params.TRIXzq,params.TRIXjxzq);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(trix[i]>matrix[i]){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> TRIXshort(Params& params){
        int n=params.C.size();
        std::vector<double> trix,matrix;
        trix.reserve(n);
        matrix.reserve(n);
        std::tie(trix,matrix)=TRIX(params.C,params.TRIXzq,params.TRIXjxzq);
        std::vector<bool> res;
        res.reserve(n);
        for(int i=0; i<n; i++){
            if(trix[i]<matrix[i]){
                res.push_back(true);
            }
            else{
                res.push_back(false);
            }
        }
        return res;
    }

    std::vector<bool> MTMcrossup(Params& params){
        int n=params.C.size();
        std::vector<double> mtm,mamtm;
        mtm.reserve(n);
        std::tie(mtm,mamtm)=MTM(params.C,params.MTMzq,params.MTMjxzq);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(mtm[i]>mamtm[i] && mtm[i-1]<=mamtm[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> MTMcrossdown(Params& params){
        int n=params.C.size();
        std::vector<double> mtm,mamtm;
        mtm.reserve(n);
        std::tie(mtm,mamtm)=MTM(params.C,params.MTMzq,params.MTMjxzq);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(mtm[i]<mamtm[i] && mtm[i-1]>=mamtm[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> DMAIcrossup(Params& params){
        int n=params.C.size();
        std::vector<double> dif,madif;
        dif.reserve(n);
        std::tie(dif,madif)=DMAI(params.C,params.DMAn1,params.DMAn2,params.DMAm);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(dif[i]>madif[i] && dif[i-1]<=madif[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> DMAIcrossdown(Params& params){
        int n=params.C.size();
        std::vector<double> dif,madif;
        dif.reserve(n);
        std::tie(dif,madif)=DMAI(params.C,params.DMAn1,params.DMAn2,params.DMAm);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(dif[i]<madif[i] && dif[i-1]>=madif[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> DMIcrossup(Params& params){
        int n=params.C.size();
        std::vector<double> pdi,mdi;
        pdi.reserve(n);
        mdi.reserve(n);
        std::tie(pdi,mdi,std::ignore,std::ignore)=DMI(params.H,params.L,params.C,params.DMIn,params.DMIn);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(pdi[i]>mdi[i] && pdi[i-1]<=mdi[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }

    std::vector<bool> DMIcrossdown(Params& params){
        int n=params.C.size();
        std::vector<double> pdi,mdi;
        pdi.reserve(n);
        mdi.reserve(n);
        std::tie(pdi,mdi,std::ignore,std::ignore)=DMI(params.H,params.L,params.C,params.DMIn,params.DMIn);
        std::vector<bool> res;
        res.reserve(n);
        if(n==1){
            res.push_back(false);
        }
        else{
            res.push_back(false);
            for (int i=1; i<n; i++){
                if(pdi[i]<mdi[i] && pdi[i-1]>=mdi[i-1]){
                    res.push_back(true);
                }
                else{
                    res.push_back(false);
                }
            }
        }
        return res;
    }
};



// int main() {
//     std::vector<double> C={0.49,0.506,0.516,0.514,0.517,0.525,0.526,0.529,0.554,0.532,0.564,0.577,0.579,0.579,0.57,0.557,0.57,0.577,0.58,0.577,0.569,0.571,0.585,	0.578,	0.576,	0.575,	0.571,	0.558,	0.551,	0.535,	0.543,	0.543,	0.551,	0.54,	0.536,	0.524,	0.526,	0.512,	0.515,	0.519,	0.528,	0.515,	0.532,	0.526,	0.511,	0.511,	0.505,	0.514,	0.514,	0.53,	0.55,	0.541,	0.547};
//     Params params;
//     params.C=C;
//     Signals signals;
//     std::vector<bool> res = signals.MACDcrossup(params);
//     std::vector<double> res2=MACD2();
//     for (int i=0; i<res.size(); i++){
//         std::cout << "MACDcrossup "<< i << " : " << params.C[i] 
//         <<" "<< res[i] << " " << res2[i] << std::endl;
//     }
//     return 0;
//     }




namespace py = pybind11;

PYBIND11_MODULE(pytech, m) {
    m.doc() = R"(
    MAcrossup(Params& params), params.C, params.MAdx, params.MAcx
    MAcrossdown(Params& params), params.C, params.MAdx, params.MAcx
    MAlong(Params& params), params.C, params.MAdx, params.MAcx
    MAshort(Params& params), params.C, params.MAdx, params.MAcx
    EMAcrossup(Params& params), params.C, params.EMAdx, params.EMAcx
    EMAcrossdown(Params& params), params.C, params.EMAdx, params.EMAcx
    EMAlong(Params& params), params.C, params.EMAdx, params.EMAcx
    EMAshort(Params& params), params.C, params.EMAdx, params.EMAcx
    WMAcrossup(Params& params), params.C, params.WMAdx, params.WMAcx
    WMAcrossdown(Params& params), params.C, params.WMAdx, params.WMAcx
    WMAlong(Params& params), params.C, params.WMAdx, params.WMAcx
    WMAshort(Params& params), params.C, params.WMAdx, params.WMAcx
    MACDcrossup(Params& params), params.C, params.MACDdx, params.MACDcx, params.MACDdea
    MACDcrossdown(Params& params), params.C, params.MACDdx, params.MACDcx, params.MACDdea
    ATRxy(Params& params), params.H, params.L, params.C, params.ATRzq, params.ATR1bs
    ATRqj(Params& params), params.H, params.L, params.C, params.ATRzq, params.ATR2xj, params.ATR2sj
    ASIcrossup(Params& params), params.H, params.L, params.C, params.O, params.ASIn, params.ASIm
    ASIcrossdown(Params& params), params.H, params.L, params.C, params.O, params.ASIn, params.ASIm
    ASIupbreakthrough(Params& params), params.H, params.L, params.C, params.O, params.ASIn, params.ASIm, params.ASItpzq
    ASIdownbreakthrough(Params& params), params.H, params.L, params.C, params.O, params.ASIn, params.ASIm, params.ASItpzq
    ROCcrossup(Params& params), params.C, params.ROCn
    ROCcrossdown(Params& params), params.C, params.ROCn
    RSIcrossup(Params& params), params.C, params.RSIdx, params.RSIcx
    RSIcrossdown(Params& params), params.C, params.RSIdx, params.RSIcx
    AROONupgrade(Params& params), params.C, params.AROONz, params.AROONzq
    AROONupless(Params& params), params.C, params.AROONz, params.AROONzq
    AROONdowngrade(Params& params), params.C, params.AROONz, params.AROONzq
    AROONdownless(Params& params), params.C, params.AROONz, params.AROONzq
    BOLLbreakup(Params& params), params.C, params.BOLLn
    BOLLbreakdown(Params& params), params.C, params.BOLLn
    BOLLlocalup(Params& params), params.C, params.BOLLn
    BOLLlocaldown(Params& params), params.C, params.BOLLn
    Kentner_ATRbreakup(Params& params), params.C, params.H, params.L, params.Kentner_ATRn, params.Kentner_ATRbs, params.Kentner_ATRmid
    Kentner_ATRbreakdown(Params& params), params.C, params.H, params.L, params.Kentner_ATRn, params.Kentner_ATRbs, params.Kentner_ATRmid
    Kentner_ATRoverup(Params& params), params.C, params.H, params.L, params.Kentner_ATRn, params.Kentner_ATRbs, params.Kentner_ATRmid
    Kentner_ATRbelowdown(Params& params), params.C, params.H, params.L, params.Kentner_ATRn, params.Kentner_ATRbs, params.Kentner_ATRmid
    KDJcrossup(Params& params), params.H, params.L, params.C, params.KDJrsv, params.KDJk, params.KDJd
    KDJcrossdown(Params& params), params.H, params.L, params.C, params.KDJrsv, params.KDJk, params.KDJd
    KDJlong(Params& params), params.H, params.L, params.C, params.KDJrsv, params.KDJk, params.KDJd
    KDJshort(Params& params), params.H, params.L, params.C, params.KDJrsv, params.KDJk, params.KDJd
    BBIcrossup(Params& params), params.C, params.BBIn1, params.BBIn2, params.BBIn3, params.BBIn4
    BBIcrossdown(Params& params), params.C, params.BBIn1, params.BBIn2, params.BBIn3, params.BBIn4
    BBIlong(Params& params), params.C, params.BBIn1, params.BBIn2, params.BBIn3, params.BBIn4
    BBIshort(Params& params), params.C, params.BBIn1, params.BBIn2, params.BBIn3, params.BBIn4
    WRoverbuy(Params& params), params.H, params.L, params.C, params.WRn, params.WRoverbuywr1
    WRoversell(Params& params), params.H, params.L, params.C, params.WRn, params.WRoversellwr1
    MFIcrossup(Params& params), params.H, params.L, params.C, params.V, params.MFIzq, params.MFIjxzq
    MFIcrossdown(Params& params), params.H, params.L, params.C, params.V, params.MFIzq, params.MFIjxzq
    OBVpriceup(Params& params), params.C, params.V, params.OBVn
    OBVpricedown(Params& params), params.C, params.V, params.OBVn
    CCIoverbuy(Params& params), params.H, params.L, params.C, params.CCIn
    CCIoversell(Params& params), params.H, params.L, params.C, params.CCIn
    TRIXcrossup(Params& params), params.C, params.TRIXzq, params.TRIXjxzq
    TRIXcrossdown(Params& params), params.C, params.TRIXzq, params.TRIXjxzq
    TRIXlong(Params& params), params.C, params.TRIXzq, params.TRIXjxzq
    TRIXshort(Params& params), params.C, params.TRIXzq, params.TRIXjxzq
    MTMcrossup(Params& params), params.C, params.MTMzq, params.MTMjxzq
    MTMcrossdown(Params& params), params.C, params.MTMzq, params.MTMjxzq
    DMAIcorossup(Params& params), params.C, params.DMAn1, params.DMAn2, params.DMAm
    DMAIcorossdown(Params& params), params.C, params.DMAn1, params.DMAn2, params.DMAm
    DMIcrossup(Params& params), params.H, params.L, params.C, params.DMIn
    DMIcrossdown(Params& params), params.H, params.L, params.C, params.DMIn
    
    up,down=ARoon(price[],n)
    rASI,rASIMA=ASI(H,L,C,O,n1,n2)
    rMTR,rATR=ATR(H,L,C,n1)
    rAveDev=AveDev(price[],n)
    rBBI=BBI(price[],n1,n2,n3,n4)
    rBOLL,up,down=BOLL(price[],n1)
    rCCI=CCI(H,L,C,n1)
    rDMA=DMA(price[],fSmooth)
    rDIF,rDIFMA=DMAI(price[],n1,n2,n3)
    rPDI,rMDI,rADX,rADXR=DMI(H,L,C,n1,n2)
    rEMA=EMA(price[],n)
    rHL=HL(price[],n1,n2)
    rK,rD,rJ=KDJ(H,L,C,n1,n2,n3)
    rMA=MA(price[],n)
    rDIF,rDEA,rMACD=MACD(price[],n1,n2,n3)
    rMean,rStd=MeanStd(price[],n1,n2)
    rMFI,rMAMFI=MFI(H,L,C,V,n1,n2)
    rMTM,rMTMMA=MTM(price[],n1,n2)
    rOBV,rMAOBV=OBV(C,V,n1)
    rROC,rMAROC=ROC(price[],n1,n2)
    rRSI1,rRSI2,rRSI3=RSI(price[],n1,n2,n3)
    rSAR,rDirection=SAR(H,L,n1,BaseAF,AddAF,MaxAF)
    rSMA=SMA(price[],n1,n2)
    rSTD=STD(price[],n)
    rTRIX,rMATRIX=TRIX(price[],n1,n2)
    rWMA=WMA(price[],n)
    rWR1,rWR2=WR(H,L,C,n1,n2)
    )"; // 可选的模块文档字符串
    m.def("ARoon", [](std::vector<double> &p, int n1){
        auto result=ARoon(p, n1);
        return py::make_tuple(std::get<0>(result), std::get<1>(result));
    }, "Enter price[] and n, and output two vectors, up and down, for ARoon"); 
    m.def("ASI", [](std::vector<double> &H,std::vector<double> &L,std::vector<double> &C,std::vector<double> &O, int n1, int n2){
        auto result=ASI(H,L,C,O, n1,n2);
        return py::make_tuple(std::get<0>(result), std::get<1>(result));
    }, R"(Enter H, L, C, O, n1, and n2, and output two vectors, ASI and ASIMA, where n1 is the ASI period, ASIMA = MA(ASI, n2))"); 
    m.def("ATR", [](std::vector<double> &H,std::vector<double> &L,std::vector<double> &C, int n1){
        auto result=ATR(H,L,C, n1);
        return py::make_tuple(std::get<0>(result), std::get<1>(result));
    }, "Enter H, L, C, and n, then output two vectors, MTR and ATR, where ATR = MA(MTR, n)");
    m.def("AveDev", &AveDev, "Enter price[] and n, then output the n-period AveDev vector of price");
    m.def("BBI", [](std::vector<double> &p, int n1, int n2, int n3, int n4){
        return BBI(p, n1, n2, n3, n4);
    }, R"(Enter price[] and n1, n2, n3, n4, then output the BBI vector of price. 
    BBI: (MA(CLOSE, n1) + MA(CLOSE, n2) + MA(CLOSE, n3) + MA(CLOSE, n4)) / 4)");
    m.def("BOLL", [](std::vector<double> &p, int n1){
        auto result=BOLL(p, n1);
        return py::make_tuple(std::get<0>(result), std::get<1>(result), std::get<2>(result));
    }, "Enter price[] and n, then output three vectors: BOLL, UPPER, and LOWER for price");
    m.def("CCI", &CCI, R"(Enter H, L, C, and n, then output the CCI vector, 
    TYP:=(HIGH+LOW+CLOSE)/3, 
    CCI=(TYP-MA(TYP,n))/(0.015*AVEDEV(TYP,n)))");
    m.def("DMA", &DMA, R"(Enter price[] and fSmooth, then output the DMA vector of price, 
     DMA(A, X) = Y = A * X + (1 - A) * Y',
     where Y' represents the value of Y from the previous period)");
    m.def("DMAI", [](std::vector<double> &p, int n1, int n2, int n3){
        auto result=DMAI(p, n1, n2, n3);
        return py::make_tuple(std::get<0>(result), std::get<1>(result));
    }, R"(Enter price[] and n1, n2, n3, then output two vectors, DIF and DIFMA, for price. 
    DIF: MA(CLOSE, N1) - MA(CLOSE, N2), 
    DIFMA: MA(DIF, N3))");
    m.def("DMI", [](std::vector<double> &H,std::vector<double> &L,std::vector<double> &C, int n1, int n2){
        auto result=DMI(H,L,C, n1, n2);
        return py::make_tuple(std::get<0>(result), std::get<1>(result), std::get<2>(result), std::get<3>(result));
    }, R"(Enter H, L, C, and n1, n2, then output four vectors: PDI, MDI, ADX, and ADXR. 
    MTR:=SUM(MAX(MAX(HIGH-LOW,ABS(HIGH-REF(CLOSE,1))),ABS(REF(CLOSE,1)-LOW)),N);
    HD :=HIGH-REF(HIGH,1);
    LD :=REF(LOW,1)-LOW;
    DMP:=SUM(IF(HD>0&&HD>LD,HD,0),N);
    DMM:=SUM(IF(LD>0&&LD>HD,LD,0),N);
    PDI: DMP100/MTR;
    MDI: DMM100/MTR;
    ADX: MA(ABS(MDI-PDI)/(MDI+PDI)*100,M);
    ADXR:(ADX+REF(ADX,M))/2)");
    m.def("EMA", &EMA, "Enter price[] and n, then output the n-period EMA vector of price");
    m.def("HL", &HL, R"(Enter price[] and n1, n2, then output the HL vector of price. 
    If n1=0, it represents the minimum value; if n1=1, it represents the maximum value. 
    n2 is the number of periods for calculating the extrema)");
    m.def("KDJ", [](std::vector<double> &H,std::vector<double> &L,std::vector<double> &C, int n1, int n2, int n3){
        auto result=KDJ(H,L,C, n1, n2, n3);
        return py::make_tuple(std::get<0>(result), std::get<1>(result), std::get<2>(result));
    }, R"(Enter H, L, C, and n1, n2, n3, then output three vectors: K, D, and J. 
    RSV:=(CLOSE-LLV(LOW,N))/(HHV(HIGH,N)-LLV(LOW,N))100; 
    K:SMA(RSV,M1,1); 
    D:SMA(K,M2,1); 
    J:3K-2*D)");
    m.def("MA", &MA, "Enter price[] and n, then output the n-period MA (Moving Average) vector of price");
    m.def("MACD", [](std::vector<double> &p, int n1, int n2, int n3){
        try{
            auto result=MACD(p, n1, n2, n3);
            return py::make_tuple(std::get<0>(result), std::get<1>(result), std::get<2>(result));
        } catch (const std::exception& e){
            throw py::value_error(e.what());
        }
    }, R"(Enter price[] and n1, n2, n3, then output three vectors for price: DIF, DEA, and MACD. 
    DIF: EMA(CLOSE, SHORT) - EMA(CLOSE, LONG), 
    DEA: EMA(DIF, MID), 
    MACD: (DIF - DEA) * 2, 
    where SHORT, LONG, and MID correspond to n1, n2, and n3 respectively)");
    m.def("MeanStd", [](std::vector<double> &p, int n1, int n2){
        auto result=MeanStd(p, n1, n2);
        return py::make_tuple(std::get<0>(result), std::get<1>(result));
    }, R"(Enter price[] and n1, n2, then output two vectors for price: Mean and Std. 
    Calculate the mean and variance of the first n1 data points. 
    When n2=0, the denominator for variance calculation is n1, otherwise it is n1-1)");
    m.def("MFI", [](std::vector<double> &H,std::vector<double> &L,std::vector<double> &C,std::vector<double> &V, int n1, int n2){
        auto result=MFI(H,L,C,V, n1,n2);
        return py::make_tuple(std::get<0>(result), std::get<1>(result));
    }, R"(Enter H, L, C, V, and n1, n2, then output two vectors: MFI and MAMFI. 
    TYP:=(HIGH+LOW+CLOSE)/3; 
    V1:=SUM(IF(TYP>REF(TYP,1),TYPVOL,0),N)/SUM(IF(TYP<REF(TYP,1),TYPVOL,0),N); 
    MFI:100-(100/(1+V1)); 
    where n1 is the period for calculating MFI, and n2 is the period for calculating MAMFI)");
    m.def("MTM", [](std::vector<double> &p, int n1, int n2){
        auto result=MTM(p, n1, n2);
        return py::make_tuple(std::get<0>(result), std::get<1>(result));
    }, R"(Enter price[] and n1, n2, then output two vectors for price: MTM and MTMMA. 
    MTM: CLOSE - REF(CLOSE, N1), 
    MTMMA: MA(MTM, N2))");
    m.def("OBV", [](std::vector<double> &C,std::vector<double> &V, int n1){
        auto result=OBV(C,V, n1);
        return py::make_tuple(std::get<0>(result), std::get<1>(result));
    }, R"(Enter C, V, and n, then output two vectors: OBV and MAOBV. 
    VA:=IF(CLOSE>REF(CLOSE,1),VOL,-VOL); where VOL represents the trading volume in shares. 
    OBV:SUM(IF(CLOSE=REF(CLOSE,1),0,VA),0); 
    MAOBV:MA(OBV,N))");
    m.def("ROC", [](std::vector<double> &p, int n1, int n2){
        auto result=ROC(p, n1, n2);
        return py::make_tuple(std::get<0>(result), std::get<1>(result));
    }, R"(Enter price[] and n1, n2, then output two vectors for price: ROC and MAROC. 
    NN:=MIN(BARSCOUNT(C),N1); 
    ROC: 100 * (CLOSE - REF(CLOSE, NN)) / REF(CLOSE, NN); 
    MAROC: MA(ROC, N2))");
    m.def("RSI", [](std::vector<double> &p, int n1, int n2, int n3){
        auto result=RSI(p, n1, n2, n3);
        return py::make_tuple(std::get<0>(result), std::get<1>(result), std::get<2>(result));
    }, R"(Enter price[] and n1, n2, n3, then output three vectors for price: RSI1, RSI2, and RSI3. 
    LC:=REF(CLOSE,1); 
    RSI1: SMA(MAX(CLOSE-LC,0),N1,1)/SMA(ABS(CLOSE-LC),N1,1)*100; 
    RSI2: SMA(MAX(CLOSE-LC,0),N2,1)/SMA(ABS(CLOSE-LC),N2,1)*100; 
    RSI3: SMA(MAX(CLOSE-LC,0),N3,1)/SMA(ABS(CLOSE-LC),N3,1)*100)");
    m.def("SAR", [](std::vector<double> &H,std::vector<double> &L, int n1,int BaseAF,int AddAF,int MaxAF){
        auto result=SAR(H,L, n1,BaseAF,AddAF,MaxAF);
        return py::make_tuple(std::get<0>(result), std::get<1>(result));
    }, R"(Enter H, L, and n1, BaseAF, AddAF, MaxAF, then output two vectors: SAR and Direction. 
    SAR: SAR = SAR + AF * (EP - SAR), 
    where AF is the acceleration factor, EP is the extreme price, and SAR is the stop-and-reverse value. 
    Direction: 1 represents the upward trend, -1 represents the downward trend)");
    m.def("SMA", [](std::vector<double> &p, int n1, int n2){
        return SMA(p, n1, n2);
    }, R"(Enter price[] and n1, n2, then output the SMA vector of price. 
    SMA = (n1 * CLOSE + n2 * SMA') / (n1 + n2), 
    where SMA' represents the value of SMA from the previous period)");
    m.def("STD", &STD, "Enter price[] and n, then output the n-period STD vector of price,where the denominator for variance calculation is n-1");
    m.def("TRIX", [](std::vector<double> &p, int n1, int n2){
        auto result=TRIX(p, n1, n2);
        return py::make_tuple(std::get<0>(result), std::get<1>(result));
    }, R"(Enter price[] and n1, n2, then output two vectors for price: TRIX and MATRIX. 
    TR:=(CLOSE-REF(CLOSE,1))/REF(CLOSE,1)*100; 
    TRMA:MA(TR,N); 
    TRIX:MA(TRMA,N); 
    MATRIX:MA(TRIX,N))");
    m.def("WMA", &WMA, "Enter price[] and n, then output the n-period WMA vector of price");
    m.def("WR", [](std::vector<double> &H,std::vector<double> &L,std::vector<double> &C, int n1, int n2){
        auto result=WR(H,L,C, n1, n2);
        return py::make_tuple(std::get<0>(result), std::get<1>(result));
    }, R"(Enter H, L, C, and n1, n2, then output two vectors: WR1 and WR2. 
    WR1: 100 * (HHV(HIGH, N) - CLOSE) / (HHV(HIGH, N) - LLV(LOW, N)), 
    WR2: 100 * (CLOSE - LLV(LOW, N2)) / (HHV(HIGH, N2) - LLV(LOW, N2)))");
    py::class_<Params>(m,"Params")
        .def(py::init<>())
        .def_readwrite("H", &Params::H)
        .def_readwrite("L", &Params::L)
        .def_readwrite("C", &Params::C)
        .def_readwrite("O", &Params::O)
        .def_readwrite("V", &Params::V)
        .def_readwrite("MAdx", &Params::MAdx)
        .def_readwrite("MAcx", &Params::MAcx)
        .def_readwrite("EMAdx", &Params::EMAdx)
        .def_readwrite("EMAcx", &Params::EMAcx)
        .def_readwrite("WMAdx", &Params::WMAdx)
        .def_readwrite("WMAcx", &Params::WMAcx)
        .def_readwrite("MACDdx", &Params::MACDdx)
        .def_readwrite("MACDcx", &Params::MACDcx)
        .def_readwrite("MACDdea", &Params::MACDdea)
        .def_readwrite("ATR1bs", &Params::ATR1bs)
        .def_readwrite("ATR2xj", &Params::ATR2xj)
        .def_readwrite("ATR2sj", &Params::ATR2sj)
        .def_readwrite("ATRzq", &Params::ATRzq)
        .def_readwrite("ASIn", &Params::ASIn)
        .def_readwrite("ASIm", &Params::ASIm)
        .def_readwrite("ASItpzq", &Params::ASItpzq)
        .def_readwrite("ROCn", &Params::ROCn)
        .def_readwrite("RSIdx", &Params::RSIdx)
        .def_readwrite("RSIcx", &Params::RSIcx)
        .def_readwrite("AROONz", &Params::AROONz)
        .def_readwrite("AROONzq", &Params::AROONzq)
        .def_readwrite("BOLLn", &Params::BOLLn)
        .def_readwrite("Kentner_ATRn", &Params::Kentner_ATRn)
        .def_readwrite("Kentner_ATRmid", &Params::Kentner_ATRmid)
        .def_readwrite("Kentner_ATRbs", &Params::Kentner_ATRbs)
        .def_readwrite("KDJrsv", &Params::KDJrsv)
        .def_readwrite("KDJk", &Params::KDJk)
        .def_readwrite("KDJd", &Params::KDJd)
        .def_readwrite("BBIn1", &Params::BBIn1)
        .def_readwrite("BBIn2", &Params::BBIn2)
        .def_readwrite("BBIn3", &Params::BBIn3)
        .def_readwrite("BBIn4", &Params::BBIn4)
        .def_readwrite("WRoverbuywr1", &Params::WRoverbuywr1)
        .def_readwrite("WRoversellwr1", &Params::WRoversellwr1)
        .def_readwrite("WRn", &Params::WRn)
        .def_readwrite("MFIzq", &Params::MFIzq)
        .def_readwrite("MFIjxzq", &Params::MFIjxzq)
        .def_readwrite("OBVn", &Params::OBVn)
        .def_readwrite("CCIn", &Params::CCIn)
        .def_readwrite("CCIoverbuy", &Params::CCIoverbuy)
        .def_readwrite("CCIoversell", &Params::CCIoversell)
        .def_readwrite("TRIXzq", &Params::TRIXzq)
        .def_readwrite("TRIXjxzq", &Params::TRIXjxzq)
        .def_readwrite("MTMzq", &Params::MTMzq)
        .def_readwrite("MTMjxzq", &Params::MTMjxzq)
        .def_readwrite("DMAn1", &Params::DMAn1)
        .def_readwrite("DMAn2", &Params::DMAn2)
        .def_readwrite("DMAm", &Params::DMAm)
        .def_readwrite("DMIn", &Params::DMIn)
        .def_readwrite("BIASjx", &Params::BIASjx)
        .def_readwrite("BIAS1glv", &Params::BIAS1glv)
        .def_readwrite("BIAS2glvxj", &Params::BIAS2glvxj)
        .def_readwrite("BIAS2glvsj", &Params::BIAS2glvsj);
    py::class_<Signals>(m,"Signals")
        .def(py::init<>())
        .def("MAcrossup", &Signals::MAcrossup,py::arg("params"), R"(MA, Intraday K-Moving Average, a simple moving average calculated at the N-day closing price.
        Golden fork: the short moving average wears the long moving average
        Note: the so-called upper crossing is the T-1 day short moving average value < long moving average value, T day short moving average value > long moving average value.
        The function parameters are C, MAdx = 5, MAcx = 20.)")
        .def("MAcrossdown", &Signals::MAcrossdown,py::arg("params"), R"(MA, Intraday K-Moving Average, a simple moving average calculated at the N-day closing price.
        Dead fork: The short moving average underpasses the long moving average
        Note: the so-called underpass is the T-1 day short moving average value > long moving average value, the T-day short moving average value < long moving average value.
        The function parameters are C, MAdx = 5, MAcx = 20.)")
        .def("MAlong", &Signals::MAlong,py::arg("params"), R"(MA, Intraday K-Moving Average, a simple moving average calculated at the N-day closing price.
        Long: T-day closing price > T-day short MA line > T-day long MA line
        The function parameters are C, MAdx = 5, MAcx = 20.)")
        .def("MAshort", &Signals::MAshort,py::arg("params"), R"(MA, Intraday K-Moving Average, a simple moving average calculated at the N-day closing price.
        Short: T-day closing price < T-day short MA line < T-day long MA line
        The function parameters are C, MAdx = 5, MAcx = 20.)")
        .def("EMAcrossup", &Signals::EMAcrossup,py::arg("params"), R"(EMA, Exponential Moving Average, a moving average calculated at the N-day closing price.
        Golden fork: the short moving average wears the long moving average
        Note: the so-called upper crossing is the T-1 day short moving average value < long moving average value, T day short moving average value > long moving average value.
        The function parameters are C, EMAdx = 5, EMAcx = 20.)")
        .def("EMAcrossdown", &Signals::EMAcrossdown,py::arg("params"), R"(EMA, Exponential Moving Average, a moving average calculated at the N-day closing price.
        Dead fork: The short moving average underpasses the long moving average
        Note: the so-called underpass is the T-1 day short moving average value > long moving average value, the T-day short moving average value < long moving average value.
        The function parameters are C, EMAdx = 5, EMAcx = 20.)")
        .def("EMAlong", &Signals::EMAlong,py::arg("params"), R"(EMA, Exponential Moving Average, a moving average calculated at the N-day closing price.
        Long: T-day closing price > T-day short EMA line > T-day long EMA line
        The function parameters are C, EMAdx = 5, EMAcx = 20.)")
        .def("EMAshort", &Signals::EMAshort,py::arg("params"), R"(EMA, Exponential Moving Average, a moving average calculated at the N-day closing price.
        Short: T-day closing price < T-day short EMA line < T-day long EMA line
        The function parameters are C, EMAdx = 5, EMAcx = 20.)")
        .def("WMAcrossup", &Signals::WMAcrossup,py::arg("params"), R"(WMA, Weighted Moving Average, a moving average calculated at the N-day closing price.
        Golden fork: the short moving average wears the long moving average
        Note: the so-called upper crossing is the T-1 day short moving average value < long moving average value, T day short moving average value > long moving average value.
        The function parameters are C, WMAdx = 5, WMAcx = 20.)")
        .def("WMAcrossdown", &Signals::WMAcrossdown,py::arg("params"), R"(WMA, Weighted Moving Average, a moving average calculated at the N-day closing price.
        Dead fork: The short moving average underpasses the long moving average
        Note: the so-called underpass is the T-1 day short moving average value > long moving average value, the T-day short moving average value < long moving average value.
        The function parameters are C, WMAdx = 5, WMAcx = 20.)")
        .def("WMAlong", &Signals::WMAlong,py::arg("params"), R"(WMA, Weighted Moving Average, a moving average calculated at the N-day closing price.
        Long: T-day closing price > T-day short WMA line > T-day long WMA line
        The function parameters are C, WMAdx = 5, WMAcx = 20.)")
        .def("WMAshort", &Signals::WMAshort,py::arg("params"), R"(WMA, Weighted Moving Average, a moving average calculated at the N-day closing price.
        Short: T-day closing price < T-day short WMA line < T-day long WMA line
        The function parameters are C, WMAdx = 5, WMAcx = 20.)")
        .def("MACDcrossup", &Signals::MACDcrossup,py::arg("params"), R"(MACD, Moving Average Convergence Divergence, a moving average calculated at the N-day closing price.
        MACD Golden Fork: On day T-1, MACD < 0, on day T, MACD > 0, DEA value on day T-1 < = DEA value on day T
        The function parameters are C, MACDdx = 12, MACDcx = 26, MACDdea = 9.)")
        .def("MACDcrossdown", &Signals::MACDcrossdown,py::arg("params"), R"(MACD, Moving Average Convergence Divergence, a moving average calculated at the N-day closing price.
        MACD Dead Fork: On day T-1, MACD > 0, on day T, MACD < 0, DEA value on day T-1 > = DEA value on day T
        The function parameters are C, MACDdx = 12, MACDcx = 26, MACDdea = 9.)")
        .def("ATRxy", &Signals::ATRxy,py::arg("params"), R"(ATR, the N-day simple moving average of true volatility.
        True volatility = MAX(MAX(HIGH-LOW,ABS(HIGH-REF(CLOSE,1))),ABS(REF(CLOSE,1)-LOW)
        The function parameters are H, L, C, ATRzq = 14, ATR1bs = 2.)")
        .def("ATRqj", &Signals::ATRqj,py::arg("params"), R"(ATR, the N-day simple moving average of true volatility.
        True volatility = MAX(MAX(HIGH-LOW,ABS(HIGH-REF(CLOSE,1))),ABS(REF(CLOSE,1)-LOW)
        The function parameters are H, L, C, ATRzq = 14, ATR2xj = 2, ATR2sj = 3.)")
        .def("ASIcrossup", &Signals::ASIcrossup,py::arg("params"), R"(ASI, Accumulation Swing Index (ASI), also known as the real line, attempts to build a fantasy line with 
        the opening, highest, lowest, and closing prices in order to explain the market trend.
        ASI cross, the gold fork is the ASI moving average on the ASI line, and the dead fork is the ASI moving average under the ASI line.
        The function parameters are H, L, C, O, ASIn = 14, ASIm = 6.)")
        .def("ASIcrossdown", &Signals::ASIcrossdown,py::arg("params"), R"(ASI, Accumulation Swing Index (ASI), also known as the real line, attempts to build a fantasy line with
        the opening, highest, lowest, and closing prices in order to explain the market trend.
        ASI cross, the gold fork is the ASI moving average on the ASI line, and the dead fork is the ASI moving average under the ASI line.
        The function parameters are H, L, C, O, ASIn = 14, ASIm = 6.)")
        .def("ASIupbreakthrough", &Signals::ASIupbreakthrough,py::arg("params"), R"(ASI, Accumulation Swing Index (ASI), also known as the real line, attempts to build a fantasy line with
        the opening, highest, lowest, and closing prices in order to explain the market trend.
        The ASI breaks through, breaking through the recent high, that is, the ASI value of the day is the largest in the near future, 
        and breaking through the recent low, that is, the ASI value of the day is the smallest in the near future.
        The function parameters are H, L, C, O, ASIn = 14, ASIm = 6, ASItpzq = 30.)")
        .def("ASIdownbreakthrough", &Signals::ASIdownbreakthrough,py::arg("params"), R"(ASI, Accumulation Swing Index (ASI), also known as the real line, attempts to build a fantasy line with
        the opening, highest, lowest, and closing prices in order to explain the market trend.
        The ASI breaks through, breaking through the recent high, that is, the ASI value of the day is the largest in the near future, 
        and breaking through the recent low, that is, the ASI value of the day is the smallest in the near future.
        The function parameters are H, L, C, O, ASIn = 14, ASIm =6, ASItpzq = 30.)")
        .def("ROCcrossup", &Signals::ROCcrossup,py::arg("params"), R"(ROC, the rate of change, 
        NN = the number of valid data periods for the closing price and the smaller value of N
        ROC = 100 * (closing price - closing price before NN day)/closing price before NN day
        ROC gold fork: wear 0 value line on ROC
        ROC dead fork: ROC under the 0 value line
        The function parameters are C, ROCn = 20.)")
        .def("ROCcrossdown", &Signals::ROCcrossdown,py::arg("params"), R"(ROC, the rate of change,
        NN = the number of valid data periods for the closing price and the smaller value of N
        ROC = 100 * (closing price - closing price before NN day)/closing price before NN day
        ROC gold fork: wear 0 value line on ROC
        ROC dead fork: ROC under the 0 value line
        The function parameters are C, ROCn = 20.)")
        .def("RSIcrossup", &Signals::RSIcrossup,py::arg("params"), R"(The RSI, the Relative Strength Index, 
        is composed of several indicator lines with different periods,
        Golden fork: short-period indicator line through long-period indicator line
        The function parameters are C, RSIdx = 6, RSIcx = 14.)")
        .def("RSIcrossdown", &Signals::RSIcrossdown,py::arg("params"), R"(The RSI, the Relative Strength Index,
        is composed of several indicator lines with different periods,
        Dead fork: short-cycle indicator line to wear long-cycle indicator line
        The function parameters are C, RSIdx = 6, RSIcx = 14.)")
        .def("AROONupgrade", &Signals::AROONupgrade,py::arg("params"), R"(AROON, the Aron indicator, consists of two lines, the upper and the lower
        Upper rail value = (number of days since the highest price in N-N days)/N * 100
        Lower rail value = (number of days since the highest price in N-N days)/N * 100
        AROON up grade means that the upper rail value is greater than the threshold value
        The function parameters are C, AROONz = 50, AROONzq = 25.)")
        .def("AROONupless", &Signals::AROONupless,py::arg("params"), R"(AROON, the Aron indicator, consists of two lines, the upper and the lower
        Upper rail value = (number of days since the highest price in N-N days)/N * 100
        Lower rail value = (number of days since the highest price in N-N days)/N * 100
        AROON up less means that the upper rail value is less than the threshold value
        The function parameters are C, AROONz = 50, AROONzq = 25.)")
        .def("AROONdowngrade", &Signals::AROONdowngrade,py::arg("params"), R"(AROON, the Aron indicator, consists of two lines, the upper and the lower
        Upper rail value = (number of days since the highest price in N-N days)/N * 100
        Lower rail value = (number of days since the highest price in N-N days)/N * 100
        AROON down grade means that the lower rail value is greater than the threshold value
        The function parameters are C, AROONz = 50, AROONzq = 25.)")
        .def("AROONdownless", &Signals::AROONdownless,py::arg("params"), R"(AROON, the Aron indicator, consists of two lines, the upper and the lower
        Upper rail value = (number of days since the highest price in N-N days)/N * 100
        Lower rail value = (number of days since the highest price in N-N days)/N * 100
        AROON down less means that the lower rail value is less than the threshold value
        The function parameters are C, AROONz = 50, AROONzq = 25.)")
        .def("BOLLbreakup", &Signals::BOLLbreakup,py::arg("params"), R"(Bollinger lines, consisting of three upper, middle and lower track lines
        Mid-rail = N-day simple moving average of the closing price
        Upper rail = middle rail value + 2 times the standard deviation of M-day closing price
        Lower rail = middle rail value - 2 times the standard deviation of the daily closing price of M
        Break through the upper track: T-1 day closing price < T-1 day upper track value, T day closing price > T day upper track value
        The function parameters are C, BOLLn = 20.)")
        .def("BOLLbreakdown", &Signals::BOLLbreakdown,py::arg("params"), R"(Bollinger lines, consisting of three upper, middle and lower track lines
        Mid-rail = N-day simple moving average of the closing price
        Upper rail = middle rail value + 2 times the standard deviation of M-day closing price
        Lower rail = middle rail value - 2 times the standard deviation of the daily closing price of M
        Break through the lower track: T-1 day closing price > T-1 day lower track value, T day closing price < T day lower track value
        The function parameters are C, BOLLn = 20.)")
        .def("BOLLlocalup", &Signals::BOLLlocalup,py::arg("params"), R"(Bollinger lines, consisting of three upper, middle and lower track lines
        Mid-rail = N-day simple moving average of the closing price
        Upper rail = middle rail value + 2 times the standard deviation of M-day closing price
        Lower rail = middle rail value - 2 times the standard deviation of the daily closing price of M
        Located in the upper rail: upper rail value > = latest price > = middle rail value
        The function parameters are C, BOLLn = 20.)")
        .def("BOLLlocaldown", &Signals::BOLLlocaldown,py::arg("params"), R"(Bollinger lines, consisting of three upper, middle and lower track lines
        Mid-rail = N-day simple moving average of the closing price
        Upper rail = middle rail value + 2 times the standard deviation of M-day closing price
        Lower rail = middle rail value - 2 times the standard deviation of the daily closing price of M
        Located in the lower rail: lower rail value < = latest price < = middle rail value
        The function parameters are C, BOLLn = 20.)")
        .def("Kentner_ATRbreakup", &Signals::Kentner_ATRbreakup,py::arg("params"), R"(The Kentner channel is composed of two upper and lower track lines. 
        By judging the relationship between the k-line and the two track lines, the buying and selling signal of the target is determined. 
        The calculation method of the upper and lower track lines is as follows:
        MTR=MAX(MAX((HIGH-LOW),ABS(REF(CLOSE,1)-HIGH)),ABS(REF(CLOSE,1)-LOW))
        ATR=MA(MTR,n=40)
        mid=EMA(CLOSE,m=60)
        up=mid+ATR*2
        down=mid-ATR*2
        Break through the upper track: T-1 day closing price < T-1 day upper track value, T day closing price > T day upper track value
        The function parameters are H, L, C, Kentner_ATRn = 40, Kentner_ATRmid = 60, Kentner_ATRbs = 2.)")
        .def("Kentner_ATRbreakdown", &Signals::Kentner_ATRbreakdown,py::arg("params"), R"(The Kentner channel is composed of two upper and lower track lines.
        By judging the relationship between the k-line and the two track lines, the buying and selling signal of the target is determined. 
        The calculation method of the upper and lower track lines is as follows:
        MTR=MAX(MAX((HIGH-LOW),ABS(REF(CLOSE,1)-HIGH)),ABS(REF(CLOSE,1)-LOW))
        ATR=MA(MTR,n=40)
        mid=EMA(CLOSE,m=60)
        up=mid+ATR*2
        down=mid-ATR*2
        Break through the lower track: T-1 day closing price > T-1 day lower track value, T day closing price < T day lower track value
        The function parameters are H, L, C, Kentner_ATRn = 40, Kentner_ATRmid = 60, Kentner_ATRbs = 2.)")
        .def("Kentner_ATRoverup", &Signals::Kentner_ATRoverup,py::arg("params"), R"(The Kentner channel is composed of two upper and lower track lines.
        By judging the relationship between the k-line and the two track lines, the buying and selling signal of the target is determined. 
        The calculation method of the upper and lower track lines is as follows:
        MTR=MAX(MAX((HIGH-LOW),ABS(REF(CLOSE,1)-HIGH)),ABS(REF(CLOSE,1)-LOW))
        ATR=MA(MTR,n=40)
        mid=EMA(CLOSE,m=60)
        up=mid+ATR*2
        down=mid-ATR*2
        Over up: the closing price is higher than the upper track value.
        The function parameters are H, L, C, Kentner_ATRn = 40, Kentner_ATRmid = 60, Kentner_ATRbs = 2.)")
        .def("Kentner_ATRbelowdown", &Signals::Kentner_ATRbelowdown,py::arg("params"), R"(The Kentner channel is composed of two upper and lower track lines.
        By judging the relationship between the k-line and the two track lines, the buying and selling signal of the target is determined. 
        The calculation method of the upper and lower track lines is as follows:
        MTR=MAX(MAX((HIGH-LOW),ABS(REF(CLOSE,1)-HIGH)),ABS(REF(CLOSE,1)-LOW))
        ATR=MA(MTR,n=40)
        mid=EMA(CLOSE,m=60)
        up=mid+ATR*2
        down=mid-ATR*2
        Below down: the closing price is lower than the lower track value.
        The function parameters are H, L, C, Kentner_ATRn = 40, Kentner_ATRmid = 60, Kentner_ATRbs = 2.)")
        .def("KDJcrossup", &Signals::KDJcrossup,py::arg("params"), R"(KDJ, Stochastic oscillator, is a technical analysis tool used to analyze the trend of stock prices.
        RSV = (CLOSE-LLV(LOW,N))/(HHV(HIGH,N)-LLV(LOW,N)) * 100
        K = SMA(RSV,M1,1)
        D = SMA(K,M2,1)
        J = 3K-2D
        Gold fork: K line through D line
        The function parameters are H, L, C, KDJrsv = 9, KDJk = 3, KDJd = 3.)")
        .def("KDJcrossdown", &Signals::KDJcrossdown,py::arg("params"), R"(KDJ, Stochastic oscillator, is a technical analysis tool used to analyze the trend of stock prices.
        RSV = (CLOSE-LLV(LOW,N))/(HHV(HIGH,N)-LLV(LOW,N)) * 100
        K = SMA(RSV,M1,1)
        D = SMA(K,M2,1)
        J = 3K-2D
        Dead fork: Wear D line under K line
        The function parameters are H, L, C, KDJrsv = 9, KDJk = 3, KDJd = 3.)")
        .def("KDJlong", &Signals::KDJlong,py::arg("params"), R"(KDJ, Stochastic oscillator, is a technical analysis tool used to analyze the trend of stock prices.
        RSV = (CLOSE-LLV(LOW,N))/(HHV(HIGH,N)-LLV(LOW,N)) * 100
        K = SMA(RSV,M1,1)
        D = SMA(K,M2,1)
        J = 3K-2D
        Long: K value > 50 and D value > 50 and J value > 50
        The function parameters are H, L, C, KDJrsv = 9, KDJk = 3, KDJd = 3.)")
        .def("KDJshort", &Signals::KDJshort,py::arg("params"), R"(KDJ, Stochastic oscillator, is a technical analysis tool used to analyze the trend of stock prices.
        RSV = (CLOSE-LLV(LOW,N))/(HHV(HIGH,N)-LLV(LOW,N)) * 100
        K = SMA(RSV,M1,1)
        D = SMA(K,M2,1)
        J = 3K-2D
        Short: K value < 50 and D value < 50 and J value < 50
        The function parameters are H, L, C, KDJrsv = 9, KDJk = 3, KDJd = 3.)")
        .def("BBIcrossup", &Signals::BBIcrossup,py::arg("params"), R"(BBI = Sum of 4-period closing simple moving average values/4.
        Golden Fork: C[T-1]<BBI[T-1] and C[T]>BBI[T]
        The function parameters are C, BBIn1 = 3, BBIn2 = 6, BBIn3 = 12, BBIn4 = 24.)")
        .def("BBIcrossdown", &Signals::BBIcrossdown,py::arg("params"), R"(BBI = Sum of 4-period closing simple moving average values/4.
        Dead Fork: C[T-1]>BBI[T-1] and C[T]<BBI[T]
        The function parameters are C, BBIn1 = 3, BBIn2 = 6, BBIn3 = 12, BBIn4 = 24.)")
        .def("BBIlong", &Signals::BBIlong,py::arg("params"), R"(BBI = Sum of 4-period closing simple moving average values/4.
        Long: C[T]>BBI[T]
        The function parameters are C, BBIn1 = 3, BBIn2 = 6, BBIn3 = 12, BBIn4 = 24.)")
        .def("BBIshort", &Signals::BBIshort,py::arg("params"), R"(BBI = Sum of 4-period closing simple moving average values/4.
        Short: C[T]<BBI[T]
        The function parameters are C, BBIn1 = 3, BBIn2 = 6, BBIn3 = 12, BBIn4 = 24.)")
        .def("WRoverbuy", &Signals::WRoverbuy,py::arg("params"), R"(WR, Williams Overbought and Oversold Index, 
        is a technical analysis tool used to analyze the trend of stock prices.
        WR1=100*(HHV(HIGH,N)-CLOSE)/(HHV(HIGH,N)-LLV(LOW,N))
        The indicator takes 50 as the central axis, and a price above (below) 50 is considered to be in a decline (rise). 
        WR1 > 80 is oversold, considering the trend rebound; WR1 < 20 is overbought, considering the trend correction.
        The function parameters are H, L, C, WRoverbuywr1 = 20, WRn = 30.)")
        .def("WRoversell", &Signals::WRoversell,py::arg("params"), R"(WR, Williams Overbought and Oversold Index,
        is a technical analysis tool used to analyze the trend of stock prices.
        WR1=100*(HHV(HIGH,N)-CLOSE)/(HHV(HIGH,N)-LLV(LOW,N))
        The indicator takes 50 as the central axis, and a price above (below) 50 is considered to be in a decline (rise).
        WR1 > 80 is oversold, considering the trend rebound; WR1 < 20 is overbought, considering the trend correction.
        The function parameters are H, L, C, WRoversellwr1 = 80, WRn = 30.)")
        .def("MFIcrossup", &Signals::MFIcrossup,py::arg("params"), R"(MFI, the Money Flow Index.
        TYP=(HIGH+LOW+CLOSE)/3
        V1=SUM(IF(TYP>REF(TYP,1),TYP*VOL,0),N)
        MFI=100-(100/(1+V1))
        MAMFI=MA(MFI,M)
        Golden fork: MFI line through MFI moving average
        The function parameters are H, L, C, V, MFIzq = 14, MFIjxzq = 6.)")
        .def("MFIcrossdown", &Signals::MFIcrossdown,py::arg("params"), R"(MFI, the Money Flow Index.
        TYP=(HIGH+LOW+CLOSE)/3
        V1=SUM(IF(TYP>REF(TYP,1),TYP*VOL,0),N)
        MFI=100-(100/(1+V1))
        MAMFI=MA(MFI,M)
        Dead fork: Wear MFI line under MFI moving average
        The function parameters are H, L, C, V, MFIzq = 14, MFIjxzq = 6.)")
        .def("OBVpriceup", &Signals::OBVpriceup,py::arg("params"), R"(OBV, On Balance Volume.
        VA=IF(CLOSE>REF(CLOSE,1),VOL,-VOL)
        OBV=IF(CLOSE==REF(CLOSE,1),0,SUM(VA,N))
        Prices go up and OBV goes down: C[T]>C[T-1] and OBV[T]<OBV[T-1]
        Prices go down and OBV goes up: C[T]<C[T-1] and OBV[T]>OBV[T-1])
        The function parameters are C, V, OBVn = 30.)")
        .def("OBVpricedown", &Signals::OBVpricedown,py::arg("params"), R"(OBV, On Balance Volume.
        VA=IF(CLOSE>REF(CLOSE,1),VOL,-VOL)
        OBV=IF(CLOSE==REF(CLOSE,1),0,SUM(VA,N))
        Prices go up and OBV goes down: C[T]>C[T-1] and OBV[T]<OBV[T-1]
        Prices go down and OBV goes up: C[T]<C[T-1] and OBV[T]>OBV[T-1])
        The function parameters are C, V, OBVn = 30.)")
        .def("CCIoverbuy", &Signals::CCIoverbuy,py::arg("params"), R"(CCI, Commodity Channel Index.
        TYP=(HIGH+LOW+CLOSE)/3
        CCI=(TYP-MA(TYP,N))/(0.015*AVEDEV(TYP,N))
        CCI > 100 is overbought, CCI < -100 is oversold.
        The function parameters are H, L, C, CCIoverbuy = 100, CCIn = 14.)")
        .def("CCIoversell", &Signals::CCIoversell,py::arg("params"), R"(CCI, Commodity Channel Index.
        TYP=(HIGH+LOW+CLOSE)/3
        CCI=(TYP-MA(TYP,N))/(0.015*AVEDEV(TYP,N))
        CCI > 100 is overbought, CCI < -100 is oversold.
        The function parameters are H, L, C, CCIoversell = -100, CCIn = 14.)")
        .def("TRIXcrossup", &Signals::TRIXcrossup,py::arg("params"), R"(TRIX, the Triple Exponential Moving Average.
        MTR=EMA(EMA(EMA(CLOSE,N),N),N)
        TRIX=(MTR-REF(MTR,1))/REF(MTR,1)*100
        MATRIX=MA(TRIX,M)
        Golden Fork: TRIX on T-1 Day < MATRIX on T-1 Day, TRIX on T Day > MATRIX on T Day
        The function parameters are C, TRIXzq = 12, TRIXjxzq = 20.)")
        .def("TRIXcrossdown", &Signals::TRIXcrossdown,py::arg("params"), R"(TRIX, the Triple Exponential Moving Average.
        MTR=EMA(EMA(EMA(CLOSE,N),N),N)
        TRIX=(MTR-REF(MTR,1))/REF(MTR,1)*100
        MATRIX=MA(TRIX,M)
        Dead Fork: TRIX on T-1 Day > MATRIX on T-1 Day, TRIX on T Day < MATRIX on T Day
        The function parameters are C, TRIXzq = 12, TRIXjxzq = 20.)")
        .def("TRIXlong", &Signals::TRIXlong,py::arg("params"), R"(TRIX, the Triple Exponential Moving Average.
        MTR=EMA(EMA(EMA(CLOSE,N),N),N)
        TRIX=(MTR-REF(MTR,1))/REF(MTR,1)*100
        MATRIX=MA(TRIX,M)
        long: T-Day TRIX > T-Day MATRIX
        The function parameters are C, TRIXzq = 12, TRIXjxzq = 20.)")
        .def("TRIXshort", &Signals::TRIXshort,py::arg("params"), R"(TRIX, the Triple Exponential Moving Average.
        MTR=EMA(EMA(EMA(CLOSE,N),N),N)
        TRIX=(MTR-REF(MTR,1))/REF(MTR,1)*100
        MATRIX=MA(TRIX,M)
        short: T-Day TRIX < T-Day MATRIX
        The function parameters are C, TRIXzq = 12, TRIXjxzq = 20.)")
        .def("MTMcrossup", &Signals::MTMcrossup,py::arg("params"), R"(MTM, the rate of change.
        MTM=C-REF(C,N)
        MTMMA=MA(MTM,M)
        Golden Fork: MTM on T-1 Day < MTMMA on T-1 Day, MTM on T Day > MTMMA on T Day
        The function parameters are C, MTMzq = 12, MTMjxzq = 6.)")
        .def("MTMcrossdown", &Signals::MTMcrossdown,py::arg("params"), R"(MTM, the rate of change.
        MTM=C-REF(C,N)
        MTMMA=MA(MTM,M)
        Dead Fork: MTM on T-1 Day > MTMMA on T-1 Day, MTM on T Day < MTMMA on T Day
        The function parameters are C, MTMzq = 12, MTMjxzq = 6.)")
        .def("DMAIcrossup", &Signals::DMAIcrossup,py::arg("params"), R"(DMA, the difference between the moving average.
        DIF=MA(C,N1)-MA(C,N2)
        DMA=MA(DIF,M)
        DMA Golden Fork: DIF line breaks through DMA line from bottom to top
        The function parameters are C, DMAn1 = 10, DMAn2 = 5, DMAm = 10.)")
        .def("DMAIcrossdown", &Signals::DMAIcrossdown,py::arg("params"), R"(DMA, the difference between the moving average.
        DIF=MA(C,N1)-MA(C,N2)
        DMA=MA(DIF,M)
        DMA Dead Fork: DIF line breaks through DMA line from top to bottom
        The function parameters are C, DMAn1 = 10, DMAn2 = 5, DMAm = 10.)")
        .def("DMIcrossup", &Signals::DMIcrossup,py::arg("params"), R"(DMI (Directional Movement Index) index is a technical indicator that 
        provides a basis for judging trends by analyzing the changes in the balance of power between buyers and sellers during the rise 
        and fall of securities prices, that is, the changes in the power of long and short parties are affected 
        by price fluctuations and occur from equilibrium to imbalance.
        DMI Golden Fork: PDI line breaks through MDI line from bottom to top
        The function parameters are H, L, C, DMIn = 14.)")
        .def("DMIcrossdown", &Signals::DMIcrossdown,py::arg("params"), R"(DMI (Directional Movement Index) index is a technical indicator that
        provides a basis for judging trends by analyzing the changes in the balance of power between buyers and sellers during the rise 
        and fall of securities prices, that is, the changes in the power of long and short parties are affected 
        by price fluctuations and occur from equilibrium to imbalance.
        DMI dead fork: PDI line falls below MDI line from top to bottom
        The function parameters are H, L, C, DMIn = 14.)");
}

