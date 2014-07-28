function [x y x0 y0]=cor_detect()
close all
clear all

a=imread('arena.jpg');
subplot(121);
imshow(a);
title('Arena');
try
    a=rgb2gray(a);
end
%figure,imshow(a);
b=im2bw(a,0.2);
se=strel('disk',5);
c=imopen(b,se);
d = bwareaopen(c,30);
d=imrotate(d,180);
pause();
subplot(122),imshow(d);
imwrite(d,'bin.jpg');
title('Proccessed Arena To Get Corners');
%figure;
%d=imclose(d,se);
%imshow(d);
%figure;
%e=imfill(g,'holes');
%imshow(e);
%figure;
%f = imclearborder(e);
%imshow(f);
h=corner(d);
[l cor1]=min(h(:,1)+h(:,2));
[m cor2]=max(h(:,1)+h(:,2));
[I,J]=size(h);
x0=h(cor1,1);
y0=h(cor1,2);
x=h(cor2,1)-x0;
y=h(cor2,2)-y0;
end