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


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

PN = m_sequence([1 0 0 0 0 0 1]);
PNLength = length(PN);
M = N*PNLength;
dopHz = 0;
PN(PN==0)=-1;
PN1 = [PN((length(PN)+1)/2:end),PN(1:(length(PN)+1)/2-1)];
PN2 = [PN((length(PN)+1)/2:end),-PN(1:(length(PN)+1)/2-1)];
    %%%%%%%%%%%%%%%%%%%%%%解码%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
b_sum = zeros(1,16);%改信噪比范围需要改这个
c_sum = zeros(1,11);

sourcelength = 100;
    
  
%生成随机数据               
SNR = -25:-10;
mengtekaluo = 10;

for j=1:length(SNR)
    
    for jj=1:mengtekaluo
        sourcecode01 = unidrnd(2,1,sourcelength)-1;
        sourcecode = sourcecode01;
        sourcecode(sourcecode==0)=-1;
        d = zeros(1,sourcelength+1);
        d(1) = 1;
        for i=2:length(d)
                d(i) = sourcecode(i-1)*d(i-1);%差分编码
        end
        d(d==-1) = 0;     
        %生成数据
        [SignalReceive,carrier] = Signal_Carrier(sourcecode01,PN,fs,fh,fl);
        % figure;plot(SignalReceive)
        [signal_temp,Noisenor2] = SignalAddPassBandNoise(SignalReceive,SNR(j),fl,fh,fs);
        signallength = length(SignalReceive);
        signal_temp1 = resample(signal_temp,100010,100000);
%         carrier = resample(carrier,100010,100000);
        signal_send = [signal_temp1,zeros(1,100000)];
        PNSignal = SignalReceive(1:M);
        inx = 0;
        inxsum = 0;
        for i=0:sourcelength-1
            temp1 = signal_send(i*M+inxsum+1:(i+1)*M+inxsum);
            temp11 =  temp1.*carrier(1:M);
            temp12 = reshape(temp11,N,[]);
            temp13 = sum(temp12);
            temp2 = signal_send((i+1)*M+inxsum+1:(i+2)*M+inxsum);
            temp21 = temp2.*carrier(1:M);
            temp22 = reshape(temp21,N,[]);
            temp23 = sum(temp22);

            temp = [temp13((length(PN)+1)/2:end),temp23(1:(length(PN)+1)/2-1)];

%             corr_31 = abs(corr_fun(temp1,temp2));
%             figure;plot(abs(corr_31))
%             [E_hn_up31,down] = envelope(6000:6700,corr_31(6000:6700),'pchip');
%             figure;plot(E_hn_up31);
            
%             corr_32 = abs(corr_fun(PNSignal,PNSignal));
%             figure;plot(abs(corr_32))
%             [E_hn_up32,down] = envelope(6000:6700,corr_32(6000:6700),'pchip');
%             figure;plot(E_hn_up32);hold on;
%             [E_hn_up31,down] = envelope(6000:6700,corr_31(6000:6700),'pchip');
%             plot(E_hn_up31,'r');

            corr_11 = corr_fun(temp,PN1);
            corr_12 = corr_fun(temp,PN2);

            corr_2 = corr_fun(temp1,PNSignal);
            [m,inx] = max(abs(corr_2));
            inx = inx-M;
            inxsum = inx+inxsum;
%             figure;plot(corr_2)
    %         [m,pos(i+1)] = max(abs(corr_1));
    %         figure;plot(corr_1)
    %         corr_2 = corr_fun(temp23,PN);
            if(max(abs(corr_11))>max(abs(corr_12)))
                dd(i+1) = 1;
            else
                dd(i+1) = 0;
            end
        end
    [a,b] = biterr(sourcecode01,dd);
        
        b_sum(j) = b_sum(j)+b;
        
    end
       
end
b_sum = b_sum./mengtekaluo;
figure;semilogy(SNR,b_sum,'k-*');






