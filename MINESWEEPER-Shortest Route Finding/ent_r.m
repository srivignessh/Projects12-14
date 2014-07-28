function [ t ] = ent_r(a,b,pxist )
[n k]=size(pxist);
for i=1:n
    if(((pxist(i,1)==a) && (pxist(i,2)==b))||((pxist(i,1)==b) && (pxist(i,2)==a)))
        t=pxist(i,3);return;
    end
end
end
