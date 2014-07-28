function [eff,ip_train_bags,ip_train_target,pt_train_bags,pt_train_target,ip_theta_ij,ip_alpha_ij,ip_v_jh,ip_w_hl,ip_b,ip_c,ip_bias_c,ip_bias_b,ip_l_b,ip_alp,pt_theta_ij,pt_alpha_ij,pt_v_jh,pt_w_hl,pt_b,pt_c,pt_bias_c,pt_bias_b,pt_l_b,pt_alp,ip_error_set,ip_output,pt_error_set,pt_output,ip_eff,ip_ka,pt_eff,pt_ka]=learn()
clear
[ip_train_bags,ip_train_target]=packbuild_ip(127); 
[pt_train_bags,pt_train_target]=packbuild_port(127);
[ip_theta_ij,ip_alpha_ij,ip_v_jh,ip_w_hl,ip_b,ip_c,ip_bias_c,ip_bias_b,ip_l_b,ip_alp]=FANNC_train_ip (ip_train_bags,ip_train_target); % Train with 256 known ips
[pt_theta_ij,pt_alpha_ij,pt_v_jh,pt_w_hl,pt_b,pt_c,pt_bias_c,pt_bias_b,pt_l_b,pt_alp]=FANNC_train_port(pt_train_bags,pt_train_target);
ip_test_bags=ip_train_bags;
ip_test_target=ip_train_target;
pt_test_bags=pt_train_bags;
pt_test_target=pt_train_target;
[ip_error_set,ip_output]=FANNC_test(ip_test_bags,ip_test_target,ip_theta_ij,ip_alpha_ij,ip_v_jh,ip_w_hl,ip_b,ip_c,ip_bias_c,ip_bias_b,ip_l_b,ip_alp); %testing with 127 known + 127 unknown 
[pt_error_set,pt_output]=FANNC_test(pt_test_bags,pt_test_target,pt_theta_ij,pt_alpha_ij,pt_v_jh,pt_w_hl,pt_b,pt_c,pt_bias_c,pt_bias_b,pt_l_b,pt_alp); %testing with 127 known + 127 unknown 
%%error analsis of error set
[ip_eff,ip_ka]= efficiency(ip_test_bags,ip_test_target,ip_output);
[pt_eff,pt_ka]= efficiency(pt_test_bags,pt_test_target,pt_output);
[eff]=finals(ip_output,pt_output);
end