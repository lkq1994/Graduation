
%% ����һ��ʱ���ź�

fs = 100000;
t = 1/fs:1/fs:1000/fs;
SignalInput = cos(2 * pi * 10000 * t)';


%% ���ź���Ӵ��޸�˹������
Snr             = -10;
[SignalAddNoise,Noisenor2] = SignalAddPassBandNoise(SignalInput,Snr,8000,12000,100000);
%% �������֤
% ESignal         = SignalInput' * SignalInput;       % �ź�����
% ENoise2         = Noisenor2 * Noisenor2';           % ��������
% aa              = 10 * log10(ESignal/ENoise2);      % �������֤
%% �����������ź�
figure
plot(real(SignalAddNoise));
