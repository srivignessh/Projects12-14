function [train_bags,train_target]=packbuild_port(l)
g_bag=cell(l,1);
b_bag=cell(l,1);
g_target=cell(l,1);
b_target=cell(l,1);
g_p=[80,23,34,45,67,78,53,56,24,46,12];
b_p=[27,57,32,62,95,17,32,54,29,51,30];
for i=1:2:l
    g_bag{i}=g_p(ceil(rand*10));  
    g_target{i}=1;
    g_bag{i+1}=b_p(ceil(rand*10));
    g_target{i+1}=-1;
    b_bag{i}=g_p(ceil(rand*10)); 
    b_target{i}=1;
    b_bag{i+1}=b_p(ceil(rand*10));
    b_target{i+1}=-1;
end
train_bags=[g_bag;b_bag];
train_target=[g_target;b_target];
end