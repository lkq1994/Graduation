
clc
clear all
close all

totallength = 10e6;

f0 = 10000;
fs = 100000;
t = 0:1/fs:(totallength-1)/fs;
carrier = sin(2*pi*f0*t);
% carrier_fft = abs(fft(carrier));
% figure;plot(carrier_fft);
% [a,b] = max(carrier_fft(1:length(carrier_fft)/2))

carrier1 = resample(carrier,100090,100000);
carrier1 = carrier1(1:length(carrier));
carrier1_fft = abs(fft(carrier1));
figure;plot(carrier1_fft);
[a,b] = max(carrier1_fft(1:length(carrier1_fft)/2))


