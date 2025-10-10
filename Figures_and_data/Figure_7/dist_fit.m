clear variables; close all; clc;

T = 50000;
y_max=0.15;
infile = sprintf('neigh_list_%.2f_opt.csv', T);
part_opt = readmatrix(fullfile('neigh_listing/opt',infile)); % Optimised case
infile = sprintf('neigh_list_%.2f_non_opt.csv', T);
part_nonOpt = readmatrix(fullfile('neigh_listing/non_opt', infile)); % Non-optimised case
N_cases = 50;
dat_opt = []; dat_nonOpt = [];
for i = 1:N_cases
    dat_opt = [dat_opt; part_opt(:,2*i-1:2*i)];
    dat_nonOpt = [dat_nonOpt; part_nonOpt(:,2*i-1:2*i)];
end

dat_opt(:,3) = dat_opt(:,1)+dat_opt(:,2);
dat_nonOpt(:,3) = dat_nonOpt(:,1)+dat_nonOpt(:,2);

dat_opt(:,4) = dat_opt(:,2)./dat_opt(:,3);
dat_nonOpt(:,4) = dat_nonOpt(:,2)./dat_nonOpt(:,3);

pd_opt = fitdist(dat_opt(:,4), 'normal')
pd_nonOpt = fitdist(dat_nonOpt(:,4), 'normal')

skewness(dat_opt(:,4))
skewness(dat_nonOpt(:,4))

kurtosis(dat_opt(:,4))-3
kurtosis(dat_nonOpt(:,4))-3

x_val = (0:0.01:1)';

n_bins = 25;
figure(1)
box on; hold on;
histogram(dat_opt(:,4),n_bins,'Normalization','pdf')
plot(x_val, pdf(pd_opt,x_val), 'r-');
xlabel('n_o/n')
ylabel('p(n_o/n)'); %ylim([0, y_max]);
tle = sprintf('T = %d, optimised', T);
title(tle)

figure(2)
box on; hold on;
histogram(dat_nonOpt(:,4),n_bins,'Normalization','pdf')
plot(x_val, pdf(pd_nonOpt,x_val), 'r-');
xlabel('n_o/n')
ylabel('p(n_o/n)'); %ylim([0 y_max]);
tle = sprintf('T = %d, non-optimised', T);
title(tle)