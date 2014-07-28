function [v] = drect(u)
[k num]=size(u);
v=[];
for i=1:num-1
    w=get_direction(u(i),u(i+1));
    v=[v w];
end

