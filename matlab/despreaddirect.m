function decode=despreaddirect(signal,fs,f0,N,PN,sourcelength)

for i=1:length(PN)
    if(PN(i) == 0)
        PN(i) = -1;
    end
end

filter_n=1024;
b=fir1(filter_n,2*f0/fs);
% d=fir1(filter_n,2*[fl fh]/fs);

t = 0:1/fs:(length(signal)-1)/fs;
uejw = sin(2*pi*f0*t);
sig_no = signal.*uejw;
% figure;plot(real(code_no))
% title('���ز���˺��źŵ�ʵ������')
sig_lowpass=filter(b,1,[sig_no zeros(1,filter_n/2)]);
sig_nc=sig_lowpass(filter_n/2+1:end); 

code_filter = reshape(sig_nc,N,[]);
en_code_resample = sum(code_filter);
% code_filter = filter(p,1,[code_no zeros(1,fix(length(p)/2))]);
% code_filter = code_filter(fix(length(p)/2)+1:end);
% figure;plot(code_filter)
% en_code_resample = resample(code_filter,fs/N,fs);

aaaa = corr_fun(en_code_resample,PN);
aaaa = aaaa(1.4e5:1.8e5);
t = 1/fs:1/fs:length(aaaa)/fs;
figure;plot(t.*127,aaaa);title('ֱ��ϵͳ��ط�');xlabel('ʱ�� (s)');ylabel('����');

decode = zeros(1,sourcelength);
PN1 = [PN,PN];PN2 = [PN,-PN];
n = 5;%���������ƫ��
for i=1:sourcelength+1
    sigdata = en_code_resample((i-1)*length(PN)+1:i*length(PN));
    corrdata = corr_fun(sigdata,PN);
    [~,pos] = max(abs(corrdata));
    if(corrdata(pos)>0)
        decode(i) = 1;
    else
        decode(i) = 0;
    end
end