function [t rout]=trace(a,b,mine)
x1=a(1);y1=a(2);
x2=b(1);y2=b(2);
len=dista(a,b);
x=abs(x1-x2);
y=abs(y1-y2);
if(x==6 && y==4)
   rout=[]; t=0;return;
end
numr=facto(len)/(facto(x)*facto(y));
rt=zeros(numr,2);
p=zeros(1,x);
   q=ones(1,y);
   r=[p q];
   z=perms(r);
   z=unique(z,'rows');
   t=[];
     if(x1==min(x1,x2) && y1==min(y1,y2) )
          k=1;l=1;
      elseif(x2==min(x1,x2) && y2==min(y1,y2) )
          k=-1;l=-1;   
      elseif(x1==min(x1,x2) && y2==min(y1,y2) )
          k=1;l=-1;   
      elseif(x2==min(x1,x2) && y1==min(y1,y2) )
          k=-1;l=1;
     end
      rout=[];
      x=x1;y=y1;
for i=1:numr
     x=x1;y=y1;
     
      if(t==1)
             break;
      end
        rout=[x1 y1];
          t=1;
          for j=1:len    
               if(~z(i,j))
                   x=x+k;
                    if(~compmine(x,y,mine))
                  t=0;rout=[];
                  break;
                    else
                       rout=[rout;x y];
                    end
               
               elseif (z(i,j))
                  
                   y=y+l;
                   if(~compmine(x,y,mine))
                      t=0;rout=[];
                      break;
                   else
                      rout=[rout;x y];
                   end 
                   end
            
          end
end
rout;
end