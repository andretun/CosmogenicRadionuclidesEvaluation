% Results from radioprotection spectrum
% clear all
close all

x_lim = 800; % cm

% Meteorite properties
meteoriteRadius = 241*100; % cm
meteoriteDensity = 1.194; % g/cm3

% Physics lists data
Shield = importdata('Al26_Shielding_M660.txt');
Shield_alpha = importdata('Al26_Shielding_M660_alpha.txt');

Shield_RadionuclidesNumber = Shield(:,2)';
sigma_Shield_RadionuclidesNumber = sqrt(Shield_RadionuclidesNumber);
Shield_RadionuclidesNumber_alpha = Shield_alpha(:,2)';
sigma_Shield_RadionuclidesNumber_alpha = sqrt(Shield_RadionuclidesNumber_alpha);

step = 2; % cm
depth = 1:step:800; % cm

% Number of Al26 created per second in the sample
upRadius = meteoriteRadius
lowRadius = meteoriteRadius - 50;
a = upRadius*upRadius*upRadius;
b = lowRadius*lowRadius*lowRadius;
mass = 4/3 * pi * (a-b) * meteoriteDensity; % g
sum(Shield_RadionuclidesNumber(1:25))*600000*250/mass

% figure(1)
% errorbar(depth, Shield_RadionuclidesNumber, sigma_Shield_RadionuclidesNumber, 's', 'Color', 'r', ...
%         'LineWidth', 1.2, 'MarkerSize', 10, 'MarkerFaceColor', 'r')
% set(gca, 'LineWidth', 2, 'XMinorTick', 'on', 'YMinorTick', 'on', 'FontSize', 20, 'FontWeight', 'bold')
% xlabel('Depth [cm]', 'FontSize', 15)
% ylabel('Number of nuclides', 'FontSize', 15)
% set(gca, 'YLim', [0 7000], 'XLim', [0 max(depth)])
% grid on
% grid minor
% legend({'Shielding', 'QGSP BIC', 'QGSP BERT', 'FTFP BERT', 'QBBC', 'FTFP INCLXX'}, 'Location', 'northeast', ...
%         'Orientation', 'vertical', 'FontSize', 15)
% title('Proton induced Al26 - flux X 100')

% figure(2)
% errorbar(depth, Shield_RadionuclidesNumber_alpha, sigma_Shield_RadionuclidesNumber_alpha, 's', 'Color', 'r', ...
%             'LineWidth', 1.2, 'MarkerSize', 10, 'MarkerFaceColor', 'r')
% set(gca, 'LineWidth', 2, 'XMinorTick', 'on', 'YMinorTick', 'on', 'FontSize', 20, 'FontWeight', 'bold')
% xlabel('Depth [cm]', 'FontSize', 15)
% ylabel('Number of nuclides', 'FontSize', 15)
% set(gca, 'YLim', [0 7000], 'XLim', [0 max(depth)])
% grid on
% grid minor
% legend({'Shielding', 'QGSP BIC', 'QGSP BERT', 'FTFP BERT', 'QBBC', 'FTFP INCLXX'}, 'Location', 'northeast', ...
%         'Orientation', 'vertical', 'FontSize', 15)
% title('Alpha induced Al26 - flux X 1000')


% Mass values at each depth
masses = zeros(1, length(Shield_RadionuclidesNumber)); % g

index = 1;
while index <= length(Shield_RadionuclidesNumber)
    upRadius = meteoriteRadius - step*(index-1);
    lowRadius = meteoriteRadius - step*index;
    a = upRadius*upRadius*upRadius;
    b = lowRadius*lowRadius*lowRadius;
    masses(index) = 4/3 * pi * (a-b) * meteoriteDensity; % g
    index = index + 1;
end
masses = masses/1000; % kg


% Activities
Shield_activity = (Shield_RadionuclidesNumber./masses)*600000;
sigma_Shield_activity = (sigma_Shield_RadionuclidesNumber./masses)*600000;
Shield_activity_alpha = Shield_RadionuclidesNumber_alpha./masses*60000;
sigma_Shield_activity_alpha = sigma_Shield_RadionuclidesNumber_alpha./masses*60000;

% % % Activity from Excel file
% meteor_activity = [46.4, 49.9, 52.4, 54.4, 56.1, 57.7, 58.9, 60.3, 61.2, 62.0, 62.9, 63.4, 64.2, 64.7, 65.2, 65.7, ...
%                     66.1, 67.0, 66.8, 66.8, 67.0, 68.1, 67.9, 69.1, 68.5, 68.5, 68.5, 68.5, 68.5, 68.5]; % dpm/kg
% meteor_depth = 0.5:1:30; % cm
% length(meteor_depth)
% length(meteor_activity)

% figure(3)
% hold on
% % fplot(funGCRProdRate, 'b', 'LineWidth', 3)
% % errorbar(depth, Shield_activity, sigma_Shield_activity, 's', 'Color', 'red', 'LineWidth', 1.2, ...
% %             'MarkerSize', 10, 'MarkerFaceColor', 'red')
% stairs(depth, Shield_activity, 'Color', 'red', 'LineWidth', 3)
% hold off
% set(gca, 'LineWidth', 2, 'XMinorTick', 'on', 'YMinorTick', 'on', 'FontSize', 20, 'FontWeight', 'bold')
% xlabel('d [cm]', 'FontSize', 20)
% ylabel('A [dpm/kg]', 'FontSize', 20)
% % set(gca, 'YLim', [0 40], 'XLim', [0 48])
% % grid on
% % grid minor
% % legend({'Physical model', 'Geant4 model'}, 'Location', 'northwest', 'Orientation', 'vertical', 'FontSize', 25)
% title('^{26}Al activity - protons', 'FontSize', 20)

% figure(4)
% hold on
% % errorbar(depth, Shield_activity_alpha, sigma_Shield_activity_alpha, 's', 'Color', 'r', 'LineWidth', 1.2, ...
% %             'MarkerSize', 10, 'MarkerFaceColor', 'r')
% stairs(depth, Shield_activity_alpha, 'Color', 'blue', 'LineWidth', 3)
% hold off
% set(gca, 'LineWidth', 2, 'XMinorTick', 'on', 'YMinorTick', 'on', 'FontSize', 20, 'FontWeight', 'bold')
% xlabel('d [cm]', 'FontSize', 20)
% ylabel('A [dpm/kg]', 'FontSize', 20)
% % set(gca, 'YLim', [0 15], 'XLim', [0 max(depth)+5])
% grid on
% grid minor
% % legend({'Shielding', 'QGSP BIC', 'QGSP BERT', 'FTFP BERT', 'QBBC', 'FTPT INCLXX'}, 'Location', 'northeast', ...
% %       'Orientation', 'vertical', 'FontSize', 15)
% title('^{26}Al activity - alphas', 'FontSize', 20)

% figure(44)
% hold on
% stairs(depth, Shield_activity, 'Color', 'red', 'LineWidth', 3)
% stairs(depth, Shield_activity_alpha, 'Color', 'blue', 'LineWidth', 3)
% hold off
% set(gca, 'LineWidth', 2, 'XMinorTick', 'on', 'YMinorTick', 'on', 'FontSize', 20, 'FontWeight', 'bold')
% xlabel('d [cm]', 'FontSize', 20)
% ylabel('A [dpm/kg]', 'FontSize', 20)
% % set(gca, 'YLim', [0 15], 'XLim', [0 max(depth)])
% grid on
% % grid minor
% legend({'proton', 'alpha'}, 'Location', 'northeast', 'Orientation', 'vertical', 'FontSize', 20)
% title('^{26}Al activity', 'FontSize', 20)


% Total activity
Shield_activity_tot = Shield_activity + Shield_activity_alpha;
sigma_Shield_activity_tot = sqrt(sigma_Shield_activity.^2 + sigma_Shield_activity_alpha.^2);


% figure(5)
% hold on
% % errorbar(depth, Shield_activity_tot , sigma_Shield_activity_tot, 's', 'Color', 'r', 'LineWidth', 1.2, ...
% %         'MarkerSize', 10, 'MarkerFaceColor', 'r')
% stairs(depth, Shield_activity_tot, 'Color', 'blue', 'LineWidth', 3)
% hold off
% set(gca, 'LineWidth', 2, 'XMinorTick', 'on', 'YMinorTick', 'on', 'FontSize', 20, 'FontWeight', 'bold')
% xlabel('d [cm]', 'FontSize', 20)
% ylabel('A [dpm/kg]', 'FontSize', 20)
% % set(gca, 'YLim', [0 170], 'XLim', [0 max(depth)+5])
% % grid on
% % grid minor
% % legend({'Shielding', 'QGSP BIC', 'QGSP BERT', 'FTFP BERT', 'QBBC', 'FTPT INCLXX'}, 'Location', 'northeast', ...
% %       'Orientation', 'vertical', 'FontSize', 15)
% title('^{26}Al activity - protons + alphas', 'FontSize', 20)

% depth = depth - step/2;
figure(6)
hold on
stairs(depth, Shield_activity, 'Color', 'red', 'LineWidth', 3)
stairs(depth, Shield_activity_alpha, 'Color', 'blue', 'LineWidth', 3)
stairs(depth, Shield_activity_tot, 'Color', 'black', 'LineWidth', 3)
% stairs(depth, Shield_activity*1.55, 'Color', 'green', 'LineWidth', 3)
hold off
set(gca, 'LineWidth', 2, 'XMinorTick', 'on', 'YMinorTick', 'on', 'FontSize', 20, 'FontWeight', 'bold', 'YScale', 'log')
xlabel('depth [cm]', 'FontSize', 20)
ylabel('Activity [dpm/kg]', 'FontSize', 20)
% set(gca, 'XLim', [0 50])
set(gca, 'XLim', [0 x_lim])
% grid on
% grid minor
legend({'proton', 'alpha', 'tot'}, 'Location', 'northeast', 'Orientation', 'vertical', 'FontSize', 20)
title('a) ^{26}Al', 'FontSize', 20)

% figure(7)
% hold on
% shadedErrorBar(depth, Shield_activity, sigma_Shield_activity, 'lineProps', 'red', 'transparent', true, ...
%                 'patchSaturation', 0.08);
% shadedErrorBar(depth, Shield_activity_alpha, sigma_Shield_activity_alpha, 'lineProps', 'blue', 'transparent', ...
%                 true, 'patchSaturation', 0.08);
% shadedErrorBar(depth, Shield_activity_tot, sigma_Shield_activity_tot, 'lineProps', 'black', 'transparent', true, ...
%                 'patchSaturation', 0.08);
% hold off
% set(gca, 'LineWidth', 2, 'XMinorTick', 'on', 'YMinorTick', 'on', 'FontSize', 20, 'FontWeight', 'bold')
% % set(gca, 'YScale', 'log')
% xlabel('d [cm]', 'FontSize', 20)
% ylabel('A [dpm/kg]', 'FontSize', 20)
% set(gca, 'XLim', [0 50])
% % set(gca, 'XLim', [0 x_lim])
% % grid on
% % grid minor
% legend({'proton', 'alpha', 'tot'}, 'Location', 'northeast', 'Orientation', 'vertical', 'FontSize', 20)
% % title('^{26}Al activity - protons + alphas', 'FontSize', 20)

% depth = depth-step/2;
% figure(8)
% hold on
% stairs(depth, Shield_activity_tot, 'Color', 'black', 'LineWidth', 3)
% stairs(depth, Shield_activity*1.55, 'Color', 'blue', 'LineWidth', 3)
% fplot(funGCRProdRate, 'red', 'LineWidth', 3)
% hold off
% set(gca, 'LineWidth', 2, 'XMinorTick', 'on', 'YMinorTick', 'on', 'FontSize', 20, 'FontWeight', 'bold')
% % set(gca, 'YScale', 'log')
% xlabel('depth [cm]', 'FontSize', 20)
% ylabel('Activity [dpm/kg]', 'FontSize', 20)
% set(gca, 'XLim', [0 50], 'YLim', [0 40])
% % grid on
% % grid minor
% legend({'Geant4 p+\alpha', 'Geant4 p*1.55', 'Physical model'}, 'Location', 'northeast', 'Orientation', 'vertical', 'FontSize', 20)
% % title('^{26}Al activity - protons + alphas', 'FontSize', 20)

% figure(9)
% hold on
% errorbar(depth, Shield_activity_tot, sigma_Shield_activity_tot, 's', 'Color', 'black', 'LineWidth', 1.2, ...
%         'MarkerSize', 10, 'MarkerFaceColor', 'black')
% errorbar(depth, Shield_activity*1.55, sigma_Shield_activity*1.55, 's', 'Color', 'blue', 'LineWidth', 1.2, ...
%         'MarkerSize', 10, 'MarkerFaceColor', 'blue')
% fplot(funGCRProdRate, 'red', 'LineWidth', 3)
% hold off
% set(gca, 'LineWidth', 2, 'XMinorTick', 'on', 'YMinorTick', 'on', 'FontSize', 25, 'FontWeight', 'bold')
% % set(gca, 'YScale', 'log')
% xlabel('depth [cm]', 'FontSize', 25)
% ylabel('Activity [dpm/kg]', 'FontSize', 25)
% set(gca, 'XLim', [0 50], 'YLim', [0 40])
% % grid on
% % grid minor
% legend({'Geant4 p+\alpha', 'Geant4 p*1.55', 'Physical model'}, 'Location', 'northeast', ...
%         'Orientation', 'vertical', 'FontSize', 25)
% % title('^{26}Al activity - protons + alphas', 'FontSize', 20)

% figure(10)
% hold on
% errorbar(depth, Shield_activity*0.55, sigma_Shield_activity*0.55, 's', 'Color', 'red', 'LineWidth', 1.2, ...
%         'MarkerSize', 10, 'MarkerFaceColor', 'red')
% errorbar(depth, Shield_activity_alpha, sigma_Shield_activity_alpha, 's', 'Color', 'blue', 'LineWidth', 1.2, ...
%         'MarkerSize', 10, 'MarkerFaceColor', 'blue')
% % fplot(funGCRProdRate, 'red', 'LineWidth', 3)
% hold off
% set(gca, 'LineWidth', 2, 'XMinorTick', 'on', 'YMinorTick', 'on', 'FontSize', 20, 'FontWeight', 'bold')
% % set(gca, 'YScale', 'log')
% xlabel('depth [cm]', 'FontSize', 20)
% ylabel('Activity [dpm/kg]', 'FontSize', 20)
% set(gca, 'XLim', [0 x_lim], 'YLim', [0 12])
% % grid on
% % grid minor
% legend({'p*0.55', '\alpha', 'Physical model'}, 'Location', 'northeast', 'Orientation', 'vertical', 'FontSize', 20)
% % title('^{26}Al activity - protons + alphas', 'FontSize', 20)

ratio_Al = Shield_activity_alpha./Shield_activity;
% figure(11)
% hold on
% stairs(depth, ratio_Al, 'Color', 'red', 'LineWidth', 3)
% stairs(depth, ratio_Na, 'Color', 'blue', 'LineWidth', 3)
% hold off
% set(gca, 'LineWidth', 2, 'XMinorTick', 'on', 'YMinorTick', 'on', 'FontSize', 20, 'FontWeight', 'bold')
% % set(gca, 'YScale', 'log')
% xlabel('depth [cm]', 'FontSize', 20)
% ylabel('$\boldmath\frac{\boldmath\alpha}{p}$', 'FontSize', 30, 'Rotation', 0, ...
%         'VerticalAlignment', 'bottom', 'Interpreter', 'latex')
% set(gca, 'XLim', [0 50], 'YLim', [0 0.2])
% % grid on
% % grid minor
% legend({'^{26}Al', '^{22}Na'}, 'Location', 'northeast', 'Orientation', 'vertical', 'FontSize', 20)
% % title('$\boldmath\frac{\boldmath\alpha}{p}$', 'FontSize', 30, 'Interpreter', 'latex')

% depth(26)
% mean(Shield_activity(1:26)*1.55)
% mean(Shield_activity_tot(1:26))