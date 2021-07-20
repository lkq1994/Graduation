clc
clear all
close all

fs = 100000;
fh = 12000;
fl = 8000;
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
t = 1/fs:1/fs:length(hn)/fs;
figure;plot(t,hn);title('仿真信道');ylim([-1.5 1.5]);xlabel('Time (s)');ylabel('Amp');

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
for jjj=4:9
    PN = PNarray(jjj,1:2^jjj-1);

    SignalReceive = Signal(sourcecode01,PN,fs,fh,fl);
    signallength = length(SignalReceive);

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
    for SNR=-30:-10
        ii = ii+1;
        snr(ii) = SNR;
%         signal = awgn(signal_send,SNR,'measured');
        [signal,Noisenor2] = SignalAddPassBandNoise(SignalReceive,SNR,fl,fh,fs);
        decode = dspreadenery(signal,fs,f0,N,PN,sourcelength);
        [a,b(ii)] = biterr(sourcecode01,decode);
%         decode = despreaddirect(signal,fs,f0,N,PN,sourcelength);
%         [a,c(ii)] = biterr(d,decode);
    end
    if jjj==4
        semilogy(snr,b,'k-*');hold on;save ber4 b;
    end
    if jjj==5
        semilogy(snr,b,'b-^');hold on;save ber5 b;
    end
    if jjj==6
        semilogy(snr,b,'r-+');hold on;save ber6 b;
    end
    if jjj==7
        semilogy(snr,b,'m-o');hold on;save ber7 b;
    end
    if jjj==8
        semilogy(snr,b,'c-x');hold on;save ber8 b;
    end
    if jjj==9
        semilogy(snr,b,'g:^');hold on;save ber9 b;
    end

end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

title('误码率曲线');xlabel('SNR / dB');ylabel('BER')
legend('扩频序列长度15','扩频序列长度31','扩频序列长度63','扩频序列长度127','扩频序列长度255','扩频序列长度511')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




