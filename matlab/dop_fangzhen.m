clc
clear all
close all

fs = 100000;
fh = 15000;
fl = 5000;
f0 = (fh+fl)/2;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
PNarray = zeros(9,2^9-1);
PNarray(9,1:2^9-1) = m_sequence([0 0 0 1 0 0 0 0 1]);
PNarray(8,1:2^8-1) = m_sequence([0 1 1 1 0 0 0 1]);
PNarray(7,1:2^7-1) = m_sequence([1 0 0 0 0 0 1]);
PNarray(6,1:2^6-1) = m_sequence([1 0 0 0 0 1]);
PNarray(5,1:2^5-1) = m_sequence([0 1 0 0 1]);
PNarray(4,1:2^4-1) = m_sequence([1 0 0 1]);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

t1 = [0.0001 0.0004 0.0008 0.001 0.0025 0.005];
amp = [1 -0.8 0.7 0.5 -0.08 0.01];
hn = zeros(1,1.1*max(t1)*fs);
for i=1:length(t1);
    hn(t1(i)*fs+1) = amp(i);
end
figure;plot(hn);title('仿真信道')

sourcelength = 10000;
%生成随机数据               
sourcecode01 = unidrnd(2,1,sourcelength)-1;
sourcecode = sourcecode01;
for i=1:length(sourcecode)
    if(sourcecode(i) == 0)
        sourcecode(i) = -1;
    end
end
d = zeros(1,sourcelength+1);
d(1) = 1;
for i=2:length(d)
    d(i) = sourcecode(i-1)*d(i-1);%差分编码
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure;
for jjj=7:7
    PN = PNarray(jjj,1:2^jjj-1);

    SignalReceive = Signal(sourcecode01,PN,fs,fh,fl);
    signallength = length(SignalReceive);
    SignalReceive = resample(SignalReceive,fs+8,fs);
    signal_send = conv(SignalReceive,hn);
    signal_send = signal_send(1:signallength);
    %%%%%%%%%%%%%%%%%%%%%%解码%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    ii=0;

    for i=1:length(d)
        if(d(i)==-1)
            d(i) = 0;
        end
    end
    N = 2*fs/(fh-fl);
    for SNR=-30:1:-10
        ii = ii+1;
        snr(ii) = SNR;
        signal = awgn(signal_send,SNR,'measured');

        decode = dspreadenery(signal,fs,f0,N,PN,sourcelength);
        [a,b(ii)] = biterr(sourcecode01,decode);
        decode = despreaddirect(signal,fs,f0,N,PN,sourcelength);
        [a,c(ii)] = biterr(d,decode);
    end
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure;
% semilogy(snr,b,'b-^');hold on;
semilogy(snr,c,'k-*')


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
x2 = [-30 -29 -28 -27 -26 -25 -24 -23 -22 -21 -20 -19 -18 -17 -16 -15 -14 -13 -12];
y2 = [0.503 0.497 0.493 0.490 0.486 0.47 0.45 0.42 0.38 0.34 0.3 0.26 0.2 0.175 0.138 0.105 0.083 0.0701 0.056];
hold on;
semilogy(x2,y2,'b-^')
title('误码率曲线');xlabel('信噪比 (dB)');ylabel('误码率')
legend('传统直扩','差分能量检测器');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




