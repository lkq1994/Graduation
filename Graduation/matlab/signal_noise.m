
%% 产生一个时域信号

fs = 100000;
t = 1/fs:1/fs:1000/fs;
SignalInput = cos(2 * pi * 10000 * t)';


%% 给信号添加带限高斯白噪声
Snr             = -10;
[SignalAddNoise,Noisenor2] = SignalAddPassBandNoise(SignalInput,Snr,8000,12000,100000);
%% 信噪比验证
% ESignal         = SignalInput' * SignalInput;       % 信号能量
% ENoise2         = Noisenor2 * Noisenor2';           % 噪声能量
% aa              = 10 * log10(ESignal/ENoise2);      % 信噪比验证
%% 添加噪声后的信号
figure
plot(real(SignalAddNoise));
