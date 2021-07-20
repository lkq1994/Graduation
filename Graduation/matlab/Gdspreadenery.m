
function decode = Gdspreadenery(signal,fs,f0,N,PN,sourcelength)


PN(PN==0)=-1;

t = 0:1/fs:(length(signal)-1)/fs;
uejw = sin(2*pi*f0*t);
code_no = signal.*uejw;
% figure;plot(real(code_no))
% title('与载波相乘后信号的实部波形')
code_filter = reshape(code_no,N,[]);
en_code_resample = sum(code_filter);

% code_filter = filter(p,1,[code_no zeros(1,fix(length(p)/2))]);
% code_filter = code_filter(fix(length(p)/2)+1:end);
% figure;plot(code_filter)
% en_code_resample = resample(code_filter,fs/N,fs);

decode = zeros(1,sourcelength);
PN1 = [PN((length(PN)+1)/2:end),PN(1:(length(PN)+1)/2-1)];PN2 = [PN((length(PN)+1)/2:end),-PN(1:(length(PN)+1)/2-1)];
n = 5;%能量检测器偏移
for i=1:sourcelength
    corrsum1 = 0;corrsum2 = 0;
%     code_corr(1:length(PN)*2) = en_code_resample((i-1)*length(PN)+1:(i+1)*length(PN));
    code_corr(1:length(PN)) = en_code_resample((i-1)*length(PN)+(length(PN)+1)/2:i*length(PN)+(length(PN)-1)/2);
    corr1 = corr_fun(code_corr,PN1);
    corr2 = corr_fun(code_corr,PN2);
% 
%     figure;plot(corr1)
%     figure;plot(corr2)

    
        corrsum1 = max(abs(corr1));
        corrsum2 = max(abs(corr2));
       

    decode(corrsum1>corrsum2)=1;
%     if(corrsum1>corrsum2)
%         decode(i) = 1;
%     else
%         decode(i) = 0;
%     end
end