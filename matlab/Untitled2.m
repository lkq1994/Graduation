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
t = 1/fs:1/fs:length(hn)/fs;
figure;plot(t,hn);title('�����ŵ�');ylim([-1.5 1.5]);xlabel('Time (s)');ylabel('Amp');

sourcelength = 1000;
%�����������               
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
    d(i) = sourcecode(i-1)*d(i-1);%��ֱ���
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

for jjj=9:9
    PN = PNarray(jjj,1:2^jjj-1);

    SignalReceive = Signal(sourcecode01,PN,fs,fh,fl);
    signallength = length(SignalReceive);
    
    signal_send1 = resample(SignalReceive,100010,100000);
    SignalReceive = signal_send1(1:length(SignalReceive));

%     signal_send = conv(SignalReceive,hn);
    signal_send = SignalReceive;
    %%%%%%%%%%%%%%%%%%%%%%����%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    ii=0;

    for i=1:length(d)
        if(d(i)==-1)
            d(i) = 0;
        end
    end
    N = 2*fs/(fh-fl);
    for SNR=-5
        ii = ii+1;
        snr(ii) = SNR;
        signal = awgn(signal_send,SNR,'measured');

%         decode = dspreadenery(signal,fs,f0,N,PN,sourcelength);
%         [a,b(ii)] = biterr(sourcecode01,decode);
        decode = despreaddirect(signal,fs,f0,N,PN,sourcelength);
        [a,c(ii)] = biterr(d,decode);
    end


end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




