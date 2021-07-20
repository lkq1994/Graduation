
function decode = dspreadenery(signal,fs,f0,N,PN,sourcelength)

% for i=1:length(PN)
%     if(PN(i) == 0)
%         PN(i) = -1;
%     end
% end

PN(PN==0)=-1;

filter_n=1024;
b=fir1(filter_n,2*f0/fs);
% d=fir1(filter_n,2*[fl fh]/fs);

t = 0:1/fs:(length(signal)-1)/fs;
uejw = sin(2*pi*f0*t);
sig_no = signal.*uejw;
% figure;plot(real(code_no))
% title('与载波相乘后信号的实部波形')
sig_lowpass=filter(b,1,[sig_no zeros(1,filter_n/2)]);
sig_nc=sig_lowpass(filter_n/2+1:end); 

code_filter = reshape(sig_nc,N,[]);
en_code_resample = sum(code_filter);

% code_filter = filter(p,1,[code_no zeros(1,fix(length(p)/2))]);
% code_filter = code_filter(fix(length(p)/2)+1:end);
% figure;plot(code_filter)
% en_code_resample = resample(code_filter,fs/N,fs);

decode = zeros(1,sourcelength);
PN1 = [PN,PN];PN2 = [PN,-PN];
n = 5;%能量检测器偏移
for i=1:sourcelength
    corrsum1 = 0;corrsum2 = 0;
    code_corr(1:length(PN)*2) = en_code_resample((i-1)*length(PN)+1:(i+1)*length(PN));
    corr1 = corr_fun(code_corr,PN1);
    corr2 = corr_fun(code_corr,PN2);
% 
%     figure;plot(corr1)
%     figure;plot(corr2)

    for ii=length(PN)+n:length(PN)*3-n
        corrsum1 = corr1(ii)^2 + corrsum1;
        corrsum2 = corr2(ii)^2 + corrsum2;
       
    end
    
    if(corrsum1>corrsum2)
        decode(i) = 1;
    else
        decode(i) = 0;
    end
end