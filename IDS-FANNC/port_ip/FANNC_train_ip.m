function [theta_ij,alpha_ij,v_jh,w_hl,b,c,bias_c,bias_b,l_b,alp]=FANNC_train_ip(train_bags,train_target)
[ni,~]=size(train_bags);
l_b=0.8;  % Leakage Threshold for Second Layer 
allow_err_d=0.11;  % Allowable error for d 
allow_err_c=0.11;  %Allowable error for c
b=1;
c=1;
bias_b=0.35;       % Bias for second Layer
bias_c=0.15;      % Bias for third Layer
alp=3;             % Radius of attractive basin
output=[];
for k=1:ni
          a=train_bags{k,1};  % Input Instance
          d_e=train_target{k,1};  % Output Instance
          [~,n_a]=size(a);  % n_a Size of a
          [~,n_b]=size(b); % n_b Size of b
          [~,n_c]=size(c);  %n_c Size of c
          [~,n_d]=size(d_e);  %n_d Size of d
           %% Intialization of Values
          if(k==1)
           BIn_ij=ones(n_a,n_b);  %First-Second Connection Layer     
           rb_ij=ones(n_a,n_b); 
           theta_ij=a';           % Distance Vector
           alpha_ij=alp*ones(n_a,n_b); % Radial Vector
           v_jh=1;   % Second - Third Layer Weights 
           w_hl=d_e;  % Third Layer Final Layer Weights 
          end
          %% Input Internal Layer Assignment
          %Product of distances of each dimension of vector is b 
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
             if(sC_h)
             [max_b,max_b_j]=max(b);
             rc_h=-(2*sC_h-bias_c);
             c(h)=1/(1+exp(rc_h));
             else
             c(h)=0;
             end
          end
          [max_ch,max_h]=max(c);  %Third Layer compettion
          for l=1:n_d
              d(l)=max_ch*w_hl(max_h,l);
          end
              output=[output;d];  
          %%   Error Correcn
          err_d=0;
          for l=1:n_d
               err_d=err_d+(d_e(l)-d(l))^2;
          end     
          err_d=(1/(n_d))*(err_d);
          if(err_d<allow_err_d)    % error_d_allowable
                j=max_b_j;
                 for i=1:n_a
                      theta=theta_ij(i,j);
                      alpha=alpha_ij(i,j);
                      if(a(i)<(theta-0.3*alpha))
                          theta_ij(i,j)=(theta+0.3*alpha+a(i)+0.8)/2;
                          alpha_ij(i,j)=(3*alpha-(10*(a(i)+0.8)-10*theta))/6;
                      elseif(a(i)>(theta+0.3*alpha))
                          theta_ij(i,j)=(theta-0.3*alpha+a(i)+0.8)/2;
                          alpha_ij(i,j)=(3*alpha+(10*(a(i)+0.8)-10*theta))/6;
                      end
                 end
          else
              %% error_d_not-allowable
              err_c=[];
              for h=1:n_c
                  err_ch=(1/n_d)*sum((w_hl(h,:)-d_e)^2);
                  err_c=[err_c err_ch];
              end
              [err_c_min,c_min_h]=min(err_c);
              if(err_c_min<allow_err_c)  
                  %% error c allowable  Append one second unit
                      b=[b 1];
                      n_b=n_b+1;
                      theta_ij=[theta_ij,a'];
                      alpha_ij=[alpha_ij,alp*ones(length(a),1)];
                      v_jh(n_b,c_min_h)=1;
                  
              else
                  %% Append two units
                  b=[b 1];
                  c=[c 1];
                      n_b=n_b+1;
                      n_c=n_c+1;
                      theta_ij=[theta_ij,a'];
                      alpha_ij=[alpha_ij,alp*ones(length(a),1)];
                      v_jh(n_b,n_c)=1;
                      w_hl=[w_hl;d_e];
                      
              end 
          end       
end
end