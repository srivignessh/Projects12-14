function [eff,ka,eff0,ka0]= efficiency(test_bags,test_target,output)
[ni,~]=size(test_target);
t=0;
f=0;
t0=0;
f0=0;
ka=[];
ka0=[];
for k=1:ni
    if(output(k)>0.7 && test_target{k,1}>0)
        t=t+1;
    elseif(output(k)<-0.7 && test_target{k,1}<0)
        t=t+1;
    else 
        f=f+1;
        ka=[ka;k,test_bags{k,1},output(k)];
    end
    if(output(k)>0 && test_target{k,1}>0)
        t0=t0+1;
    elseif(output(k)<0 && test_target{k,1}<0)
        t0=t0+1;
    else 
        f0=f0+1;
        ka0=[ka0;k,test_bags{k,1},output(k)];
    end
end
eff=t/(t+f);
eff0=t0/(t0+f0);
end