function [ t ] = compmine(a,b,mine)
    t=1;
    [n i]=size(mine);
 for i=1:n   
if(mine(i,1)==a && mine(i,2)==b)
    t=0;return;
end
 end
end

