function [checks mine pt]= points(x,y,x0,y0)
    a=imread('arena.jpg');
pt=zeros(5,7);
[I,J,K]=size(a);
bmine=zeros(I,J);
for mi=1:I
    for mj=1:J
        if(a(mi,mj,1)>100 && a(mi,mj,2)<70 && a(mi,mj,3)<70)
            bmine(mi,mj)=1;
           
        end
    end
end
%figure,imshow(bmine);
mine=[];
[mine pt] = checks_detect(bmine,-20,x,y,x0,y0,mine,pt);
checks=[0 0];        
bgreen=zeros(I,J);
for gi=1:I
    for gj=1:J
        if(a(gi,gj,1)<70 && a(gi,gj,2)>100 && a(gi,gj,3)<70)
            bgreen(gi,gj)=1;
        end
    end
end
%%figure,imshow(bgreen);
[checks pt] = checks_detect(bgreen,5,x,y,x0,y0,checks,pt);
bblue=zeros(I,J);
for bi=1:I
    for bj=1:J
        if(a(bi,bj,1)<70 && a(bi,bj,2)<150&& a(bi,bj,3)>100)
            bblue(bi,bj)=1;
        end
    end
end
%figure,imshow(bblue);
[checks pt] = checks_detect(bblue,10,x,y,x0,y0,checks,pt);
byellow=zeros(I,J);
for yi=1:I
    for yj=1:J
        if(a(yi,yj,1)>100 && a(yi,yj,2)>100 && a(yi,yj,3)<70)
            byellow(yi,yj)=1;
        end
    end
end
%figure,imshow(byellow);
[checks pt] = checks_detect(byellow,15,x,y,x0,y0,checks,pt);
checks=[checks;[6,4]];
checks=unique(checks,'rows');
mine=unique(mine,'rows');
pause();
clc
close all



