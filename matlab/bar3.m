clc
clear all
close all

fs = 100000;
fh = 12000;
fl = 8000;
f0 = (fh+fl)/2;
N = 2*fs/(fh-fl);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
PNarray = zeros(9,2^9-1);
PNarray(9,1:2^9-1) = m_sequence([0 0 0 1 0 0 0 0 1]);
PNarray(8,1:2^8-1) = m_sequence([0 1 1 1 0 0 0 1]);
PNarray(7,1:2^7-1) = m_sequence([1 0 0 0 0 0 1]);
PNarray(6,1:2^6-1) = m_sequence([1 0 0 0 0 1]);
PNarray(5,1:2^5-1) = m_sequence([0 1 0 0 1]);
PNarray(4,1:2^4-1) = m_sequence([1 0 0 1]);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

t1 = [0.0001 0.0004 0.0008 0.001 0.0025 0.05];
% t1 = [0.00001 0.00004 0.00008 0.0001 0.00025 0.0005];
amp = [1 -0.8 0.7 0.5 -0.08 0.01];
hn = zeros(1,1*max(t1)*fs);
for i=1:length(t1)
    hn(t1(i)*fs+1) = amp(i);
end
t = 1/fs:1/fs:length(hn)/fs;
figure;plot(t,hn);title('仿真信道');ylim([-1.5 1.5]);xlabel('时间 (s)');ylabel('幅度');


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
mengtekaluo = 1000;
for jjj=7:7

    
    %%%%%%%%%%%%%%%%%%%%%%解码%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    ii=0;

    
    
    b_sum = zeros(1,26);%改信噪比范围需要改这个
    c_sum = zeros(1,26);
    for SNR=-25:0
        ii = ii+1;
        snr(ii) = SNR;
        
        
        %%%%%%%%%%%%%%%%%%%%%%
        sourcelength = 100;
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
            PN = PNarray(jjj,1:2^jjj-1);
%生成数据
        SignalReceive = Signal(sourcecode01,PN,fs,fh,fl);
%         figure;plot(SignalReceive)
        signallength = length(SignalReceive);
        signal_send1 = resample(SignalReceive,100000,100000);

        signal_send = conv(signal_send1,hn);
        signal_send2 = signal_send(1:signallength);

        %%%%%%%%%%%%%%%%%%%
        
        
        
        for jj=1:mengtekaluo
%             signal = awgn(signal_send2,SNR,'measured');
            [signal,Noisenor2] = SignalAddPassBandNoise(signal_send2,SNR,fl,fh,fs);
            decode = dspreadenery(signal,fs,f0,N,PN,sourcelength);
            [a,b] = biterr(sourcecode01,decode);
            b_sum(ii) = b_sum(ii)+b;
            decode = despreaddirect(signal,fs,f0,N,PN,sourcelength);
            d(d==-1)=0;
            [a,c] = biterr(d,decode);
            c_sum(ii) = c_sum(ii)+c;
        end
    end
   figure;semilogy(snr,b_sum./mengtekaluo,'k-*');
   hold on;semilogy(snr,c_sum./mengtekaluo,'b-^');

end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

title('误码率曲线');xlabel('信噪比 (dB)');ylabel('误码率')
legend('差分能量检测器','传统直扩')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




