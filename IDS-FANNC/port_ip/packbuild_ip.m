function [train_bags,train_target]=packbuild_ip(l)
g_bag=cell(l,1);
b_bag=cell(l,1);
g_target=cell(l,1);
b_target=cell(l,1);
for i=1:2:l
    g_bag{i}=[192,168,45,2*i];  % Good IP addresses are 192.168.45.2,192.168.45.3,192.168.45.6,192.168.45.7,192.168.45.10,192.168.45.11..
    g_target{i}=1;
    g_bag{i+1}=[192,168,45,2*i+1];
    g_target{i+1}=1;
    b_bag{i}=[192,168,45,2*(i+1)]; % Bad IP addresses are 192.168.45.4,192.168.45.5,192.168.45.8,192.168.45.9,192.168.45.12,192.168.45.13...
    b_target{i}=-1;
    b_bag{i+1}=[192,168,45,2*(i+1)+1];
    b_target{i+1}=-1;
end
train_bags=[g_bag;b_bag];
train_target=[g_target;b_target];
end