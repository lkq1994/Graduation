function [SignalAddNoise,Noisenor2] = SignalAddPassBandNoise(SignalInput,Snr,fl,fh,fs)
%{
    函数功能说明：给一段信号添加带限高斯白噪声；
    输入参数说明：
    SignalInput：   需要添加噪声的信号
    Snr:            添加噪声后的信噪比
    PassFreqcoeff:  带通滤波器系数
%}
    %% 输入参数判断
    % 输入的序列必须是N×1或者1×N;
    PassFreqcoeff = fir1(512, [fl-5000 fh+5000]/(fs/2), 'BandPass');
    
    
    [m,n] = size(SignalInput);
    if (m~=1) && (n~=1)
        error('输入信号SignalInput必须为向量形式！')
    elseif m == 1
        SendSignalNum   = n;
        TempSignalInput = SignalInput;
    else
        SendSignalNum   = m;
        TempSignalInput = SignalInput.';
    end
    
    %% 给信号添加噪声
    Noise           = randn(1, 2 * SendSignalNum);               % 产生噪声点数是信号噪声的两倍
    NoiseFilterd    = filter(PassFreqcoeff, 1,  Noise);
    NoiseExtra      = NoiseFilterd(SendSignalNum - SendSignalNum/2:SendSignalNum + SendSignalNum/2 - 1);
    ENoise          = NoiseExtra * NoiseExtra';                 % 计算噪声的能量
    ESignal         = TempSignalInput * TempSignalInput';       % 计算信号的能量
    Noisenorl       = NoiseExtra / sqrt(ENoise);                % 噪声归一化
    Snr_ratio       = 10^( - Snr/20);
    Noisenor2       = Noisenorl * Snr_ratio * sqrt(ESignal);    % 得到带限的高斯白噪声
    SignalAddNoise  = TempSignalInput + Noisenor2;
 
end