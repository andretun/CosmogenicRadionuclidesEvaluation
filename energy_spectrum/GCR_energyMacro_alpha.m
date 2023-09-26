% GCR spectrum calculation for Geant4 energy histogram
clear all
close all

meteoriteRadius = 242.22; % m

C = 5.5e7; % particles/(MeV sr s m2)
phi = 660; % MeV - modulation parameter
m = 3727.379378; % MeV - alpha particle mass

k = phi*1.786e-3 - 0.1323;

Jalpha = @(E) C*power(E, k)*(E + 2*m) / ( (E + 700) * (E + 2*m + 700) * power(E + 312500*power(E, -2.5) + 700, 1.65 + k) );

integralFlux = integral(Jalpha, 0, inf, ArrayValued=true) % particles/(m2 sr s)
NumberOfParticles = integralFlux*4*pi*pi*meteoriteRadius*meteoriteRadius % particles/s

energy1 = 1:0.5:100; % MeV
energy2 = 105:5:1000; % MeV
energy3 = 1050:50:3000; % MeV
energy4 = 3500:500:215000; % MeV
%energy5 = 3500:500:100000; % MeV
energy = [energy1, energy2, energy3, energy4]; %, energy5];

integralFlux = integral(Jalpha, energy(1), energy(end), ArrayValued=true) % particles/(m2 sr s)
NumberOfParticles = integralFlux*4*pi*pi*meteoriteRadius*meteoriteRadius % particles/s

meanFlux = zeros(length(energy) - 1, 1);

index = 1;
while index <= length(energy) - 1
    meanFlux(index) = integral(Jalpha, energy(index), energy(index+1), ArrayValued=true) / ( energy(index+1) - energy(index) ); % particles/(MeV m2 sr s)
    index = index + 1;
end

% index = 1;
% while index <= length(energy) - 1
%     meanFlux(index) = J(energy(index));
%     index = index + 1;
% end

meanFlux = meanFlux';
energy = energy(1:length(energy)-1);
output = [energy; meanFlux];

% figure(1)
% hold on
% fplot(Jalpha, 'LineWidth', 2 , 'Color', 'red')
% bar(energy, meanFlux)
% hold off
% set(gca, 'LineWidth', 2, 'XMinorTick', 'on', 'YMinorTick', 'on', 'FontSize', 20, 'FontWeight', 'bold')
% xlabel('Energy [MeV]', 'FontSize', 15)
% ylabel('Flux [MeV-1 cm-2 s-1]', 'FontSize', 15)
% set(gca, 'YScale', 'log', 'XScale', 'log')
% set(gca, 'YScale', 'log', 'XScale', 'log')
% set(gca, 'YLim', [10e-8 101], 'XLim', [10e-1 10e4])
% grid on
% grid minor
% title('Alpha Flux')


fileID = fopen('spectrum.txt', 'w');
fprintf(fileID,'%6.2f %12.9f\n', output);
fclose(fileID);
