function [Signalx , carrier] = Signal_Carrier(sourcecode , PN , fs , fh , fl)

sourcelength = length(sourcecode);
for i=1:length(PN)
    if(PN(i) == 0)
        PN(i) = -1;
    end
end

for i=1:length(sourcecode)
    if(sourcecode(i) == 0)
        sourcecode(i) = -1;
    end
end

d = zeros(1,sourcelength+1);
d(1) = 1;
for i=2:length(d)
    d(i) = sourcecode(i-1)*d(i-1);%²î·Ö±àÂë
end

for i=1:length(d)
    for ii=1:length(PN)
        d_PN((i-1)*length(PN)+ii) = d(i)*PN(ii);
    end
end

f0 = (fl+fh)/2;
N = fs/(fh-fl)*2;
n = N/(fs/f0);
totallength = N*length(d)*length(PN);
t = 0:1/fs:(totallength-1)/fs;
carrier = sin(2*pi*f0*t);

alpha = 1.0;
p = rcosfir(alpha,[ ],N,1,'sqrt');
for i=1:length(d_PN)
    for ii=1:N
        d_N((i-1)*N+ii) = d_PN(i);
    end  
end

tx = [d_N zeros(1,fix(length(p)/2))];
txSig = filter(p,1,tx);
txSig = txSig(fix(length(p)/2)+1:end);
txSig = txSig./max(txSig);

%µ÷ÖÆ
Signalx = txSig.*carrier;



