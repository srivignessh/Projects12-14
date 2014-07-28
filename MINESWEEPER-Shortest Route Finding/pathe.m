function [ route,rte] = pathe(checks,mine)
route=[];
[no l]=size(checks);
z=1:no-2;
dif=perms(z);
dif=unique(dif,'rows');
[num no]=size(dif);
sho=[];
[pxist rte]=p_exist(checks,mine);
 for n=1:num
     temp=0;
     for i=1:no-1
            if(i==1)
               
                           if(~ent_r(dif(n,i)+1,1,pxist))
                               temp=200;break;end;
                temp=dista(checks(dif(n,i)+1,:),checks(1,:));
            end
                        if(~ent_r(dif(n,i)+1,dif(n,i+1)+1,pxist))
                                temp=200;break;end;
                        temp=temp+dista(checks(dif(n,i)+1,:),checks(dif(n,i+1)+1,:));
     end
   if(~ent_r(no+2,dif(n,i+1)+1,pxist))
                             temp=200; end;
    temp=temp+dista(checks(no+2,:),checks(dif(n,i+1)+1,:)); 
 sho=[sho;temp];
 end
 minlen=min(sho);
 t=1;
 for j=1:num
     if(sho(j)==minlen)
         route=dif(j,:)+1;
         t=t+1;
              end
 end
route=[1 route no+2];
end

