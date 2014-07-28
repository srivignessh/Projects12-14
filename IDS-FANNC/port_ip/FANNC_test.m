function [error_set,output,train_nbag,train_ntarget]=FANNC_test(test_bags,test_target,theta_ij,alpha_ij,v_jh,w_hl,b,c,bias_c,bias_b,l_b,alp)
[ni,~]=size(test_bags);
output=[];
error_set=[];
train_nbag=cell(1,1);
train_ntarget=cell(1,1);
for k=1:ni
          a=test_bags{k,1};
          [~,n_a]=size(a);
          [~,n_b]=size(b);
          [~,n_c]=size(c);
          %% Input Internal Layer Assignment
          for j=1:n_b
               PBIn_j=1;
               for i=1:n_a
                 rb_ij(i,j)=((a(i)-theta_ij(i,j))/(alpha_ij(i,j)))^2;
                 BIn_ij(i,j)=exp(-rb_ij(i,j));
                 PBIn_j=PBIn_j*BIn_ij(i,j);
               end
               rb_j=-(2*PBIn_j-bias_b);
               b(j)=1/(1+exp(rb_j));
          end
          %% Output External Layer Assignment 
          for  h=1:n_c  
             sC_h=0;
             for j=1:n_b
               if(b(j)>l_b)
                   sC_h=sC_h+b(j)*v_jh(j,h);  %Leakage Competiton
               end 
             end
             [~,max_b_j]=max(b);
             rc_h=-(2*sC_h-bias_c);
             c(h)=1/(1+exp(rc_h)); 
          end
          [min_ch,min_h]=min(c);
          [max_ch,max_h]=max(c);
          if((max_ch-min_ch)>0.3)
              s=1;
          end
          d=max_ch*w_hl(max_h,1);
          if(abs(d)<0.5) % No Mapping Exist
             error_set=[error_set;a];    
          end
          output=[output;d];       
              
end

end