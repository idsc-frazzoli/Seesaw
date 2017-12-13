function [] = save_figures(path, t, r, y, u, task_string)

figure_name = strcat('seesaw_measurement_', task_string, '_fig1');
h = figure('Name', figure_name);
set(h,'Units','Inches');
pos = get(h,'Position');
plot(t, r, 'r')
hold on;
plot(t, y)
grid on;

xlabel_string = 'System time [s]';
xlabel(xlabel_string, 'interpreter', 'Latex', 'Fontsize', 20)
ylabel('Reference and Measurement [ticks]', 'interpreter', ...
'Latex', 'Fontsize', 20)
title({'Comparing reference to measurement output'}, ...
'interpreter', 'Latex', 'Fontsize', 20)
legend('Reference', 'Measurement', 'interpreter', 'Latex', 'Fontsize', 30)
set(h,'PaperPositionMode','Auto','PaperUnits','Inches', ...
'PaperSize',[pos(3), pos(4)])
print(h, figure_name, '-dpdf')
% ------------------------
% DATA IS COPIED TO FIGURE FOLDER LOCATION IN "PATH"
name_string = strcat('seesaw_measurement_', task_string, '_fig1');
source = strcat('./', name_string, '.pdf');
destination = strcat(path, name_string, '.pdf');
copyfile(source, destination);
% ------------------------

figure_name = strcat('seesaw_measurement_', task_string, '_fig2');
h = figure('Name', figure_name);
set(h,'Units','Inches');
pos = get(h,'Position');
plot(t, u)

grid on;
xlabel(xlabel_string, 'interpreter', 'Latex', 'Fontsize', 20)
ylabel('Input u to Seesaw', 'interpreter', 'Latex', 'Fontsize', 20)
title({'Corresponding input difference signal to Seesaw'}, ...
'interpreter', 'Latex', 'Fontsize', 20)
set(h,'PaperPositionMode','Auto','PaperUnits','Inches', ...
'PaperSize',[pos(3), pos(4)])
print(h, figure_name, '-dpdf')
% ------------------------
% DATA IS COPIED TO FIGURE FOLDER LOCATION IN "PATH"
name_string = strcat('seesaw_measurement_', task_string, '_fig2');
source = strcat('./', name_string, '.pdf');
destination = strcat(path, name_string, '.pdf');
copyfile(source, destination);

% ------------------------

end