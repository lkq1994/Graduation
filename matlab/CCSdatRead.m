clc;clear all;close all;
I = importdata('LFM.dat');    

B = I.textdata;
B = B(2:end,:);
B = B(:,1);
% data = zeros(size(B),1);

for i=1:10000
    data(i) = str2num(cell2mat(B(i,1)));
end

fftdata = abs(fft(data));

figure;plot(fftdata(1:5000))
n1 = 256;
window=hanning(n1);
w1=window;

figure;
[S,F,T,P]=spectrogram(data,w1,8,2048,100);
h = pcolor(T ,F,abs(S));
% caxis([4,8]);
set(h,'edgecolor','none','facecolor','interp');
colorbar;
ylim([0 20])

