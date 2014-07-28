function [ k ] = swap_point(k)
z(1)=k(1);z(2)=k(2);
k(1)=z(2);k(2)=z(1);
end

