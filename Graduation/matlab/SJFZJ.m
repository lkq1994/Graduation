clc;clear all;close all;
fs=48e3;
fc=6e3;

%多途信道
CJ1=impseq(1,1,0.02*fs);
CJ2=impseq(0.02*fs/10,1,0.02*fs);
CJ3=impseq(0.02*fs/15,1,0.02*fs);
ht=CJ1+0.2*CJ2+0.7*CJ3;
ht = ht.*1e-3;
figure(15)
plot(ht);
fs1=12e3;fl=14e3;fh=18e3;
B=fh-fl;T=0.2;k=B/T;
t1=0:1/fs1:T-1/fs1;
pt=cos(2*pi*fl*t1+pi*k*t1.^2);%探测信号
prt=conv(ht,pt)+wgn(1,(length(ht)+length(pt)-1),5);%接收探测
%将prt反转
% %prtf=prt(:,end:-1:1);
 prtf=fliplr(prt);%两种反转方法
 %信道估计
 htf=conv(prtf,pt);
 figure(17)
plot(htf); 
for i=1:length(htf)
    if htf(i)>1200*0.2
        htf(i)=htf(i);
    else htf(i)=0;
    end
end
        
figure(16)
plot(htf);


Num=100;
x=sign(rand(1,Num)-0.5);
figure(1)
plot(x)
title('初始信号');
%产生m序列
initial=[1 0 0 1 1 0 0 1 1];
feedback=1021;
[m]=m_sequence(initial);
a=sign(m-0.5);
N=511;
d=kron(x,a);
figure(2)
plot(d)
title('扩展序列')
%升采样
N_pn=12;
d_s=rectpulse(d,N_pn);
figure(3)
plot(d_s);
%调制
fs=48e3;
fc=6e3;
t=0:1/fs:length(d_s)/fs-1/fs;
c=2*cos(2*pi*fc*t);
signal=d_s.*c;
p_f(signal,fs);
figure(5)
plot(signal);
x0=zeros(1,48e2);

% initial=[1 1 1 0 0 1 0 1 0];
% feedback=1021;
% [m]=m_seq(initial,feedback);
% L=sign(m-0.5);
fs1=48e2;fl=4e2;fh=6e2;
B=fh-fl;T=0.8;k=B/T;
t1=0:1/fs1:T-1/fs1;
L=fliplr(cos(2*pi*fl*t1+pi*k*t1.^2));
sign=[L x0 signal];
figure(7)
plot(sign);
sig=conv(ht,sign)+wgn(1,(length(ht)+length(sign)-1),5);%经多途信道
signal_sf=conv(sig,htf);%时反处理
figure(8)
plot(signal_sf);
%同步
st2=corr_fun(signal_sf,L);
[s1,s2]=max(st2);
figure(9)
plot(st2);
ST=signal_sf(s2+length(x0)+1:s2+length(x0)+Num*N*N_pn);
figure(10)
plot(ST);
%解调
B=0.5;
t=0:1/fs:length(ST)/fs-1/fs;
c_a=B*cos(2*pi*fc*t);
signal_h= ST.*c_a;
figure(11)
plot( signal_h);
%低通滤波
filter_n=512;
b1=fir1(filter_n,2*6000/fs);
y=filter(b1,1,[signal_h zeros(1,fix(length(b1)/2))]);
y=y(fix(length(b1)/2)+1:end);
figure(12)
plot(y);
%降采样
y_j=reshape(y,N_pn,[]);
y_j=sum(y_j);
figure(13)
plot(y_j);
%解扩
jk=corr_fun(y_j,a);
figure(14)
plot(jk);
%解码
for i=1:Num
    sig_re=jk(1+(i-1)*N:i*N+1);
    [x1,y1]=max(abs(sig_re));
    if jk(y1+(i-1)*N)>0
         out(i)=1;
       else
        out(i)=-1;
    end
end
    %out(i)=sign(jk(y1+(i-1)*N));
   
% for i=1:51610
%     if jk(i)>=0.05
%         jk(i)=1;
%     end
%     if jk(i)<=(-0.049)
%         jk(i)=(-1);
%     end
%     if abs(jk(i))~=1
%         jk(i)=0;
%     end
%     

find(out~=x)
