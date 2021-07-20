function [SignalAddNoise,Noisenor2] = SignalAddPassBandNoise(SignalInput,Snr,fl,fh,fs)
%{
    ��������˵������һ���ź���Ӵ��޸�˹��������
    �������˵����
    SignalInput��   ��Ҫ����������ź�
    Snr:            ���������������
    PassFreqcoeff:  ��ͨ�˲���ϵ��
%}
    %% ��������ж�
    % ��������б�����N��1����1��N;
    PassFreqcoeff = fir1(512, [fl-5000 fh+5000]/(fs/2), 'BandPass');
    
    
    [m,n] = size(SignalInput);
    if (m~=1) && (n~=1)
        error('�����ź�SignalInput����Ϊ������ʽ��')
    elseif m == 1
        SendSignalNum   = n;
        TempSignalInput = SignalInput;
    else
        SendSignalNum   = m;
        TempSignalInput = SignalInput.';
    end
    
    %% ���ź��������
    Noise           = randn(1, 2 * SendSignalNum);               % ���������������ź�����������
    NoiseFilterd    = filter(PassFreqcoeff, 1,  Noise);
    NoiseExtra      = NoiseFilterd(SendSignalNum - SendSignalNum/2:SendSignalNum + SendSignalNum/2 - 1);
    ENoise          = NoiseExtra * NoiseExtra';                 % ��������������
    ESignal         = TempSignalInput * TempSignalInput';       % �����źŵ�����
    Noisenorl       = NoiseExtra / sqrt(ENoise);                % ������һ��
    Snr_ratio       = 10^( - Snr/20);
    Noisenor2       = Noisenorl * Snr_ratio * sqrt(ESignal);    % �õ����޵ĸ�˹������
    SignalAddNoise  = TempSignalInput + Noisenor2;
 
end