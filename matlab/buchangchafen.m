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
    ii=0;

    b_sum = zeros(1,26);%改信噪比范围需要改这个
    c_sum = zeros(1,26);

    sourcelength = 1000;
        %生成随机数据               
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
    figure;plot(SignalReceive)
    signallength = length(SignalReceive);
    signal_temp = resample(SignalReceive,100010,100000);
    SNR = -15;
    [signal_temp,Noisenor2] = SignalAddPassBandNoise(signal_temp,SNR,fl,fh,fs);
    
    signal_send = signal_temp;
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

        
        corr_11 = corr_fun(temp,PN1);
        corr_12 = corr_fun(temp,PN2);
        
        corr_2 = corr_fun(temp1,PNSignal);
        [m,inx] = max(abs(corr_2));
        inx = inx-6350;
        inxsum = inx+inxsum;
%         figure;plot(corr_2)
%         [m,pos(i+1)] = max(abs(corr_1));
%         figure;plot(corr_1)
%         corr_2 = corr_fun(temp23,PN);
        if(max(abs(corr_11))>max(abs(corr_12)))
            dd(i+1) = 1;
        else
            dd(i+1) = 0;
        end
    end
    [a,c] = biterr(sourcecode01,dd)
%     temp1 = signal_send(1*M+1:2*M).*carrier(1:M);
%     temp11 = reshape(temp1,N,[]);
%     temp12 = sum(temp11);
% %     figure;plot(corr_fun(temp12,PN))
%     temp2 = signal_send(2*M+1:3*M).*carrier(1:M);
%     temp21 = reshape(temp2,N,[]);
%     temp22 = sum(temp21);
%     figure;plot(corr_fun(temp22,PN))
%     figure;plot(corr_fun(temp12,temp22))
%     figure;plot(corr_fun(temp1,temp2))

% temp3 = signal_send.*carrier; 
% temp31 = reshape(temp3,N,[]);
% temp32 = sum(temp31);


% figure;plot(corr_fun(temp32,PN))
    
    
    
    
    
    