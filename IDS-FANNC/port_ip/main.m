function[eff]=finals(ip_output,pt_output)
v=length(ip_output);
tt=0;
tf=0;
ft=0;
ff=0;
for i=1:v
if(ip_output(i) > 0.7 && pt_output(i) > 0.7)
    tt=tt+1; %Fully good IP, Port
elseif(ip_output(i) > 0.7 && pt_output(i) < 0.7)
    tf=tf+1; % Good IP Bad Port
elseif(ip_output(i) < 0.7 && pt_output(i) > 0.7)
    ft=ft+1; % Good Port Bad IP
elseif(ip_output(i) < 0.7 && pt_output(i) < 0.7)
    ff=ff+1; % Bad Port Bad IP
end
eff=[tt,tf,ft,ff];
end